const uint8_t controlPins[] = { 12, 14, 27, 26 };
const uint8_t segmentPins[] = { 0, 1, 2, 3, 4, 5, 6 };
const uint8_t digitPins[] = {33, 32};
const String numbers[] = {"1111110", "0110000", "1101101", "1111001", "0110011", "1011011", "1011111", "1110000", "1111111", "1111011"};
int second = 23;

void segmentledSetup() {
    for (int i = 0; i < 4; ++i)
    {
        pinMode(controlPins[i], OUTPUT);
    }
    for (int i = 0; i < 2; ++i)
    {
        pinMode(digitPins[i], OUTPUT);
    }
    setNumber(second);
}

void writeCustomPin(int desiredPin) {
  digitalWrite(controlPins[0], desiredPin & 1);
  digitalWrite(controlPins[1], 1 & desiredPin >> 1);
  digitalWrite(controlPins[2], 1 & desiredPin >> 2);
  digitalWrite(controlPins[3], 1 & desiredPin >> 3);
}

int ledLastDigit = 0;
unsigned long long lastMillisDigit = 0;
unsigned long long lastMillisSeg = 0;
unsigned long long previousMillis = 0;
int numbertodisplay[] = {0,0};
int curSegment = 0;

void setNumber(int number) {
  numbertodisplay[0] = number / 10;
  numbertodisplay[1] = number % 10;
  curSegment = 0;
  ledLastDigit = 0;
}

void displayNumber() {
  unsigned long long milliss = millis();
  if (milliss - lastMillisSeg > 19) {
    lastMillisSeg = milliss;
    curSegment = curSegment + 1;
    if (curSegment == 7)
      curSegment = 0;
  }
  String mynumber = numbers[numbertodisplay[ledLastDigit]];
  if (mynumber[curSegment] == '1') {
    writeCustomPin(curSegment);
  }
  if (milliss - lastMillisDigit > 160) {
    
    curSegment = 0;
    lastMillisDigit = milliss;
    lastMillisSeg = milliss;
    ledLastDigit = 1 - ledLastDigit;
    if (mynumber[curSegment] == '1') {
      writeCustomPin(curSegment);
    }
    digitalWrite(digitPins[ledLastDigit], LOW);
    digitalWrite(digitPins[1-ledLastDigit], HIGH);
  }
  // digitalWrite(digitPins[ledLastDigit], LOW);
  // digitalWrite(digitPins[1-ledLastDigit], HIGH);
  
}

void countdown() {
  unsigned long currentMillis = millis();

  if(currentMillis - previousMillis >= 1000)
  {
    previousMillis = currentMillis;

    second--;
    if(second == 0)
      second = 20;
    setNumber(second);
  }
}

void segmentledLoop() {
    countdown();
    displayNumber();
}