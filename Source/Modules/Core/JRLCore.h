/**
    @file JRL_Core.h
    @copyright jrlanglois

    This is the master module header for various core classes, configurations and tools.

    @note Please keep the inclusions alphabetically sorted!
*/
#ifndef JRL_CORE_H
#define JRL_CORE_H

#include "JuceHeader.h"

#ifdef JUCE_MSVC
    #pragma warning (disable: 4201) //Nonstandard extension used: nameless struct/union
    #pragma warning (disable: 4505) //Unreferenced local function has been removed
    #pragma warning (disable: 4266) //No override available for virtual member function from base - 'BaseClass' - function is hidden
    #pragma warning (disable: 4996) //This function or variable may be unsafe. Consider using "some bs safer version".

    //The following are warnings that are off by default (@see: http://msdn.microsoft.com/en-us/library/23k5d385.aspx)
    //#pragma warning (default: 4266)     //no override available for function from base class; function is hidden
    #pragma warning (default: 4264)     //no override available for function from base class; function is hidden
    #pragma warning (default: 4263)     //'function': member function does not override any base class virtual member function
    #pragma warning (default: 4265)     //'class': class has virtual functions, but destructor is not virtual
    #pragma warning (default: 4355)     //'this' : used in base member initializer list
    //#pragma warning (default: 4710)   //'function': function not inlined
    #pragma warning (default: 4738)     //storing 32-bit float result in memory, possible loss of performance
    #pragma warning (default: 4946)     //reinterpret_cast used between related classes: 'class1' and 'class2'
#endif //JUCE_MSVC

/** Runs TRANS() over every string contained in the array

    @param[in/out] The strings to translate back into the given array
*/
static void translate (juce::StringArray& strings)
{
    for (int i = strings.size(); --i >= 0;)
        strings.strings.setUnchecked (i, TRANS (strings.getReference (i)));
}

#endif //JRL_CORE_H