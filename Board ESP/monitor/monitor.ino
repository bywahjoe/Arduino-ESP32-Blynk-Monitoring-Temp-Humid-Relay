/*----------------------
  Firmansyah Wahyu
  @2021
  https://github.com/bywahjoe/Arduino-ESP32-Blynk-Monitoring-Temp-Humid-Relay.git
------------------------*/

#include <WiFi.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#include "pinku.h"
#include <BlynkSimpleEsp32.h>

//Milis Setting
const long interval = 2000;
unsigned long before = 0;

float mySuhu = 0;
int myTanah = 0;

BlynkTimer ceknotif;
BlynkTimer mysensor;

LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(pin_suhu, type_suhu);

void notif() {
  Serial.print("Blynk is Notify");
  
  if (myTanah < 7) {
    Blynk.notify("Tanah Kering Menyiram");
    Serial.println("Tanah Kering:");
  } else {
    Serial.println("Tanah Basah:");
  }
}
void sendSensor() {

  if (myTanah < 7) {
    buzzON();
    Serial2.write("n");//ON
  }
  else {
    buzzOFF();
    Serial2.write("f");//OFF
  }

  Blynk.virtualWrite(2, mySuhu);
  Blynk.virtualWrite(3, myTanah);

}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial2.begin(115200);
  pinMode(buzz, OUTPUT);

  lcd.init();
  lcd.backlight();
  dht.begin();

  WiFi.begin(ssid, pass);

  String statusWifi = "Connected";
  int retry = 1;
  while (WiFi.status() != WL_CONNECTED) {

    lcd.setCursor(0, 0);
    lcd.print("Connecting WiFi");
    lcd.setCursor(1, 1);
    lcd.print(retry);

    if (retry > 100) {
      statusWifi = "Error";
      break;
    }
    else {
      retry++;
    }
    delay(500);
  }

  Blynk.begin(myblynk, ssid, pass);
  ceknotif.setInterval(7000L, notif);
  mysensor.setInterval(5000L, sendSensor);

}

void loop() {
  // put your main code here, to run repeatedly:
  mySuhu = getSuhu();
  myTanah = getTanah();

  unsigned long now = millis();
  if (now - before >= interval) {
    tampil(mySuhu, myTanah);
    before = now;
  }

  Blynk.run();
  mysensor.run();
  ceknotif.run();
}
void tampil(float mysuhu, int mysoil) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SUHU  : ");
  lcd.print(mysuhu);
  lcd.print((char)223);
  lcd.print("C");
  lcd.setCursor(0, 1);
  lcd.print("LEMBAB: ");
  lcd.print(mysoil);
  lcd.print("%");
}
void buzzON() {
  digitalWrite(buzz, HIGH);
}
void buzzOFF() {
  digitalWrite(buzz, LOW);
}
float getSuhu() {
  float val = dht.readTemperature();
  return val;
}
int getTanah() {
  //kering sakitik
  int val = analogRead(pin_tanah);
  Serial.print("Sensor Asli"); Serial.println(val);
  val = constrain(val, min_tanah, max_tanah);

  Serial.print("Constrain"); Serial.println(val);
  int convert = map(val, min_tanah, max_tanah, 0, 95);

  return (100 - convert);
}
