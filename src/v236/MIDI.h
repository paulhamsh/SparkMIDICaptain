#ifndef MIDI_h
  #define MIDI_h

  #ifdef USB_HOST
    #include <usbh_midi.h>
    #include <SPI.h>

    USB Usb;
    USBH_MIDI Midi(&Usb);
    bool usb_connected;
    uint16_t rcvd;
    uint8_t chan;
    uint8_t midi_buf[50*4];
  #endif


  void setup_midi();
  bool update_midi(byte *mid);

#endif
