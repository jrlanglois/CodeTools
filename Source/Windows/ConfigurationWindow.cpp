#include "ConfigurationWindow.h"

ConfigurationWindow::ConfigurationWindow()
{
    addLabel ("Line ending format", "");
    addLabel ("Number of spaces per tab", "");
    addLabel ("Always remove document start whitespace", "");
    addLabel ("Document end whitespace clean type", "");

    setSize (getLargestLabelWidth() * 2, (labels.size() + 1) * LabelHeight);
}

ConfigurationWindow::~ConfigurationWindow()
{
}
 
//==============================================================================
void ConfigurationWindow::addLabel (const juce::String& text,
                                    const juce::String& tooltip)
{
    if (juce::Label* label = labels.add (new juce::Label (juce::String::empty, text + ":")))
    {
        label->setTooltip (tooltip);
        label->setJustificationType (juce::Justification::centredRight);

        addAndMakeVisible (label);
    }
}

int ConfigurationWindow::getLargestLabelWidth() const
{
    int largestWidth = 0;

    for (int i = 0; i < labels.size(); ++i)
        if (juce::Label* label = labels.getUnchecked (i))
            largestWidth = juce::jmax (largestWidth, label->getFont().getStringWidth (label->getText()));

    return largestWidth;
}

//==============================================================================
void ConfigurationWindow::resized()
{
    const juce::Rectangle<int> labelRect (getLargestLabelWidth(), LabelHeight);

    for (int i = 0; i < labels.size(); ++i)
        if (juce::Label* label = labels.getUnchecked (i))
            label->setBounds (labelRect.withY ((LabelHeight/ 2) + (LabelHeight * i)));
}

void ConfigurationWindow::sliderValueChanged (juce::Slider* const)
{
}

void ConfigurationWindow::comboBoxChanged (juce::ComboBox* const)
{
}