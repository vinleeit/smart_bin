#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <SRF05.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 2, 16);
Servo servo;
SRF05 srfMotion(32, 35);

enum LidStatus {
  closed,
  closing,
  opening,
  opened
};

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
    lcd.setCursor(0, row);
    lcd.printf("%16s", " ");
    lcd.setCursor(0, row);
    lcd.print(msg);
  }
}


int lidPosition = 0;
LidStatus lidStatus = closed;
int lidCountdown = 500;
void updateLid() {
  float distMotion = srfMotion.getCentimeter();
  if (distMotion < 10) {
    if (lidStatus == closed) {
      lidStatus = opening;
    } else if (lidStatus == closing) {
      lidStatus = opening;
    }
    lidCountdown = 300;
  } else {
    if (lidStatus == opened && lidCountdown == 0) {
      lidStatus = closing;
    }
  }

  if (lidStatus == opened && lidCountdown > 0) {
    lidCountdown--;
  }

  if (lidStatus == opening) {
    lidPosition++;
    if (lidPosition == 180) {
      lidStatus = opened;
    }
  } else if (lidStatus == closing) {
    lidPosition--;
    if (lidPosition == 0) {
      lidStatus = closed;
    }
  }
  servo.write(lidPosition);
}

void setup() {
  Serial.begin(115200);

  lcd.init();
  lcd.backlight();

  srfMotion.setCorrectionFactor(1.035);

  servo.attach(33);
  servo.write(0);

  init_clk(10, 400);
}


void loop() {
  if (clk == 200) {
    displayLcd("HELLO", 0);
  } else if (clk == 400) {
    displayLcd("BYE", 0);
  }

  updateLid();
  cycleClk();
  // for (int i = 0; i < 180; i++) {
  //   servo.write(i);
  //   delay(5);
  // }
  // for (int i = 180; i >= 0; i--) {
  //   servo.write(i);
  //   delay(5);
  // }
}
