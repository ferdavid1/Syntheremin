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
float duration = 0;
float distance = 0;

const int pitchpin = A0; // Pitch Pot (analog)
const int tonelengthpin = A1; // Tone Length Pot (analog)
const int modpin = A2; // Mod pot (analog)
//const int sequenceinterval = A3; // Sequence Interval Pot (analog)
// Waveform switches
const int switch1 = 2; // sine
const int switch2 = 3; // triangle
const int switch3 = 4; // square 
const int switch4 = 5; // saw
const int switch5 = 6; // ramp 
const int switch6 = 7; // noise

//Envelopes
const int envelopepin = A3; // 4-way envelope switch (or potentially another pot)
const int LEDPin = 9;
int onsize = 0; // length of the vector of switch modes (HIGH OR LOW)
synth edgar;    //-Make a synth

void update() {
  // use 6 arduino toggle switches to choose SINE,TRIANGLE,SQUARE,SAW,RAMP,NOISE
  // map values of int, pitch, tonelength of AnalogRead from 0 - 1023 to 0 - 127? divide them by 8.06 and round 
  int pitch = round(analogRead(pitchpin)/8.06);
  int tonelength = round(analogRead(tonelengthpin)/8.06);
  int mod = round(analogRead(modpin)/8.06);
//  Serial.println(pitch);  
//  Serial.println(tonelength);
//  Serial.println(mod);
  
  //setupVoice( voice[0-3] , waveform[SINE,TRIANGLE,SQUARE,SAW,RAMP,NOISE] , pitch[0-127], envelope[ENVELOPE0-ENVELOPE3], length[0-127], mod[0-127, 64=no mod])

  int switch1state = digitalRead(switch1);
  int switch2state = digitalRead(switch2);
  int switch3state = digitalRead(switch3);
  int switch4state = digitalRead(switch4);
  int switch5state = digitalRead(switch5);
  int switch6state = digitalRead(switch6);
  int envelope = round(analogRead(envelopepin)/8.06); // not sure what the output of the 4-way switch will be. if cant figure out, use a pot for envelope and threshold it. For now assuming it will output 1,2,3,or 4
  int envel = ENVELOPE0; // set default envelope
  if (envelope < 32) {
    envel = ENVELOPE0;
  }
  else if ((envelope >= 32) && (envelope < 64)) {
    envel = ENVELOPE1;
  }
  else if ((envelope >= 64) && (envelope < 96)) {
    envel = ENVELOPE2;
  }
  else {
//    Serial.println(envelope);
    envel = ENVELOPE3;
  }
//  Serial.println(envel);
  int switchstates[] = {switch1state, switch2state, switch3state, switch4state, switch5state, switch6state};
  std::vector< int > onswitches;
  for (int i = 0; i < 6; i++) {
//    Serial.println(i);
//    Serial.println(switchstates[i]); // check that at least one of them is "HIGH"
    if (switchstates[i] == 0) {
      onswitches.push_back(i);
    }
  }
  Serial.println("-------------------------");
//  Serial.println(onswitches);
  onsize = sizeof(onswitches) / sizeof(int);
  for (int i = 0; i < onsize + 1; i++) {
//    edgar.setupVoice(i, onswitches[i], pitch, envel, tonelength, mod); // second parameter: 0,1,2,3,4,5 = SINE,TRIANGLE,SQUARE,SAW,RAMP,NOISE
    edgar.setWave(i, onswitches[i]);
    edgar.setPitch(i, pitch);
    edgar.setEnvelope(i, envel);
    edgar.setLength(i, tonelength);
    edgar.setMod(i, mod);
  }
}
void setup() {
  edgar.begin(); //-Start it up, with audio output from pin 11
  update();
  pinMode(LEDPin, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  Serial.begin(115200);
  edgar.setupVoice(0,SINE,60,ENVELOPE1,60,64);
  edgar.setupVoice(1,TRIANGLE,0,ENVELOPE3,64,64);
  edgar.setupVoice(2,SQUARE,0,ENVELOPE2 ,70,64);
  edgar.setupVoice(3,SAW,0,ENVELOPE3,20,64);
  edgar.setupVoice(4,RAMP,0,ENVELOPE1,64, 64);
  edgar.setupVoice(5,NOISE,0,ENVELOPE1,64, 64);
  // ADD CALL TO POWER LIBRARY FOR TIMEOUT DURATION (MAKE IT SOMETHING LIKE 3 HRS)
}
void loop()
{
  digitalWrite(LEDPin, HIGH);
  digitalWrite(trig, LOW);
  delayMicroseconds(20);
  digitalWrite(trig, HIGH);
  delayMicroseconds(20);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  distance = (duration / 2) / 29;
  if (duration > 2000) {
    duration = 2000;
  }
  Serial.println(duration);
//  Serial.println(onsize); // check that it isn't zero. if it is, onsize didn't get updated when update() was called in setup(). 
  for (int i = 0; i < onsize + 1; i++) {
    edgar.trigger(i);
    delay(duration/10);
  }
  update();
   
  // ADD CALL TO THE POWER LIBRARY TO CHECK IF TIMEOUT
}

