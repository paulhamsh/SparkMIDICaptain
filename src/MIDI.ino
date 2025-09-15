#include "MIDI.h"

void setup_midi() {
  byte b;

#ifdef USB_HOST
  if (Usb.Init() == -1) {
    DEBUG("USB host init failed");
    usb_connected = false;
  }
  else {
    DEBUG("USB host running");
    usb_connected = true;   
  }
#endif
}

bool update_midi(byte *mid) {
  bool got_midi;
  byte b;
  
  got_midi = false;

#ifdef USB_HOST
  // USB MIDI  
  if (usb_connected) {
    Usb.Task();

    if (Midi) {                                                  // USB Midi
      rcvd = Midi.RecvData(midi_buf, false);
      if (rcvd > 0 && !(midi_buf[0] == 0 && midi_buf[1] == 0 && midi_buf[2] == 0)) {
        mid[0] = midi_buf[0];
        mid[1] = midi_buf[1];
        mid[2] = midi_buf[2];
        got_midi = true;
      }
    }
  }
#endif

  if (got_midi) {
    Serial.print("MIDI ");
    Serial.print(mid[0], HEX);
    Serial.print(" ");
    Serial.print(mid[1]);
    Serial.print(" ");   
    Serial.println(mid[2]);
  }
  return got_midi;
}
