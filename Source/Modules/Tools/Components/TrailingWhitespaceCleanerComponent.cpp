TrailingWhitespaceCleanerComponent::TrailingWhitespaceCleanerComponent (const CodeFileList& codeFiles) :
    ToolComponent ("Trailing Whitespace Cleaner", codeFiles)
{
    addTextButton (apply, TRANS ("Clean"), TRANS ("Clean up the whitespace in the code files"));

    removeDocumentStartWhitespace.setToggleState (true, juce::dontSendNotification);
    removeDocumentStartWhitespace.setButtonText (TRANS ("Remove document-start whitespace"));
    removeDocumentStartWhitespace.setTooltip (TRANS ("This will remove any whitespace located at the start of the code files"));

    {
        static const char* const ops[] =
        {
            NEEDS_TRANS ("Do nothing"),
            NEEDS_TRANS ("Remove All"),
            NEEDS_TRANS ("Keep one blank line (C++ standard\")"),
            nullptr
        };

        juce::StringArray options (ops);
        translate (options);

        documentEndOptions.addItemList (options, 1);
    }

    documentEndOptions.setTooltip (TRANS ("This will allow removing any whitespace located at the end of the code files"));
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