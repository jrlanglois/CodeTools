#ifndef JRL_MAIN_WINDOW_H
#define JRL_MAIN_WINDOW_H

#include "MainComponent.h"

/**
    @file Main.cpp
    @copyright jrlanglois

*/
class MainWindow : public juce::DocumentWindow
{
public:
    /** Constructor */
    MainWindow();

    /** Destructor */
    ~MainWindow();

    //==============================================================================
    /** @internal */
    void closeButtonPressed() override;

private:
    //==============================================================================
    juce::ComponentBoundsConstrainer constrainer;
    juce::LookAndFeel_V3 lnf;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
};

#endif //JRL_MAIN_WINDOW_H