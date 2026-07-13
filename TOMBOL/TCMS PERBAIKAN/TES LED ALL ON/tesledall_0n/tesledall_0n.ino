// =========== Normal Mode ============

//const byte ledPins[] = {
//   2, 3, 4, 5, 6, 7, 8, 9 };

// const byte NUM_LEDS = sizeof(ledPins) / sizeof(ledPins[0]);

// void setup() {
//   // Inisialisasi Serial (opsional)
//   Serial.begin(9600);
//   Serial.println("Program Start");

//   // Set semua pin sebagai OUTPUT dan nyalakan LED
//   for (byte i = 0; i < NUM_LEDS; i++) {
//     pinMode(ledPins[i], OUTPUT);
//     digitalWrite(ledPins[i], HIGH);   // LED ON
//   }

//   Serial.println("Semua LED Menyala");
// }

// void loop() {
//   // Pastikan semua LED tetap menyala
//   for (byte i = 0; i < NUM_LEDS; i++) {
//     digitalWrite(ledPins[i], HIGH);
//   }

//   delay(100);
// }

// ========= Pariasi Mode ===========

const byte ledPins[] = {2, 3, 4, 5, 6, 7, 8, 9};
const byte NUM_LEDS = sizeof(ledPins) / sizeof(ledPins[0]);

void setup() {
  for (byte i = 0; i < NUM_LEDS; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);   // Semua LED mati
  }
}

void loop() {

  // Menyalakan LED satu per satu
  for (byte i = 0; i < NUM_LEDS; i++) {
    digitalWrite(ledPins[i], HIGH);
    delay(500);    // Jeda 0,5 detik
  }

  delay(1000);     // Semua LED menyala selama 1 detik

  // Mematikan LED satu per satu
  for (byte i = 0; i < NUM_LEDS; i++) {
    digitalWrite(ledPins[i], LOW);
    delay(500);
  }

  delay(1000);     // Semua LED mati selama 1 detik
}