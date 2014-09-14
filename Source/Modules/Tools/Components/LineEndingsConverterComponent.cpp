LineEndingsConverterComponent::LineEndingsConverterComponent (const CodeFileList& codeFiles) :
    ToolComponent ("Line-Endings Converter", codeFiles)
{
    addTextButton (convert, "Convert", "Convert all the line-endings of the code files");

    formats.setEditableText (false);
    formats.addItemList (LineEndingsConverter::getEndingFormatsAsStrings(), 1);
    formats.setSelectedItemIndex (3);

    addAndMakeVisible (&formats);
}

//==============================================================================
void LineEndingsConverterComponent::resized()
{
    const int width         = getWidth();
    const int height        = getHeight();
    const int margin        = getMarginSize();
    const int buttonWidth   = getDefaultButtonWidth();
    const int itemHeight    = getItemHeight();

    formats.setBounds (margin, margin, buttonWidth * 3, itemHeight);

    convert.setBounds (width - buttonWidth - margin,
                       height - itemHeight - margin,
                       buttonWidth,
                       itemHeight);
}

void LineEndingsConverterComponent::buttonClicked (juce::Button* const button)
{
    if (&convert == button)
        LineEndingsConverter (getCodeFiles()).perform ((LineEndingsConverter::LineEndingFormat) (formats.getSelectedItemIndex() - 1));
}