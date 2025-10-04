// Proves 18 receives ok
// Have both S3 running this sketch
// Link pin 17 on one to 18 on the other
// Watch serial monitor on the second one (with pin 18 in use)
// See this:
//      Test message Test message
// being slowly written out

unsigned long tim;
char msg[20] = "Test message ";
int msg_len;
int pos;

void setup() {
  Serial.begin(115200);
  //                               RX, TX
  Serial1.begin(31250, SERIAL_8N1, 18, 17);
  delay(1000);
  Serial.println("STARTED");
  tim = millis();

  msg_len = strlen(msg);
  pos = 0;
};

byte b;
void loop() {
  
  while (Serial1.available()) {
    b = Serial1.read();
    Serial.print(char(b));
  }

  if (millis() - tim > 200) {
    tim = millis();
    // Serial.println("TICK");
    Serial1.write(msg[pos]);
    pos++;
    if (pos >= msg_len) pos = 0;
  }
}
