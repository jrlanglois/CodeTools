#ifndef JRL_TABS_TO_SPACES_H
#define JRL_TABS_TO_SPACES_H

/**
    @file TabsToSpaces.h
    @copyright jrlanglois

*/
class TabsToSpaces : public CodeTool
{
public:
    /** Constructor */
    TabsToSpaces (const CodeFileList& codeFiles);

    //==============================================================================
    static int getMaxNumSpacesPerTab() noexcept { return 10; }

    void perform (int numSpacesPerTab);

private:
    //==============================================================================
    juce::String createSpaceString (int numSpacesPerTab);

    void cleanFile (const juce::File& file, const juce::String& spaceString);

    //==============================================================================
    TabsToSpaces();
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TabsToSpaces)
};

#endif //JRL_TABS_TO_SPACES_H