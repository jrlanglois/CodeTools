LineEndingsConverter::LineEndingsConverter (const CodeFileList& c) :
    CodeTool (c)
{
}

//==============================================================================
juce::String LineEndingsConverter::endingsFormatToString (const LineEndingFormat format) noexcept
{
    switch (format)
    {
        case None:                  return juce::String::empty;
        case LineFeedOnly:          return "\n";
        case CarriageReturnOnly:    return "\r";
        case BothCRLF:              return "\r\n";
        case BothLFCR:              return "\n\r";

        default:
        break;
    };

    jassertfalse;
    return juce::String::empty;
}

juce::StringArray LineEndingsConverter::getEndingFormatsAsStrings() noexcept
{
    static const char* const ops[] =
    {
        NEEDS_TRANS ("None [Puts everything on the same line]"),
        NEEDS_TRANS ("Line-Feed Only [e.g.: Mac, Unix-based]"),
        NEEDS_TRANS ("Carriage Return Only"),
        NEEDS_TRANS ("Both CR/LF [e.g.: Windows, typical code line-endings]"),
        NEEDS_TRANS ("Both LF/CR"),
        nullptr
    };

    juce::StringArray names (ops);
    translate (names);

    return names;
}

//==============================================================================
void LineEndingsConverter::cleanFile (const juce::File& file, const juce::String& lineEndingToUse)
{
    if (! file.hasWriteAccess())
        return;

    juce::StringArray lines;
    file.readLines (lines);

    juce::ScopedPointer<juce::FileOutputStream> stream (file.createOutputStream());

    if (stream != nullptr)
        writeLinesToStream (stream, lines, lineEndingToUse);
}

void LineEndingsConverter::perform (const LineEndingFormat format)
{
    const CodeFileList& codeFiles = getCodeFiles();

    const juce::String lineEndingToUse (endingsFormatToString (format));

    for (int i = codeFiles.getNumFiles(); --i >= 0;)
        cleanFile (codeFiles[i], lineEndingToUse);
}