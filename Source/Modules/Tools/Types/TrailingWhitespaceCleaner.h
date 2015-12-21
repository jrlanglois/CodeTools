#ifndef JRL_TRAILING_WHITESPACE_CLEANER_H
#define JRL_TRAILING_WHITESPACE_CLEANER_H

/**
    @file TrailingWhitespaceCleaner.h
    @copyright jrlanglois

*/
class TrailingWhitespaceCleaner : public CodeTool
{
public:
    /** Constructor */
    TrailingWhitespaceCleaner (const CodeFileList& codeFiles);

    //==============================================================================
    enum WhitespaceRemovalOptions
    {
        DoNothing = 0,
        RemoveAll,
        KeepOneBlankLine
    };

    void perform (bool removeDocumentStartWhitespace,
                  WhitespaceRemovalOptions documentEndOptions);

private:
    //==============================================================================
    void cleanLine (juce::String& line);

    void cleanRange (juce::StringArray& lines, int start, int end);

    void cleanFile (const juce::File& file,
                    bool removeDocumentStartWhitespace,
                    WhitespaceRemovalOptions documentEndRemovalOptions);

    //==============================================================================
    TrailingWhitespaceCleaner() JUCE_DELETED_FUNCTION;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TrailingWhitespaceCleaner)
};

#endif //JRL_TRAILING_WHITESPACE_CLEANER_H