#include <Arduino.h>

#include <LiquidCrystal_I2C.h>
#include <HX711.h>
#include <SRF05.h>
#include <Servo.h>

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

// Motion SRF05 pins
const int motionTrigger = 5;
const int motionEcho = 18;
// Motion SRF05
SRF05 motionSrf(motionTrigger, motionEcho);
const double motionCorrectionFactor = 1.035;
const int maxMotionDist = 8; // In centimeters

// Height SRF05 pins
const int heightTrigger = 25;
const int heightEcho = 26;
// Height SRF05
SRF05 heightSrf(heightTrigger, heightEcho);
const double heightCorrectionFactor = 1.035;

// Servo pins
const int servoPin = 13;
// Servo
Servo servo;
bool isLidOpen = false;
int pos = 0;


// Display height of rubbish inside the bin.
void displayHeight()
{
  const double dist = heightSrf.getCentimeter();
  int roundedDist = (int)(dist + 0.5); // Round distance to decimal point

  lcd.setCursor(0, 0);     // First row
  lcd.printf("Distance:"); // Label

  lcd.setCursor(0, 1);                                             // Second row
  int lSpacing = lcdCols - 4 - floor(log10(abs(roundedDist) + 1)); // Left spacing
  lcd.printf("%*s%d cm", lSpacing, " ", roundedDist);              // Value
}

// Display any object's weight into the LCD.
void displayWeight()
{
  double weight = scale.get_units() * -1000;
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

// Controls lid: open or close it depending on the ultrasonic sensor.
// If an object, such as a hand, is placed under 8 cm from the sensor,
// The lid of the rubbish bin will open. Otherwise, it will close.
void lidController()
{
  const bool ok = (motionSrf.getCentimeter() <= maxMotionDist);
  if (ok)
  {
    if (!isLidOpen)
    {
      for (; pos <= 180; pos += 1)
      {
        servo.write(pos);
        delay(3);
      }
      isLidOpen = true;
    }
  }
  else
  {
    if (isLidOpen)
    {
      delay(1500);
      for (; pos >= 0; pos -= 1)
      {
        servo.write(pos);
        delay(3);
      }
      isLidOpen = false;
    }
  }
}

// Entry point
void setup()
{
  Serial.begin(115200);

  // Setup LCD
  lcd.init();      // initialize LCD
  lcd.backlight(); // turn on LCD backlight

  // Load cell setup
  scale.begin(dout, clk);
  scale.set_scale(calibrationFactor);
  scale.tare();

  // Setup ultrasonic
  motionSrf.setCorrectionFactor(motionCorrectionFactor);
  heightSrf.setCorrectionFactor(heightCorrectionFactor);

  // Setup servo
  servo.attach(servoPin);
}

// Body
void loop()
{
  displayHeight();
  displayWeight();
  lidController();
}