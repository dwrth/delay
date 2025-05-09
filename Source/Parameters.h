/*
  ==============================================================================

    Parameters.h
    Created: 16 Dec 2024 9:00:04pm
    Author:  David Werth

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "juce_audio_basics/juce_audio_basics.h"
#include "juce_audio_processors/juce_audio_processors.h"

const juce::ParameterID gainParamID{"gain", 1};
const juce::ParameterID delayTimeParamID{"delayTime", 1};
const juce::ParameterID mixParamID{"mix", 1};
const juce::ParameterID feedbackParamID{"feedback", 1};
const juce::ParameterID stereoParamID{"stereo", 1};
const juce::ParameterID lowCutParamID{"lowCut", 1};
const juce::ParameterID highCutParamID{"highCut", 1};
const juce::ParameterID tempoSyncParamID{"tempoSync", 1};
const juce::ParameterID delayNoteParamID{"dealyNote", 1};

class Parameters {
 public:
  Parameters(juce::AudioProcessorValueTreeState& apvts);

  static juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
  static constexpr float minDelayTime = 5.0f;
  static constexpr float maxDelayTime = 5000.0f;

  void prepareToPlay(double sampleRate) noexcept;
  void reset() noexcept;
  void update() noexcept;
  void smoothen() noexcept;

  float gain = 0.0f;
  float delayTime = 0.0f;
  float mix = 1.0f;
  float feedback = 0.0f;
  float panL = 0.0f;
  float panR = 1.0f;
  float lowCut = 20.0f;
  float highCut = 20000.0f;

  int delayNote = 0;
  bool tempoSync = false;

  juce::AudioParameterBool* tempoSyncParam;

 private:
  juce::AudioParameterFloat* gainParam;
  juce::LinearSmoothedValue<float> gainSmoother;

  juce::AudioParameterFloat* mixParam;
  juce::LinearSmoothedValue<float> mixSmoother;

  juce::AudioParameterFloat* delayTimeParam;
  float targetDelayTime = 0.0f;
  float coeff = 0.0f;

  juce::AudioParameterFloat* feedbackParam;
  juce::LinearSmoothedValue<float> feedbackSmoother;

  juce::AudioParameterFloat* stereoParam;
  juce::LinearSmoothedValue<float> stereoSmoother;

  juce::AudioParameterFloat* lowCutParam;
  juce::LinearSmoothedValue<float> lowCutSmoother;

  juce::AudioParameterFloat* highCutParam;
  juce::LinearSmoothedValue<float> highCutSmoother;

  juce::AudioParameterChoice* delayNoteParam;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Parameters)
};
