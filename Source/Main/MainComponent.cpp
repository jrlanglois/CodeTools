#include "MainComponent.h"
#include "BinaryData.h"
#include "CommandIDs.h"
#include "UserSettings.h"
#include "../Windows/ConfigurationWindow.h"

//==============================================================================
MainComponent::MainComponent()
{
    codeFilesSizeConstrainer.setMinimumWidth (200);
    codeFilesSizeConstrainer.setMaximumWidth (400);

    codeFiles.setSize (300, 800);

    resizerBar = new juce::ResizableEdgeComponent (&codeFiles,
                                                   &codeFilesSizeConstrainer,
                                                   juce::ResizableEdgeComponent::rightEdge);

    resizerBar->setAlwaysOnTop (true);

    codeEditor = new juce::CodeEditorComponent (codeDocument, nullptr);

    addAndMakeVisible (&codeFiles);
    addAndMakeVisible (resizerBar);
    addAndMakeVisible (codeEditor);
}

MainComponent::~MainComponent()
{
    resizerBar = nullptr;
    codeEditor = nullptr;
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::darkgrey);
}

void MainComponent::resized()
{
    juce::Rectangle<int> r (getLocalBounds());

    codeFiles.setBounds (r.removeFromLeft (codeFiles.getWidth()));

    if (resizerBar != nullptr)
        resizerBar->setBounds (r.withWidth (4));

    if (codeEditor != nullptr)
        codeEditor->setBounds (r);
}

void MainComponent::childBoundsChanged (juce::Component* child)
{
    if (child == &codeFiles)
        resized();
}

//==============================================================================
juce::ApplicationCommandTarget* MainComponent::getNextCommandTarget()
{
    return nullptr;
}

void MainComponent::getAllCommands (juce::Array<juce::CommandID>& commands)
{
    const juce::OwnedArray<juce::ApplicationCommandInfo>& aci
        = CommandIDs::CommandIDHelper::getInstance()->commands;

    for (int i = aci.size(); --i >= 0;)
        commands.addIfNotAlreadyThere (aci.getUnchecked (i)->commandID);

    juce::DefaultElementComparator<juce::CommandID> comparator;
    commands.sort (comparator);
}

void MainComponent::getCommandInfo (const juce::CommandID commandID,
                                    juce::ApplicationCommandInfo& result)
{
    const juce::OwnedArray<juce::ApplicationCommandInfo>& aci
        = CommandIDs::CommandIDHelper::getInstance()->commands;

    for (int i = aci.size(); --i >= 0;)
    {
        juce::ApplicationCommandInfo& cmd = *aci.getUnchecked (i);

        if (commandID == cmd.commandID)
        {
            result = cmd;
            break;
        }
    }
}

bool MainComponent::perform (const juce::ApplicationCommandTarget::InvocationInfo& info)
{
    CodeFileList codeFilesToEdit;

    {
        juce::StringArray files (codeFiles.getSelectedCodeFiles());

        if (files.size() <= 0)
        {
            const juce::Array<juce::File>& list (codeFiles.getCodeFiles().getFiles());

            for (int i = 0; i < list.size(); ++i)
                files.addIfNotAlreadyThere (list.getUnchecked (i).getFullPathName());
        }

        codeFilesToEdit.addFiles (files);
    }

    switch (info.commandID)
    {
        case CommandIDs::ProjectNew:
        {
        }
        break;

        case CommandIDs::ProjectOpen:
        {
        }
        break;

        case CommandIDs::ProjectSave:
        {
        }
        break;

        case CommandIDs::ProjectSaveAs:
        {
        }
        break;

        case CommandIDs::ProjectClose:
        {
        }
        break;

        case CommandIDs::OpenFiles:
        {
        }
        break;

        case CommandIDs::OpenIntrojucerProject:
        {
        }
        break;

        case CommandIDs::Exit:
        {
        }
        break;

        case CommandIDs::EditUndo:
        {
            undoManager.undo();
        }
        break;

        case CommandIDs::EditRedo:
        {
            undoManager.redo();
        }
        break;

        case CommandIDs::FilesCapitaliseStringLiterals:
        {
        }
        break;

        case CommandIDs::FilesCleanTrailingWhitespace:
            TrailingWhitespaceCleaner (codeFilesToEdit)
                .perform (UserSettings::getInstance()->getBool ("RemoveDocumentStartWhitespace"),
                          (TrailingWhitespaceCleaner::WhitespaceRemovalOptions) UserSettings::getInstance()->getInt ("RemoveDocumentStartWhitespace",
                                                                                (int) TrailingWhitespaceCleaner::KeepOneBlankLine));
        break;

        case CommandIDs::FilesConvertLineEndings:
        {
        }
        break;

        case CommandIDs::FilesConvertTabsToSpaces:
            TabsToSpaces (codeFilesToEdit).perform (UserSettings::getInstance()->getInt ("NumSpacesOnTabReplace", 4));
        break;

        case CommandIDs::FilesModularise:
        {
        }
        break;

        case CommandIDs::ShowSettings:
        {
            BasicWindow* doc = new BasicWindow (TRANS ("Settings"), juce::Colours::darkgrey, juce::DocumentWindow::closeButton);

            doc->setResizable (false, false);
            doc->setUsingNativeTitleBar (true);

            ConfigurationWindow* cw = new ConfigurationWindow();
            doc->setContentOwned (cw, true);
            doc->centreWithSize (cw->getWidth(), cw->getHeight());

            doc->setVisible (true);
        }
        break;

        default:
            jassertfalse;
            return false;
        break;
    };

    return true;
}