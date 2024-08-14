const uint8_t controlPins[] = { 12, 14, 27, 26 };
const uint8_t segmentPins[] = { 0, 1, 2, 3, 4, 5, 6 };
const uint8_t digitPins[] = {33, 32};
const String numbers[] = {"1111110", "0110000", "1101101", "1111001", "0110011", "1011011", "1011111", "1110000", "1111111", "1111011"};

int second = 8;
int blue_led = 19;
int green_led = 18;
int red_led = 5; 
int currentTrafficState = 0; //0 is red, 1 is green
int redTime = 8, greenTime = 4;

void trafficLightSetup() {
    for (int i = 0; i < 4; ++i)
    {
        pinMode(controlPins[i], OUTPUT);
    }
    for (int i = 0; i < 2; ++i)
    {
        pinMode(digitPins[i], OUTPUT);
    }
    setNumber(redTime);
    pinMode(red_led, OUTPUT);
    pinMode(green_led, OUTPUT);
    pinMode(blue_led, OUTPUT);
}

void ledColor(int red_value, int green_value, int blue_value) {
  analogWrite(red_led,red_value);
  analogWrite(green_led,green_value);
  analogWrite(blue_led,blue_value);
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
    Serial.println(second);
    if(second == 0)
      {
        currentTrafficState = 1 - currentTrafficState;
        if (currentTrafficState == 0)
        {
          second = redTime;
          ledColor(255,0,0);
        } else {
          second = greenTime;
          ledColor(0,255,0);
        }
      }
    setNumber(second);
  }
}

void trafficLightLoop() {
    countdown();
    displayNumber();
}