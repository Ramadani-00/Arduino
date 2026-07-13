const int numButtons = 24;

int ledPins[numButtons];
int buttonPins[numButtons];

const int triggerButtonPin = 51;
const int triggerLedPin    = 26;

const int numPairs = numButtons / 2;
bool ledStatePairs[numPairs][2];
// [pair][0 = ganjil, 1 = genap]

// ================= LED UPDATE =================
void updatePairLEDs() {
  for (int pair = 0; pair < numPairs; pair++) {
    int idx1 = pair * 2;
    int idx2 = pair * 2 + 1;

    digitalWrite(ledPins[idx1], ledStatePairs[pair][0] ? HIGH : LOW);
    digitalWrite(ledPins[idx2], ledStatePairs[pair][1] ? HIGH : LOW);
  }
}

// ================= KIRIM SEMUA STATUS LED =================
void sendAllLEDStates() {
  for (int pair = 0; pair < numPairs; pair++) {
    int idx1 = pair * 2;
    int idx2 = pair * 2 + 1;

    Serial.print("S");
    Serial.print(idx1);
    Serial.print(":");
    Serial.println(ledStatePairs[pair][0] ? 1 : 0);

    Serial.print("S");
    Serial.print(idx2);
    Serial.print(":");
    Serial.println(ledStatePairs[pair][1] ? 1 : 0);
  }
}

// ================= SERIAL (DELPHI) =================
void handleSerial() {
  if (!Serial.available()) return;

  String cmd = Serial.readStringUntil('\n');
  cmd.trim();

  // Format: L,index,value  → contoh: L,3,1
  if (!cmd.startsWith("L,")) return;

  int p1 = cmd.indexOf(',');
  int p2 = cmd.lastIndexOf(',');

  int idx = cmd.substring(p1 + 1, p2).toInt();
  int val = cmd.substring(p2 + 1).toInt();

  if (idx < 0 || idx >= numButtons) return;

  int pair = idx / 2;
  int pos  = idx % 2;

  ledStatePairs[pair][pos] = (val == 1);
  ledStatePairs[pair][1 - pos] = false;

  updatePairLEDs();

  Serial.print("S");
  Serial.print(idx);
  Serial.print(":");
  Serial.println(val);
}

// ================= HARDWARE BUTTON =================
void handleButtons() {
  static unsigned long lastDebounce = 0;
  if (millis() - lastDebounce < 40) return;
  lastDebounce = millis();

  for (int pair = 0; pair < numPairs; pair++) {
    int idx1 = pair * 2;
    int idx2 = pair * 2 + 1;

    bool btnGanjil = digitalRead(buttonPins[idx1]) == LOW;
    bool btnGenap  = digitalRead(buttonPins[idx2]) == LOW;

    if (btnGanjil) {
      ledStatePairs[pair][0] = true;
      ledStatePairs[pair][1] = false;

      updatePairLEDs();

      Serial.print("S");
      Serial.print(idx1);
      Serial.println(":1");
    }
    else if (btnGenap) {
      ledStatePairs[pair][0] = false;
      ledStatePairs[pair][1] = true;

      updatePairLEDs();

      Serial.print("S");
      Serial.print(idx2);
      Serial.println(":1");
    }
  }
}

// ================= SETUP =================
void setup() {
  Serial.begin(115200);
  Serial.setTimeout(20);

  for (int i = 0; i < numButtons; i++) {
    ledPins[i]    = i + 2;
    buttonPins[i] = i + 27;

    pinMode(ledPins[i], OUTPUT);
    pinMode(buttonPins[i], INPUT_PULLUP);
    digitalWrite(ledPins[i], LOW);
  }

  for (int pair = 0; pair < numPairs; pair++) {
    ledStatePairs[pair][0] = false;
    ledStatePairs[pair][1] = false;
  }

  pinMode(triggerButtonPin, INPUT_PULLUP);
  pinMode(triggerLedPin, OUTPUT);
  digitalWrite(triggerLedPin, LOW);
}

// ================= LOOP =================
void loop() {
  handleSerial();
  handleButtons();

  static bool lastTriggerState = false;
  bool triggerPressed = digitalRead(triggerButtonPin) == LOW;

  // ===== MODE TRIGGER (OVERRIDE) =====
  if (triggerPressed) {
    for (int i = 0; i < numButtons; i++) {
      digitalWrite(ledPins[i], HIGH);
    }
    digitalWrite(triggerLedPin, HIGH);
  } else {
    digitalWrite(triggerLedPin, LOW);
    updatePairLEDs();
  }

  // ===== KIRIM STATUS TRIGGER =====
  if (triggerPressed != lastTriggerState) {
    lastTriggerState = triggerPressed;

    if (triggerPressed) {
      Serial.println("T:1");
    } else {
      Serial.println("T:0");
      sendAllLEDStates();   //PENTING: sinkron ulang Delphi
    }
  }
}
