/*
  ==============================================================================

    LookAndFeel.cpp
    Created: 6 Jan 2025 8:25:15pm
    Author:  David Werth

  ==============================================================================
*/

#include "LookAndFeel.h"

RotaryKnobLookAndFeel::RotaryKnobLookAndFeel() {
  setColour(juce::Label::textColourId, Colors::Knob::label);
  setColour(juce::Slider::textBoxTextColourId, Colors::Knob::label);
}

void RotaryKnobLookAndFeel::drawRotarySlider(
    juce::Graphics &g, int x, int y, int width, [[maybe_unused]] int height,
    float sliderPos, float rotaryStartAngle, float rotaryEndAngle,
    juce::Slider &slider) {
  auto bounds = juce::Rectangle<int>(x, y, width, width).toFloat();
  auto knobRect = bounds.reduced(10.0f, 10.0f);
  g.setColour(Colors::Knob::outline);
  g.fillEllipse(knobRect);
}
