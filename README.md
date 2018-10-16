# Syntheremin
- Code for Arduino 6-wavetable synth with ultrasonic sensor theremin module
- Waveforms: SINE, TRIANGLE, SQUARE, SAW, RAMP, NOISE
- MIDI-controllable with MIDI_synth.ino (on the arduino) and midikeys_serial.py (on a host computer) scripts working in conjunction. 

# Adaptation of:
	- http://www.instructables.com/id/Turn-your-Arduino-into-a-4-voice-wavetable-synth-w/

# Wiring

- Synth

	- Reminder: use 1K resistors instead of 2.2K throughout
	- Audio out at Pin 11
	- follow schematic.fzz for full wiring and circuit diagrams
	
- Ultrasonic Sensor

	US VCC -> Arduino 5v

	US GND -> Arduino GND
	
	US Trig -> Arduino pin 13
	
	US Echo -> Arduino pin 12

- Cable out to amplifier/pedalboard with 1/4 in. jack, or 1/4-to-headphone-jack adapter to headphones/speaker