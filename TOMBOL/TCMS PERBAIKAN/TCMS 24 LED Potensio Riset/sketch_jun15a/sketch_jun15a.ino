// =========== Lampu Stabil Normal ===============================

#define LED_ON HIGH
#define LED_OFF LOW

#define BUTTON_PRESSED LOW
#define BUTTON_NOT_PRESSED HIGH

#define ON_BUTTON_DOWN LOW
#define ON_BUTTON_UP HIGH

#define LCN_CODE 200
#define LSN_CODE 201
#define LCA_CODE 202
#define LSA_CODE 203
#define BSN_CODE 204
#define LGA_CODE 205
#define CAP_INHIBITE_CODE 206

#define BUFFER_SIZE 256
#define COMMAND_RECEIVED_SIZE 6
#define PACKET_SIZE 8
#define MAX_BUTTON 24

const byte potPin = A0; 
volatile byte brightness = 255; // Ditambahkan volatile karena diakses di interrupt

byte ledPin[MAX_BUTTON] = {
  2, 3, 4, 5, 6, 7,
  8, 9, 10, 11,
  16, 17,    
  18, 19,    
  12, 13,    
  14, 15,    
  20, 21, 22, 23, 24, 25
};

byte buttonPin[MAX_BUTTON] = {
  27, 28, 29, 30, 31, 32,
  33, 34, 35, 36,
  41, 42,    
  43, 44,    
  37, 38,    
  39, 40,    
  45, 46, 47, 48, 49, 50
};

byte lampTest_LedPin = 26;
byte lampTest_ButtonPin = 51;

byte receivedBuffer[BUFFER_SIZE];
byte receivedCMD[COMMAND_RECEIVED_SIZE];
byte sentCMD[PACKET_SIZE];

byte caracter;

byte buttonState[MAX_BUTTON];
byte lastButtonState[MAX_BUTTON];
volatile byte stateLed[MAX_BUTTON]; // Ditambahkan volatile
byte backupStateLed[MAX_BUTTON];

byte lampTest_ButtonState;
byte lampTest_LastButtonState;

volatile bool lampTestActive = false; // Ditambahkan volatile
unsigned long lampTestStart = 0;
unsigned long nowMillis;

// Ditambahkan untuk tracking waktu baca analog agar tidak membebani loop
unsigned long lastPotRead = 0; 

bool isEven(byte num) {
  return !(num & 0x01);
}

uint32_t encodeByte(byte b0, byte b1, byte b2, byte b3) {
  return ((uint32_t)b3 << 24) |
         ((uint32_t)b2 << 16) |
         ((uint32_t)b1 << 8) |
         (uint32_t)b0;
}

void extractByte(uint32_t state, byte *b0, byte *b1, byte *b2, byte *b3) {
  *b0 = state & 0xFF;
  *b1 = (state >> 8) & 0xFF;
  *b2 = (state >> 16) & 0xFF;
  *b3 = (state >> 24) & 0xFF;
}

uint32_t encode_array(volatile byte *arr, uint8_t len) {
  uint32_t result = 0;
  for (byte i = 0; i < len; i++) {
    result |= ((uint32_t)(arr[i] == LED_ON)) << i;
  }
  return result;
}

bool receiveWithStartEndMarkers(byte rc, byte *command) {
  static bool recvInProgress = false;
  static byte ndx = 0;

  if (rc == '<') {
    recvInProgress = true;
    ndx = 0;
    return false;
  }

  if (recvInProgress) {
    if (rc == '>') {
      recvInProgress = false;
      memcpy(command, receivedBuffer, ndx);
      return true;
    } else {
      if (ndx < BUFFER_SIZE) {
        receivedBuffer[ndx++] = rc;
      }
    }
  }
  return false;
}

void build_send_command(byte *buff, byte code, byte num, uint32_t state) {
  byte b0, b1, b2, b3;
  extractByte(state, &b0, &b1, &b2, &b3);

  buff[0] = '<';
  buff[1] = code;
  buff[2] = num;
  buff[3] = b3;
  buff[4] = b2;
  buff[5] = b1;
  buff[6] = b0;
  buff[7] = '>';
}

