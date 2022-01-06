#include <Arduino.h>

#include <LiquidCrystal_I2C.h>

// Set LCD columns and rows
const int lcdCols = 16;
const int lcdRows = 2;

// Set LCD address
LiquidCrystal_I2C lcd(0x27, lcdCols, lcdRows);

void setupLCD()
{
  lcd.init();      // initialize LCD
  lcd.backlight(); // turn on LCD backlight
}

// Display dust bin capacity on LCD
void displayCapacity(double value)
{
  int val = (int)(value * 100);
  int lpad = (int)(value * 14);
  int rpad = 14 - lpad;

  lcd.setCursor(0, 0);               // First row
  lcd.printf("Capacity: %d%%", val); // Value (percentage)

  lcd.setCursor(0, 1);                                       // Second row
  lcd.printf("[%.*s%*s]", lpad, "||||||||||||||", rpad, ""); // Progress bar
}

void setup()
{
  setupLCD(); // Setup LCD
}

void loop()
{
  displayCapacity(0.1); // Display capacity on LCD
}