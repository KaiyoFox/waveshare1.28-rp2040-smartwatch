#include <Arduino.h>
#include <Arduino_JSON.h>
#include <ArduinoBLE.h>
#include <string>

const int txPin = D5; // GPIO 16
//const int rxPin = 17; // GPIO 17
//And pin D3 for signal enable / watch for data, (set to HIGH to enable data send to waveshare)

BLEService ledService("19B10000-E8F2-537E-4F6C-D104768A1214"); // Bluetooth® Low Energy LED Service
BLEByteCharacteristic switchCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);
BLEStringCharacteristic switchResponseCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1215", BLENotify, 256);

const int ledPin = LED_BUILTIN; // pin to use for the LED

byte receivedValues[2048];
int valueCount = 0; // Number of values currently stored

void sendText(String text){//const char* text) {
  int lastOne = 0;
  digitalWrite(D4, LOW);
  delay(10);
  digitalWrite(D3, HIGH);
  //while(digitalRead(D2) == LOW){delay(500);}
  //delay(5150); //150 for normal useage,
  //delay(1150);
  delay(80);//WAS 100
  digitalWrite(D3, LOW);
  delay(80);
  for (int bit = 0; bit < 8; bit++) {
    digitalWrite(D5, ('\2' >> bit) & 1);
    delay(5); //4 is usual,, CHANGED TO 5
    if(lastOne == 0){
      lastOne = 1;
      digitalWrite(D4, HIGH);
    } else{
      lastOne = 0;
      digitalWrite(D4, LOW);
    }
    delay(5);
  }
  delay(50);//WAS 50
  for (int bit = 0; bit < 8; bit++) {
    digitalWrite(D5, ('\2' >> bit) & 1);
    delay(5); //4 is usual
    if(lastOne == 0){
      lastOne = 1;
      digitalWrite(D4, HIGH);
    } else{
      lastOne = 0;
      digitalWrite(D4, LOW);
    }
    delay(5);
  }
  delay(50);
  for (size_t i = 0; text[i] != '\0'; i++) {
    for (int bit = 0; bit < 8; bit++) {
      //delay(5);
      digitalWrite(D5, (text[i] >> bit) & 1);
      delay(5); //2 is lowest usually
      if(lastOne == 0){
        digitalWrite(D4, HIGH);
        lastOne = 1;
      } else{
        digitalWrite(D4, LOW);
        lastOne = 0;
      }
      delay(5); //3;
    }
    delay(4);
  }
  delay(10);
  for (int bit = 0; bit < 8; bit++) {
    digitalWrite(D5, ('\0' >> bit) & 1);
    delay(5); //4 is usual
    if(lastOne == 0){
      lastOne = 1;
      digitalWrite(D4, HIGH);
    } else{
      lastOne = 0;
      digitalWrite(D4, LOW);
    }
    delay(4);
  }
  delay(2);
}

void setup() {
  Serial.begin(9600);

  //while (!Serial);

  pinMode(ledPin, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);
  delay(100);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);

  if (!BLE.begin()) {
    Serial.println("starting Bluetooth® Low Energy module failed!");
    while (1);
  }

  BLE.setLocalName("LED");
  BLE.setAdvertisedService(ledService);
  ledService.addCharacteristic(switchCharacteristic);
  ledService.addCharacteristic(switchResponseCharacteristic);
  BLE.addService(ledService);
  switchCharacteristic.writeValue(72);
  switchResponseCharacteristic.writeValue("Erm");
  BLE.advertise();

  Serial.println("BLE LED Peripheral");
  pinMode(D5, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D3, OUTPUT);
  
  pinMode(D1, OUTPUT);
  digitalWrite(D1, LOW);
  delay(1000); //One second delay for Waveshare rp2040 to setup FIRST Very important
  pinMode(D0, INPUT); //D5
  pinMode(D1, INPUT); //D4 clock
  pinMode(D2, INPUT); //See who to listen too

  digitalWrite(D4, LOW);
  digitalWrite(D3, LOW);


  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);
  delay(100);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
}


