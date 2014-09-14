#ifndef JRL_MAIN_COMPONENT_H
#define JRL_MAIN_COMPONENT_H

#include "../Modules/JRLHeader.h"

/**
    @file MainComponent.h
    @copyright jrlanglois

*/
class MainComponent : public juce::Component,
                      private juce::Button::Listener
{
public:
    /** Constructor */
    MainComponent();

    /** Destructor */
    ~MainComponent();

    //==============================================================================
    /** @internal */
    void paint (juce::Graphics& g) override;
    /** @internal */
    void resized() override;
    /** @internal */
    void buttonClicked (juce::Button* button) override;

private:
    //==============================================================================
    class ToolbarItemFactory;

    //==============================================================================
    juce::TooltipWindow tooltipWindow;
    juce::SystemTrayIconComponent trayIcon;
    juce::UndoManager undoManager;

    juce::ScopedPointer<ToolbarItemFactory> toolbarItemFactory;
    juce::ScopedPointer<juce::Toolbar> toolbar;

    CodeFileListComponent codeFiles;
    juce::CodeDocument codeDocument;
    juce::ScopedPointer<juce::CodeEditorComponent> codeEditor;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};

#endif //JRL_MAIN_COMPONENT_H