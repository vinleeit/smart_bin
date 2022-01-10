# Smart Dustbin

## Background

## Features

- Open lid contactless

- Scan trash content (weight and height)

- Temperature and humidity monitor

- Flame detection

- Air quality & hazardous gas detection (supposed to be odor sensor)

- Notifications with time record

## Components and Supplies

### Main

| Components                           | Quantity |
| ------------------------------------ | -------- |
| ESP32                                | 1        |
| SG90 micro-servo motor               | 1        |
| SparkFun ultrasonic sensor - HC-SR04 | 2        |
| Load cell weight seonsor with frame  | 1        |

### Additional

| Components                             | Quantity |
| -------------------------------------- | -------- |
| Real-time clock module - DS3231/ZS-042 | 1        |
| Buzzer                                 | 1        |
| RGB Led                                | 1        |
| LCD                                    | 1        |
| Temperature & humidity sensor          | 1        |
| Flame sensor module                    | 1        |
| Garbage container + lid                | 1        |
| Gas sensor - MQ-135                    | 1        |

### Power

| Components                 | Quantity |
| -------------------------- | -------- |
| Battery holder with 2 slot | 1        |
| AAA batteries              | 2        |
| Jumper wires               | DEPENDS  |

| Components      | Quantity |
| --------------- | -------- |
| 9V battery      | 1        |
| 9V battery clip | 1        |
| Switch          | 1        |

## Ports

### Ultrasonic

- echo: GPIO18

- trigger: GPIO5

### LCD

- sda: GPIO21

- slc: GPIO22

### Load Cell

- dout: GPIO33

- clk: GPIO32

## Useful Links

- https://create.arduino.cc/projecthub/kmutt-thailand-students-in-training-period-at-esiee-amiens-france/smart-waste-bin-e70fb1

- https://create.arduino.cc/projecthub/mohd-shahid/smart-dustbin-using-arduino-c0bb7a
