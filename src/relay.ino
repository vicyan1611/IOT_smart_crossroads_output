int relayState = 0;
unsigned long long relayLastMillis = 0;

void relaySetup() {
  pinMode(13, OUTPUT);
  digitalWrite(13,HIGH);
}

int isControlRelay = 0;

void handleRelay(String strStatus) {
  int status = strStatus.toInt();
  if (status == 1) {
    isControlRelay = 1;
    digitalWrite(13, HIGH);
  } else {
    digitalWrite(13, LOW);
    isControlRelay = 0;
  }
}

void relayLoop() {
  if (isControlRelay == 1) return;
  unsigned long long currentMillis = millis();
  if (relayState == 1) {
    if (currentMillis - relayLastMillis > 2000) { // thoi gian tuoi cay
      relayState = 1 - relayState;
      digitalWrite(13, HIGH);
      relayLastMillis = currentMillis;
    }
  } else {
    if (currentMillis - relayLastMillis > 10000) { // thoi gian ngung tuoi
      relayState = 1 - relayState;
      digitalWrite(13, LOW);
      relayLastMillis = currentMillis;
    }
  } 
}