#ifndef JRL_CONFIGURATION_WINDOW_H
#define JRL_CONFIGURATION_WINDOW_H

#include "../Modules/JRLHeader.h"

/**
    @file ConfigurationWindow.h
    @copyright jrlanglois

*/
class ConfigurationWindow : public juce::Component
{
public:
    /** Constructor */
    ConfigurationWindow();

    /** Destructor */
    ~ConfigurationWindow();

    //==============================================================================

private:
    //==============================================================================

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ConfigurationWindow)
};

#endif //JRL_CONFIGURATION_WINDOW_H