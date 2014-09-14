ToolComponent::ToolComponent (const juce::String& n, const CodeFileList& f) :
    name (n),
    codeFiles (f)
{
}

//==============================================================================
void ToolComponent::addLabel (juce::Label& label,
                              const juce::String& text,
                              const juce::String& tooltip)
{
    label.setText (text, juce::NotificationType::dontSendNotification);
    label.setTooltip (tooltip);
    label.setFont (juce::Font (15.0f, juce::Font::plain));
    label.setJustificationType (juce::Justification::centredRight);
    label.setEditable (false, false, false);
    label.setColour (juce::Label::textColourId, juce::Colours::black);
    label.setColour (juce::Label::backgroundColourId, juce::Colour (juce::Colours::transparentBlack));

    labelList.addIfNotAlreadyThere (&label);
    addAndMakeVisible (&label);
}

void ToolComponent::addTextEditor (juce::TextEditor& editor,
                                   const juce::String& text,
                                   const juce::String& tooltip,
                                   const bool addListener)
{
    editor.setText (text);
    editor.setTooltip (tooltip);
    editor.setMultiLine (false);
    editor.setReturnKeyStartsNewLine (false);
    editor.setReadOnly (false);
    editor.setScrollbarsShown (true);
    editor.setCaretVisible (true);
    editor.setPopupMenuEnabled (true);

    if (addListener)
        editor.addListener (this);

    textEditorList.addIfNotAlreadyThere (&editor);
    addAndMakeVisible (&editor);
}

void ToolComponent::addTextButton (juce::TextButton& button,
                                   const juce::String& text,
                                   const juce::String& tooltip,
                                   const bool addListener)
{
    button.setButtonText (text);
    button.setTooltip (tooltip);
    button.setColour (juce::TextButton::buttonColourId, juce::Colour (0xff3dc40d));
    button.setColour (juce::TextButton::buttonOnColourId, juce::Colour (0xff007a06));

    if (addListener)
        button.addListener (this);

    addAndMakeVisible (&button);
}

int ToolComponent::getLargestLabelTextWidth() const
{
    float largestWidth = 0;

    for (int i = labelList.size(); --i >= 0;)
    {
        const juce::Label* label = labelList.getUnchecked (i);

        largestWidth = juce::jmax (label->getFont().getStringWidthFloat (label->getText()),
                                   largestWidth);
    }

    return juce::roundFloatToInt (largestWidth);
}

void ToolComponent::positionLabels (const int offsetX, const int offsetY,
                                    const int width, const int height,
                                    const int spacingY)
{
    for (int i = labelList.size(); --i >= 0;)
    {
        labelList.getUnchecked (i)->setBounds (offsetX,
                                               offsetY + (height * i) + (spacingY * i),
                                               width,
                                               height);
    }
}