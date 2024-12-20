/*
  ==============================================================================

    RotaryKnob.h
    Created: 19 Dec 2024 9:56:26pm
    Author:  David Werth

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class RotaryKnob  : public juce::Component
{
public:
    RotaryKnob();
    ~RotaryKnob() override;

    void resized() override;
    
    juce::Slider slider;
    juce::Label label;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RotaryKnob)
};
