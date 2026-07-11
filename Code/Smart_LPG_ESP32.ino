// Smart LPG Gas Leakage Detection & Automatic Safety System
// ESP32 + MQ2 + LCD + Relay + Servo + Buzzer
// Configure threshold after calibration.

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESP32Servo.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo servo;

// Pins
const int MQ2_PIN = 34;
const int SERVO_PIN = 13;
const int RELAY_PIN = 26;
const int BUZZER_PIN = 27;

// Change this after checking Serial Monitor
int threshold = 1800;

bool leak = false;

void setup() {

  Serial.begin(115200);

  Wire.begin(21,22);

  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  // Relay OFF (ACTIVE LOW relay)
  digitalWrite(RELAY_PIN, HIGH);
  digitalWrite(BUZZER_PIN, LOW);

  servo.setPeriodHertz(50);
  servo.attach(SERVO_PIN);
  servo.write(0);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0,0);
  lcd.print(" SMART LPG");
  lcd.setCursor(0,1);
  lcd.print("   SYSTEM");
  delay(2000);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("LPG SAFE");
  lcd.setCursor(0,1);
  lcd.print("Monitoring");
}

void loop() {

  int gas = analogRead(MQ2_PIN);

  Serial.print("Gas = ");
  Serial.println(gas);

  if (gas > threshold && !leak) {

    leak = true;

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("WARNING!!");
    lcd.setCursor(0,1);
    lcd.print("GAS LEAK");

    digitalWrite(BUZZER_PIN, HIGH);

    // Relay ON
    digitalWrite(RELAY_PIN, LOW);

    servo.write(90);
  }

  else if (gas <= threshold && leak) {

    leak = false;

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("LPG SAFE");
    lcd.setCursor(0,1);
    lcd.print("Monitoring");

    digitalWrite(BUZZER_PIN, LOW);

    // Relay OFF
    digitalWrite(RELAY_PIN, HIGH);

    servo.write(0);
  }

  delay(200);
}