#include "MainWindow.h"
#include "UserSettings.h"

MainWindow::MainWindow() :
    juce::DocumentWindow (ProjectInfo::projectName,
                          juce::Colours::darkgrey,
                          juce::DocumentWindow::allButtons)
{
    setLookAndFeel (&lnf);

    MainComponent* component = new MainComponent();

    //N.B.: The order matters here:
    CommandIDs::CommandIDHelper::getInstance()->populateApplicationCommandManager (commandManager);
    UserSettings::getInstance()->load();
    commandManager.setFirstCommandTarget (component);

    centreWithSize (800, 550);
    setContentOwned (component, false);
    setResizable (true, false);
    setVisible (true);
    setUsingNativeTitleBar (true);
    setMenuBar (this);

    constrainer.setMinimumSize (800, 550);
    setConstrainer (&constrainer);
}

MainWindow::~MainWindow()
{
    commandManager.setFirstCommandTarget (nullptr);
    setMenuBar (nullptr);
    setLookAndFeel (nullptr);
}

//==============================================================================
void MainWindow::closeButtonPressed()
{
    juce::JUCEApplication::getInstance()->systemRequestedQuit();
}

//==============================================================================
void MainWindow::addCommandItem (juce::PopupMenu& menu,
                                 const CommandIDs::IDTag tag)
{
    CommandIDs::addCommandItem (menu, &commandManager, tag);
}

void MainWindow::createFileMenu (juce::PopupMenu& menu)
{
    addCommandItem (menu, CommandIDs::ProjectNew);
    menu.addSeparator();
    addCommandItem (menu, CommandIDs::ProjectOpen);

#if 0 //Recent projects
    juce::PopupMenu recentFiles;
    settings->recentFiles.createPopupMenuItems (recentFiles, recentProjectsBaseID, true, true);
    menu.addSubMenu ("Open Recent", recentFiles);
#endif

    menu.addSeparator();
    addCommandItem (menu, CommandIDs::ProjectClose);
    addCommandItem (menu, CommandIDs::ProjectSave);
    addCommandItem (menu, CommandIDs::ProjectSaveAs);
    menu.addSeparator();
    addCommandItem (menu, CommandIDs::OpenFiles);
    addCommandItem (menu, CommandIDs::OpenIntrojucerProject);
    menu.addSeparator();
    addCommandItem (menu, CommandIDs::Exit);
}

void MainWindow::createEditMenu (juce::PopupMenu& menu)
{
    addCommandItem (menu, CommandIDs::EditUndo);
    addCommandItem (menu, CommandIDs::EditRedo);
    menu.addSeparator();
    addCommandItem (menu, CommandIDs::EditCut);
    addCommandItem (menu, CommandIDs::EditCopy);
    addCommandItem (menu, CommandIDs::EditPaste);
    addCommandItem (menu, CommandIDs::EditDelete);
    menu.addSeparator();
    addCommandItem (menu, CommandIDs::EditSelectAll);
}

void MainWindow::createViewMenu (juce::PopupMenu& menu)
{
    addCommandItem (menu, CommandIDs::ShowSettings);
    menu.addSeparator();
    addCommandItem (menu, CommandIDs::ShowLineNumbers);
}

void MainWindow::createToolsMenu (juce::PopupMenu& menu)
{
    addCommandItem (menu, CommandIDs::FilesConvertLineEndings);
    addCommandItem (menu, CommandIDs::FilesModularise);
    addCommandItem (menu, CommandIDs::FilesCapitaliseStringLiterals);
    addCommandItem (menu, CommandIDs::FilesConvertTabsToSpaces);
    addCommandItem (menu, CommandIDs::FilesCleanTrailingWhitespace);
}

//==============================================================================
juce::StringArray MainWindow::getMenuBarNames()
{
    juce::StringArray names;
    names.add (TRANS ("File"));
    names.add (TRANS ("Edit"));
    names.add (TRANS ("View"));
    names.add (TRANS ("Tools"));

    return names;
}

juce::PopupMenu MainWindow::getMenuForIndex (const int, const juce::String& menuName)
{
    juce::PopupMenu menu;

    if (menuName == TRANS ("File"))         createFileMenu (menu);
    else if (menuName == TRANS ("Edit"))    createEditMenu (menu);
    else if (menuName == TRANS ("View"))    createViewMenu (menu);
    else if (menuName == TRANS ("Tools"))   createToolsMenu (menu);
    else                                    jassertfalse; //Have the names changed?

    return menu;
}

void MainWindow::menuItemSelected (const int, const int)
{
}