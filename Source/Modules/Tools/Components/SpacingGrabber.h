#ifndef JRL_SPACING_GRABBER_H
#define JRL_SPACING_GRABBER_H

/**
    @file SpacingGrabber.h
    @copyright jrlanglois

*/
class SpacingGrabber : public juce::Component
{
public:
    /** Constructor */
    SpacingGrabber();

    //==============================================================================
    /** @internal */
    void paint (juce::Graphics& g) override;
    /** @internal */
    void mouseEnter (const juce::MouseEvent& e) override;
    /** @internal */
    void mouseDrag (const juce::MouseEvent& e) override;
    /** @internal */
    void mouseExit (const juce::MouseEvent& e) override;

private:
    //==============================================================================
    juce::Colour baseColour;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SpacingGrabber)
};

#endif //JRL_SPACING_GRABBER_H