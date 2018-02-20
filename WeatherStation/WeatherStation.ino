#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Adafruit_BMP085.h>

#define DHTPIN 12
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27,20,4);
Adafruit_BMP085 bmp;
uint8_t degree[8] = {0x8,0xf4,0x8,0x43,0x4,0x4,0x43,0x0};
uint8_t sunny[8]  = {0x0,0x4,0x15,0xe,0x1b,0xe,0x15,0x4};
uint8_t cloudy[8] = {0xc,0x1e,0x0,0x6,0xf,0x0,0xc,0x1e};
uint8_t rainy[8]  = {0xc,0x1e,0xa,0x5,0x0,0x6,0xf,0x5};
char weather = 0;
char celsius = 0;
int dec = 1;

void setup() {
   Serial.begin(9600);
  dht.begin();
  if (!bmp.begin())  Serial.println("Could not find a valid BMP085 sensor, check wiring!");
  lcd.init();
  lcd.backlight();
  lcd.createChar(0, degree);
  lcd.createChar(1, sunny);
  lcd.createChar(2, cloudy);
  lcd.createChar(3, rainy);
}

void loop() {
  float t = dht.readTemperature(); 
  float t2 = bmp.readTemperature();
  float h = dht.readHumidity();
  float p = bmp.readPressure();
  float hpa = p/100.0;
  
  if(hpa<1000.0) weather = 3;
  if(hpa>=1000.0 && hpa<1020.0) weather = 2;
  if(hpa>=1020.0) weather = 1;
  
  //Serial.println(bmp.readAltitude());

  lcd.setCursor(0,0);
  lcd.print("T:");
  lcd.print(t2,2);
  lcd.print(celsius);
  
  lcd.print(" T:");
  lcd.print(t,0);
  lcd.print(celsius);
  lcd.print(" ");
  lcd.print(weather);

  if(hpa<1000.0) dec = 2;
  lcd.setCursor(0,1);
  lcd.print("P:");
  lcd.print(hpa,dec);

  lcd.print(" H:");
  lcd.print(h,0);
  lcd.print("% ");
  lcd.print(weather);
  
  delay (1000);
}
