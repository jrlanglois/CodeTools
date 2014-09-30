#ifndef JRL_COMMAND_IDS_H
#define JRL_COMMAND_IDS_H

#include "../Modules/JRLHeader.h"

/**
    A namespace to hold all the possible command IDs.
*/
namespace CommandIDs
{
    enum IDTag
    {
        ProjectNew                      = 1,
        ProjectOpen,
        ProjectSave,
        ProjectSaveAs,
        ProjectClose,
        OpenFiles,
        OpenIntrojucerProject,
        Exit,

        EditUndo,
        EditRedo,
        EditCut,
        EditCopy,
        EditPaste,
        EditDelete,
        EditSelectAll,

        FilesConvertLineEndings,
        FilesModularise,
        FilesCapitaliseStringLiterals,
        FilesConvertTabsToSpaces,
        FilesCleanTrailingWhitespace,

        ShowSettings,
        ShowLineNumbers,

        numIDTags = ShowLineNumbers
    };

    //==============================================================================
    void populateApplicationCommandManager (juce::ApplicationCommandManager& commandManager);

    juce::String getName (IDTag tag);

    juce::String getDescription (IDTag tag);

    void addCommandItem (juce::PopupMenu& menu,
                         juce::ApplicationCommandManager* commandManager,
                         IDTag tag);

    //==============================================================================
    class CommandIDHelper : public juce::DeletedAtShutdown
    {
    public:
        CommandIDHelper() :
            populatedCommandManager (false)
        {
            populateCategoryNames();
            populateCommands();
        }

        //==============================================================================
        juce_DeclareSingleton (CommandIDHelper, true)

        //==============================================================================
        void populateApplicationCommandManager (juce::ApplicationCommandManager& commandManager)
        {
            if (! populatedCommandManager)
            {
                for (int i = commands.size(); --i >= 0;)
                    if (juce::ApplicationCommandInfo* commandInfo = commands.getUnchecked (i))
                        commandManager.registerCommand (*commandInfo);
            }

            populatedCommandManager = true;
        }

        //==============================================================================
        juce::OwnedArray<juce::ApplicationCommandInfo> commands;

    private:
        //==============================================================================
        juce::StringArray categoryNames;
        bool populatedCommandManager;

        //==============================================================================
        enum Category
        {
            MenuFile = 0,
            MenuEdit,
            MenuView,
            MenuTools
        };

        void populateCategoryNames()
        {
            categoryNames.add (TRANS ("File"));
            categoryNames.add (TRANS ("Edit"));
            categoryNames.add (TRANS ("View"));
            categoryNames.add (TRANS ("Tools"));
        }

        const juce::String& getNameForCategory (Category category) const
        {
            return categoryNames[(int) category];
        }

        void registerCommand (IDTag tag,
                                const juce::String& name,
                                const juce::String& description,
                                Category category)
        {
            juce::ApplicationCommandInfo* commandInfo = commands.add (new juce::ApplicationCommandInfo ((juce::CommandID) tag));

            commandInfo->shortName      = name;
            commandInfo->description    = description;
            commandInfo->categoryName   = getNameForCategory (category);
        }

        void populateCommands()
        {
            registerCommand (ProjectNew, TRANS ("New Project"), TRANS ("Create a new project"), MenuFile);
            registerCommand (ProjectOpen, TRANS ("Open Project"), TRANS ("Open an existing project"), MenuFile);
            registerCommand (ProjectSave, TRANS ("Save Project"), TRANS ("Save the current project"), MenuFile);
            registerCommand (ProjectSaveAs, TRANS ("Save Project As"), TRANS ("Save the current project"), MenuFile);
            registerCommand (ProjectClose, TRANS ("Close Project"), TRANS ("Save the current project under a different name"), MenuFile);
            registerCommand (OpenFiles, TRANS ("Open Files"), TRANS ("Close the current project"), MenuFile);
            registerCommand (OpenIntrojucerProject, TRANS ("Open Introjucer Project"), TRANS ("Import referenced files from an Introjucer project"), MenuFile);
            registerCommand (Exit, TRANS ("Exit"), TRANS ("Exit the application"), MenuFile);

            registerCommand (EditUndo, TRANS ("Undo"), TRANS ("Undo"), MenuEdit);
            registerCommand (EditRedo, TRANS ("Redo"), TRANS ("Redo"), MenuEdit);
            registerCommand (EditCut, TRANS ("Cut"), TRANS ("Cut"), MenuEdit);
            registerCommand (EditCopy, TRANS ("Copy"), TRANS ("Copy"), MenuEdit);
            registerCommand (EditPaste, TRANS ("Paste"), TRANS ("Paste"), MenuEdit);
            registerCommand (EditDelete, TRANS ("Delete"), TRANS ("Delete"), MenuEdit);
            registerCommand (EditSelectAll, TRANS ("Select All"), TRANS ("Select All"), MenuEdit);

            registerCommand (FilesConvertLineEndings, TRANS ("Convert Line Endings"), TRANS ("Convert the line endings of the selected file(s)"), MenuView);
            registerCommand (FilesModularise, TRANS ("Modularise"), TRANS ("Create a C++ module out of the selected file(s)"), MenuView);
            registerCommand (FilesCapitaliseStringLiterals, TRANS ("Capitalise String Literals"), TRANS ("Capitalise string literals of the selected file(s)"), MenuView);
            registerCommand (FilesConvertTabsToSpaces, TRANS ("Convert Tabs to Spaces"), TRANS ("Convert tabs in the selected file(s) to spaces"), MenuView);
            registerCommand (FilesCleanTrailingWhitespace, TRANS ("Clean Trailing Whitespace"), TRANS ("Trim out any desired trailing whitespace of the selected file(s)"), MenuView);

            registerCommand (ShowSettings, TRANS ("Settings"), TRANS ("Show the application's settings"), MenuTools);
            registerCommand (ShowLineNumbers, TRANS ("Show Line Numbers"), TRANS ("Toggle to display line numbers"), MenuTools);
        }

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CommandIDHelper)
    };
}

#endif //JRL_COMMAND_IDS_H