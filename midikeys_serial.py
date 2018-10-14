import pygame 
import pygame.midi
from pygame.locals import *

pygame.init()
pygame.fastevent.init()
event_get = pygame.fastevent.get
event_post = pygame.fastevent.post

pygame.midi.init()
# print(pygame.midi.get_device_info(3))
i = pygame.midi.Input(3)
pygame.display.set_caption("Reading MIDI Keyboard Input")
screen = pygame.display.set_mode((400,300), RESIZABLE, 32)

going = True
while going:

        events = event_get()
        print(i.poll())
        for e in events:
                if e.type in [QUIT]:
                        going = False
                if e.type in [KEYDOWN]:
                        going = False

        if i.poll():
                midi_events = i.read(10)

                if int(midi_events[0][0][0]) in [224,225,226]:#Pitch Bender
                        print(str(midi_events[0][0][2]))#right(0)  center(64)  left(124)
                        
                # print("full midi_events " + str(midi_events))
                print("my midi note is " + str(midi_events[0][0][1]))
                # convert them into pygame events.
                midi_evs = pygame.midi.midis2events(midi_events, i.device_id)

                for m_e in midi_evs:
                        event_post( m_e )

print("exit button clicked.")
i.close()
pygame.midi.quit()
pygame.quit()
exit()