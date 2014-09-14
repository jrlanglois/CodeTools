#include "MainWindow.h"

/**
    @file Main.h
    @copyright jrlanglois

*/
class MainApplication : public juce::JUCEApplication
{
public:
    /** Constructor */
    MainApplication();

    //==============================================================================
    /** @internal */
    void initialise (const juce::String& commandLine) override;
    /** @internal */
    void shutdown() override;
    /** @internal */
    void suspended() override;
    /** @internal */
    void resumed() override;
    /** @internal */
    void systemRequestedQuit() override;
    /** @internal */
    void anotherInstanceStarted (const juce::String& commandLine) override;
    /** @internal */
    const juce::String getApplicationName() override;
    /** @internal */
    const juce::String getApplicationVersion() override;
    /** @internal */
    bool moreThanOneInstanceAllowed() override;

private:
    //==============================================================================
    juce::ScopedPointer<MainWindow> mainWindow;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainApplication)
};

//==============================================================================
//This macro generates the main() routine that launches the app.
START_JUCE_APPLICATION (MainApplication)