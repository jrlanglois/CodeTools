#ifndef JRL_TOOL_COMPONENT_H
#define JRL_TOOL_COMPONENT_H

/**
    @file ToolComponent.h
    @copyright jrlanglois

*/
class ToolComponent : public juce::Component,
                      public juce::Button::Listener,
                      public juce::TextEditor::Listener
{
public:
    /** Constructor */
    explicit ToolComponent (const juce::String& toolName,
                            const CodeFileList& codeFiles);

    //==============================================================================
    /** Get the name of this tool */
    const juce::String& getToolName() const noexcept { return name; }

    /** Get a reference to the list of code files */
    const CodeFileList& getCodeFiles() const noexcept { return codeFiles; }

    //==============================================================================
    /** @internal */
    virtual void resized() = 0;
    /** @internal */
    virtual void buttonClicked (juce::Button* button) = 0;

protected:
    //==============================================================================
    virtual void addLabel (juce::Label& label,
                           const juce::String& text,
                           const juce::String& tooltip = juce::String::empty);

    virtual void addTextEditor (juce::TextEditor& editor,
                                const juce::String& text = juce::String::empty,
                                const juce::String& tooltip = juce::String::empty,
                                bool addListener = false);

    virtual void addTextButton (juce::TextButton& button,
                                const juce::String& text = juce::String::empty,
                                const juce::String& tooltip = juce::String::empty,
                                bool addListener = true);

    int getLargestLabelTextWidth() const;

    void positionLabels (int offsetX, int offsetY,
                         int width, int height,
                         int spacingY);

    //==============================================================================
    int getMarginSize() const noexcept          { return 8; }
    int getDefaultButtonWidth() const noexcept  { return getMarginSize() * getMarginSize() * 2; }
    int getItemHeight() const noexcept          { return getMarginSize() * 3; }

    //==============================================================================
    juce::Array<juce::Label*> labelList;
    juce::Array<juce::TextEditor*> textEditorList;

private:
    //==============================================================================
    const juce::String name;
    const CodeFileList& codeFiles;

    //==============================================================================
    ToolComponent();
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ToolComponent)
};

#endif //JRL_TOOL_COMPONENT_H