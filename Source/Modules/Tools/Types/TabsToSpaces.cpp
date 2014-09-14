#include "TabsToSpaces.h"

TabsToSpaces::TabsToSpaces (const CodeFileList& c) :
    CodeTool (c)
{
}

//==============================================================================
juce::String TabsToSpaces::createSpaceString (int numSpacesPerTab)
{
    juce::String spacer;

    while (--numSpacesPerTab >= 0)
        spacer += " ";

    return spacer;
}

void TabsToSpaces::cleanFile (const juce::File& file, const juce::String& spaceString)
{
    if (! file.hasWriteAccess())
        return;

    juce::StringArray lines;
    file.readLines (lines);

    //Replace the tab character:
    for (int i = lines.size(); --i >= 0;)
        lines.getReference (i) = lines.getReference (i).replace ("\t", spaceString, true);

    juce::ScopedPointer<juce::FileOutputStream> stream (file.createOutputStream());

    if (stream != nullptr)
        writeLinesToStream (stream, lines);
}

//==============================================================================
void TabsToSpaces::perform (int numSpacesPerTab)
{
    numSpacesPerTab = juce::jlimit (0, getMaxNumSpacesPerTab(), numSpacesPerTab);

    const CodeFileList& codeFiles = getCodeFiles();
    const juce::String spaceString (createSpaceString (numSpacesPerTab));

    for (int i = codeFiles.getNumFiles(); --i >= 0;)
        cleanFile (codeFiles[i], spaceString);
}