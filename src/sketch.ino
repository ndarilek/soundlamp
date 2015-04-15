#include <MozziGuts.h> // this makes everything work 
#include <Metronome.h>
#include <SampleHuffman.h>

#include "chirp.h"

SampleHuffman chirp(CHIRP_SOUNDDATA, CHIRP_HUFFMAN, CHIRP_SAMPLE_BITS);

Metronome metronome(500);

#define DEBUG 1

void setup() {
  startMozzi();
  if(DEBUG)
    Serial.begin(9600);
}

void updateControl(){
  if(metronome.ready()) {
    if(DEBUG)
      Serial.println("chirp");
    chirp.start();
  }
}

int updateAudio(){
  return chirp.next();
}

void loop() {
  audioHook();
}