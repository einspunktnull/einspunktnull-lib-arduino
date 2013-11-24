#include <AndroduinoBluetooth.h>

/**********************************************************************
 * DECLARAITION AND INITIALISATION
 **********************************************************************/
//HARDWARE CONSTANTS
const int PINDO_LED = 10;
const int PINDI_BTN = 8;
//OUTPUT CONSTANTS
const char TX_BTN = 0x01;
const char TX_VAL_LOW = 0x00;
const char TX_VAL_HIGH = 0x01;
//INPUT CONSTANTS
const char RX_LED = 0x01;
const char RX_TEST = 0x02;
//BT COMMUNIZER
AndroduinoBluetooth androduinoBt;
//LOGIC
int lastBtnState = 0;

/**********************************************************************
 * SETUP
 **********************************************************************/
void setup() {
  Serial.begin(115200);
  Serial3.begin(115200);
  pinMode(PINDO_LED, OUTPUT);
  pinMode(PINDI_BTN, INPUT);
  registerReceiveEventFunctions();
}

void registerReceiveEventFunctions() {
  androduinoBt.registerFunction(rxLed, RX_LED);
  androduinoBt.registerFunction(rxTest, RX_TEST);
}

/**********************************************************************
 * MAIN LOOP AND LOGICS
 **********************************************************************/
void loop() {
  androduinoBt.receive();
  checkBtnPress();
}

void checkBtnPress() {
  int btnState = digitalRead(PINDI_BTN);
  if (btnState != lastBtnState) {
    lastBtnState = btnState;
    char val = btnState == HIGH ? TX_VAL_HIGH : TX_VAL_LOW;
    androduinoBt.send(TX_BTN,val);
  }
}

/**********************************************************************
 * RECEIVE EVENT FUNCTIONS
 **********************************************************************/
void rxLed(byte flag, byte numValues) {
  uint8_t cool = androduinoBt.getByte();
  digitalWrite(PINDO_LED, cool);
}

void rxTest(byte flag, byte numValues) {

  for(int i = 0;i<numValues;i++){
    int val = androduinoBt.getIntAt(i);
    digitalWrite(PINDO_LED,HIGH);
    delay(val);
    digitalWrite(PINDO_LED,LOW);
    delay(val);
  }
}



