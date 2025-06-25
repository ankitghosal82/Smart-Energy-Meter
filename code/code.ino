/* Fill-in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID           "TMPL3iAUVxal2"
#define BLYNK_TEMPLATE_NAME         "smart energy meter"
#define BLYNK_AUTH_TOKEN            "x_8PKdO5zUyc3bff_9BqMHnWv46Wz4Vo"
// #define BLYNK_TEMPLATE_ID "TMPL35SdbMEc4"
// #define BLYNK_TEMPLATE_NAME "IOT Smart Energy Meter"
// #define BLYNK_AUTH_TOKEN "ZJnfoF9cW5yGR0CDGumbyoaaOVZ_3Hb7"

/* Comment this out to disable prints and save space */ 
#define BLYNK_PRINT Serial

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#include <movingAvg.h> 

#include "EnergyCalc.h"

BlynkTimer timer; 

movingAvg avgV(5);
movingAvg avgI(5);
movingAvg avgP(5);

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Sudev";
char pass[] = "wwaces2004";
// char ssid[] = "DryIce";
// char pass[] = "NoRandomCharacters";

double voltage, current, power, energy = 0, avgVoltage, avgCurrent, avgPower;

void serialprint() {
  Serial.print(realPower);
  Serial.print(' ');
  Serial.print(apparentPower);
  Serial.print(' ');
  Serial.print(Vrms);
  Serial.print(' ');
  Serial.print(Irms);
  Serial.print(' ');
  Serial.print(powerFactor);
  Serial.print('\t');
  Serial.print(avgPower);
  Serial.print(' ');
  Serial.print(avgVoltage);
  Serial.print(' ');
  Serial.print(avgCurrent);
  Serial.print(' ');
  Serial.print(energy);
  Serial.print(' ');

  Serial.println();
  delay(100);
}

void updateBlynkValue() {
  if(voltage < 50) {
    avgVoltage = 0;
    avgPower = 0;
  }
  if(avgPower < 8) {
    avgPower = 0;
  }
  Blynk.virtualWrite(V0, avgVoltage);
  Blynk.virtualWrite(V1, avgCurrent/1000.0); //avgPower == 0 ? 0 : avgPower / avgVoltage);
  Blynk.virtualWrite(V2, avgPower);
  Blynk.virtualWrite(V3, energy);
}
void printToLCD() {
  lcd.setCursor(0, 0);
  if(voltage < 10) lcd.print("00");
  else if(voltage < 100) lcd.print("0");
  lcd.print(voltage, 2);
  lcd.print("V  ");

  lcd.setCursor(8, 0);
  lcd.print(current, 3);
  lcd.print(" A ");

  lcd.setCursor(0, 1);
  if(avgPower < 10) lcd.print("00");
  else if(avgPower < 100) lcd.print("0");
  lcd.print(avgPower, 2);
  lcd.print("W  ");

  lcd.setCursor(8, 1);
  if(avgPower < 10) lcd.print("0");
  lcd.print(energy / 1000.0, 5);
  lcd.print("U   ");
}

void setup() {  
  Serial.begin(9600);
  
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("WiFi Not"); 
  lcd.setCursor(0, 1);
  lcd.print("Connected");

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  avgV.begin();
  avgI.begin();
  avgP.begin();

  timer.setInterval(1000L, updateBlynkValue);
  timer.setInterval(2000L, printToLCD);
}

void loop() {
  Blynk.run();
  timer.run();
  calcVI(20,2000);         // Calculate all. No.of half wavelengths (_crossings), time-out
  serialprint();           // Print out all variables (realpower, apparent power, Vrms, Irms, power factor)

  power      = realPower;        //extract Real Power into variable
  voltage    = Vrms;             //extract Vrms into Variable
  current    = Irms;             //extract Irms into Variable

  avgVoltage = avgV.reading(voltage);
  avgCurrent = avgI.reading(current * 1000.0);
  avgPower   = avgP.reading(abs(power));
 
  if(voltage < 50) {
    current = 0;
    voltage = 0;
    power   = 0;
  }
  if(avgPower < 8 ) {
    power = 0;
  }
  
  unsigned long currentTime = millis();
  if (lastTime > 0) {
    double timeInterval = ((currentTime - lastTime) / 3600000.0);   // 3600000ms in an hour
    energy += abs(power) * timeInterval;
  }
  lastTime = currentTime;
}