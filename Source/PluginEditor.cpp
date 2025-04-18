/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginEditor.h"
#include "../JuceLibraryCode/BinaryData.h"
#include "LookAndFeel.h"
#include "PluginProcessor.h"
#include "juce_events/juce_events.h"
#include "juce_graphics/juce_graphics.h"
#include "juce_gui_basics/juce_gui_basics.h"

//==============================================================================
DelayAudioProcessorEditor::DelayAudioProcessorEditor(DelayAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p) {
  setLookAndFeel(&mainLF);

  delayGroup.setText("Delay");
  delayGroup.setTextLabelPosition(juce::Justification::horizontallyCentred);
  delayGroup.addAndMakeVisible(delayTimeKnob);
  delayGroup.addChildComponent(delayNoteKnob);
  updateDelayKnobs(audioProcessor.params.tempoSyncParam->get());

  tempoSyncButton.setButtonText("Sync");
  tempoSyncButton.setClickingTogglesState(true);
  tempoSyncButton.setBounds(0, 0, 70, 27);
  tempoSyncButton.setLookAndFeel(ButtonLookAndFeel::get());
  delayGroup.addAndMakeVisible(tempoSyncButton);
  addAndMakeVisible(delayGroup);

  feedbackGroup.setText("Feedback");
  feedbackGroup.setTextLabelPosition(juce::Justification::horizontallyCentred);
  feedbackGroup.addAndMakeVisible(feedbackKnob);
  feedbackGroup.addAndMakeVisible(stereoKnob);
  feedbackGroup.addAndMakeVisible(lowCutKnob);
  feedbackGroup.addAndMakeVisible(highCutKnob);
  addAndMakeVisible(feedbackGroup);

  outputGroup.setText("Output");
  outputGroup.setTextLabelPosition(juce::Justification::horizontallyCentred);
  outputGroup.addAndMakeVisible(gainKnob);
  outputGroup.addAndMakeVisible(mixKnob);
  addAndMakeVisible(outputGroup);

  gainKnob.slider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::green);

  audioProcessor.params.tempoSyncParam->addListener(this);
  setSize(500, 330);
}

DelayAudioProcessorEditor::~DelayAudioProcessorEditor() {
  audioProcessor.params.tempoSyncParam->removeListener(this);
  setLookAndFeel(nullptr);
}

//==============================================================================
void DelayAudioProcessorEditor::paint(juce::Graphics& g) {
  auto noise = juce::ImageCache::getFromMemory(BinaryData::Noise_png, BinaryData::Noise_pngSize);
  auto fillType = juce::FillType(noise, juce::AffineTransform::scale(0.5f));
  g.setFillType(fillType);
  g.fillRect(getLocalBounds());

  auto rect = getLocalBounds().withHeight(40);
  g.setColour(Colors::background);
  g.fillRect(rect);

  auto image = juce::ImageCache::getFromMemory(BinaryData::Dbbahn_png, BinaryData::Dbbahn_pngSize);

  int destWidth = image.getWidth() / 20;
  int destHeight = image.getHeight() / 20;

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
  tempoSyncButton.setTopLeftPosition(20, delayTimeKnob.getBottom() + 10);
  delayNoteKnob.setTopLeftPosition(delayTimeKnob.getX(), delayTimeKnob.getY());
  mixKnob.setTopLeftPosition(20, 20);
  gainKnob.setTopLeftPosition(mixKnob.getX(), mixKnob.getBottom() + 10);
  feedbackKnob.setTopLeftPosition(20, 20);
  stereoKnob.setTopLeftPosition(feedbackKnob.getRight() + 20, 20);
  lowCutKnob.setTopLeftPosition(feedbackKnob.getX(), feedbackKnob.getBottom() + 10);
  highCutKnob.setTopLeftPosition(lowCutKnob.getRight() + 20, lowCutKnob.getY());
}

void DelayAudioProcessorEditor::parameterValueChanged(int, float value) {
  if (juce::MessageManager::getInstance()->isThisTheMessageThread()) {
    updateDelayKnobs(value != 0.0f);
  } else {
    juce::MessageManager::callAsync([this, value] { updateDelayKnobs(value != 0.0f); });
  }
}

void DelayAudioProcessorEditor::updateDelayKnobs(bool tempoSyncActive) {
  delayTimeKnob.setVisible(!tempoSyncActive);
  delayNoteKnob.setVisible(tempoSyncActive);
}
