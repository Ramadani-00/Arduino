#include "Keyboard.h"

const int PIN_A = 2;
const int PIN_B = 3;
const int PIN_C = 4;   

bool lastBtnStateKeyA = HIGH;
bool buttonStateKeyA = HIGH;

bool lastBtnStateKeyB = HIGH;
bool buttonStateKeyB = HIGH;

bool lastBtnStateKeyC = HIGH;  
bool buttonStateKeyC = HIGH;   

void setup() {
  pinMode(PIN_A, INPUT_PULLUP);
  pinMode(PIN_B, INPUT_PULLUP);
  pinMode(PIN_C, INPUT_PULLUP); 
  Keyboard.begin();
}

void loop() {
  // Tombol A
  buttonStateKeyA = digitalRead(PIN_A);
  if (buttonStateKeyA != lastBtnStateKeyA) {
    delay(5);
    buttonStateKeyA = digitalRead(PIN_A);
    if (buttonStateKeyA == LOW && lastBtnStateKeyA == HIGH) {
      Keyboard.write('A');
    }
  }
  lastBtnStateKeyA = buttonStateKeyA;

  // Tombol B
  buttonStateKeyB = digitalRead(PIN_B);
  if (buttonStateKeyB != lastBtnStateKeyB) {
    delay(5);
    buttonStateKeyB = digitalRead(PIN_B);
    if (buttonStateKeyB == LOW && lastBtnStateKeyB == HIGH) {
      Keyboard.write('B');
    }
  }
  lastBtnStateKeyB = buttonStateKeyB;

  // Tombol C
  buttonStateKeyC = digitalRead(PIN_C);
  if (buttonStateKeyC != lastBtnStateKeyC) {
    delay(5);
    buttonStateKeyC = digitalRead(PIN_C);
    if (buttonStateKeyC == LOW && lastBtnStateKeyC == HIGH) {
      Keyboard.write('C');
    }
  }
  lastBtnStateKeyC = buttonStateKeyC;
}
