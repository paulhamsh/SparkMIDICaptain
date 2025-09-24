#include <usbh_midi.h>
#include <SPI.h>

// Enable USB host debugging in settings.h 
// Somewhere like this:  Arduino\libraries\USB_Host_Shield_Library_2.0\settings.h
// Depends where your library is stored
// Check in File / Preferences / Settings / Sketchbook location: c:\xxx\xxx\xxx\Arduino

// Set this to 1 to activate serial debugging 
// #define ENABLE_UHS_DEBUGGING 1



USB Usb;
USBH_MIDI Midi(&Usb);

bool usb_connected;
uint16_t rcvd;
uint8_t midi_buf[50*4];

void setup() {
  Serial.begin(115200);
  while (!Serial) {};
  Serial.println("Started");

  delay(2000);

  if (Usb.Init() == -1) {
    Serial.println("USB host init failed");
    usb_connected = false;
  }
  else {
    Serial.println("USB host running");
    usb_connected = true;   
  }
}

void loop() {
  byte mi[3];

  if (usb_connected) {
    Usb.Task();

    if (Midi) {                      
      rcvd = Midi.RecvData(midi_buf, false);
      if (rcvd > 0) Serial.println("Got some USB midi data");

      if (rcvd > 0 && !(midi_buf[0] == 0 && midi_buf[1] == 0 && midi_buf[2] == 0)) {
        Serial.print(midi_buf[0], HEX); Serial.print(" ");
        Serial.print(midi_buf[1], HEX); Serial.print(" ");
        Serial.print(midi_buf[2], HEX); Serial.println();

      }
    }
  }
}
