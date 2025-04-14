#include "DelayLine.h"
#include <JuceHeader.h>
#include <cstddef>
#include "juce_core/system/juce_PlatformDefs.h"

void DelayLine::setMaximumDelayInSamples(int maxLenghtInSamples) {
  jassert(maxLenghtInSamples > 0);

  int paddedLength = maxLenghtInSamples + 1;

  if (bufferLength < paddedLength) {
    bufferLength = paddedLength;

    buffer.reset(new float[size_t(bufferLength)]);
  }
}

void DelayLine::reset() noexcept {
  writeIndex = bufferLength - 1;

  for (size_t i = 0; i < size_t(bufferLength); ++i) {
    buffer[i] = 0.0f;
  }
}

void DelayLine::write(float input) noexcept {
  jassert(bufferLength > 0;);

  writeIndex++;

  if (writeIndex >= bufferLength) {
    writeIndex = 0;
  }

  buffer[size_t(writeIndex)] = input;
}

float DelayLine::read(float delayInSamples) const noexcept {
  jassert(delayInSamples >= 0.0f);
  jassert(delayInSamples <= bufferLength - 1.0f);

  int readIndex = int(std::round(writeIndex - delayInSamples));

  if (readIndex < 0) {
    readIndex += bufferLength;
  }

  return buffer[size_t(readIndex)];
}
