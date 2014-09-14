#ifndef JRL_CODE_TOKENISER_FACTORY_H
#define JRL_CODE_TOKENISER_FACTORY_H

/**
    @file CodeTokeniserFactory.h
    @copyright jrlanglois


*/
class CodeTokeniserFactory
{
public:
    /** Constructor*/
    CodeTokeniserFactory() noexcept;

    //==============================================================================
    juce::CodeTokeniser* getTokeniserForFile (const juce::File& file) const;

private:
    //==============================================================================
    juce::OwnedArray<juce::CodeTokeniser> tokenisers;

    //==============================================================================
    void populateTokenisers();

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CodeTokeniserFactory)
};

#endif //JRL_CODE_TOKENISER_FACTORY_H