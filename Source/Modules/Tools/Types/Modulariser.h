#ifndef JRL_MODULARISER_H
#define JRL_MODULARISER_H

/**
    @file Modulariser.h
    @copyright jrlanglois

*/
class Modulariser : public CodeTool
{
public:
    /** Constructor */
    Modulariser (const CodeFileList& codeFiles);

    //==============================================================================
    void saveTo (const juce::File& destinationFolder,
                 const juce::String& sourceFolderToRemove,
                 const juce::String& moduleName,
                 const juce::String& headerGuard,
                 const juce::String& desiredNamespace);

private:
    //==============================================================================
    Modulariser();
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Modulariser)
};

#endif //JRL_MODULARISER_H