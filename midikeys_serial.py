import logging
import sys
import time

from rtmidi.midiutil import open_midiinput

log = logging.getLogger('midiin_poll')
logging.basicConfig(level=logging.DEBUG)

try:
	midiin, port_name = open_midiinput(3)
except (EOFError, KeyboardInterrupt):
	sys.exit()

print("Press Control-C to exit")
try:
	while True:
		msg = midiin.get_message()
		if msg:
			message, deltatime = msg
			import serial
			with serial.Serial('COM1', 31250) as ser:
				ser.write(message.encode('utf-8'))
		time.sleep(0.01)		
except (KeyboardInterrupt):
	print('')
finally:
	print("Exit.")
	midiin.close_port()
	del midiin