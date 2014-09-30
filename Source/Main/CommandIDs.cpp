#include "CommandIDs.h"

namespace CommandIDs
{
    //==============================================================================
    juce_ImplementSingleton (CommandIDHelper)

    //==============================================================================
    void populateApplicationCommandManager (juce::ApplicationCommandManager& commandManager)
    {
        if (CommandIDHelper* helper = CommandIDHelper::getInstance())
            for (int i = helper->commands.size(); --i >= 0;)
                if (juce::ApplicationCommandInfo* commandInfo = helper->commands.getUnchecked (i))
                    commandManager.registerCommand (*commandInfo);
    }

    juce::String getName (const IDTag tag)
    {
        if (CommandIDHelper* helper = CommandIDHelper::getInstance())
            for (int i = helper->commands.size(); --i >= 0;)
                if (juce::ApplicationCommandInfo* commandInfo = helper->commands.getUnchecked (i))
                    if (commandInfo->commandID == (int) tag)
                        return commandInfo->shortName;

        jassertfalse;
        return juce::String::empty;
    }

    juce::String getDescription (const IDTag tag)
    {
        if (CommandIDHelper* helper = CommandIDHelper::getInstance())
            for (int i = helper->commands.size(); --i >= 0;)
                if (juce::ApplicationCommandInfo* commandInfo = helper->commands.getUnchecked (i))
                    if (commandInfo->commandID == (int) tag)
                        return commandInfo->description;

        jassertfalse;
        return juce::String::empty;
    }

    void addCommandItem (juce::PopupMenu& menu,
                         juce::ApplicationCommandManager* const commandManager,
                         const IDTag tag)
    {
        menu.addCommandItem (commandManager, tag, getName (tag));
    }
}