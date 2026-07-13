// #define MAX_BUTTON 1
// #define LED_ON HIGH
// #define LED_OFF LOW
// #define BUTTON_PRESSED LOW
// #define BUTTON_NOT_PRESSED HIGH

// int buttonPin[MAX_BUTTON] = {3};
// int ledPin[MAX_BUTTON]    = {2};

// uint8_t prevButtonState[MAX_BUTTON];
// uint8_t curButtonState[MAX_BUTTON];
// uint8_t ledState[MAX_BUTTON];

// String buffer = "";

// void setup() {
//   Serial.begin(115200);

//   for (int i = 0; i < MAX_BUTTON; i++) {
//     pinMode(buttonPin[i], INPUT_PULLUP);
//     pinMode(ledPin[i], OUTPUT);

//     prevButtonState[i] = BUTTON_NOT_PRESSED;
//     curButtonState[i]  = BUTTON_NOT_PRESSED;
//     ledState[i]        = LED_OFF;

//     digitalWrite(ledPin[i], LED_OFF);
//   }

//   Serial.println("READY");
// }

// void loop() {

//   // ===== BACA TOMBOL (TOGGLE LED) =====
//   for (int i = 0; i < MAX_BUTTON; i++) {
//     curButtonState[i] = digitalRead(buttonPin[i]);

//     if (prevButtonState[i] == BUTTON_NOT_PRESSED &&
//         curButtonState[i] == BUTTON_PRESSED)
//     {
//       ledState[i] = !ledState[i];
//       digitalWrite(ledPin[i], ledState[i]);

//       // Kirim status ke Delphi
//       Serial.print("S");
//       Serial.print(i);
//       Serial.print(":");
//       Serial.println(ledState[i]);

//       delay(150);
//     }

//     prevButtonState[i] = curButtonState[i];
//   }

//   // ===== TERIMA PERINTAH DARI DELPHI =====
//   while (Serial.available()) {
//     char c = Serial.read();
//     if (c == '\n') {
//       processCommand(buffer);
//       buffer = "";
//     } else {
//       buffer += c;
//     }
//   }
// }

// void processCommand(String cmd) {
//   // Format: L0:1
//   if (cmd[0] == 'L') {
//     int idx = cmd[1] - '0';
//     int val = cmd[3] - '0';

//     if (idx >= 0 && idx < MAX_BUTTON) {
//       ledState[idx] = val;
//       digitalWrite(ledPin[idx], val ? LED_ON : LED_OFF);

//       // Kirim balik status baru
//       Serial.print("S");
//       Serial.print(idx);
//       Serial.print(":");
//       Serial.println(val);
//     }
//   }
// }


// ========== Riset ==================


#define MAX_SWITCH 1

#define LED_ON HIGH
#define LED_OFF LOW

// ===== PIN =====
int switchPin[MAX_SWITCH] = {6}; // Saklar di pin 3
int ledPin[MAX_SWITCH]    = {5}; // LED di pin 2

int potPin = A1; // Potensio di A0

// ===== VARIABLE =====
uint8_t switchState[MAX_SWITCH];
uint8_t lastSwitchState[MAX_SWITCH];
uint8_t ledState[MAX_SWITCH];

String buffer = "";

void setup() {

  Serial.begin(115200);

  // ===== SETUP SWITCH & LED =====
  for (int i = 0; i < MAX_SWITCH; i++) {

    pinMode(switchPin[i], INPUT_PULLUP);
    pinMode(ledPin[i], OUTPUT);

    switchState[i] = HIGH;
    lastSwitchState[i] = HIGH;

    ledState[i] = LED_OFF;

    digitalWrite(ledPin[i], LED_OFF);
  }

  Serial.println("READY");
}

void loop() {

  // =====================================
  // BACA SAKLAR
  // =====================================
  for (int i = 0; i < MAX_SWITCH; i++) {

    switchState[i] = digitalRead(switchPin[i]);

    // Jika saklar ON
    if (switchState[i] == LOW) {
      ledState[i] = LED_ON;
    }
    // Jika saklar OFF
    else {
      ledState[i] = LED_OFF;
    }

    digitalWrite(ledPin[i], ledState[i]);

    // Kirim status hanya jika berubah
    if (switchState[i] != lastSwitchState[i]) {

      Serial.print("S");
      Serial.print(i);
      Serial.print(":");
      Serial.println(ledState[i]);

      lastSwitchState[i] = switchState[i];
    }
  }

  // =====================================
  // BACA POTENSIO A0
  // =====================================
  int potValue = analogRead(potPin);

  Serial.print("P0:");
  Serial.println(potValue);

  delay(50);

  // =====================================
  // TERIMA PERINTAH DARI DELPHI
  // =====================================
  while (Serial.available()) {

    char c = Serial.read();

    if (c == '\n') {
      processCommand(buffer);
      buffer = "";
    }
    else {
      buffer += c;
    }
  }
}

// =====================================
// PROCESS COMMAND DARI DELPHI
// =====================================
void processCommand(String cmd) {

  // Format: L0:1
  if (cmd[0] == 'L') {

    int idx = cmd[1] - '0';
    int val = cmd[3] - '0';

    if (idx >= 0 && idx < MAX_SWITCH) {

      ledState[idx] = val;

      digitalWrite(ledPin[idx], val ? LED_ON : LED_OFF);

      // Kirim balik status
      Serial.print("S");
      Serial.print(idx);
      Serial.print(":");
      Serial.println(val);
    }
  }
}