/*----------------------
  Firmansyah Wahyu
  @2021
  https://github.com/bywahjoe/Arduino-ESP32-Blynk-Monitoring-Temp-Humid-Relay.git
  ------------------------*/

#include <SoftwareSerial.h>
#define relay 7

//Waktu Siram
int banyak = 25000;
int sedang = 20000;
int dikit = 15000;

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
    if (recv == 'b') {
      pompaON(); delay(banyak);}
    else if (recv == 's') {
      pompaON();delay(sedang);    }
    else if (recv == 'd') {
      pompaON();delay(dikit);}
    else if (recv == 't') {pompaOFF();}
    else {}
    pompaOFF();
    mySerial.begin(115200);
  } else {}
}
void pompaON() {
  Serial.println("RELAY IS ON");
  digitalWrite(relay, HIGH);
}
void pompaOFF() {
  Serial.println("RELAY IS OFF");
  digitalWrite(relay, LOW);
}
