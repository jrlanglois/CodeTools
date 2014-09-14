#ifndef JRL_LINE_ENDINGS_CONVERTER_H
#define JRL_LINE_ENDINGS_CONVERTER_H

#include "CodeTool.h"

/**
    @file LineEndingsConverter.h
    @copyright jrlanglois

*/
class LineEndingsConverter : public CodeTool
{
public:
    /** Constructor */
    LineEndingsConverter (const CodeFileList& codeFiles);

    //==============================================================================
    enum LineEndingFormat
    {
        None = 0,
        LineFeedOnly,
        CarriageReturnOnly,
        BothCRLF,
        BothLFCR,

        numFormats //< Please, keep last!
    };

    static juce::String endingsFormatToString (LineEndingFormat format) noexcept;
    static juce::StringArray getEndingFormatsAsStrings() noexcept;

    //==============================================================================
    void perform (LineEndingFormat format);

private:
    //==============================================================================
    void cleanFile (const juce::File& file, const juce::String& lineEndingToUse);

    //==============================================================================
    LineEndingsConverter();
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LineEndingsConverter)
};

#endif //JRL_LINE_ENDINGS_CONVERTER_H