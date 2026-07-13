#define MAX_BUTTON 24
#define LED_ON HIGH
#define LED_OFF LOW
#define BUTTON_PRESSED LOW
#define BUTTON_NOT_PRESSED HIGH

// Tombol & LED utama
int buttonPin[MAX_BUTTON] = {26, 27, 28, 29, 30, 31, 32, 33, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47};
int ledPin[MAX_BUTTON]    = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17,18, 19, 20, 21, 22, 23, 24, 25};

// Tombol & LED TRIGGER
int triggerButton = 51;   // tombol trigger
int triggerLed    = 50;   // LED trigger

uint8_t prevButtonState[MAX_BUTTON];
uint8_t curButtonState[MAX_BUTTON];
uint8_t ledState[MAX_BUTTON];        // state toggle LED utama

uint8_t prevTriggerState = BUTTON_NOT_PRESSED;  // Menyimpan status tombol trigger

void setup() {
  Serial.begin(115200);

  // Setup tombol & LED utama
  for (int i = 0; i < MAX_BUTTON; i++) {
    pinMode(buttonPin[i], INPUT_PULLUP);
    pinMode(ledPin[i], OUTPUT);
    prevButtonState[i] = BUTTON_NOT_PRESSED;
    curButtonState[i]  = BUTTON_NOT_PRESSED;
    ledState[i] = LED_OFF;
    digitalWrite(ledPin[i], LED_OFF);
  }

  // Setup tombol & LED trigger
  pinMode(triggerButton, INPUT_PULLUP);
  pinMode(triggerLed, OUTPUT);
  digitalWrite(triggerLed, LOW);  // LED trigger mulai mati

  Serial.println("Tester tombol-LED siap dengan toggle + trigger hold!");
}

void loop() {
  // ======================= TOMBOL LED UTAMA (TOGGLE) =======================
  for (int i = 0; i < MAX_BUTTON; i++) {
    curButtonState[i] = digitalRead(buttonPin[i]);

    // Toggle hanya saat tombol baru ditekan (falling edge)
    if (prevButtonState[i] == BUTTON_NOT_PRESSED &&
        curButtonState[i] == BUTTON_PRESSED)
    {
      ledState[i] = !ledState[i];           // Toggle LED
      digitalWrite(ledPin[i], ledState[i]); // Update hardware

      // Serial monitor: print status tombol dan LED
      Serial.print("Button ");
      Serial.print(i);
      Serial.print(" pressed → LED ");
      Serial.println(ledState[i] ? "ON" : "OFF");
    }

    prevButtonState[i] = curButtonState[i];
  }

  // ======================= TOMBOL TRIGGER (HOLD) =======================
  int trigState = digitalRead(triggerButton);
  if (trigState == BUTTON_PRESSED) {
    // Trigger ON → Semua LED utama menyala
    for (int i = 0; i < MAX_BUTTON; i++) {
      digitalWrite(ledPin[i], HIGH);
    }
    // LED trigger juga menyala
    digitalWrite(triggerLed, HIGH);

    // Serial monitor: print status trigger
    Serial.println("TRIGGER BUTTON PRESSED → Semua LED ON, Trigger LED ON");
  } else {
    // Trigger OFF → Kembalikan LED utama sesuai dengan status toggle
    for (int i = 0; i < MAX_BUTTON; i++) {
      digitalWrite(ledPin[i], ledState[i]);
    }
    // LED trigger mati
    digitalWrite(triggerLed, LOW);

    // Serial monitor: print status trigger
    Serial.println("TRIGGER BUTTON RELEASED → Semua LED OFF (status toggle), Trigger LED OFF");
  }

  // Memberi waktu agar serial monitor dapat memperbaharui status dengan baik
  delay(100);  // Mengurangi kecepatan pembaruan serial agar lebih mudah dibaca
}
