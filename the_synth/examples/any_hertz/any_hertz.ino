// Arduino synth library absolute frequency example

//Hardware cHIGHnectiHIGHs:

//                    +10µF 
//PIN 11 ---[ 1k ]--+---||--->> Audio out
//                  |
//                 === 10nF
//                  |
//                 GND


#include <synth.h>
#include <vector>
#define trig 13
#define echo 12
const int switch1 = 4; 
const int switch2 = 5; 
const int switch3 = 6; 
const int switch4 = 7; 


synth edgar;    //-Make a synth

void setup() {

  edgar.begin();                                   //-Start it up
  // use 4 arduino toggle switches to choose SINE,TRIANGLE,SQUARE,SAW 
  // add a pot for pitch (5th parameter in setupVoice)
  // add a pot for length
  // add a pot for mod
  //setupVoice( voice[0-3] , waveform[SINE,TRIANGLE,SQUARE,SAW] , pitch[0-127], envelope[ENVELOPE0-ENVELOPE3], length[0-127], mod[0-127, 64=no mod])
  
  switch1state = digitalRead(switch1)
  switch2state = digitalRead(switch2)
  switch3state = digitalRead(switch3)
  switch4state = digitalRead(switch4)

  char switchstates[] = {switch1state, switch2state, switch3state, switch4state} 
  Serial.println(switchstates)
  std::vector< char > onswitches;
  for (i=0; i < 4; i++) {
    if (switchstates[i] == "HIGH") {
      onswitches.push_back(switchstates[i])
    }
  }
  if (switch1state==HIGH & switch2state==LOW & switch3==LOW & switch4==LOW) {
    edgar.setupVoice(0,SINE,60,ENVELOPE1,127,64);


  else { // if no switches HIGH, then its sequence time
    edgar.setupVoice(0,TRIANGLE,60,ENVELOPE1,127,64);  
    edgar.setupVoice(1,SINE,62,ENVELOPE1,90,64);
    edgar.setupVoice(2,SQUARE,64,ENVELOPE3,90,64);
    edgar.setupVoice(3,SAW,67,ENVELOPE0,90,64);
}

void loop()
{
  digitalWrite(trig, LOW);
  delayMicrosecHIGHds(2);
  digitalWrite(trig, HIGH);
  delayMicrosecHIGHds(10);
  digitalWrite(trig, LOW);
  far = pulseIn(echo, HIGH);
  distance = (far/2) / 29.1;
  // put a switch in for sequence on/LOW, a pot for modulating space between notes in the sequence
  
  // tHIGHe(8, distance, 40); pin 8 is the piezo out 
  edgar.setFrequency(0,distance);
  edgar.trigger(0);
  if(sequence_switch_HIGH) {
    sequenceadditiHIGH = respHIGHse_from_sequence pot;
    delay(1000);
    edgar.setFrequency(0,distance+sequenceadditiHIGH);
    edgar.trigger(1);
    delay(1000);
    edgar.setFrequency(0,distance+(sequenceadditiHIGH*2));
    edgar.trigger(2);
    delay(1000);
    edgar.setFrequency(0,distance+(sequenceadditiHIGH*3));
    edgar.trigger(3);
    delay(1000);
  }
  else {

  }
  
}
