/*----------------------
  Firmansyah Wahyu
  @2021
  https://github.com/bywahjoe/Arduino-ESP32-Blynk-Monitoring-Temp-Humid-Relay.git
  ------------------------*/

#include <SoftwareSerial.h>
#define relay 7

SoftwareSerial mySerial(8, 9);//rx tx

void setup() {
  Serial.begin(115200);
  mySerial.begin(115200);
  pinMode(relay, OUTPUT);
}
void loop() {
  char recv;
  if (mySerial.available()) {
    recv = mySerial.read();
    Serial.println(recv);
    if (recv == 'n') pompaON();
    else if (recv == 'f')pompaOFF();
    else {}
    
  } else {

  }
  //  pompaON();
  //  delay(4000);
  //  pompaOFF();
  //  delay(2000);
}
void pompaON() {
  Serial.println("RELAY IS ON");
  digitalWrite(relay, HIGH);
}
void pompaOFF() {
  Serial.println("RELAY IS OFF");
  digitalWrite(relay, LOW);
}
