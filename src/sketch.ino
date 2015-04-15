#include <MozziGuts.h> // this makes everything work 
#include <Metronome.h>
#include <Oscil.h>
#include <tables/sin2048_int8.h>

Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> sinWave(SIN2048_DATA);

Metronome metronome(500);

#define DEBUG true

int baseFreq = 8000;

void setup() {
  startMozzi();
  sinWave.setFreq(baseFreq);
  if(DEBUG)
    Serial.begin(9600);
}

unsigned long lastReady = 0;

const int bandwidth = 3000;

void updateControl(){
  unsigned long now = mozziMicros();
  if(metronome.ready()) {
    lastReady = now;
    sinWave.setFreq(baseFreq);
    sinWave.setPhase(0);
  } else if(now-lastReady <= 10000) {
    float ratio = (now-lastReady)/10000;
    if(DEBUG)
      Serial.println(ratio);
    sinWave.setFreq(baseFreq+((int)ratio*bandwidth));
  } else {
    lastReady = 0;
  }
}

int updateAudio(){
  if(lastReady == 0)
    return 0;
  else
    return sinWave.next();
}

void loop() {
  audioHook();
}