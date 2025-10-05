// Dependencies:
// NimBLE-Arduino               2.3.6                        
// SSD1306 by Adafruit          2.5.14     
// ESP32 Dev Module board       3.2.0   
// Adafruit GFX                 1.12.1
// USB Host Shield Library 2.0  1.7.0                    https://yuuichiakagawa.github.io/USBH_MIDI/  and  https://github.com/felis/USB_Host_Shield_2.0

//#define OLED_ON
//#define USB_HOST
#define USB_S3
#define ESP_DEVKIT
#define BLE_MIDI

//#define CLASSIC
//#define PSRAM

#include "SparkIO.h"
#include "Spark.h"
#include "Screen.h"
#include "MIDI.h"

int my_preset;

void setup() {
  Serial.begin(115200);
  while (!Serial) {};

  delay(1000);

  splash_screen();

  setup_midi();

  Serial.println("Spark MIDI Captain");
  Serial.println("==================");

  spark_state_tracker_start();

  show_connected();
  DEBUG("Starting");

  my_preset = 0;
}


void loop() {
  byte mi[3];
  int midi_chan, midi_cmd;
  bool onoff;
  char msg[20];
  
  
  if (update_midi(mi)) {
    midi_chan = (mi[0] & 0x0f) + 1;
    midi_cmd = mi[0] & 0xf0;
    onoff = (mi[2] == 127 ? true : false);

    if (midi_cmd == 0xb0) {     
      switch (mi[1]) {
        case 10:   change_amp_param(AMP_GAIN,   mi[2]/127.0); 
                   Serial.print("Change amp gain ");
                   Serial.print(mi[2]/127.0);
                   break;
        case 11:   change_amp_param(AMP_MASTER, mi[2]/127.0); 
                   Serial.print("Change amp master volume ");
                   Serial.print(mi[2]/127.0);
                   break;         
        case 20:   change_noisegate_toggle();  
                   Serial.print("Toggle noisegate");               
                   break;
        case 21:   change_comp_toggle();                      
                   Serial.println("Toggle comp");      
                   break;
        case 22:   change_drive_toggle();   
                   Serial.println("Toggle drive");                        
                   break;
        case 23:   change_mod_toggle();     
                   Serial.println("Toggle mod");                        
                   break;
        case 80:   change_delay_toggle();   
                   Serial.println("Toggle delay");                        
                   break; 
        case 81:   change_reverb_toggle();                    
                   Serial.println("Toggle reverb");      
                   break; 
        case 24:   my_preset++;
                   if (my_preset > max_preset) my_preset = 0;
                   change_hardware_preset(my_preset);
                   Serial.println("Preset up");
                   break; 
        case 84:   my_preset--;
                   if (my_preset < 0)  my_preset = max_preset;
                   change_hardware_preset(my_preset);
                   Serial.println("Preset down");
                   break;             
      }
    }

    // Update display
    #ifdef OLED_ON
    sprintf(msg, "%2x %3d %3d", mi[0], mi[1], mi[2]);
    show_message(msg, display_preset_num);
    #endif
  }

  if (update_spark_state()) {
    Serial.print("Got message ");
    Serial.println(cmdsub, HEX);
  }

}
