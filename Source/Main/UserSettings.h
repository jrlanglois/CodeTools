#ifndef JRL_USER_SETTINGS_H
#define JRL_USER_SETTINGS_H

#include "../Modules/JRLHeader.h"

/**
    @file Main.cpp
    @copyright jrlanglois

*/
class UserSettings : public juce::DeletedAtShutdown
{
public:
    /** Constructor */
    UserSettings();

    /** Destructor */
    ~UserSettings();

    //==============================================================================
    juce_DeclareSingleton (UserSettings, true)

    //==============================================================================
    /** */
    void load();

    /** */
    void save();

    //==============================================================================
    juce::File getFile() const noexcept;

    //==============================================================================
    /** */
    juce::String getString (const juce::String& name, const juce::String& defaultValue);

    /** */
    bool getBool (const juce::String& name, bool defaultValue);

    /** */
    int getInt (const juce::String& name, int defaultValue);

    /** */
    juce::int64 getInt64 (const juce::String& name, juce::int64 defaultValue);

    /** */
    float getFloat (const juce::String& name, float defaultValue);

    /** */
    double getDouble (const juce::String& name, double defaultValue);

    //==============================================================================
    /** */
    void setString (const juce::String& name, const juce::String& value);

    /** */
    void setBool (const juce::String& name, bool value);

    /** */
    void setInt (const juce::String& name, int value);

    /** */
    void setInt64 (const juce::String& name, juce::int64 value);

    /** */
    void setFloat (const juce::String& name, float value);

    /** */
    void setDouble (const juce::String& name, double value);

private:
    //==============================================================================
    juce::ValueTree settings;
    bool settingsHaveChanged;

    //==============================================================================
    void saveIfNeeded();
    void populateSettingsIfNeeded();

    //==============================================================================
    template<typename ReturnType>
    ReturnType getProperty (const juce::String& name,
                            ReturnType defaultValue,
                            bool (juce::var::*isReturnType)() const noexcept)
    {
        const juce::var child ((juce::var) settings.getPropertyAsValue (name, nullptr));

        if ((child.*isReturnType)())
            return static_cast<ReturnType> (child);

        return defaultValue;
    }

    template<typename ValueType>
    void setProperty (const juce::String& name, ValueType value)
    {
        settings.setProperty (name, value, nullptr);
        settingsHaveChanged = true;
    }

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (UserSettings)
};

#endif //JRL_USER_SETTINGS_H