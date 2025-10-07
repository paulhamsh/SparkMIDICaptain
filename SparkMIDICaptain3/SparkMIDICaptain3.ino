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


char *amps[]{"Twin","94MatchDCV2","RolandJC120","Bassman","AC Boost","AmericanHighGain","SLO100","YJM100","OrangeAD30","BE101","EVH","Rectifier","ADClean","Bogner","W600"};
int num_amps;
int my_amp;

char *mods[]{"Cloner","Flanger","ChorusAnalog","UniVibe","Tremolator","Tremolo","Phaser","UniVibe"};
int num_mods;
int my_mod;


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

  num_amps = sizeof(amps) / sizeof(char *);
  my_amp = 0;
  Serial.print("Number of amps in list ");
  Serial.println(num_amps);

  num_mods = sizeof(mods) / sizeof(char *);
  my_mod = 0;
  Serial.print("Number of mods in list ");
  Serial.println(num_mods);
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
                   Serial.println(mi[2]/127.0);
                   break;
        case 11:   change_amp_param(AMP_MASTER, mi[2]/127.0); 
                   Serial.print("Change amp master volume ");
                   Serial.println(mi[2]/127.0);
                   break;         
        case 20:   change_noisegate_toggle();  
                   Serial.println("Toggle noisegate");               
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
        case 82:   my_amp++;
                   if (my_amp >= num_amps)  my_amp = 0;
                   change_amp_model(amps[my_amp]);
                   Serial.print("Change amp model to ");
                   Serial.println(amps[my_amp]);
                   break; 
        case 83:   my_mod++;
                   if (my_mod >= num_mods)  my_mod = 0;
                   change_mod_model(mods[my_mod]);
                   Serial.print("Change mod model to ");
                   Serial.println(mods[my_mod]);
                   break; 
      }
    }

    if (midi_cmd == 0x80) {     
      switch (mi[1]) {
        case 57:   change_noisegate_toggle();  
                   Serial.println("Toggle noisegate");               
                   break;
        case 59:   change_comp_toggle();                      
                   Serial.println("Toggle comp");      
                   break;
        case 60:   change_drive_toggle();   
                   Serial.println("Toggle drive");                        
                   break;
        case 62:   change_mod_toggle();     
                   Serial.println("Toggle mod");                        
                   break;
        case 64:   change_delay_toggle();   
                   Serial.println("Toggle delay");                        
                   break; 
        case 65:   change_reverb_toggle();                    
                   Serial.println("Toggle reverb");      
                   break; 
        case 67:   my_preset++;
                   if (my_preset > max_preset) my_preset = 0;
                   change_hardware_preset(my_preset);
                   Serial.println("Preset up");
                   break; 
        case 69:   my_preset--;
                   if (my_preset < 0)  my_preset = max_preset;
                   change_hardware_preset(my_preset);
                   Serial.println("Preset down");
                   break;        
        case 71:   my_amp++;
                   if (my_amp >= num_amps)  my_amp = 0;
                   change_amp_model(amps[my_amp]);
                   Serial.print("Change amp model to ");
                   Serial.println(amps[my_amp]);
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
