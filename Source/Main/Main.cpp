#include "Main.h"

MainApplication::MainApplication()
{
}

//==============================================================================
void MainApplication::initialise (const juce::String& /*commandLine*/)
{
    mainWindow = new MainWindow();
}

void MainApplication::shutdown()
{
    mainWindow = nullptr;
}

//==============================================================================
void MainApplication::suspended()
{
}

void MainApplication::resumed()
{
}

void MainApplication::systemRequestedQuit()
{
    quit();
}

//==============================================================================
void MainApplication::anotherInstanceStarted (const juce::String& /*commandLine*/)
{
}

//==============================================================================
const juce::String MainApplication::getApplicationName()
{
    return ProjectInfo::projectName;
}

const juce::String MainApplication::getApplicationVersion()
{
    return ProjectInfo::versionString;
}

bool MainApplication::moreThanOneInstanceAllowed()
{
    return false;
}