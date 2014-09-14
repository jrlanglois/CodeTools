#ifndef JRL_LINE_ENDINGS_CONVERTER_COMPONENT_H
#define JRL_LINE_ENDINGS_CONVERTER_COMPONENT_H

#include "ToolComponent.h"
#include "../Types/LineEndingsConverter.h"

/**
    @file LineEndingsConverterComponent.h
    @copyright jrlanglois

*/
class LineEndingsConverterComponent : public ToolComponent
{
public:
    /** Constructor */
    LineEndingsConverterComponent (const CodeFileList& codeFiles);

    //==============================================================================
    /** @internal */
    void resized() override;
    /** @internal */
    void buttonClicked (juce::Button* button) override;

private:
    //==============================================================================
    juce::TextButton convert;
    juce::ComboBox formats;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LineEndingsConverterComponent)
};

#endif //JRL_LINE_ENDINGS_CONVERTER_COMPONENT_H