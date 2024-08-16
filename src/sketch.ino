
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Hello, ESP32!");
  trafficLightSetup();
  relaySetup();
  button_stepmotorSetup();
  mqttSetup();
}

void loop() {
  trafficLightLoop();
  button_stepmotorLoop();
  relayLoop();
  mqttLoop();
  delay(10); // this speeds up the simulation
}
