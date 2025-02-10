/*
  ==============================================================================

    Parameters.cpp
    Created: 16 Dec 2024 9:00:04pm
    Author:  David Werth

  ==============================================================================
*/

#include "Parameters.h"
#include <memory>
#include "juce_audio_processors/juce_audio_processors.h"
#include "juce_core/juce_core.h"
template <typename T>
static void castParameter(juce::AudioProcessorValueTreeState& apvts, const juce::ParameterID& id, T& destination) {
  destination = dynamic_cast<T>(apvts.getParameter(id.getParamID()));
  jassert(destination);  // parameter does not exist or wrong type
}

static juce::String stringFromMilliseconds(float value, int) {
  if (value < 10.0f)
    return juce::String(value, 2) + " ms";
  if (value < 100.0f)
    return juce::String(value, 1) + " ms";
  if (value < 1000.0f)
    return juce::String(int(value)) + " ms";
  return juce::String(value * 0.001f, 2) + " s";
}

static float millisecondsFromString(const juce::String& text) {
  float value = text.getFloatValue();
  if (!text.endsWithIgnoreCase("ms")) {
    if (!text.endsWithIgnoreCase("s") || value < Parameters::minDelayTime) {
      return value * 1000.0f;
    }
  }
  return value;
}

static juce::String stringFromDecibels(float value, int) {
  return juce::String(value, 1) + " dB";
}

static juce::String stringFromPercent(float value, int) {
  return juce::String(int(value)) + " %";
}

Parameters::Parameters(juce::AudioProcessorValueTreeState& apvts) {
  castParameter(apvts, gainParamID, gainParam);
  castParameter(apvts, delayTimeParamID, delayTimeParam);
  castParameter(apvts, mixParamID, mixParam);
  castParameter(apvts, feedbackParamID, feedbackParam);
}

juce::AudioProcessorValueTreeState::ParameterLayout Parameters::createParameterLayout() {
  juce::AudioProcessorValueTreeState::ParameterLayout layout;
  layout.add(std::make_unique<juce::AudioParameterFloat>(
      gainParamID, "Output Gain", juce::NormalisableRange<float>{-12.0f, 12.0f}, 0.0f,
      juce::AudioParameterFloatAttributes().withStringFromValueFunction(stringFromDecibels)));
  layout.add(std::make_unique<juce::AudioParameterFloat>(
      delayTimeParamID, "Delay Time", juce::NormalisableRange<float>{minDelayTime, maxDelayTime, 0.001f, 0.25f}, 100.0f,
      juce::AudioParameterFloatAttributes()
          .withStringFromValueFunction(stringFromMilliseconds)
          .withValueFromStringFunction(millisecondsFromString)));
  layout.add(std::make_unique<juce::AudioParameterFloat>(
      mixParamID, "Mix", juce::NormalisableRange<float>{0.0f, 100.0f, 1.0f}, 100.0f,
      juce::AudioParameterFloatAttributes().withStringFromValueFunction(stringFromPercent)));
  layout.add(std::make_unique<juce::AudioParameterFloat>(
      feedbackParamID, "Feedbak", juce::NormalisableRange<float>(-100.0f, 100.0f, 1.0f), 0.0f,
      juce::AudioParameterFloatAttributes().withStringFromValueFunction(stringFromPercent)));
  return layout;
}

void Parameters::update() noexcept {
  gainSmoother.setTargetValue(juce::Decibels::decibelsToGain(gainParam->get()));
  mixSmoother.setTargetValue(mixParam->get() * 0.01f);
  targetDelayTime = delayTimeParam->get();
  if (delayTime == 0.0f)
    delayTime = targetDelayTime;

  feedbackSmoother.setTargetValue(feedbackParam->get() * 0.01f);
}

void Parameters::prepareToPlay(double sampleRate) noexcept {
  double duration = 0.02;
  gainSmoother.reset(sampleRate, duration);
  mixSmoother.reset(sampleRate, duration);
  feedbackSmoother.reset(sampleRate, duration);

  coeff = 1.0f - std::exp(-1.0f / (0.2f * float(sampleRate)));
}

void Parameters::reset() noexcept {
  delayTime = 0.0f;

  gain = 0.0f;
  gainSmoother.setCurrentAndTargetValue(juce::Decibels::decibelsToGain(gainParam->get()));

  mix = 1.0f;
  mixSmoother.setCurrentAndTargetValue(mixParam->get() * 0.01f);

  feedback = 0.0f;
  feedbackSmoother.setCurrentAndTargetValue(feedbackParam->get() * 0.01f);
}

void Parameters::smoothen() noexcept {
  gain = gainSmoother.getNextValue();
  mix = mixSmoother.getNextValue();
  delayTime += (targetDelayTime - delayTime) * coeff;
  feedback = feedbackSmoother.getNextValue();
}
