#ifndef JRL_MAIN_COMPONENT_H
#define JRL_MAIN_COMPONENT_H

#include "../Modules/JRLHeader.h"

/**
    @file MainComponent.h
    @copyright jrlanglois

*/
class MainComponent : public juce::Component,
                      public juce::ApplicationCommandTarget
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
    void childBoundsChanged (juce::Component* child) override;
    /** @internal */
    juce::ApplicationCommandTarget* getNextCommandTarget() override;
    /** @internal */
    void getAllCommands (juce::Array<juce::CommandID>& commands) override;
    /** @internal */
    void getCommandInfo (juce::CommandID commandID, juce::ApplicationCommandInfo& result) override;
    /** @internal */
    bool perform (const juce::ApplicationCommandTarget::InvocationInfo& info) override;

private:
    //==============================================================================
    class BasicWindow : public juce::DocumentWindow
    {
    public:
        BasicWindow (const juce::String& name, juce::Colour backgroundColour, int buttonsNeeded) :
            juce::DocumentWindow (name, backgroundColour, buttonsNeeded)
        {
        }

        void closeButtonPressed() override
        {
            delete this;
        }

    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BasicWindow)
    };

    //==============================================================================
    juce::TooltipWindow tooltipWindow;
    juce::SystemTrayIconComponent trayIcon;
    juce::UndoManager undoManager;

    CodeFileListComponent codeFiles;

    juce::ScopedPointer<juce::ResizableEdgeComponent> resizerBar;
    juce::ComponentBoundsConstrainer codeFilesSizeConstrainer;

    juce::CodeDocument codeDocument;
    juce::ScopedPointer<juce::CodeEditorComponent> codeEditor;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};

#endif //JRL_MAIN_COMPONENT_H