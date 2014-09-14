#include "TrailingWhitespaceCleaner.h"

TrailingWhitespaceCleaner::TrailingWhitespaceCleaner (const CodeFileList& c) :
    CodeTool (c)
{
}

//==============================================================================
void TrailingWhitespaceCleaner::cleanLine (juce::String& line)
{
    line = line.trimEnd()
               .trimCharactersAtEnd ("\t")
               .trimEnd()
               .trimCharactersAtEnd ("\t");
}

//==============================================================================
bool TrailingWhitespaceCleaner::cleanFromBound (juce::StringArray& lines, const int index)
{
    juce::String& string = lines.getReference (index);
    cleanLine (string);

    if (string.isEmpty())
        lines.remove (index);
    else
        return true;

    return false;
}

int TrailingWhitespaceCleaner::cleanFileStart (juce::StringArray& lines)
{
    for (int i = 0; i < lines.size(); ++i)
        if (cleanFromBound (lines, i))
            return i;

    return 0;
}

int TrailingWhitespaceCleaner::cleanFileEnd (juce::StringArray& lines)
{
    for (int i = lines.size(); --i >= 0;)
        if (cleanFromBound (lines, i))
            return i;

    return lines.size();
}

//==============================================================================
void TrailingWhitespaceCleaner::cleanRange (juce::StringArray& lines, const int start, const int end)
{
    for (int i = start; i < end; ++i)
        cleanLine (lines.getReference (i));
}

//==============================================================================
void TrailingWhitespaceCleaner::cleanFile (const juce::File& file,
                                           const bool removeDocumentStartWhitespace,
                                           const WhitespaceRemovalOptions documentEndOptions)
{
    if (! file.hasWriteAccess())
        return;

    juce::StringArray lines;
    file.readLines (lines);

    cleanRange (lines,
                removeDocumentStartWhitespace
                    ? cleanFileStart (lines)
                    : 0,
                documentEndOptions != DoNothing
                    ? cleanFileEnd (lines)
                    : lines.size());

    const juce::String last (lines.strings.getLast().trim());

    if (documentEndOptions == KeepOneBlankLine
        && lines.size() > 0 && last.isNotEmpty()
        && last != "\r" && last != "\n"
        && last != juce::newLine.getDefault() && last != "\n\r")
    {
        lines.add (juce::newLine);
    }

    juce::ScopedPointer<juce::FileOutputStream> stream (file.createOutputStream());

    if (stream != nullptr)
        writeLinesToStream (stream, lines);
}

void TrailingWhitespaceCleaner::perform (const bool removeDocumentStartWhitespace,
                                         const WhitespaceRemovalOptions documentEndOptions)
{
    const CodeFileList& codeFiles = getCodeFiles();

    for (int i = codeFiles.getNumFiles(); --i >= 0;)
        cleanFile (codeFiles[i], removeDocumentStartWhitespace, documentEndOptions);
}