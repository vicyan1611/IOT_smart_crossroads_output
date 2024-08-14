int relayState = 0;
unsigned long long relayLastMillis = 0;

void relaySetup() {
  pinMode(13, OUTPUT);
  digitalWrite(13,HIGH);
}

void relayLoop() {
  unsigned long long currentMillis = millis();
  if (relayState == 1) {
    if (currentMillis - relayLastMillis > 2000) { // thoi gian tuoi cay
      relayState = 1 - relayState;
      digitalWrite(13, HIGH);
      relayLastMillis = currentMillis;
    }
  } else {
    if (currentMillis - relayLastMillis > 5000) { // thoi gian ngung tuoi
      relayState = 1 - relayState;
      digitalWrite(13, LOW);
      relayLastMillis = currentMillis;
    }
  } 
}