void ledAction(byte number, bool sendCap) {
  if (number >= MAX_BUTTON) return;

  if (isEven(number)) {
    stateLed[number] = LED_ON;
    if ((number + 1) < MAX_BUTTON)
      stateLed[number + 1] = LED_OFF;
  } else {
    stateLed[number] = LED_ON;
    stateLed[number - 1] = LED_OFF;
  }

  if (sendCap) {
    build_send_command(sentCMD, CAP_INHIBITE_CODE, number, 1);
    Serial.write(sentCMD, PACKET_SIZE);
  }
}

void ledAllAction(uint32_t state) {
  for (byte i = 0; i < MAX_BUTTON; i++) {
    stateLed[i] = ((state >> i) & 0x01) ? LED_ON : LED_OFF;
  }

  build_send_command(sentCMD, LSA_CODE, 255, encode_array(stateLed, MAX_BUTTON));
  Serial.write(sentCMD, PACKET_SIZE);
}

// FUNGSI INI DIJALANKAN OTOMATIS OLEH TIMER INTERRUPT (Bukan di Loop)
ISR(TIMER2_COMPA_vect) {
  static byte softPwmCounter = 0;
  
  // Update 24 Utama LED
  for (byte i = 0; i < MAX_BUTTON; i++) {
    if (stateLed[i] == LED_ON) {
      if (softPwmCounter < brightness) {
        digitalWrite(ledPin[i], HIGH);
      } else {
        digitalWrite(ledPin[i], LOW);
      }
    } else {
      digitalWrite(ledPin[i], LOW);
    }
  }
  
  // Update Lamp Test LED
  if (lampTestActive) {
    if (softPwmCounter < brightness) {
      digitalWrite(lampTest_LedPin, HIGH);
    } else {
      digitalWrite(lampTest_LedPin, LOW);
    }
  } else {
    digitalWrite(lampTest_LedPin, LOW);
  }
  
  softPwmCounter++; 
}

void Turn_All_LED(byte state) {
  for (byte i = 0; i < MAX_BUTTON; i++) {
    stateLed[i] = state;
  }
}

void scanButtonsFast() {
  for (byte i = 0; i < MAX_BUTTON; i++) {
    byte cur = digitalRead(buttonPin[i]);

    if (cur != lastButtonState[i]) {
      lastButtonState[i] = cur;
      if (cur == BUTTON_PRESSED) {
        ledAction(i, true);
      }
    }
  }
}

void Lamp_Test() {
  lampTest_ButtonState = digitalRead(lampTest_ButtonPin);

  if (lampTest_LastButtonState == BUTTON_NOT_PRESSED &&
      lampTest_ButtonState == BUTTON_PRESSED) {

    for (byte i = 0; i < MAX_BUTTON; i++) {
      backupStateLed[i] = stateLed[i];
    }

    lampTestActive = true;
    lampTestStart = nowMillis;
    Turn_All_LED(LED_ON);
  }

  if (lampTestActive && (nowMillis - lampTestStart >= 3000)) {
    for (byte i = 0; i < MAX_BUTTON; i++) {
      stateLed[i] = backupStateLed[i];
    }
    lampTestActive = false;
  }

  lampTest_LastButtonState = lampTest_ButtonState;
}

void processCommand() {
  byte cmd_code = receivedCMD[0];
  byte cmd_number = receivedCMD[1];

  uint32_t cmd_state = encodeByte(
    receivedCMD[5],
    receivedCMD[4],
    receivedCMD[3],
    receivedCMD[2]);

  switch (cmd_code) {
    case LCN_CODE:
      ledAction(cmd_number, false);
      break;

    case LCA_CODE:
      if (cmd_number == 255) {
        ledAllAction(cmd_state);
      }
      break;

    case LGA_CODE:
      build_send_command(sentCMD, LSA_CODE, 255, encode_array(stateLed, MAX_BUTTON));
      Serial.write(sentCMD, PACKET_SIZE);
      break;
  }
}

