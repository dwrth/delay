/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginEditor.h"
#include "../JuceLibraryCode/BinaryData.h"
#include "LookAndFeel.h"
#include "PluginProcessor.h"
#include "juce_graphics/juce_graphics.h"
#include "juce_gui_basics/juce_gui_basics.h"

//==============================================================================
DelayAudioProcessorEditor::DelayAudioProcessorEditor(DelayAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p) {
  setLookAndFeel(&mainLF);

  delayGroup.setText("Delay");
  delayGroup.setTextLabelPosition(juce::Justification::horizontallyCentred);
  delayGroup.addAndMakeVisible(delayTimeKnob);
  addAndMakeVisible(delayGroup);

  feedbackGroup.setText("Feedback");
  feedbackGroup.setTextLabelPosition(juce::Justification::horizontallyCentred);
  feedbackGroup.addAndMakeVisible(feedbackKnob);
  addAndMakeVisible(feedbackGroup);

  outputGroup.setText("Output");
  outputGroup.setTextLabelPosition(juce::Justification::horizontallyCentred);
  outputGroup.addAndMakeVisible(gainKnob);
  outputGroup.addAndMakeVisible(mixKnob);
  addAndMakeVisible(outputGroup);

  gainKnob.slider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::green);

  setSize(500, 330);
}

DelayAudioProcessorEditor::~DelayAudioProcessorEditor() {
  setLookAndFeel(nullptr);
}

//==============================================================================
void DelayAudioProcessorEditor::paint(juce::Graphics& g) {
  auto noise = juce::ImageCache::getFromMemory(BinaryData::Noise_png, BinaryData::Noise_pngSize);
  auto fillType = juce::FillType(noise, juce::AffineTransform::scale(0.5f));
  g.setFillType(fillType);
  g.fillRect(getLocalBounds());

  auto rect = getLocalBounds().withHeight(40);
  g.setColour(Colors::header);
  g.fillRect(rect);

  auto image = juce::ImageCache::getFromMemory(BinaryData::Logo_png, BinaryData::Logo_pngSize);

  int destWidth = image.getWidth() / 2;
  int destHeight = image.getHeight() / 2;

  g.drawImage(image, getWidth() / 2 - destWidth / 2, 0, destWidth, destHeight, 0, 0, image.getWidth(),
              image.getHeight());
}

void DelayAudioProcessorEditor::resized() {
  auto bounds = getLocalBounds();

  int y = 50;
  int height = bounds.getHeight() - 60;

  delayGroup.setBounds(10, y, 110, height);

  outputGroup.setBounds(bounds.getWidth() - 160, y, 150, height);

  feedbackGroup.setBounds(delayGroup.getRight() + 10, y, outputGroup.getX() - delayGroup.getRight() - 20, height);

  delayTimeKnob.setTopLeftPosition(20, 20);
  mixKnob.setTopLeftPosition(20, 20);
  gainKnob.setTopLeftPosition(mixKnob.getX(), mixKnob.getBottom() + 10);
  feedbackKnob.setTopLeftPosition(20, 20);
}
