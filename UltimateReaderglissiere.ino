#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <RTClib.h>

RTC_DS1307 rtc;
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define DHTPIN 2       
#define DHTTYPE DHT11  
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // initialize the lcd it's black light
  lcd.init();
  lcd.backlight();
  dht.begin();
  Intro();
  lcd.clear();
  rtc.begin();
  rtc.adjust(DateTime(2024, 12, 31, 2, 35, 00));
}

void loop() {
  Time();
  TempHum();
}

// Create a real time customizable on the first line
void Time(){
  DateTime now = rtc.now();
  lcd.setCursor(0, 0);
  lcd.print("Time: ");

  int heureLocale = now.hour(); 
  if (heureLocale > 23) {
    heureLocale = 0;  
  }
  lcd.print(heureLocale);
  lcd.print(":");
  if (now.minute() < 10) lcd.print("0");
  lcd.print(now.minute(), DEC);
  lcd.print(":");
  if (now.second() < 10) lcd.print("0");
  lcd.print(now.second(), DEC);
  delay(100);
}

// Create on second line a moving information or on ambient temperature or on ambient humidity
void TempHum() {
  float temp = dht.readTemperature();
  float Hum = dht.readHumidity();
  String msgT = "Temp: " + String(temp, 2) + "C";
  String msgH = "Hum: " + String(Hum, 2) + "%";

  for (int i = 16; i >= 0; i--) { //entry right to left Temp
    Time();
    lcd.clear();
    lcd.setCursor(i, 1);
    lcd.print(msgT);
    delay(50);
  }
  Time();
  delay(2000);
  for (int i = 0; i >= -16; i--) { //Out from right to left Temp
    Time();
    lcd.clear();
    lcd.setCursor(i, 1);
    lcd.print(msgT);
    delay(50);
  }
  for (int j = 16; j >= 0; j--) { //Entry from right to left Hum
    Time();
    lcd.clear();
    lcd.setCursor(j, 1);
    lcd.print(msgH);
    delay(50);
  }
  Time();
  delay(2000);
  for (int k = 0; k >= -16; k--) { //Out from right to left Hum
    Time();
    lcd.clear();
    lcd.setCursor(k, 1);
    lcd.print(msgH);
    delay(50);
  }
}

void Intro() {
  String msg1 = "Read of Temp&Hum";
  String msg2 = "Made by LG";

  for (int i = 16; i >= 0; i--) {
    lcd.clear();
    lcd.setCursor(i, 0);
    lcd.print(msg1);
    delay(50);
  }
  delay(1000);
  for (int j = 16; j >= 0 ; j--) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(msg1);
    lcd.setCursor(j, 1); 
    lcd.print(msg2);
    delay(50);
  }
  delay(3000);
  }