void setup() {
  for (byte i = 0; i < MAX_BUTTON; i++) {
    pinMode(ledPin[i], OUTPUT);
    pinMode(buttonPin[i], INPUT_PULLUP);
    stateLed[i] = isEven(i) ? LED_ON : LED_OFF;
    lastButtonState[i] = digitalRead(buttonPin[i]);
  }

  pinMode(lampTest_LedPin, OUTPUT);
  pinMode(lampTest_ButtonPin, INPUT_PULLUP);
  lampTest_LastButtonState = digitalRead(lampTest_ButtonPin);

  Serial.begin(115200);
  Serial.setTimeout(0);

  // === SETUP TIMER INTERRUPT (Timer 2) ===
  cli(); // Matikan interrupt global sementara
  TCCR2A = 0;
  TCCR2B = 0;
  TCNT2  = 0;
  OCR2A = 39; // Set ke ~50 microsecond per langkah PWM
  TCCR2A |= (1 << WGM21); // Mode CTC
  TCCR2B |= (1 << CS21);  // Prescaler 8
  TIMSK2 |= (1 << OCIE2A); // Aktifkan interrupt timer
  sei(); // Aktifkan kembali interrupt global
}

void loop() {
  nowMillis = millis();

  // Membaca potensiometer setiap 50 milidetik sekali saja (menghemat cpu)
  if (nowMillis - lastPotRead >= 50) {
    lastPotRead = nowMillis;
    int potValue = analogRead(potPin);
    brightness = map(potValue, 0, 1023, 0, 255);
  }

  while (Serial.available()) {
    caracter = Serial.read();
    if (receiveWithStartEndMarkers(caracter, receivedCMD)) {
      processCommand();
    }
  }

  scanButtonsFast();
  Lamp_Test();
}




// =========== Lampu Berkedip Tidak Maksimal ===========================

// #define LED_ON HIGH
// #define LED_OFF LOW

// #define BUTTON_PRESSED LOW
// #define BUTTON_NOT_PRESSED HIGH

// #define ON_BUTTON_DOWN LOW
// #define ON_BUTTON_UP HIGH

// #define LCN_CODE 200
// #define LSN_CODE 201
// #define LCA_CODE 202
// #define LSA_CODE 203
// #define BSN_CODE 204
// #define LGA_CODE 205
// #define CAP_INHIBITE_CODE 206

// #define BUFFER_SIZE 256
// #define COMMAND_RECEIVED_SIZE 6
// #define PACKET_SIZE 8
// #define MAX_BUTTON 24 // Tetap 24 untuk tombol utama (Total 25 termasuk Lamp Test)

// // Tambahan komponen Potensiometer
// const byte potPin = A0; 
// byte brightness = 255;

// // Pin Secara Urut
// // byte ledPin[MAX_BUTTON] = {
// //   2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13,
// //   14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25
// // };

// // byte buttonPin[MAX_BUTTON] = {
// //   27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38,
// //   39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50
// // };

// // Perbaikan Pin Terbalik
// byte ledPin[MAX_BUTTON] = {
//   2, 3, 4, 5, 6, 7,
//   8, 9, 10, 11,

//   16, 17,    // indeks 10,11

//   18, 19,    // indeks 12,13 

//   12, 13,    // indeks 14,15

//   14, 15,    // indeks 16,17 

//   20, 21, 22, 23, 24, 25
// };

// byte buttonPin[MAX_BUTTON] = {
//   27, 28, 29, 30, 31, 32,
//   33, 34, 35, 36,

//   41, 42,    // indeks 10,11

//   43, 44,    // indeks 12,13 

//   37, 38,    // indeks 14,15

//   39, 40,    // indeks 16,17 

//   45, 46, 47, 48, 49, 50
// };

// // Komponen ke-25 (Lamp Test)
// byte lampTest_LedPin = 26;
// byte lampTest_ButtonPin = 51;

// byte receivedBuffer[BUFFER_SIZE];
// byte receivedCMD[COMMAND_RECEIVED_SIZE];
// byte sentCMD[PACKET_SIZE];

