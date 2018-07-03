// Arduino synth library absolute frequency example

//Hardware cHIGHnectiHIGHs:

//                    +10�F
//PIN 11 ---[ 1k ]--+---||--->> Audio out
//                  |
//                 === 10nF
//                  |
//                 GND

#include <StandardCplusplus.h>
#include <synth.h>
// IMPORT POWER LIBRARY
#include <vector>
#define trig 13
#define echo 12
const int pitchpin = 0; // Pitch Pot (analog)
const int tonelengthpin = 1; // Tone Length Pot (analog)
const int modpin = 2; // Mod pot (analog)
// Waveform switches
const int switch1 = 2; // sine
const int switch2 = 3; // triangle
const int switch3 = 4; // square 
const int switch4 = 5; // saw
const int switch5 = 6; // ramp 
const int switch6 = 7; // noise
//Envelopes
const int envelopeswitch = 8 // 4-way envelope switch (or potentially another pot)
const int sequenceinterval = 3; // Sequence Interval Pot (analog)
const int LEDPin = 9;

synth edgar;    //-Make a synth

void update() {
  // use 6 arduino toggle switches to choose SINE,TRIANGLE,SQUARE,SAW,RAMP,NOISE
  // add a pot for pitch (5th parameter in setupVoice)
  int pitch = analogRead(pitchpin);
  int tonelength = analogRead(tonelengthpin);
  int mod = analogRead(modpin);
  //setupVoice( voice[0-3] , waveform[SINE,TRIANGLE,SQUARE,SAW,RAMP,NOISE] , pitch[0-127], envelope[ENVELOPE0-ENVELOPE3], length[0-127], mod[0-127, 64=no mod])

  char switch1state = digitalRead(switch1);
  char switch2state = digitalRead(switch2);
  char switch3state = digitalRead(switch3);
  char switch4state = digitalRead(switch4);
  char switch5state = digitalRead(switch5);
  char switch6state = digitalRead(switch6);
  int envelope = analogRead(envelopeswitch); // not sure what the output of the 4-way switch will be. if cant figure out, use a pot for envelope and threshold
  switch (envelope) {
    case 1:
      envel = ENVELOPE0;
    case 2:
      envel = ENVELOPE1;
    case 3:
      envel = ENVELOPE2;
    case 4:
      envel = ENVELOPE3;
  }

  char switchstates[] = {switch1state, switch2state, switch3state, switch4state, switch5state, switch6state};
  Serial.println(switchstates);
  std::vector< int > onswitches;
  for (int i = 0; i < 6; i++) {
    if (switchstates[i] == "HIGH") {
      onswitches.push_back(i);
    }
  }
  int onsize = sizeof(onswitches) / sizeof(int);
  for (int i = 0; i < onsize + 1; i++) {
    edgar.setupVoice(i, onswitches[i], pitch, envel, tonelength, mod); // second parameter: 0,1,2,3,4,5 = SINE,TRIANGLE,SQUARE,SAW,RAMP,NOISE
  }
}
void setup() {
  edgar.begin(); //-Start it up
  update();
  pinMode(OUTPUT, LEDPin);
  digitalWrite(LEDPin, HIGH);
  // ADD CALL TO POWER LIBRARY FOR TIMEOUT DURATION (MAKE IT SOMETHING LIKE 3 HRS)
}
void loop()
{
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  distance = microsecondsToCentimeters(duration);

  // tone(8, distance, 40); pin 8 is the piezo out
  sequenceaddition = analogRead(sequenceinterval);
  for (int i = 0; i < onsize + 1; i++) {
    edgar.setFrequency(i, distance + (sequenceaddition * i));
    edgar.trigger(i);
  }
  //  if (millis() % 1000 == 0) {
//    update(); // update switch configurations to see if they've been changed, every second
//  }
  update();
  // ADD CALL TO THE POWER LIBRARY TO CHECK IF TIMEOUT
}
