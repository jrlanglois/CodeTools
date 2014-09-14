#include "MainWindow.h"
#include "UserSettings.h"

MainWindow::MainWindow() :
    juce::DocumentWindow (ProjectInfo::projectName,
                          juce::Colours::darkgrey,
                          juce::DocumentWindow::allButtons)
{
    setLookAndFeel (&lnf);

    UserSettings::getInstance()->load();

    centreWithSize (800, 550);
    setContentOwned (new MainComponent(), false);
    setResizable (true, false);
    setVisible (true);
    setUsingNativeTitleBar (true);

    constrainer.setMinimumSize (800, 550);
    setConstrainer (&constrainer);
}

MainWindow::~MainWindow()
{
    setLookAndFeel (nullptr);
}

//==============================================================================
void MainWindow::closeButtonPressed()
{
    juce::JUCEApplication::getInstance()->systemRequestedQuit();
}