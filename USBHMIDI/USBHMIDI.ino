#include "MIDI.h"

unsigned long tim;


void setup()
{
  Serial.begin(115200);
  midi_setup();
  tim = millis();
}



void loop()
{
  midi_loop();

  if (millis() - tim > 1000) {
    Serial.println("ALIVE");
    tim = millis();
  }

  if (isMidiData) {
    Serial.println("MIDI DATA: ");
    Serial.print(midi_data[0], HEX);
    Serial.print(" ");
    Serial.print(midi_data[1], HEX);
    Serial.print(" ");
    Serial.print(midi_data[2]);
    Serial.print(" ");
    Serial.println(midi_data[3]);
    isMidiData = false;
  }

}