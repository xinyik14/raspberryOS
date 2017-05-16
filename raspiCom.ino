
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
}

void loop() {
  // put your main code here, to run repeatedly:

  // connect to Raspi
  

  
  if (Serial.available()){

    
    
     mSerialRead = Serial.parseInt();
     //Serial.println(mSerialRead);
     
    sendRaspiData(mSerialRead);
    Serial.println(recvData);
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
