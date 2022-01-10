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

// SRF05 pins
const int trigger = 5;
const int echo = 18;
// SRF05
SRF05 srf(trigger, echo);

// Servo pins
const int servoPin = 13;
// Servo
Servo servo;

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

void setupUltrasonic()
{
  srf.setCorrectionFactor(1.035);
}

void setupServo()
{
  servo.attach(servoPin);
}

// Get the distance measured from ultrasonic sensor.
double getDist()
{
  return srf.getCentimeter();
}

// Display distance into the LCD. The distance is obtained from the [getDist] function.
void displayDist()
{
  double dist = getDist();
  int roundedDist = (int)(dist + 0.5); // Round distance to decimal point

  lcd.setCursor(0, 0);     // First row
  lcd.printf("Distance:"); // Label

  lcd.setCursor(0, 1);                                             // Second row
  int lSpacing = lcdCols - 4 - floor(log10(abs(roundedDist) + 1)); // Left spacing
  lcd.printf("%*s%d cm", lSpacing, " ", roundedDist);              // Value
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

// Used to move servo hand
void moveServo()
{
  for (int pos = 0; pos <= 180; pos += 1)
  {
    servo.write(pos);
    delay(5);
  }
  for (int pos = 180; pos >= 0; pos -= 1)
  {
    servo.write(pos);
    delay(5);
  }
}

void setup()
{
  Serial.begin(115200);
  setupLCD();
  setupLoadCell();
  setupUltrasonic();
  setupServo();
}

void loop()
{
  // displayDist();
  // displayWeight();
  moveServo();
}