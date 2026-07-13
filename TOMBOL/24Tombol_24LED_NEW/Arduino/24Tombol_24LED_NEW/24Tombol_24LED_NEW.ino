#define NUM_BUTTONS 24

// ===== LOGIC LEVEL =====
#define LED_ON  HIGH
#define LED_OFF LOW

#define BUTTON_PRESSED     LOW
#define BUTTON_NOT_PRESSED HIGH

// ===== PIN CONFIG =====
int ledPins[NUM_BUTTONS];        // LED 1–24  -> pin 2–25
int buttonPins[NUM_BUTTONS];     // BTN 1–24  -> pin 27–50

const int triggerButtonPin = 51; // Trigger button
const int triggerLedPin    = 26; // Trigger LED

// ===== STATE =====
uint8_t prevButtonState[NUM_BUTTONS];
uint8_t curButtonState[NUM_BUTTONS];
uint8_t ledState[NUM_BUTTONS];

bool prevTriggerPressed = false;

// ===== SERIAL BUFFER =====
String serialBuffer = "";

// =================================================
void setup() {
  Serial.begin(115200);

  // Init LED & Button
  for (int i = 0; i < NUM_BUTTONS; i++) {
    ledPins[i]    = i + 2;
    buttonPins[i] = i + 27;

    pinMode(ledPins[i], OUTPUT);
    pinMode(buttonPins[i], INPUT_PULLUP);

    prevButtonState[i] = BUTTON_NOT_PRESSED;
    curButtonState[i]  = BUTTON_NOT_PRESSED;
    ledState[i]        = LED_OFF;

    digitalWrite(ledPins[i], LED_OFF);
  }

  // Trigger
  pinMode(triggerButtonPin, INPUT_PULLUP);
  pinMode(triggerLedPin, OUTPUT);
  digitalWrite(triggerLedPin, LED_OFF);

  Serial.println("READY");
}

// =================================================
void loop() {
  readButtons();
  handleTrigger();
  handleSerial();

  delay(50); // debounce sederhana
}

// =================================================
// ===== BUTTON TOGGLE =====
void readButtons() {
  for (int i = 0; i < NUM_BUTTONS; i++) {
    curButtonState[i] = digitalRead(buttonPins[i]);

    if (prevButtonState[i] == BUTTON_NOT_PRESSED &&
        curButtonState[i]  == BUTTON_PRESSED) {

      ledState[i] = !ledState[i];
      digitalWrite(ledPins[i], ledState[i]);

      sendLedState(i);
    }

    prevButtonState[i] = curButtonState[i];
  }
}

// =================================================
// ===== TRIGGER HOLD MODE =====
void handleTrigger() {
  bool triggerPressed = digitalRead(triggerButtonPin) == BUTTON_PRESSED;

  // Trigger baru ditekan
  if (triggerPressed && !prevTriggerPressed) {
    for (int i = 0; i < NUM_BUTTONS; i++) {
      digitalWrite(ledPins[i], LED_ON);
      sendLedState(i, 1);
    }
    digitalWrite(triggerLedPin, LED_ON);
  }

  // Trigger dilepas
  if (!triggerPressed && prevTriggerPressed) {
    for (int i = 0; i < NUM_BUTTONS; i++) {
      digitalWrite(ledPins[i], ledState[i]);
      sendLedState(i);
    }
    digitalWrite(triggerLedPin, LED_OFF);
  }

  prevTriggerPressed = triggerPressed;
}

// =================================================
// ===== SERIAL HANDLER =====
void handleSerial() {
  while (Serial.available()) {
    char c = Serial.read();

    if (c == '\n') {
      processCommand(serialBuffer);
      serialBuffer = "";
    } else {
      serialBuffer += c;
    }
  }
}

// =================================================
// ===== COMMAND PARSER =====
// Format dari Delphi: L<index>:<0|1>
void processCommand(String cmd) {
  cmd.trim();
  if (cmd.length() < 4) return;

  if (cmd[0] == 'L') {
    int p = cmd.indexOf(':');
    if (p < 0) return;

    int idx = cmd.substring(1, p).toInt();
    int val = cmd.substring(p + 1).toInt();

    if (idx >= 0 && idx < NUM_BUTTONS) {
      ledState[idx] = val ? LED_ON : LED_OFF;
      digitalWrite(ledPins[idx], ledState[idx]);
      sendLedState(idx);
    }
  }
}

// =================================================
// ===== SERIAL RESPONSE =====
void sendLedState(int idx) {
  sendLedState(idx, ledState[idx] ? 1 : 0);
}

void sendLedState(int idx, int val) {
  Serial.print("S");
  Serial.print(idx);
  Serial.print(":");
  Serial.println(val);
}
