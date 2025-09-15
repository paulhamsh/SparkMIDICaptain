// Dependencies:
// NimBLE-Arduino               1.4.3                        
// SSD1306 by Adafruit          2.5.14     
// ESP32 Dev Module board       3.2.0   
// Adafruit GFX                 1.12.1
// USB Host Shield Library 2.0  1.7.0                    https://yuuichiakagawa.github.io/USBH_MIDI/  and  https://github.com/felis/USB_Host_Shield_2.0

#define OLED_ON
#define USB_HOST
#define ESP_DEVKIT

//#define CLASSIC
//#define PSRAM

#include "SparkIO.h"
#include "Spark.h"
#include "Screen.h"
#include "MIDI.h"


void setup() {
  Serial.begin(115200);
  while (!Serial) {};

  delay(1000);

  splash_screen();
  setup_midi();

  Serial.println("Spark MIDI Captain");
  Serial.println("==================");

  spark_state_tracker_start();

  DEBUG("Starting");
}


void loop() {
  byte mi[3];
  int midi_chan, midi_cmd;
  bool onoff;
  

  if (update_spark_state()) {
    Serial.print("Got message ");
    Serial.println(cmdsub, HEX);
  }

  if (update_midi(mi)) {
    midi_chan = (mi[0] & 0x0f) + 1;
    midi_cmd = mi[0] & 0xf0;
    onoff = (mi[2] == 127 ? true : false);
    
    if (midi_cmd == 0xc0) { 
      switch (mi[1]) {
        case 0:              change_hardware_preset(0);                 break; // MIDI Captain 1A
        case 1:              change_hardware_preset(1);                 break; // MIDI Captain 1B
        case 2:              change_hardware_preset(2);                 break; // MIDI Captain 1C
        case 3:              change_hardware_preset(3);                 break; // MIDI Captain 1D
      }
    }

    // Other examples - need the correct midi code frrom MIDI Captain to get these working
    if (midi_cmd == 0xb0) {     
      switch (mi[1]) {
        case 1:              change_amp_param(AMP_GAIN, mi[2]/127.0);   break; // MIDI Captain        
        case 2:              change_amp_param(AMP_MASTER, mi[2]/127.0); break; // MIDI Captain 
        case 3:              change_drive_toggle();                     break; // MIDI Captain  
        case 4:              change_mod_toggle();                       break; // MIDI Captain      
        case 5:              change_delay_toggle();                     break; // MIDI Captain 
        case 6:              change_reverb_toggle();                    break; // MIDI Captain 
        case 7:              change_hardware_preset(0);                 break; // MIDI Captain 
        case 8:              change_hardware_preset(1);                 break; // MIDI Captain 
        case 9:              change_hardware_preset(2);                 break; // MIDI Captain 
        case 10:             change_hardware_preset(3);                 break; // MIDI Captain 
        case 11:             change_comp_onoff(onoff);                  break; // MIDI Captain 
        }
    }
  }
}
