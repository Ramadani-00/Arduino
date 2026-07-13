#define LED_ON HIGH
#define LED_OFF LOW

#define BUTTON_PRESSED LOW
#define BUTTON_NOT_PRESSED HIGH

// Pin LED
const int led1 = 2;
const int led2 = 3;
const int led3 = 4;

// Pin Switch
const int switch1 = 5;
const int switch2 = 6;

void setup() {
  // Konfigurasi LED
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

  // Konfigurasi Switch
  pinMode(switch1, INPUT_PULLUP);
  pinMode(switch2, INPUT_PULLUP);

  // LED 1 selalu ON
  digitalWrite(led1, LED_ON);

  // LED 2 dan LED 3 mati saat awal
  digitalWrite(led2, LED_OFF);
  digitalWrite(led3, LED_OFF);

  Serial.begin(115200);
  Serial.println("Program 3 LED & 2 Switch");
}

void loop() {
  // Pastikan LED 1 selalu menyala
  digitalWrite(led1, LED_ON);

  // Baca kondisi switch
  int state1 = digitalRead(switch1);
  int state2 = digitalRead(switch2);

  // Switch 1 mengontrol LED 2
  if (state1 == BUTTON_PRESSED) {
    digitalWrite(led2, LED_ON);
  } else {
    digitalWrite(led2, LED_OFF);
  }

  // Switch 2 mengontrol LED 3
  if (state2 == BUTTON_PRESSED) {
    digitalWrite(led3, LED_ON);
  } else {
    digitalWrite(led3, LED_OFF);
  }

  delay(50);
}