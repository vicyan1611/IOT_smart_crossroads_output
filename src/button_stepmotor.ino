#include <Stepper.h>

int stepsPerRevolution = 200;
Stepper myStepper(stepsPerRevolution, 16, 4, 0, 2);

void button_stepmotorSetup() {
  pinMode(17, INPUT);
  myStepper.setSpeed(60);
}

void button_stepmotorLoop() {
  int signal = digitalRead(17);
  if (signal == HIGH) {
    Serial.println("button is pressed");
  }
  //myStepper.step(stepsPerRevolution); call when need to step
}