#pragma once

#include <JuceHeader.h>
#include "juce_graphics/juce_graphics.h"
#include "juce_gui_basics/juce_gui_basics.h"

namespace Colors {
const juce::Colour background{245, 240, 235};
const juce::Colour header{40, 40, 40};

namespace Knob {
const juce::Colour trackBackground{205, 200, 195};
const juce::Colour trackActive{177, 101, 135};
const juce::Colour outline{255, 250, 245};
const juce::Colour gradientTop{250, 245, 240};
const juce::Colour gradientBottom{240, 235, 230};
const juce::Colour dial{100, 100, 100};
const juce::Colour dropShadow{195, 190, 185};
const juce::Colour label{80, 80, 80};
const juce::Colour textBoxBackground{80, 80, 80};
const juce::Colour value{240, 240, 240};
const juce::Colour caret{255, 255, 255};
}  // namespace Knob

namespace Group {
const juce::Colour label{160, 155, 150};
const juce::Colour outline{235, 230, 225};
}  // namespace Group
namespace Button {
const juce::Colour text{80, 80, 80};
const juce::Colour textToggled{40, 40, 40};
const juce::Colour background{245, 240, 235};
const juce::Colour backgroundToggled{255, 250, 245};
const juce::Colour outline{235, 230, 225};
}  // namespace Button
}  // namespace Colors

class Fonts {
  Fonts() = delete;

 public:
  static juce::Font getFont(float height = 16.0f);

 private:
  static const juce::Typeface::Ptr typeFace;
};

class RotaryKnobLookAndFeel : public juce::LookAndFeel_V4 {
 public:
  RotaryKnobLookAndFeel();

  juce::Font getLabelFont(juce::Label&) override;
  juce::Label* createSliderTextBox(juce::Slider&) override;
  void drawTextEditorOutline(juce::Graphics&, int, int, juce::TextEditor&) override {}
  void fillTextEditorBackground(juce::Graphics&, int, int, juce::TextEditor&) override;

  static RotaryKnobLookAndFeel* get() {
    static RotaryKnobLookAndFeel instance;
    return &instance;
  }

  void drawRotarySlider(juce::Graphics& g,
                        int x,
                        int y,
                        int width,
                        int height,
                        float sliderPos,
                        float rotaryStartAngle,
                        float rotaryEndAngle,
                        juce::Slider& slider) override;

 private:
  juce::DropShadow dropShadow{Colors::Knob::dropShadow, 6, {0, 3}};
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RotaryKnobLookAndFeel)
};

class ButtonLookAndFeel : public juce::LookAndFeel_V4 {
 public:
  ButtonLookAndFeel();

  static ButtonLookAndFeel* get() {
    static ButtonLookAndFeel instance;
    return &instance;
  }

  void drawButtonBackground(juce::Graphics& g,
                            juce::Button& button,
                            const juce::Colour& backgroundColour,
                            bool shouldDrawButtonAsHighlighted,
                            bool shouldDrawButtonAsDown) override;

  void drawButtonText(juce::Graphics& g,
                      juce::TextButton& button,
                      bool shouldDrawButtonAsHighlighted,
                      bool shouldDrawButtonAsDown) override;

 private:
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ButtonLookAndFeel)
};

class MainLookAndFeel : public juce::LookAndFeel_V4 {
 public:
  MainLookAndFeel();

  juce::Font getLabelFont(juce::Label&) override;

 private:
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainLookAndFeel)
};