// byte caracter;

// byte buttonState[MAX_BUTTON];
// byte lastButtonState[MAX_BUTTON];
// byte stateLed[MAX_BUTTON];
// byte backupStateLed[MAX_BUTTON];

// byte lampTest_ButtonState;
// byte lampTest_LastButtonState;

// bool lampTestActive = false;
// unsigned long lampTestStart = 0;
// unsigned long nowMillis;

// bool isEven(byte num) {
//   return !(num & 0x01);
// }

// uint32_t encodeByte(byte b0, byte b1, byte b2, byte b3) {
//   return ((uint32_t)b3 << 24) |
//          ((uint32_t)b2 << 16) |
//          ((uint32_t)b1 << 8) |
//          (uint32_t)b0;
// }

// void extractByte(uint32_t state, byte *b0, byte *b1, byte *b2, byte *b3) {
//   *b0 = state & 0xFF;
//   *b1 = (state >> 8) & 0xFF;
//   *b2 = (state >> 16) & 0xFF;
//   *b3 = (state >> 24) & 0xFF;
// }

// uint32_t encode_array(uint8_t *arr, uint8_t len) {
//   uint32_t result = 0;

//   for (byte i = 0; i < len; i++) {
//     result |= ((uint32_t)(arr[i] == LED_ON)) << i;
//   }

//   return result;
// }

// bool receiveWithStartEndMarkers(byte rc, byte *command) {
//   static bool recvInProgress = false;
//   static byte ndx = 0;

//   if (rc == '<') {
//     recvInProgress = true;
//     ndx = 0;
//     return false;
//   }

//   if (recvInProgress) {
//     if (rc == '>') {
//       recvInProgress = false;
//       memcpy(command, receivedBuffer, ndx);
//       return true;
//     } else {
//       if (ndx < BUFFER_SIZE) {
//         receivedBuffer[ndx++] = rc;
//       }
//     }
//   }

//   return false;
// }

// void build_send_command(byte *buff, byte code, byte num, uint32_t state) {
//   byte b0, b1, b2, b3;

//   extractByte(state, &b0, &b1, &b2, &b3);

//   buff[0] = '<';
//   buff[1] = code;
//   buff[2] = num;
//   buff[3] = b3;
//   buff[4] = b2;
//   buff[5] = b1;
//   buff[6] = b0;
//   buff[7] = '>';
// }

// void ledAction(byte number, bool sendCap) {
//   if (number >= MAX_BUTTON) return;

//   if (isEven(number)) {
//     stateLed[number] = LED_ON;

//     if ((number + 1) < MAX_BUTTON)
//       stateLed[number + 1] = LED_OFF;
//   } else {
//     stateLed[number] = LED_ON;
//     stateLed[number - 1] = LED_OFF;
//   }

//   if (sendCap) {
//     build_send_command(
//       sentCMD,
//       CAP_INHIBITE_CODE,
//       number,
//       1);

//     Serial.write(sentCMD, PACKET_SIZE);
//   }
// }

// void ledAllAction(uint32_t state) {
//   for (byte i = 0; i < MAX_BUTTON; i++) {
//     stateLed[i] = ((state >> i) & 0x01) ? LED_ON : LED_OFF;
//   }

//   build_send_command(
//     sentCMD,
//     LSA_CODE,
//     255,
//     encode_array(stateLed, MAX_BUTTON));

//   Serial.write(sentCMD, PACKET_SIZE);
// }

// // Menggunakan Software PWM agar ke-24 LED utama meredup halus bersamaan
// void Update_All_LED() {
//   static byte softPwmCounter = 0;
  
//   for (byte i = 0; i < MAX_BUTTON; i++) {
//     if (stateLed[i] == LED_ON) {
//       if (softPwmCounter < brightness) {
//         digitalWrite(ledPin[i], HIGH);
//       } else {
//         digitalWrite(ledPin[i], LOW);
//       }
//     } else {
//       digitalWrite(ledPin[i], LOW);
//     }
//   }
  
//   softPwmCounter++; 
// }

