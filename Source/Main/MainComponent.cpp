#include "MainComponent.h"
#include "BinaryData.h"

//==============================================================================
class MainComponent::ToolbarItemFactory : public juce::ToolbarItemFactory
{
public:
    ToolbarItemFactory (juce::Button::Listener& sourceListener) noexcept :
        listener (sourceListener)
    {
        populateIcons();
    }

    //==============================================================================
    enum ToolbarItemIds
    {
        ProjectNew = 1,
        ProjectOpen,
        ProjectSave,
        ProjectSaveAs,
        ProjectUndo,
        ProjectRedo,
        FilesConvertLineEndings,
        FilesModularise,
        FilesCapitaliseStringLiterals,
        FilesConvertTabsToSpaces,
        FilesCleanTrailingWhitespace,
        Settings
    };

    //==============================================================================
    void getAllToolbarItemIds (juce::Array<int>& ids) override
    {
        ids.add (ProjectNew);
        ids.add (ProjectOpen);
        ids.add (ProjectSave);
        ids.add (ProjectSaveAs);
        ids.add (ProjectUndo);
        ids.add (ProjectRedo);
        ids.add (FilesConvertLineEndings);
        ids.add (FilesModularise);
        ids.add (FilesCapitaliseStringLiterals);
        ids.add (FilesConvertTabsToSpaces);
        ids.add (FilesCleanTrailingWhitespace);
        ids.add (Settings);

        ids.add (separatorBarId);
    }

    void getDefaultItemSet (juce::Array<int>& ids) override
    {
        ids.add (ProjectNew);
        ids.add (ProjectOpen);
        ids.add (ProjectSave);
        ids.add (ProjectSaveAs);

        ids.add (separatorBarId);

        ids.add (ProjectUndo);
        ids.add (ProjectRedo);

        ids.add (separatorBarId);

        ids.add (FilesConvertLineEndings);
        ids.add (FilesModularise);
        ids.add (FilesCapitaliseStringLiterals);
        ids.add (FilesConvertTabsToSpaces);
        ids.add (FilesCleanTrailingWhitespace);

        ids.add (separatorBarId);

        ids.add (Settings);
    }

    juce::ToolbarItemComponent* createItem (int itemId) override
    {
        switch (itemId)
        {
            case ProjectNew:    return createButtonFromZipFileSVG (itemId, TRANS ("New"),
                                                                   TRANS ("Create a new project"),
                                                                   "document-new.svg");

            case ProjectOpen:   return createButtonFromZipFileSVG (itemId, TRANS ("Open"),
                                                                   TRANS ("Open an existing project"),
                                                                   "document-open.svg");

            case ProjectSave:   return createButtonFromZipFileSVG (itemId, TRANS ("Save"),
                                                                   TRANS ("Save the current project"),
                                                                   "document-save.svg");

            case ProjectSaveAs: return createButtonFromZipFileSVG (itemId, TRANS ("Save As"),
                                                                   TRANS ("Save the current project under a different name"),
                                                                   "document-save-as.svg");

            case ProjectUndo:   return createButtonFromZipFileSVG (itemId, TRANS ("Undo"),
                                                                   TRANS ("Undo"),
                                                                   "edit-undo.svg");

            case ProjectRedo:   return createButtonFromZipFileSVG (itemId, TRANS ("Redo"),
                                                                   TRANS ("Redo"),
                                                                   "edit-redo.svg");

            case FilesCapitaliseStringLiterals: return createButtonFromZipFileSVG (itemId, TRANS ("Capitalise String Literals"),
                                                                   TRANS ("Capitalise string literals of the selected file(s)"),
                                                                   "media-record.svg");

            case FilesCleanTrailingWhitespace:  return createButtonFromZipFileSVG (itemId, TRANS ("Clean Trailing Whitespace"),
                                                                   TRANS ("Trim out any desired trailing whitespace of the selected file(s)"),
                                                                   "media-record.svg");

            case FilesConvertLineEndings:       return createButtonFromZipFileSVG (itemId, TRANS ("Convert Line Endings"),
                                                                   TRANS ("Convert the line endings of the selected file(s)"),
                                                                   "media-record.svg");

            case FilesConvertTabsToSpaces:      return createButtonFromZipFileSVG (itemId, TRANS ("Redo"),
                                                                   TRANS ("Convert tabs in the selected file(s) to spaces"),
                                                                   "media-record.svg");

            case FilesModularise:               return createButtonFromZipFileSVG (itemId, TRANS ("Modularise"),
                                                                   TRANS ("Create a C++ module out of the selected file(s)"),
                                                                   "media-record.svg");

            case Settings:      return createButtonFromZipFileSVG (itemId, TRANS ("Settings"),
                                                                   TRANS ("Settings"),
                                                                   "preferences-system.svg");

            default:
            break;
        }

        jassertfalse; //Unknown item ID!
        return nullptr;
    }

private:
    //==============================================================================
    juce::Button::Listener& listener;
    juce::StringArray iconNames;
    juce::OwnedArray<juce::Drawable> iconsFromZipFile;

