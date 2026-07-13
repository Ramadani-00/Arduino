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

#define BUFFER_SIZE 256
#define COMMAND_RECEIVED_SIZE 6
#define PACKET_SIZE 8

#define MAX_BUTTON 3

byte ledPin[MAX_BUTTON];
byte buttonPin[MAX_BUTTON];

char caracter;

byte receivedBuffer[BUFFER_SIZE];

byte receivedCMD[COMMAND_RECEIVED_SIZE];
byte sentCMD[PACKET_SIZE];

byte cmd_code;
byte cmd_number;
byte cmd_state0;
byte cmd_state1;
byte cmd_state2;
byte cmd_state3;
uint32_t cmd_state;

byte buttonState[MAX_BUTTON];
byte lastButtonState[MAX_BUTTON];

byte stateLed[MAX_BUTTON];

bool receiveWithStartEndMarkers(byte rc, byte* command)
{
  static bool recvInProgress = false;
  static int ndx = 0;
  byte startMarker = '<';
  byte endMarker = '>';

  if (true==recvInProgress)
  {
    if (rc == endMarker)
    {    
      recvInProgress = false;
      memcpy(command, receivedBuffer, ndx);
      ndx = 0;             
      return true;
    }
    else
    {        
      receivedBuffer[ndx] = rc;
      ndx++;
      if (ndx >= BUFFER_SIZE)
        ndx = BUFFER_SIZE-1;        
    }
  }
  else if (rc == startMarker)
  {
    recvInProgress = true;
    memset(receivedBuffer, 0, sizeof(receivedBuffer)); 
  }
  return false;
}

uint32_t encodeByte(byte b0, byte b1, byte b2, byte b3)
{
  return (uint32_t)((b3 << 24) | (b2 << 16) | (b1 << 8) | b0);
}

void extractByte(uint32_t state, byte *b0, byte *b1, byte *b2, byte *b3)
{
  *b0 = (state & 0xFF);
  *b1 = (state & 0xFF00) >> 8;
  *b2 = (state & 0xFF0000) >> 16;
  *b3 = (state & 0xFF000000) >> 24;
}

void build_send_command(byte* buff, byte code, byte num, uint32_t state)
{
  byte b0, b1, b2, b3;

  extractByte(state, &b0, &b1, &b2, &b3);

  buff[0]='<';
  buff[1]=code;
  buff[2]=num;
  buff[3]=b3;
  buff[4]=b2;
  buff[5]=b1;
  buff[6]=b0;
  buff[7]='>';
}

void mapPin()
{
  memset(ledPin, 0, sizeof(ledPin));
  memset(buttonPin, 0, sizeof(buttonPin));
  
  // Pemetaan manual LED
  ledPin[0] = 2; // LED 1
  ledPin[1] = 3; // LED 2
  ledPin[2] = 4; // LED 3

  // Pemetaan manual Switch
  buttonPin[0] = 5; // Switch 1
  buttonPin[1] = 6; // Switch 2
  buttonPin[2] = 0; // Switch 3 tidak digunakan
}

uint32_t encode_array(uint8_t *arr, uint8_t len)
{
    uint32_t result = 0;

    for (int i=0; i<len; i++)
    {
      result |= arr[i]<<i;
    }
    return result;
}

void ledAction(byte number, uint32_t state)
{
  if (ledPin[number])
  {
    digitalWrite(ledPin[number], (byte) state);
    stateLed[number] = (byte) state;

    build_send_command(sentCMD, LSN_CODE, number, state);
    Serial.write(sentCMD, sizeof(sentCMD));
  }
}

void ledAllAction(uint32_t state)
{
  for (int i = 0; i < MAX_BUTTON; i++) {
    if (ledPin[i])
    {
      digitalWrite(ledPin[i], (byte) state); 
      stateLed[i] = (byte) state;
    }
  }
  build_send_command(sentCMD, LSA_CODE, 255, encode_array(stateLed, MAX_BUTTON));
  Serial.write(sentCMD, sizeof(sentCMD));
}

void setup()
{  
  mapPin();

  for (int i=0; i<MAX_BUTTON; i++)
  {
    if (ledPin[i])
      pinMode(ledPin[i], OUTPUT);  
    if (buttonPin[i])
      pinMode(buttonPin[i], INPUT_PULLUP);

    stateLed[i] = LED_OFF;

    buttonState[i] = BUTTON_NOT_PRESSED;
    lastButtonState[i] = BUTTON_NOT_PRESSED;
  }

  // LOGIKA BARU: LED 1 langsung menyala terus sejak awal start
  digitalWrite(ledPin[0], LED_ON);
  stateLed[0] = LED_ON;

  Serial.begin(115200);  
}

void loop()
{
  // 1. KONTROL SERIAL MONITOR / KOMPUTER
  if(Serial.available()>0)
  {
    caracter = Serial.read();    
    if (true==receiveWithStartEndMarkers(caracter, receivedCMD))
    {
      cmd_code = receivedCMD[0];
      cmd_number = receivedCMD[1];

      cmd_state3 = receivedCMD[2];
      cmd_state2 = receivedCMD[3];
      cmd_state1 = receivedCMD[4];
      cmd_state0 = receivedCMD[5];

      cmd_state = encodeByte(cmd_state0, cmd_state1, cmd_state2, cmd_state3);
      
      // Mengabaikan perintah eksternal untuk LED 1 agar tetap menyala terus
      if (cmd_code==LCN_CODE && cmd_number != 0)
      {
        ledAction(cmd_number, cmd_state);        
      }
      else if (cmd_code==LCA_CODE)
      {
        if (255==cmd_number) 
        {          
          ledAllAction(cmd_state);
          // Mengembalikan LED 1 ke posisi ON jika terpengaruh perintah 'All'
          digitalWrite(ledPin[0], LED_ON);
          stateLed[0] = LED_ON;
        }
      }
    }    
  }  

  // 2. LOGIKA BARU: LED KONDISIONAL MENGIKUTI SWITCHsecara Real-Time
  // Pengecekan Switch 1 (Index 0) mengontrol LED 2 (Index 1)
  if (digitalRead(buttonPin[0]) == BUTTON_PRESSED) {
    if (stateLed[1] != LED_ON) {
      digitalWrite(ledPin[1], LED_ON);
      stateLed[1] = LED_ON;
      build_send_command(sentCMD, BSN_CODE, 0, ON_BUTTON_DOWN);
      Serial.write(sentCMD, sizeof(sentCMD));
    }
  } else {
    if (stateLed[1] != LED_OFF) {
      digitalWrite(ledPin[1], LED_OFF);
      stateLed[1] = LED_OFF;
      build_send_command(sentCMD, BSN_CODE, 0, ON_BUTTON_UP);
      Serial.write(sentCMD, sizeof(sentCMD));
    }
  }

  // Pengecekan Switch 2 (Index 1) mengontrol LED 3 (Index 2)
  if (digitalRead(buttonPin[1]) == BUTTON_PRESSED) {
    if (stateLed[2] != LED_ON) {
      digitalWrite(ledPin[2], LED_ON);
      stateLed[2] = LED_ON;
      build_send_command(sentCMD, BSN_CODE, 1, ON_BUTTON_DOWN);
      Serial.write(sentCMD, sizeof(sentCMD));
    }
  } else {
    if (stateLed[2] != LED_OFF) {
      digitalWrite(ledPin[2], LED_OFF);
      stateLed[2] = LED_OFF;
      build_send_command(sentCMD, BSN_CODE, 1, ON_BUTTON_UP);
      Serial.write(sentCMD, sizeof(sentCMD));
    }
  }

  delay(10);
}
