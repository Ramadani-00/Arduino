#define MAX_BUTTON 6
#define LED_ON HIGH
#define LED_OFF LOW
#define BUTTON_PRESSED LOW
#define BUTTON_NOT_PRESSED HIGH

int buttonPin[MAX_BUTTON] = {8, 9, 10, 11, 12, 13};
int ledPin[MAX_BUTTON]    = {2, 3, 4, 5, 6, 7};

uint8_t prevButtonState[MAX_BUTTON];
uint8_t curButtonState[MAX_BUTTON];
uint8_t ledState[MAX_BUTTON];

String buffer = "";

void setup() {
  Serial.begin(115200);

  for (int i = 0; i < MAX_BUTTON; i++) {
    pinMode(buttonPin[i], INPUT_PULLUP);
    pinMode(ledPin[i], OUTPUT);

    prevButtonState[i] = BUTTON_NOT_PRESSED;
    curButtonState[i]  = BUTTON_NOT_PRESSED;
    ledState[i]        = LED_OFF;

    digitalWrite(ledPin[i], LED_OFF);
  }

  Serial.println("READY");
}

void loop() {

  // ===== BACA TOMBOL (TOGGLE LED) =====
  for (int i = 0; i < MAX_BUTTON; i++) {
    curButtonState[i] = digitalRead(buttonPin[i]);

    if (prevButtonState[i] == BUTTON_NOT_PRESSED &&
        curButtonState[i] == BUTTON_PRESSED)
    {
      ledState[i] = !ledState[i];
      digitalWrite(ledPin[i], ledState[i]);

      // Kirim status ke Delphi
      Serial.print("S");
      Serial.print(i);
      Serial.print(":");
      Serial.println(ledState[i]);

      delay(150);
    }

    prevButtonState[i] = curButtonState[i];
  }

  // ===== TERIMA PERINTAH DARI DELPHI =====
  while (Serial.available()) {
    char c = Serial.read();
    if (c == '\n') {
      processCommand(buffer);
      buffer = "";
    } else {
      buffer += c;
    }
  }
}

void processCommand(String cmd) {
  // Format: L0:1
  if (cmd[0] == 'L') {
    int idx = cmd[1] - '0';
    int val = cmd[3] - '0';

    if (idx >= 0 && idx < MAX_BUTTON) {
      ledState[idx] = val;
      digitalWrite(ledPin[idx], val ? LED_ON : LED_OFF);

      // Kirim balik status baru
      Serial.print("S");
      Serial.print(idx);
      Serial.print(":");
      Serial.println(val);
    }
  }
}
