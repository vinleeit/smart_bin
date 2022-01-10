#include <Arduino.h>

#include <LiquidCrystal_I2C.h>
#include <HX711.h>

// Set LCD columns and rows
const int lcdCols = 16;
const int lcdRows = 2;
// Set LCD address
LiquidCrystal_I2C lcd(0x27, lcdCols, lcdRows);

// HX711 pins
const int dout = 33;
const int clk = 32;
// HX711
HX711 scale;
const float calibrationFactor = -206650; // Adjusted accordingly

void setupLCD()
{
  lcd.init();      // initialize LCD
  lcd.backlight(); // turn on LCD backlight
}

void setupLoadCell()
{
  scale.begin(dout, clk);
  scale.set_scale(calibrationFactor);
  scale.tare();
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

// Get the weight of any object rested on top of the load cell.
double getWeight()
{
  return scale.get_units() * -1000;
}

// Display any object's weight into the LCD. The weight is obtained from
// the [getWeight] function.
void displayWeight()
{
  double weight = getWeight();
  if (weight < 1)
  {
    // Remove weight noises under 1 gram
    weight = 0;
  }
  int roundedWeight = (int)(weight + 0.5); // Round weight to decimal point

  lcd.setCursor(0, 0);   // First row
  lcd.printf("Weight:"); // Label

  lcd.setCursor(0, 1);                                               // Second row
  int lSpacing = lcdCols - 4 - floor(log10(abs(roundedWeight) + 1)); // Left spacing
  lcd.printf("%*s%d gr", lSpacing, " ", roundedWeight);              // Value
}

void setup()
{
  Serial.begin(115200);
  setupLCD();
  setupLoadCell();
}

void loop()
{
  // displayCapacity(0.1);
  displayWeight();
}