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

#define MAX_BUTTON 2

byte ledPin[MAX_BUTTON] = {2, 3};
byte buttonPin[MAX_BUTTON] = {4, 5};

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

bool receiveWithStartEndMarkers(byte rc, byte *command)
{
  static bool recvInProgress = false;
  static int ndx = 0;

  const byte startMarker = '<';
  const byte endMarker = '>';

  if (recvInProgress)
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
        ndx = BUFFER_SIZE - 1;
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
  return ((uint32_t)b3 << 24) |
         ((uint32_t)b2 << 16) |
         ((uint32_t)b1 << 8)  |
         (uint32_t)b0;
}

void extractByte(uint32_t state,
                 byte *b0,
                 byte *b1,
                 byte *b2,
                 byte *b3)
{
  *b0 = state & 0xFF;
  *b1 = (state >> 8) & 0xFF;
  *b2 = (state >> 16) & 0xFF;
  *b3 = (state >> 24) & 0xFF;
}

void build_send_command(byte *buff,
                        byte code,
                        byte num,
                        uint32_t state)
{
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

uint32_t encode_array(uint8_t *arr, uint8_t len)
{
  uint32_t result = 0;

  for (int i = 0; i < len; i++)
  {
    result |= ((uint32_t)arr[i]) << i;
  }

  return result;
}

void ledAction(byte number, uint32_t state)
{
  if (number >= MAX_BUTTON)
    return;

  digitalWrite(ledPin[number], (byte)state);

  stateLed[number] = (byte)state;

  build_send_command(
    sentCMD,
    LSN_CODE,
    number,
    state);

  Serial.write(sentCMD, sizeof(sentCMD));
}

void ledAllAction(uint32_t state)
{
  for (int i = 0; i < MAX_BUTTON; i++)
  {
    digitalWrite(ledPin[i], (byte)state);
    stateLed[i] = (byte)state;
  }

  build_send_command(
    sentCMD,
    LSA_CODE,
    255,
    encode_array(stateLed, MAX_BUTTON));

  Serial.write(sentCMD, sizeof(sentCMD));
}

void twoStateButton(byte index)
{
  buttonState[index] =
      (byte)digitalRead(buttonPin[index]);

  if (BUTTON_NOT_PRESSED == lastButtonState[index] &&
      BUTTON_PRESSED == buttonState[index])
  {
    build_send_command(
      sentCMD,
      BSN_CODE,
      index,
      ON_BUTTON_DOWN);

    Serial.write(sentCMD, sizeof(sentCMD));
  }
  else if (BUTTON_PRESSED == lastButtonState[index] &&
           BUTTON_NOT_PRESSED == buttonState[index])
  {
    build_send_command(
      sentCMD,
      BSN_CODE,
      index,
      ON_BUTTON_UP);

    Serial.write(sentCMD, sizeof(sentCMD));
  }

  lastButtonState[index] = buttonState[index];
}

void setup()
{
  for (int i = 0; i < MAX_BUTTON; i++)
  {
    pinMode(ledPin[i], OUTPUT);
    pinMode(buttonPin[i], INPUT_PULLUP);

    digitalWrite(ledPin[i], LED_OFF);
    stateLed[i] = LED_OFF;

    // baca kondisi tombol saat startup
    buttonState[i] = digitalRead(buttonPin[i]);
    lastButtonState[i] = buttonState[i];
  }

  Serial.begin(115200);
}

void loop()
{
  while (Serial.available() > 0)
  {
    caracter = Serial.read();

    if (receiveWithStartEndMarkers(caracter, receivedCMD))
    {
      cmd_code = receivedCMD[0];
      cmd_number = receivedCMD[1];

      cmd_state3 = receivedCMD[2];
      cmd_state2 = receivedCMD[3];
      cmd_state1 = receivedCMD[4];
      cmd_state0 = receivedCMD[5];

      cmd_state = encodeByte(
        cmd_state0,
        cmd_state1,
        cmd_state2,
        cmd_state3);

      if (cmd_code == LCN_CODE)
      {
        ledAction(cmd_number, cmd_state);
      }
      else if (cmd_code == LCA_CODE)
      {
        if (cmd_number == 255)
        {
          ledAllAction(cmd_state);
        }
      }
    }
  }

  for (int i = 0; i < MAX_BUTTON; i++)
  {
    twoStateButton(i);
  }

  delay(10);
}