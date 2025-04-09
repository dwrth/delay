#include "Tempo.h"
#include "juce_audio_basics/juce_audio_basics.h"

// Ranges from 1/32 over 1/16 triplet and 1/32 dotted to 1/1
static std::array<double, 16> noteLengthMultipliers = {0.125, 0.5 / 3.0, 0.1875, 0.25, 1.0 / 3.0, 0.375,
                                                       0.5,   2.0 / 3.0, 0.75,   1.0,  4.0 / 3.0, 1.5,
                                                       2.0,   8.0 / 3.0, 3.0,    4.0};

void Tempo::reset() noexcept {
  bpm = 120.0;
}

void Tempo::update(const juce::AudioPlayHead* playhead) noexcept {
  if (playhead == nullptr) {
    return;
  }

  const auto opt = playhead->getPosition();

  if (!opt.hasValue()) {
    return;
  }

  const auto& pos = *opt;

  if (pos.getBpm().hasValue()) {
    bpm = *pos.getBpm();
  }
}

double Tempo::getMillisecondsForNoteLength(int index) const noexcept {
  return 60000.0 * noteLengthMultipliers[size_t(index)] / bpm;
}
