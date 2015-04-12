int speakerPin = 9;

const int highChirp = 20;

const int lowChirp = 14;



const int chirpCycle = 70;

const int chirpPause = 8;

const int numChirps = 10;

const int midChirp = 150;

void setup() {
  pinMode(speakerPin, OUTPUT);
}

int baseFrequency = 10000;

int width = 100;

void loop() {
  for(int i = baseFrequency; i < baseFrequency+width; i++) {
    tone(speakerPin, i);
    delay(1);
  }
  noTone(speakerPin);
  delay(1000-width);
}