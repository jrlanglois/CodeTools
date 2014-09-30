#ifndef JRL_CONFIGURATION_WINDOW_H
#define JRL_CONFIGURATION_WINDOW_H

#include "../Modules/JRLHeader.h"

/**
    @file ConfigurationWindow.h
    @copyright jrlanglois

*/
class ConfigurationWindow : public juce::Component,
                            public juce::Slider::Listener,
                            public juce::ComboBox::Listener
{
public:
    /** Constructor */
    ConfigurationWindow();

    /** Destructor */
    ~ConfigurationWindow();

    //==============================================================================
    /** @internal */
    void resized() override;
    /** @internal */
    void sliderValueChanged (juce::Slider* slider) override;
    /** @internal */
    void comboBoxChanged (juce::ComboBox* comboBoxThatHasChanged) override;

private:
    //==============================================================================
    enum
    {
        LabelHeight = 36
    };

    juce::OwnedArray<juce::Label> labels;

    //==============================================================================
    void addLabel (const juce::String& text,
                   const juce::String& tooltip);

    int getLargestLabelWidth() const;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ConfigurationWindow)
};

#endif //JRL_CONFIGURATION_WINDOW_H