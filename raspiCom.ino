#include <SPI.h>
#include "Adafruit_BLE_UART.h"

#define ADAFRUITBLE_REQ 10
#define ADAFRUITBLE_RDY 2    
#define ADAFRUITBLE_RST 9

Adafruit_BLE_UART BTLEserial = Adafruit_BLE_UART(ADAFRUITBLE_REQ, ADAFRUITBLE_RDY, ADAFRUITBLE_RST);

const int ckPin = 22;
const int rxPin = 24;
const int txPin = 26;

bool raspiConnected = false;

int data = 123;

int recvData = 0;
int mSerialRead = 0;

void connectRaspi(void);

void setup() {
  // put your setup code here, to run once:
  pinMode(ckPin, OUTPUT);
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);

  Serial.begin(115200);
  while (!Serial){
    ; 
  } 
  connectRaspi();
  BTLEserial.begin();
}

aci_evt_opcode_t laststatus = ACI_EVT_DISCONNECTED;

void loop() {
  // put your main code here, to run repeatedly:

  BTLEserial.pollACI();
  aci_evt_opcode_t status = BTLEserial.getState();
  if (status != laststatus) {
    if (status == ACI_EVT_DEVICE_STARTED) {
        Serial.println(F("* Advertising started"));
    }
    if (status == ACI_EVT_CONNECTED) {
        Serial.println(F("* Connected!"));
    }
    if (status == ACI_EVT_DISCONNECTED) {
        Serial.println(F("* Disconnected or advertising timed out"));
    }
    // OK set the last status change to this one
    laststatus = status;
  }

  if (status == ACI_EVT_CONNECTED) {
      while (BTLEserial.available()) {
        char c = BTLEserial.read();
        sendRaspiData(c);
      }
  } 
}

void connectRaspi(void){
    int synBit = 0; 
    raspiConnected = false;
    while (!raspiConnected){
      synBit = 1 - synBit;
      digitalWrite(ckPin, LOW);
      digitalWrite(txPin, synBit);
      delay(1);
      digitalWrite(ckPin, HIGH);
      delay(1);
      if (digitalRead(rxPin) == HIGH){
        raspiConnected = true;  
      }  
    }
    return;
}

void sendRaspiData(int data){
  
    int sendData = data, i = 0;
    recvData = 0;
    
    for (i = 0; i < 8; i++){
      digitalWrite(ckPin, LOW);
      if ((sendData & 0x01) != 0){
        digitalWrite(txPin, HIGH);  
      } else {
        digitalWrite(txPin, LOW);
      }
      sendData >>= 1;
      digitalWrite(ckPin,HIGH);
      delay(1);
      if (digitalRead(rxPin) == LOW){
        recvData = recvData + (0 << i);
      } else {
        recvData = recvData + (1 << i);
      }
    }
}
