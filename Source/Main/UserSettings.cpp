#include "UserSettings.h"

//==============================================================================
namespace UserSettingsHelpers
{
    /** */
    static juce::File getApplicationSettingsFolder()
    {
       #if JUCE_WINDOWS
        const juce::File folder (juce::File::getSpecialLocation (juce::File::userApplicationDataDirectory).getChildFile ("CodeFileTools"));
       #elif JUCE_MAC
        const juce::File folder ("~/Library/Preferences/com.CodeFileTools.xml");
       #elif JUCE_LINUX
        const juce::File folder ("~/.config/CodeFileTools");
       #else
        #error Insert the appropriate user settings folder path for this platform here.
       #endif

        static bool firstTime = true;

        if (firstTime)
        {
            firstTime = false;

            if (! folder.createDirectory())
                jassertfalse; //Failed to create application folder
        }

        return folder;
    }

    /** */
    static const juce::String filename = "settings.xml";
}

//==============================================================================
juce_ImplementSingleton (UserSettings)

//==============================================================================
UserSettings::UserSettings() :
    settingsHaveChanged (false)
{
    saveIfNeeded();
}

UserSettings::~UserSettings()
{
    saveIfNeeded();

    clearSingletonInstance();
}

//==============================================================================
juce::File UserSettings::getFile() const noexcept
{
   #if JUCE_WINDOWS
    return UserSettingsHelpers::getApplicationSettingsFolder().getChildFile (UserSettingsHelpers::filename);
   #else
    #error Insert the appropriate user settings file path here, for this platform.
   #endif
}

//==============================================================================
void UserSettings::populateSettingsIfNeeded()
{
    juce::File settingsFile (getFile());

    if (! settingsFile.existsAsFile())
    {
        settingsFile.create();
        settingsHaveChanged = true;
    }

    if (settings.getNumChildren() <= 0)
    { //Load defaults from the binary:
    }
}

void UserSettings::saveIfNeeded()
{
    populateSettingsIfNeeded();

    if (settingsHaveChanged)
    {
        settingsHaveChanged = false;

        juce::File settingsFile (getFile());

        if (! settingsFile.existsAsFile())
            settingsFile.create();

        juce::ScopedPointer<juce::FileOutputStream> fos (settingsFile.createOutputStream());

        if (fos != nullptr)
        {
            juce::ScopedPointer<juce::XmlElement> state (settings.createXml());

            if (state != nullptr)
                state->writeToFile (settingsFile, juce::String::empty);
        }

    }
}

//==============================================================================
void UserSettings::load()
{
}

void UserSettings::save()
{
}

//==============================================================================
juce::String UserSettings::getString (const juce::String& name, const juce::String& defaultValue)
{
    return getProperty (name, defaultValue, &juce::var::isString);
}

bool UserSettings::getBool (const juce::String& name, const bool defaultValue)
{
    return getProperty (name, defaultValue, &juce::var::isBool);
}

int UserSettings::getInt (const juce::String& name, const int defaultValue)
{
    return getProperty (name, defaultValue, &juce::var::isInt);
}

juce::int64 UserSettings::getInt64 (const juce::String& name, const juce::int64 defaultValue)
{
    return getProperty (name, defaultValue, &juce::var::isInt64);
}

float UserSettings::getFloat (const juce::String& name, const float defaultValue)
{
    return (float) getProperty (name, (double) defaultValue, &juce::var::isDouble);
}

double UserSettings::getDouble (const juce::String& name, const double defaultValue)
{
    return getProperty (name, defaultValue, &juce::var::isDouble);
}

//==============================================================================
void UserSettings::setString (const juce::String& name, const juce::String& value)  { setProperty (name, value); }
void UserSettings::setBool (const juce::String& name, const bool value)             { setProperty (name, value); }
void UserSettings::setInt (const juce::String& name, const int value)               { setProperty (name, value); }
void UserSettings::setInt64 (const juce::String& name, const juce::int64 value)     { setProperty (name, value); }
void UserSettings::setFloat (const juce::String& name, const float value)           { setProperty (name, value); }
void UserSettings::setDouble (const juce::String& name, const double value)         { setProperty (name, value); }