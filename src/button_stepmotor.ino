#include <Stepper.h>

int stepsPerRevolution = 100;
Stepper myStepper(200, 16, 4, 0, 2);
int stepperState = 1;
void button_stepmotorSetup() {
  pinMode(17, INPUT);
  myStepper.setSpeed(150);
  stepperState = 1;
}

void button_stepmotorLoop() {
  int signal = digitalRead(17);
  if (signal == HIGH) {
    myStepper.step(stepperState * stepsPerRevolution);
    stepperState = -stepperState; 
  }
}