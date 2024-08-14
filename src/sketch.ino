
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Hello, ESP32!");
  trafficLightSetup();
  servoSetup();
  relaySetup();
  button_stepmotorSetup();
}

void loop() {
  servoLoop();
  trafficLightLoop();
  button_stepmotorLoop();
  relayLoop();
  delay(10); // this speeds up the simulation
}
