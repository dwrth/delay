#pragma once

#include <JuceHeader.h>
#include "juce_audio_basics/juce_audio_basics.h"

class Tempo {
 public:
  void reset() noexcept;

  void update(const juce::AudioPlayHead* playhead) noexcept;

  double getMillisecondsForNoteLength(int index) const noexcept;

  double getTempo() const noexcept { return bpm; }

 private:
  double bpm = 120.0;
};
