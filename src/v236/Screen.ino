#include "Screen.h"

void splash_screen() {
  Wire.begin(OLED_SDA, OLED_SCL);  // set my SDA, SCL

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println("SSD1306 allocation failed");
    while (true); 
  }

  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.setCursor(40, 10);
  display.print("MIDI");
  display.setCursor(20, 40);
  display.print("CAPTAIN");
  display.display();
}
