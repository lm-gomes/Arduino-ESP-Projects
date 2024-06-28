#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>

#define sinal 52

OneWire oneWire(sinal);
DallasTemperature sensors(&oneWire);
LiquidCrystal_I2C lcd(0x27, 20, 4);

float temperature = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  sensors.begin();

  lcd.init();
  lcd.backlight();
  lcd.clear();

}

void loop() {
  // put your main code here, to run repeatedly:
  sensors.requestTemperatures();
  Serial.print("A temperatura é: ");
  temperature = sensors.getTempCByIndex(0);

  lcd.setCursor(0, 0);
  lcd.print("Temperatura");
  lcd.setCursor(0, 1);
  lcd.print("ambiente:");
  lcd.setCursor(0, 2);
  lcd.print(temperature);
  lcd.setCursor(6, 2);
  lcd.print("C");
  
}
