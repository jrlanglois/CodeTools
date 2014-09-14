TrailingWhitespaceCleanerComponent::TrailingWhitespaceCleanerComponent (const CodeFileList& codeFiles) :
    ToolComponent ("Trailing Whitespace Cleaner", codeFiles)
{
    addTextButton (apply, "Clean", "Clean up the whitespace in the code files");

    removeDocumentStartWhitespace.setToggleState (true, juce::dontSendNotification);
    removeDocumentStartWhitespace.setButtonText ("Remove document-start whitespace");
    removeDocumentStartWhitespace.setTooltip ("This will remove any whitespace located at the start of the code files");

    const char* const options[] =
    {
        "Do nothing",
        "Remove All",
        "Keep one blank line (C++ standard\")",
        nullptr
    };

    documentEndOptions.addItemList (juce::StringArray (options), 1);
    documentEndOptions.setTooltip ("This will allow removing any whitespace located at the end of the code files");
    documentEndOptions.setSelectedItemIndex (2, juce::dontSendNotification);

    addAndMakeVisible (&removeDocumentStartWhitespace);
    addAndMakeVisible (&documentEndOptions);
}

//==============================================================================
void TrailingWhitespaceCleanerComponent::resized()
{
    const int width         = getWidth();
    const int height        = getHeight();
    const int margin        = getMarginSize();
    const int buttonWidth   = getDefaultButtonWidth();
    const int itemHeight    = getItemHeight();

    removeDocumentStartWhitespace.getLookAndFeel().changeToggleButtonWidthToFitText (removeDocumentStartWhitespace);
    removeDocumentStartWhitespace.setBounds (margin, margin, removeDocumentStartWhitespace.getWidth(), itemHeight);

    documentEndOptions.setBounds (margin,
                                  margin + removeDocumentStartWhitespace.getBottom(),
                                  removeDocumentStartWhitespace.getWidth() + buttonWidth,
                                  itemHeight);

    apply.setBounds (width - buttonWidth - margin,
                     height - itemHeight - margin,
                     buttonWidth,
                     itemHeight);
}

void TrailingWhitespaceCleanerComponent::buttonClicked (juce::Button* const button)
{
    if (&apply == button)
    {
        TrailingWhitespaceCleaner (getCodeFiles()).perform (removeDocumentStartWhitespace.getToggleState(),
                                                            (TrailingWhitespaceCleaner::WhitespaceRemovalOptions) documentEndOptions.getSelectedItemIndex());
    }
}