// void Turn_All_LED(byte state) {
//   for (byte i = 0; i < MAX_BUTTON; i++) {
//     stateLed[i] = state;
//   }
// }

// void scanButtonsFast() {
//   for (byte i = 0; i < MAX_BUTTON; i++) {
//     byte cur = digitalRead(buttonPin[i]);

//     if (cur != lastButtonState[i]) {
//       lastButtonState[i] = cur;

//       if (cur == BUTTON_PRESSED) {
//         ledAction(i, true);
//       }
//     }
//   }
// }

// void Lamp_Test() {

//   lampTest_ButtonState = digitalRead(lampTest_ButtonPin);

//   if (lampTest_LastButtonState == BUTTON_NOT_PRESSED &&
//       lampTest_ButtonState == BUTTON_PRESSED) {

//     // Simpan kondisi LED saat ini
//     for (byte i = 0; i < MAX_BUTTON; i++) {
//       backupStateLed[i] = stateLed[i];
//     }

//     lampTestActive = true;
//     lampTestStart = nowMillis;

//     // Nyalakan semua LED
//     Turn_All_LED(LED_ON);
//   }

//   if (lampTestActive &&
//       (nowMillis - lampTestStart >= 3000)) {

//     // Kembalikan kondisi LED sebelumnya
//     for (byte i = 0; i < MAX_BUTTON; i++) {
//       stateLed[i] = backupStateLed[i];
//     }

//     lampTestActive = false;
//   }

//   // WAJIB ADA
//   lampTest_LastButtonState = lampTest_ButtonState;
// }

// void processCommand() {
//   byte cmd_code = receivedCMD[0];
//   byte cmd_number = receivedCMD[1];

//   uint32_t cmd_state = encodeByte(
//     receivedCMD[5],
//     receivedCMD[4],
//     receivedCMD[3],
//     receivedCMD[2]);

//   switch (cmd_code) {

//     case LCN_CODE:
//       ledAction(cmd_number, false);
//       break;

//     case LCA_CODE:
//       if (cmd_number == 255) {
//         ledAllAction(cmd_state);
//       }
//       break;

//     case LGA_CODE:
//       build_send_command(
//         sentCMD,
//         LSA_CODE,
//         255,
//         encode_array(stateLed, MAX_BUTTON));

//       Serial.write(sentCMD, PACKET_SIZE);
//       break;
//   }
// }

// void setup() {

//   for (byte i = 0; i < MAX_BUTTON; i++) {

//     pinMode(ledPin[i], OUTPUT);
//     pinMode(buttonPin[i], INPUT_PULLUP);

//     stateLed[i] = isEven(i) ? LED_ON : LED_OFF;

//     lastButtonState[i] = digitalRead(buttonPin[i]);
//   }

//   pinMode(lampTest_LedPin, OUTPUT);
//   pinMode(lampTest_ButtonPin, INPUT_PULLUP);

//   lampTest_LastButtonState =
//     digitalRead(lampTest_ButtonPin);

//   Serial.begin(115200);
//   Serial.setTimeout(0);

//   Update_All_LED();
// }

// void loop() {

//   nowMillis = millis();

//   // Membaca nilai potensiometer (A0) dan mengubah skalanya ke 0-255
//   int potValue = analogRead(potPin);
//   brightness = map(potValue, 0, 1023, 0, 255);

//   while (Serial.available()) {

//     caracter = Serial.read();

//     if (receiveWithStartEndMarkers(caracter, receivedCMD)) {
//       processCommand();
//     }
//   }

//   scanButtonsFast();
//   Lamp_Test();
//   Update_All_LED();

//   // Lamp Test LED juga ikut terpengaruh oleh redup potensiometer
//   if (lampTestActive) {
//     static byte lampTestPwmCounter = 0;
//     if (lampTestPwmCounter < brightness) {
//       digitalWrite(lampTest_LedPin, HIGH);
//     } else {
//       digitalWrite(lampTest_LedPin, LOW);
//     }
//     lampTestPwmCounter++;
//   } else {
//     digitalWrite(lampTest_LedPin, LOW);
//   }
// }
