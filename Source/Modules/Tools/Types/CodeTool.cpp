#include "CodeTool.h"

CodeTool::CodeTool (const CodeFileList& c) noexcept :
    codeFiles (c)
{
}

CodeTool::~CodeTool()
{
}

//==============================================================================
bool CodeTool::canApplyToFile (const juce::File& file) const
{
    return file.hasFileExtension (CodeFileList::getAllWildcards().removeCharacters ("*"));
}

//==============================================================================
void CodeTool::writeLinesToStream (juce::FileOutputStream* stream,
                                   juce::StringArray& lines,
                                   const juce::String& lineEnding)
{
    jassert (stream != nullptr);

    stream->setPosition (0);

    if (stream->truncate().wasOk())
    {
        const int size = lines.size();

        for (int i = 0; i < size; ++i)
        {
            const juce::String& line = lines.getReference (i);
            stream->writeText (line + (line.endsWith (lineEnding) ? juce::String::empty : lineEnding),
                               false, false);
        }
    }
}