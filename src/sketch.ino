#include <MozziGuts.h> // this makes everything work 
#include <Metronome.h>
#include <Oscil.h>
#include <tables/sin2048_int8.h>

#include "config.h"

Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> chirp(SIN2048_DATA);

Metronome metronome(500);

#define DEBUG true

int baseFreq = 8000;

void setup() {
  startMozzi();
  chirp.setFreq(baseFreq);
  if(DEBUG)
    Serial.begin(9600);
}

unsigned long lastReady = 0;

const int bandwidth = 3000;

int counter = 0;

/*
 * Lower-frequency pulses travel further and cut through ambient sound, but provide less detail.
 * Higher-frequency pulses give more detail but travel less far, and are obscured by ambience.
 * This variable sets a ratio of low-frequency, long-range pulses to high-frequency, detailed pulses.
 * Cyclists will likely want more long-range pulses, while sports require short-range, detailed pulses.
 *
 * 0 == 1 lower, long-range pulse followed by 3 higher, short-range pulses
 * 1 == 1 short-range pulse, 1 long-range pulse
 * 2 == 3 long-range pulses, 1 short-range pulse
*/

int pulseMode = 0;

bool shouldLongPulse() {
  if(pulseMode == 0)
    if(counter == 0)
      return true;
    else
      return false;
  else if(pulseMode == 1)
    if(counter == 0 || counter == 2)
      return true;
    else
      return false;
  else if(pulseMode == 2)
    if(counter < 3)
      return true;
    else
      return false;
}

// Long-range pulses are 2 KHz lower than short-range pulses.

#define LONG_RANGE_PULSE_OFFSET -2000

int baseFreqOffset = 0;

void updateControl(){
  unsigned long now = mozziMicros();
  if(metronome.ready()) {
    lastReady = now;
    if(shouldLongPulse())
      baseFreqOffset = LONG_RANGE_PULSE_OFFSET;
    else
      baseFreqOffset = 0;
    chirp.setFreq(baseFreq+baseFreqOffset);
    chirp.setPhase(0);
    counter++;
    if(counter == 4)
      counter = 0;
  } else if(now > lastReady && now-lastReady <= 10000) {
    float ratio = (now-lastReady)/10000;
    chirp.setFreq(baseFreq+baseFreqOffset+((int)ratio*bandwidth));
  } else
    lastReady = 0;
}

int updateAudio(){
  if(lastReady == 0)
    return 0;
  else
    return chirp.next();
}

void loop() {
  audioHook();
}