#ifndef JRL_TABS_TO_SPACES_COMPONENT_H
#define JRL_TABS_TO_SPACES_COMPONENT_H

#include "../Types/TabsToSpaces.h"

/**
    @file TabsToSpacesComponent.h
    @copyright jrlanglois

*/
class TabsToSpacesComponent : public ToolComponent
{
public:
    /** Constructor */
    TabsToSpacesComponent (const CodeFileList& codeFiles);

    //==============================================================================
    /** @internal */
    void resized() override;
    /** @internal */
    void buttonClicked (juce::Button* button) override;

private:
    //==============================================================================
    juce::TextButton convert;
    juce::Label lblSpaceChanger;
    juce::Slider spaceChanger;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TabsToSpacesComponent)
};

#endif //JRL_TABS_TO_SPACES_COMPONENT_H