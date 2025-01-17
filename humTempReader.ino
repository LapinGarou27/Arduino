#include <LiquidCrystal.h>  // Inclure la bibliothèque pour l'écran LCD
#include <DHT.h>  


#define DHTPIN 12         
#define DHTTYPE DHT11    
DHT dht(DHTPIN, DHTTYPE); 

LiquidCrystal lcd(12, 11, 10, 9, 8, 7, 6, 5, 4, 3); 

void setup() {
  lcd.begin(16, 2);      
  dht.begin();
}

void loop() {
  // create on the second line two information, One is ambien tempreature, the other is ambien Humidity
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.println(" degC");  
  lcd.setCursor(0, 1);
  lcd.print("Hum: ");
  lcd.print(humidity);  
  lcd.print(" %");
  delay(2000);
}