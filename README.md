# Syntheremin
- Code for Arduino 6-wavetable synth with ultrasonic sensor theremin module
- Waveforms: SINE, TRIANGLE, SQUARE, SAW, RAMP, NOISE

- http://www.instructables.com/id/Turn-your-Arduino-into-a-4-voice-wavetable-synth-w/

# Wiring

- Synth

	follow the instructables directions, except use pin 11 instead of 6 and 1K resistor instead of 2.2K
	
- Ultrasonic Sensor ('US')

	US VCC -> Arduino 5v
	US GND -> Arduino GND(1st)
	US Trig -> Arduino pin 13
	US Echo -> Arduino pin 12

- Piezo Sensor ('PS')
	
	PS Red -> Arduino pin 8
	PS Black -> Arduino GND(2nd)

- Wire out to speakers with 1/4 in. jack