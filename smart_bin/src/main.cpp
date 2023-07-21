#include <Arduino.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <HX711.h>
#include <LiquidCrystal_I2C.h>
#include <SRF05.h>
#include <Servo.h>
#include <WiFi.h>

LiquidCrystal_I2C lcd(0x27, 2, 16);  // (address, columns, rows)
Servo servo;                         // (PWM)
HX711 scale;                         // (dout, sck)
SRF05 srfMotion(32, 35);             // (trigger, echo)
SRF05 srfCapacity(33, 34);           // (trigger, echo)

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

const String ssid = "smart_bin", password = "smart_bin123", baseUrl = "http://localhost:8080/api/device";
int sendData(String data, String endpoint) {
  HTTPClient client;

  client.setTimeout(2500);
  client.begin(baseUrl + endpoint);
  client.addHeader("Content-Type", "application/json");
  int result = client.POST(data);
  client.end();
  return result;
}
int sendCapacity(float heightFactor) {
  DynamicJsonDocument data(1024);
  String json;

  data["serial"] = "esp32a";
  data["heightFactor"] = heightFactor;
  serializeJson(data, json);
  sendData(json, "/");
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
int lidCountdown = 200;
void updateLid() {
  float distMotion = srfMotion.getCentimeter();
  if (distMotion < 10) {
    if (lidStatus == closed) {
      lidStatus = opening;
    } else if (lidStatus == closing) {
      lidStatus = opening;
    }
    lidCountdown = 200;
  } else {
    if (lidStatus == opened && lidCountdown == 0) {
      lidStatus = closing;
    }
  }

  if (lidStatus == opened && lidCountdown > 0) {
    lidCountdown--;
  }

  if (lidStatus == opening) {
    lidPosition += 5;
    if (lidPosition == 180) {
      lidStatus = opened;
    }
  } else if (lidStatus == closing) {
    lidPosition -= 5;
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
  srfCapacity.setCorrectionFactor(1.035);

  scale.begin(2, 4);
  scale.set_scale(-390.278);
  scale.tare();

  servo.attach(25);
  servo.write(0);

  init_clk(10, 400);
}

void findCalibrationFactor() {
  if (scale.is_ready()) {
    scale.set_scale();
    Serial.println("Tare... remove any weights from the scale.");
    delay(2000);
    scale.tare();
    Serial.println("Tare done...");
    Serial.print("Place a known weight on the scale...");
    delay(2000);
    long reading = scale.get_units(10);
    Serial.print("Result: ");
    Serial.println(reading);
  } else {
    Serial.println("HX711 not found.");
  }
  delay(1000);
}

void loop() {
  if (clk == 200) {
    displayLcd("HELLO", 0);
  } else if (clk == 400) {
    displayLcd("BYE", 0);
  }

  if (clk % 20 == 0) {
    if (clk >= 200 && clk < 400) {
      displayLcd("Cap[h]: " + String(srfCapacity.getCentimeter(), 0) + "cm", 1);
    } else if (clk == 400 || (clk >= 0 && clk < 200)) {
      float cap = scale.get_units(10);
      if (cap < 0) {
        cap = 0;
      }
      displayLcd("Cap[w]: " + String(cap, 0) + "g", 1);
    }
  }

  updateLid();
  cycleClk();
}
