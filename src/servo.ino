#include <ESP32Servo.h>

const int servoPin = 15;
Servo servo;

void servoSetup() {
  servo.attach(15);
  servo.write(0);
}

void servoLoop() {
  servo.write(180);
}