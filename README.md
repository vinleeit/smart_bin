# Smart Rubbish Bin

## Members

- Almada Putra

- Arvin Lee

- Gadtardi Wongkaren

- Jeconiah Richard

## Background

\-

## Features

- Open lid contactless

- Scan rubbish bin capacity/fullness (weight and height)

- Display useful information on LCD

### Future Improvements

- Temperature and humidity monitor

- Flame detection

- Air quality & hazardous gas detection (supposed to be odor sensor)

## Components and Supplies

### Main

| Components                          | Quantity |
| ----------------------------------- | -------- |
| ESP32 Esspresif WRoom               | 1        |
| MG90S micro-servo motor             | 1        |
| Ultrasonic sensor - SRF05           | 2        |
| Load cell weight seonsor with frame | 1        |
| LCD with I2C                        | 1        |
| Rubbish bin + lid                   | 1        |
| Jumper wires                        | DEPENDS  |

### Additional (Optional)

| Components                             | Quantity |
| -------------------------------------- | -------- |
| Real-time clock module - DS3231/ZS-042 | 1        |
| Buzzer                                 | 1        |
| RGB Led                                | 1        |
| Temperature & humidity sensor          | 1        |
| Flame sensor module                    | 1        |
| Gas sensor - MQ-135                    | 1        |

### Power (Optional)

| Components                 | Quantity |
| -------------------------- | -------- |
| Battery holder with 2 slot | 1        |
| AAA batteries              | 2        |

| Components      | Quantity |
| --------------- | -------- |
| 9V battery      | 1        |
| 9V battery clip | 1        |
| Switch          | 1        |

## Libraries

| Title              | Creator                       | Version | Github Link                                                                        |
| ------------------ | ----------------------------- | ------- | ---------------------------------------------------------------------------------- |
| LiquidCrystal\_I2C | macroschwartz \[johnrickman\] | 1.1.4   | [/johnrickman/LiquidCrystal_I2C](https://github.com/johnrickman/LiquidCrystal_I2C) |
| HX711              | bodge                         | 0.7.5   | [/bodge/HX711](https://github.com/bogde/HX711)                                     |
| SRF05              | robtillaart                   | 0.1.2   | [/RobTillaart/SRF05](https://github.com/RobTillaart/SRF05)                         |
| ServoESP32         | roboticsbrno                  | 1.0.3   | [/RoboticsBrno/ServoESP32](https://github.com/RoboticsBrno/ServoESP32)             |

## Ports

| Port   | Usage      | Name    |
| ------ | ---------- | ------- |
| GPIO18 | Ultrasonic | echo    |
| GPIO05 | Ultrasonic | trigger |
| GPIO21 | LCD        | sda     |
| GPIO22 | LCD        | slc     |
| GPIO33 | Load Cell  | dout    |
| GPIO32 | Load Cell  | clk     |

## Useful Links

- https://create.arduino.cc/projecthub/kmutt-thailand-students-in-training-period-at-esiee-amiens-france/smart-waste-bin-e70fb1

- https://create.arduino.cc/projecthub/mohd-shahid/smart-dustbin-using-arduino-c0bb7a
