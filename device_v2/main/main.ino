#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 2, 16);


int clk, clkReset, clkCycle;
void init_clk(int _clkCycle, int _clkReset) {
  if (_clkCycle < 0) {
    _clkCycle = 0;
  }
  if (_clkCycle > 1000) {
    _clkCycle = 1000;
  }
  clkCycle = _clkCycle;

  if (_clkReset < 1) {
    _clkReset = 1;
  }
  clkReset = _clkReset;
}
void cycleClk() {
  if (clk == clkReset) {
    clk = 1;
  } else {
    clk += 1;
  }
  delay(clkCycle);
}

void displayLcd(String msg, int row) {
  if (row >= 0 && row < 2) {
    lcd.setCursor(row, 0);
    lcd.clear();
    lcd.print(msg);
  }
}

void setup() {
  Serial.begin(115200);

  lcd.init();
  lcd.backlight();

  init_clk(1000, 4);
}

void loop() {
  if (clk == 2) {
    displayLcd("HELLO", 0);
  } else if (clk == 4) {
    displayLcd("BYE", 0);
  }
  Serial.println(clk);
  cycleClk();
}