    //==============================================================================
    /** */
    void populateIcons()
    {
        jassert (iconsFromZipFile.size() == 0);

        juce::MemoryInputStream iconsFileStream (BinaryData::toolbarIconsZip, BinaryData::toolbarIconsZipSize, false);
        juce::ZipFile icons (&iconsFileStream, false);

        for (int i = 0; i < icons.getNumEntries(); ++i)
        {
            juce::ScopedPointer<juce::InputStream> svgFileStream (icons.createStreamForEntry (i));

            if (svgFileStream != nullptr)
            {
                iconNames.add (icons.getEntry (i)->filename);
                iconsFromZipFile.add (juce::Drawable::createFromImageDataStream (*svgFileStream));
            }
        }
    }

    /** This is a little utility to create a button with one of the SVG images from a binary data ZIP file */
    juce::ToolbarButton* createButtonFromZipFileSVG (int itemId,
                                                     const juce::String& text,
                                                     const juce::String& tooltip,
                                                     const juce::String& filename)
    {
        if (juce::Drawable* const image = iconsFromZipFile [iconNames.indexOf (filename)])
        {
            if (juce::Drawable* const imageCopy = image->createCopy())
            {
                juce::ToolbarButton* button = new juce::ToolbarButton (itemId, text, imageCopy, nullptr);
                button->setTooltip (tooltip);
                button->addListener (&listener);
                return button;
            }
        }

        jassertfalse; //Probably an incorrect file name
        return nullptr;
    }

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ToolbarItemFactory)
};

//==============================================================================
MainComponent::MainComponent() :
    toolbar (new juce::Toolbar())
{
    toolbarItemFactory = new ToolbarItemFactory (*this);
    toolbar->addDefaultItems (*toolbarItemFactory);

    codeEditor = new juce::CodeEditorComponent (codeDocument, nullptr);

    addAndMakeVisible (toolbar);
}

MainComponent::~MainComponent()
{
    toolbar = nullptr;
    toolbarItemFactory = nullptr;
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::darkgrey);
}

void MainComponent::resized()
{
    const int width = getWidth();
    //const int height = getHeight();
    //const int halfHeight = height / 2;
    //const int offset = 4;
    //const int doubleOffset = offset * 2;

    toolbar->setBounds (0, 0, width, 48);
}

void MainComponent::buttonClicked (juce::Button* const button)
{
    if (juce::ToolbarButton* tb = dynamic_cast<juce::ToolbarButton*> (button))
    {
        switch (tb->getItemId())
        {
            case ToolbarItemFactory::ProjectNew:
            break;

            case ToolbarItemFactory::ProjectOpen:
            break;

            case ToolbarItemFactory::ProjectSave:
            break;

            case ToolbarItemFactory::ProjectSaveAs:
            break;

            case ToolbarItemFactory::ProjectUndo:
            break;

            case ToolbarItemFactory::ProjectRedo:
            break;

            case ToolbarItemFactory::FilesCapitaliseStringLiterals:
            break;

            case ToolbarItemFactory::FilesCleanTrailingWhitespace:
            break;

            case ToolbarItemFactory::FilesConvertLineEndings:
            break;

            case ToolbarItemFactory::FilesConvertTabsToSpaces:
            break;

            case ToolbarItemFactory::FilesModularise:
            break;

            case ToolbarItemFactory::Settings:
            break;

            default:
                jassertfalse;
            break;
        };
    }
}

//==============================================================================