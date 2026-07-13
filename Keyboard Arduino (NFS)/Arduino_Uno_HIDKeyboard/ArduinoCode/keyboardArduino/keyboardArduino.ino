uint8_t buf[8] = {0};  

// A
bool lastBtnStateKeyA = HIGH;
bool buttonStateKeyA = HIGH;

// B
bool lastBtnStateKeyB = HIGH;
bool buttonStateKeyB = HIGH;

// C
bool lastBtnStateKeyC = HIGH;
bool buttonStateKeyC = HIGH;

// D
bool lastBtnStateKeyD = HIGH;
bool buttonStateKeyD = HIGH;

#define PIN_A 2
#define PIN_B 3
#define PIN_C 4
#define PIN_D 5

void setup() {
  Serial.begin(9600);

  pinMode(PIN_A, INPUT_PULLUP);
  pinMode(PIN_B, INPUT_PULLUP);
  pinMode(PIN_C, INPUT_PULLUP);
  pinMode(PIN_D, INPUT_PULLUP);
}

void loop() {
  // ====== A ======
  buttonStateKeyA = digitalRead(PIN_A);
  if (buttonStateKeyA != lastBtnStateKeyA) {
    delay(5); // debouncing
    if (buttonStateKeyA == LOW) { 
      buf[2] = 4; 
      Serial.write(buf, 8);
      releaseKey();
    }
    lastBtnStateKeyA = buttonStateKeyA;
  }

  // ====== B ======
  buttonStateKeyB = digitalRead(PIN_B);
  if (buttonStateKeyB != lastBtnStateKeyB) {
    delay(5);
    if (buttonStateKeyB == LOW) {
      buf[2] = 5; 
      Serial.write(buf, 8);
      releaseKey();
    }
    lastBtnStateKeyB = buttonStateKeyB;
  }

  // ====== C ======
  buttonStateKeyC = digitalRead(PIN_C);
  if (buttonStateKeyC != lastBtnStateKeyC) {
    delay(5);
    if (buttonStateKeyC == LOW) {
      buf[2] = 6; 
      Serial.write(buf, 8);
      releaseKey();
    }
    lastBtnStateKeyC = buttonStateKeyC;
  }

  // ====== D ======
  buttonStateKeyD = digitalRead(PIN_D);
  if (buttonStateKeyD != lastBtnStateKeyD) {
    delay(5);
    if (buttonStateKeyD == LOW) {
      buf[2] = 7; 
      Serial.write(buf, 8);
      releaseKey();
    }
    lastBtnStateKeyD = buttonStateKeyD;
  }
}

void releaseKey() {
  buf[0] = 0;
  buf[2] = 0;
  Serial.write(buf, 8);
}
