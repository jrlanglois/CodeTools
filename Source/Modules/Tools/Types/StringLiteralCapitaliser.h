#ifndef JRL_STRING_LITERAL_CAPITALISER_H
#define JRL_STRING_LITERAL_CAPITALISER_H

/**
    @file StringLiteralCapitaliser.h
    @copyright jrlanglois

*/
class StringLiteralCapitaliser : public CodeTool
{
public:
    /** Constructor */
    StringLiteralCapitaliser (const CodeFileList& codeFiles);

    //==============================================================================
    enum Style
    {
        AllUpperCase = 0,
        AllLowerCase,
        TitleCase,
        SentenceCase
    };

    void perform (Style style);

private:
    //==============================================================================
    class CaseChangeBase;
    class CaseChangeUpper;
    class CaseChangeLower;
    class CaseChangeTitle;
    class CaseChangeSentence;

    juce::OwnedArray<CaseChangeBase> caseChangers;

    //==============================================================================
    void getLiteralsFromLines (juce::StringArray& literals, const juce::StringArray& lines);
    CaseChangeBase* getCaseChangeForStyle (Style style) const noexcept;
    void capitalise (const juce::File& file, Style style);

    //==============================================================================
    StringLiteralCapitaliser();
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StringLiteralCapitaliser)
};

#endif //JRL_STRING_LITERAL_CAPITALISER_H