int lastState;
int curState;
int lastTime = 0;
int totalTimeToRec = 0;
char receiveChar() {
  char receivedChar = 0;
  for (int bit = 0; bit < 8; bit++) {
    lastTime=millis();
    while(lastState == curState && millis()-lastTime<5000){
      //Serial.println(lastState);
      //Serial.println(curState);
      curState = digitalRead(D1); //d4
    }
    //Serial.println("newChar");
    lastState=curState;
    receivedChar |= (digitalRead(D0) << bit); //d6
    //delayMicroseconds(60); // Adjust this delay as needed
  }
  //Serial.println(receivedChar);
  return receivedChar;
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);
  delay(100);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  BLEDevice central = BLE.central();

  if (central) {
    Serial.print("Connected to central: ");
    Serial.println(central.address());

    while (central.connected()) {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(500);
      digitalWrite(LED_BUILTIN, LOW);
      delay(500);
      digitalWrite(LED_BUILTIN, HIGH);
      delay(500);
      while (central.connected()){
        delay(40);

        if(digitalRead(D1)==HIGH){//if(digitalRead(D2)==HIGH){
            //digitalWrite(LED_BUILTIN, LOW);
            char receivedText[32] = "";
            int index = 0;
            int lastState = LOW;//digitalRead(D1); //d4
            int curState = lastState;
            totalTimeToRec=millis();
            while (millis()-totalTimeToRec<10000) {//cant take longer than 10 seconds
                char receivedChar = receiveChar();
                if (receivedChar == '\0') {
                break; // End of transmission
                }
                receivedText[index++] = receivedChar;
            }
            if(millis()-totalTimeToRec>10000){
                Serial.println("Timed out.");
            }
            receivedText[index] = '\0'; // Add null-terminator for the string
            //if(receivedText[0]==' '){
            memmove(receivedText, receivedText + 1, strlen(receivedText));
            //}
            //digitalWrite(LED_BUILTIN, HIGH);
            if(strlen(receivedText) > 2){
                Serial.println(receivedText);
                //std::string message = "8015744494;";
                //message += receivedText;
                                                //20 byte limit
                switchResponseCharacteristic.setValue(receivedText);
                Serial.println(receivedText);
            }
            delay(200);
        } else{
            //BLEDevice central = BLE.central();
            digitalWrite(LED_BUILTIN, HIGH);
            delay(500);
            digitalWrite(LED_BUILTIN, LOW);
            delay(500);
            //delay(40);
            //digitalWrite(LED_BUILTIN, HIGH);
            //delay(40);
            if (switchCharacteristic.written()) {
                byte value = switchCharacteristic.value();
                if (valueCount < 356) {
                    if(value!=0){
                    receivedValues[valueCount] = value;
                    valueCount++;
                    }
                } else{
                    Serial.println("Ran out of Memory.");
                }

                Serial.println(value);

                if (value == 153) {
                    break;
                }
            }
          }
      }

      String receivedString = ""; // Define a String to store the received characters
      Serial.println("Received values: ");
      for (int i = 0; i < valueCount; i++) {
        if(receivedValues[i]!=153){
          char letter = char(receivedValues[i]);
          receivedString += letter;
          Serial.print(letter);
        }
      }
      valueCount = 0;
      Serial.println();

      // Send received data over GPIO
      //const char* message = receivedString;
      Serial.println("Sending the following data: ");
      Serial.print(receivedString);
      
      //JSONVar myObject = JSON.parse(receivedString);

      //Serial.println(myObject["text"]);
      
      sendText(receivedString);//myObject["text"]); //receivedString
      delay(100);

                                //20 byte limit
                                    //to send data
      //Serial.println("Wack");
    }

    Serial.print(F("Disconnected from central: "));
    Serial.println(central.address());
  }
}
