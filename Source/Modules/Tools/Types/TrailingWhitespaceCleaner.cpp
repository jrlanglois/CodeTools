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

    if (lines.size() <= 0)
        return;

    while (lines.strings.getLast().trim().isEmpty())
        lines.remove (lines.size() - 1);

    lines.minimiseStorageOverheads();

    cleanRange (lines, 0, lines.size());

    if (removeDocumentStartWhitespace)
    {
        for (int i = 0; i < lines.size(); ++i)
        {
            if (lines[i].isEmpty())
            {
                lines.remove (i);
                --i;
            }
            else
            {
                break;
            }
        }
    }

    //Remove empty lines at the end of the file:
    for (int i = lines.size(); --i >= 0;)
    {
        if (lines[i].isEmpty())
            lines.remove (i);
        else
            break;
    }
#if 0
    if (documentEndOptions == KeepOneBlankLine)
    {
        const juce::String last (lines.strings[lines.size() - 1].trim());

        if (lines.size() == 0)
        {
            lines.add (juce::newLine);
        }
        else
        {
            if (last.isNotEmpty())
            {
                if (last == "\r" || last == "\n" || last == "\n\r" || last == "\r\n")
                    lines.strings.getReference (lines.size() - 1) = juce::newLine;
                else
                    lines.add (juce::newLine);
            }
            else
            {
                lines.strings.getReference (lines.size() - 1) = juce::newLine;
            }
        }
    }
#endif
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