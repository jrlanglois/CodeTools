TabsToSpacesComponent::TabsToSpacesComponent (const CodeFileList& codeFiles) :
    ToolComponent ("Tabs to Spaces", codeFiles)
{
    addTextButton (convert, "Convert", "Convert all \"\\t\" (aka: tab) characters to a desired number of spaces (or 1, or none)");
    addLabel (lblSpaceChanger, "Num spaces:", "");

    spaceChanger.setTextBoxStyle (juce::Slider::TextBoxRight, true, getItemHeight() + getMarginSize(), getItemHeight());
    spaceChanger.setRange (0.0, (double) TabsToSpaces::getMaxNumSpacesPerTab(), 1.0);
    spaceChanger.setValue (4.0, juce::dontSendNotification);

    addAndMakeVisible (&spaceChanger);
}

//==============================================================================
void TabsToSpacesComponent::resized()
{
    const int width         = getWidth();
    const int height        = getHeight();
    const int margin        = getMarginSize();
    const int buttonWidth   = getDefaultButtonWidth();
    const int itemHeight    = getItemHeight();

    lblSpaceChanger.setBounds (margin, margin, getLargestLabelTextWidth() + margin * 2, itemHeight);
    spaceChanger.setBounds (margin + lblSpaceChanger.getRight(), margin, buttonWidth * 2, itemHeight);

    convert.setBounds (width - buttonWidth - margin,
                       height - itemHeight - margin,
                       buttonWidth,
                       itemHeight);
}

void TabsToSpacesComponent::buttonClicked (juce::Button* const button)
{
    if (&convert == button)
        TabsToSpaces (getCodeFiles()).perform ((int) spaceChanger.getValue());
}