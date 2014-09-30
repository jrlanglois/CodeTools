#ifndef JRL_MAIN_WINDOW_H
#define JRL_MAIN_WINDOW_H

#include "MainComponent.h"
#include "CommandIDs.h"

/**
    @file Main.cpp
    @copyright jrlanglois

*/
class MainWindow : public juce::DocumentWindow,
                   private juce::MenuBarModel
{
public:
    /** Constructor */
    MainWindow();

    /** Destructor */
    ~MainWindow();

    //==============================================================================
    /** @internal */
    void closeButtonPressed() override;
    /** @internal */
    juce::StringArray getMenuBarNames() override;
    /** @internal */
    juce::PopupMenu getMenuForIndex (int topLevelMenuIndex, const juce::String& menuName) override;
    /** @internal */
    void menuItemSelected (int menuItemID, int topLevelMenuIndex) override;

private:
    //==============================================================================
    juce::ComponentBoundsConstrainer constrainer;
    juce::LookAndFeel_V3 lnf;
    juce::ApplicationCommandManager commandManager;

    //==============================================================================
    void addCommandItem (juce::PopupMenu& menu,
                         CommandIDs::IDTag tag);

    void createFileMenu (juce::PopupMenu& menuToFill);
    void createEditMenu (juce::PopupMenu& menuToFill);
    void createViewMenu (juce::PopupMenu& menuToFill);
    void createToolsMenu (juce::PopupMenu& menuToFill);

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
};

#endif //JRL_MAIN_WINDOW_H