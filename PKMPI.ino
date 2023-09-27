#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h> //WIFI HARUS ON
#include <BlynkSimpleEsp8266.h>

#define BLYNK_TEMPLATE_ID "TMPL6LDzOd0GO"
#define BLYNK_TEMPLATE_NAME "CONTROLLER"
#define BLYNK_AUTH_TOKEN "dNiuTk5rYhJ_MZfBepVypLb-XgSIO6x-"

char auth[] = "dNiuTk5rYhJ_MZfBepVypLb-XgSIO6x-";
char ssid[] = "BOGOR PRIDE";
char pass[] = "mylord1010";

// char ssid[] = "MaCha PKM";
// char pass[] = "bismillahpimnasyaallah";

BlynkTimer timer;

int thermoDO = 4;
int thermoCS = 5;
int thermoCLK = 6;

#define thermoDO D4
#define thermoCS D5
#define thermoCLK D6
#include "max6675.h"
MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

#define relay1 D0
#define relay2 D1
#define relay3 D2
#define relay4 D3

// #define linearup D7
// #define lineardown D8

BLYNK_WRITE(V7){
  bool value4 = param.asInt();
  if(value4 == 1){
    digitalWrite(D7, HIGH);
  }else{
    digitalWrite(D7, LOW);
  }
}

BLYNK_WRITE(V9){
  bool value5 = param.asInt();
  if(value5 == 1){
    digitalWrite(D8, HIGH);
  }else{
    digitalWrite(D8, LOW);
  }
}

BLYNK_WRITE(V4){
  bool value2 = param.asInt();
  if(value2 == 1){
    relayHotWater();
    ledBlynkV2On();
  }else{
    relayHotWaterOff();
    ledBlynkV2Off();
  }
}

BLYNK_WRITE(V8){
  bool value3 = param.asInt();
  if(value3 == 1){
    mixerOn();
    ledBlynkV3On();
  }else{
    mixerOff();
    ledBlynkV3Off();
  }
}

BLYNK_WRITE(V0){
  bool value1 = param.asInt();
  if(value1 == 1){
    Serial.print("Test");
    // relayAirKranOn();
    // blynkOn();
    // ledBlynkV5On();
    // delay(3000);
    // relayAirKranOff();
    // blynkOff();
    // ledBlynkV5Off();
    Serial.print("Test2");
    // relayHeaterOn();
    // blynkOn();
    // Blynk.logEvent("suhu", "Air sedang dipanaskan. Hindari Kontak Langsung, Benda PANAS");
    // ledBlynkV6On();
    // mixerOn();
    // ledBlynkV3On();
    Serial.print("Test3");
    // blynkOn();
    // ledBlynkV3On();
  }else{
    Serial.print("Test4");
    //heateroff
    // mixerOff();
    // blynkOff();
    // ledBlynkV3Off();
  }
}
//=======================================

//=======================================
//Valve Air Panas
void relayHotWater(){
  digitalWrite(relay3, HIGH);
}
void relayHotWaterOff(){
  digitalWrite(relay3, LOW);
}
//=======================================
// Water Heater
void relayHeaterOn(){
  digitalWrite(relay2, HIGH);
}
void relayHeaterOff(){
  digitalWrite(relay2, LOW);
}
//=======================================
// Valve Sambungan Kran Air ( Dingin )
void relayAirKranOn(){
  digitalWrite(relay1, HIGH);
}
void relayAirKranOff(){
  digitalWrite(relay1, LOW);
}
//=======================================
// Koneksi Button Blynk
void blynkOn(){
  Blynk.virtualWrite(V0, HIGH);
}
void blynkOff(){
  Blynk.virtualWrite(V0, LOW);
}
//=======================================
// Mesin Mixer
void mixerOn(){
  digitalWrite(relay4, HIGH);
}
void mixerOff(){
  digitalWrite(relay4, LOW);
}
//=======================================
// Indikator LED Blynk V5
void ledBlynkV5On(){
  Blynk.virtualWrite(V5, HIGH);
}
void ledBlynkV5Off(){
  Blynk.virtualWrite(V5, LOW);
}
//=======================================
// Indikator LED Blynk V6
void ledBlynkV6On(){
  Blynk.virtualWrite(V6, HIGH);
}
void ledBlynkV6Off(){
  Blynk.virtualWrite(V6, LOW);
}
//=======================================
// Indikator LED Blynk V7
void ledBlynkV2On(){
  Blynk.virtualWrite(V2, HIGH);
}
void ledBlynkV2Off(){
  Blynk.virtualWrite(V2, LOW);
}
//=======================================
// Indikator LED Blynk V9
void ledBlynkV3On(){
  Blynk.virtualWrite(V3, HIGH);
}
void ledBlynkV3Off(){
  Blynk.virtualWrite(V3, LOW);
}
//=======================================
// // Linear UP
// void linearUp(){
//   digitalWrite(D7, HIGH);
// }
// // Linear Down
// void linearDown(){
//   digitalWrite(D8, HIGH);
// }
//=======================================
void setup() {
  // put your setup code here, to run once:
  timer.setInterval(2500L, sendSensor);
  Serial.begin(115200);
  pinMode(relay1, OUTPUT);
  pinMode (relay2, OUTPUT);
  pinMode (relay3, OUTPUT);
  pinMode (relay4, OUTPUT);
  pinMode (D7, OUTPUT);
  pinMode (D8, OUTPUT);
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
}

void loop() {
  // BLYNK_WRITE(V0);
  // Serial.print("C = ");
  // float s = thermocouple.readCelsius();
  // Serial.println(thermocouple.readCelsius());
  // if(thermocouple.readCelsius() > 80.00){
  //   relayHeaterOff();
  //   Blynk.logEvent("suhu", "AIR telah PANAS. Silahkan salurkan AIR PANAS ke wadah MIXER. Tekan OPEN");
  //   ledBlynkV5Off();
  //   ledBlynkV6Off();
  // }
  // else{
  //   relayHeaterOn();
  //   ledBlynkV6On();
  // }

  // Serial.print("F = ");// sebenarnya F tidak terlalu dibutuhkan karena sudah ada C
  // Serial.println(thermocouple.readFahrenheit());
  // delay(1000);

  Blynk.run();
  timer.run();
}

void sendSensor(){//syntax pengiriman value sensor
  float s = thermocouple.readCelsius();
  if(isnan(s)){
    Serial.println("FAILED");
    return;
  }
  Blynk.virtualWrite(V1, s);
}
