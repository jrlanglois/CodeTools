#ifndef JRL_MODULARISER_COMPONENT_H
#define JRL_MODULARISER_COMPONENT_H

#include "../Types/Modulariser.h"

/**
    @file ModulariserComponent.h
    @copyright jrlanglois

*/
class ModulariserComponent : public ToolComponent
{
public:
    /** Constructor */
    ModulariserComponent (const CodeFileList& codeFiles);

    //==============================================================================
    /** @internal */
    void resized() override;
    /** @internal */
    void buttonClicked (juce::Button* button) override;

private:
    //==============================================================================
    juce::TextButton btnGenerate;
    juce::TextButton btnBrowse;
    juce::Label lblAdditionalHeaders;
    juce::Label lblModuleFilename;
    juce::Label lblHeaderGuard;
    juce::Label lblNamespace;
    juce::Label lblDestinationFolder;
    juce::TextEditor txtAdditionalHeaders;
    juce::TextEditor txtModuleFilename;
    juce::TextEditor txtHeaderGuard;
    juce::TextEditor txtNamespace;
    juce::TextEditor txtDestinationFolder;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ModulariserComponent)
};

#endif //JRL_MODULARISER_COMPONENT_H