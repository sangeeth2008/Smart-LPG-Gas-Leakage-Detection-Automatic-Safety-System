# Smart LPG Gas Leakage Detection & Automatic Safety System

## Features
- MQ-2 gas leak detection
- 16x2 I2C LCD status
- Automatic buzzer alarm
- Relay output for exhaust fan
- Servo-based gas valve shutoff

## ESP32 Pin Mapping
| Device | GPIO |
|---|---:|
| MQ2 | 34 |
| Servo | 13 |
| Relay | 26 |
| Buzzer | 27 |
| LCD SDA | 21 |
| LCD SCL | 22 |

## Libraries
- LiquidCrystal_I2C
- ESP32Servo
-Wire.h 