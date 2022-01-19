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
const int motionTrigger = 26;
const int motionEcho = 25;
// Motion SRF05
SRF05 motionSrf(motionTrigger, motionEcho);
const double motionCorrectionFactor = 1.035;
const int maxMotionDist = 8; // In centimeters

// Height SRF05 pins
const int heightTrigger = 5;
const int heightEcho = 18;
// Height SRF05
SRF05 heightSrf(heightTrigger, heightEcho);
const double heightCorrectionFactor = 1.035;

// Servo pins
const int servoPin = 13;
// Servo
Servo servo;
bool isLidOpen = false;
int pos = 0;

int count = 0;
int curDispIndex = 0;

void display(String title, double val, String unit)
{
  lcd.setCursor(0, 0);      // First row
  lcd.printf("%s:", title); // Label

  int roundedVal = (int)(val + 0.5); // Round distance to decimal point

  lcd.setCursor(0, 1);                                                            // Second row
  int lSpacing = lcdCols - floor(log10(abs(roundedVal) + 1)) - 2 - unit.length(); // Left spacing
  lcd.printf("%*s%d %s", lSpacing, " ", roundedVal, unit);                        // Value
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
  if ((count % 10) == 0)
  {
    curDispIndex += 1;
    if (curDispIndex > 1)
    {
      curDispIndex = 0;
    }
    lcd.clear();
  }

  if (curDispIndex == 0)
  {
    const double dist = heightSrf.getCentimeter();

    // Display height of rubbish inside the bin.
    display("Distance", dist, "cm");
  }
  else if (curDispIndex == 1)
  {
    double weight = scale.get_units() * -1000;
    if (weight < 1)
    {
      // Remove weight noises under 1 gram
      weight = 0;
    }

    // Display any object's weight into the LCD.
    display("Weight", weight, "gr");
  }

  // Controls lid: open or close it depending on the ultrasonic sensor.
  // If an object, such as a hand, is placed under 8 cm from the sensor,
  // The lid of the rubbish bin will open. Otherwise, it will close.
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
  count += 1;
  delay(500);
}