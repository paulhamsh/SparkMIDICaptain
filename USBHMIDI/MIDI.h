#ifndef MIDI_h

#define MIDI_h

#include <usb/usb_host.h>
#include "show_desc.hpp"
#include "usbhhelp.hpp"

bool isMidiData;
byte midi_data[4];

void midi_setup();
void midi_loop();

#endif