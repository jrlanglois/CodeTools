#ifndef JRL_TRAILING_WHITESPACE_CLEANER_COMPONENT_H
#define JRL_TRAILING_WHITESPACE_CLEANER_COMPONENT_H

#include "../Types/TrailingWhitespaceCleaner.h"

/**
    @file TrailingWhitespaceCleanerComponent.h
    @copyright jrlanglois

*/
class TrailingWhitespaceCleanerComponent : public ToolComponent
{
public:
    /** Constructor */
    TrailingWhitespaceCleanerComponent (const CodeFileList& codeFiles);

    //==============================================================================
    /** @internal */
    void resized() override;
    /** @internal */
    void buttonClicked (juce::Button* button) override;

private:
    //==============================================================================
    juce::TextButton apply;
    juce::ToggleButton removeDocumentStartWhitespace;
    juce::ToggleButton removeDocumentEndWhitespace;
    juce::ComboBox documentEndOptions;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TrailingWhitespaceCleanerComponent)
};

#endif //JRL_TRAILING_WHITESPACE_CLEANER_COMPONENT_H