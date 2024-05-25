#include <Arduino.h>
#include <Arduino_JSON.h>
#include <ArduinoBLE.h>
#include <string>

//const int txPin = D5;  // GPIO 16
//const int rxPin = 17; // GPIO 17
//And pin D3 for signal enable / watch for data, (set to HIGH to enable data send to waveshare)

const int sendPin = 5;     // Pin to send data
const int receivePin = 4;  // Pin to receive data



BLEService ledService("19B10000-E8F2-537E-4F6C-D104768A1214");  // Bluetooth® Low Energy LED Service
BLEByteCharacteristic switchCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite | BLENotify);
BLEStringCharacteristic switchResponseCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1215", BLENotify, 256);  //256

const int ledPin = LED_BUILTIN;  // pin to use for the LED

byte receivedValues[2048];
int valueCount = 0;  // Number of values currently stored

void sendTextO_L_D(String text) {  //const char* text) {
  int lastOne = 0;
  digitalWrite(D4, LOW);
  delay(500);  //10
  digitalWrite(D3, HIGH);
  //while(digitalRead(D2) == LOW){delay(500);}
  //delay(5150); //150 for normal useage,
  //pinMode(D0, OUTPUT); //NEW
  //delay(1150);
  delay(150);  //WAS 100 wAS 80
  digitalWrite(D3, LOW);
  delay(3000);  // WAS 80 too
  for (int bit = 0; bit < 8; bit++) {
    digitalWrite(D5, ('\2' >> bit) & 1);
    //digitalWrite(D0, ('\2' >> bit) & 1);
    delay(5);  //4 is usual,, CHANGED TO 5
    if (lastOne == 0) {
      lastOne = 1;
      digitalWrite(D4, HIGH);
    } else {
      lastOne = 0;
      digitalWrite(D4, LOW);
    }
    delay(5);
  }
  delay(20);  //WAS 50
  for (int bit = 0; bit < 8; bit++) {
    digitalWrite(D5, ('\2' >> bit) & 1);
    //digitalWrite(D0, ('\2' >> bit) & 1);
    delay(5);  //4 is usual
    if (lastOne == 0) {
      lastOne = 1;
      digitalWrite(D4, HIGH);
    } else {
      lastOne = 0;
      digitalWrite(D4, LOW);
    }
    delay(5);
  }
  delay(20);
  for (size_t i = 0; text[i] != '\0'; i++) {
    for (int bit = 0; bit < 8; bit++) {
      //delay(5);
      digitalWrite(D5, (text[i] >> bit) & 1);
      //digitalWrite(D0, ('\2' >> bit) & 1);
      delay(7);  //2 is lowest usually
      if (lastOne == 0) {
        digitalWrite(D4, HIGH);
        lastOne = 1;
      } else {
        digitalWrite(D4, LOW);
        lastOne = 0;
      }
      delay(2);  //3;
    }
    delay(2);
  }
  delay(10);
  for (int bit = 0; bit < 8; bit++) {
    digitalWrite(D5, ('\0' >> bit) & 1);
    //digitalWrite(D0, ('\2' >> bit) & 1);
    delay(5);  //4 is usual
    if (lastOne == 0) {
      lastOne = 1;
      digitalWrite(D4, HIGH);
    } else {
      lastOne = 0;
      digitalWrite(D4, LOW);
    }
    delay(4);
  }
  delay(20);
  digitalWrite(D4, LOW);
}

int timeRec = 0;
void sendText(String text) {  //new
  bool msgFailed = false;
  digitalWrite(sendPin, LOW);
  delay(50);
  digitalWrite(D3, HIGH);
  int startFast = millis();
  bool lastStateOfIt = digitalRead(receivePin);
  while (millis() - startFast < 5000 && digitalRead(receivePin) == lastStateOfIt) {};
  //delay(5000);  //WAS 100 wAS 80
  digitalWrite(D3, LOW);
  delay(20);
  text += '\0';
  for (int i = 0; i < text.length(); i++) {
    //delay(5);
    Serial.println(text[i]);
    digitalWrite(sendPin, LOW);  //reset?
    delay(1);                    //5
    bool last = LOW;
    digitalWrite(sendPin, HIGH);
    delay(5);  //5aaaaaaaaa10--------was 5
    //digitalWrite(sendPin, LOW);
    for (int j = 0; j < 8; j++) {
      if (text[i] & (1 << j)) {
        digitalWrite(sendPin, HIGH);
      } else {
        digitalWrite(sendPin, LOW);
      }
      //delay(3);  //3 so far best- was 1
      timeRec = millis();
      while (digitalRead(receivePin) == last && millis() - timeRec < 200) {}  //200
      if (millis() - timeRec >= 200) {                                        //20
        Serial.println("Timeout");
        msgFailed = true;
        return;
      }
      last = digitalRead(receivePin);
    }
    digitalWrite(sendPin, LOW);
    if (msgFailed) {
      return;
    }
  }
  digitalWrite(sendPin, LOW);
}

char receiveChar() {  //new
  char receivedChar = 0;
  bool last = LOW;
  digitalWrite(sendPin, LOW);
  while (digitalRead(receivePin) == LOW) {}
  delay(15);
  for (int i = 0; i < 8; i++) {
    delay(50);  //100
    receivedChar |= (digitalRead(receivePin) << i);
    if (last == HIGH) {
      digitalWrite(sendPin, LOW);
      last = LOW;
    } else {
      digitalWrite(sendPin, HIGH);
      last = HIGH;
    }
  }
  return receivedChar;
}

//char receivedText[2048] = "";
char* receivedTextMAIN;
void receiveText() {
  char receivedText[2048] = "";
  int index = 0;
  while (true) {
    char receivedChar = 0;
    bool last = LOW;
    digitalWrite(sendPin, LOW);
    while (digitalRead(receivePin) == LOW) {}
    delay(15);
    for (int i = 0; i < 8; i++) {
      delay(3);  //JUST CHANGED 4/15 8:41pm 5 100
      receivedChar |= (digitalRead(receivePin) << i);
      if (last == HIGH) {
        digitalWrite(sendPin, LOW);
        last = LOW;
      } else {
        digitalWrite(sendPin, HIGH);
        last = HIGH;
      }
    }
    if (receivedChar == '\0') {
      break;
    } else {
      receivedText[index++] = receivedChar;
    }
  }
  digitalWrite(sendPin, LOW);
  Serial.println(receivedText);
  receivedTextMAIN = receivedText;
}


void setup() {
  pinMode(sendPin, OUTPUT);
  pinMode(receivePin, INPUT);
  pinMode(D3, OUTPUT);
  digitalWrite(D3, LOW);

  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  digitalWrite(D0, HIGH);
  digitalWrite(D1, HIGH);



  Serial.begin(9600);

  //while (!Serial);

  pinMode(ledPin, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  digitalWrite(LED_BUILTIN, HIGH);
  delay(3000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(100);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);

  if (!BLE.begin()) {
    Serial.println("starting Bluetooth® Low Energy module failed!");
    while (1)
      ;
  }

  BLE.setLocalName("Warp Smart Watch");
  BLE.setAdvertisedService(ledService);
  ledService.addCharacteristic(switchResponseCharacteristic);
  ledService.addCharacteristic(switchCharacteristic);
  BLE.addService(ledService);
  switchResponseCharacteristic.writeValue("Erm");
  switchCharacteristic.writeValue(72);
  BLE.advertise();

  Serial.println("BLE LED Peripheral");

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
char receiveCharO_L_D() {
  char receivedChar = 0;
  for (int bit = 0; bit < 8; bit++) {
    lastTime = millis();
    while (lastState == curState && millis() - lastTime < 5000) {
      //Serial.println(lastState);
      //Serial.println(curState);
      curState = digitalRead(D1);  //d4
    }
    //Serial.println("newChar");
    lastState = curState;
    receivedChar |= (digitalRead(D0) << bit);  //d6
    //delayMicroseconds(60); // Adjust this delay as needed
  }
  //Serial.println(receivedChar);
  return receivedChar;
}






unsigned long disconnectStartTime = 0;
bool disconnectTimeout = false;
bool debug = false;

int lastByte = 0;

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);
  delay(100);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  BLEDevice central = BLE.central();

  if (central || debug) {
    Serial.print("Connected to central: ");
    if (central) {
      switchResponseCharacteristic.setValue("DevStart");
      Serial.println(central.address());
    } else {
      Serial.println("debug");
    }

    if (central.connected()) {
      String receivedString = "{\"tite\": \"con\", \"text\": \"con\", \"app\": \"con\"}";
      delay(100);
      sendText(receivedString);
    }
    while (central.connected() || debug) {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(700);
      digitalWrite(LED_BUILTIN, LOW);
      delay(500);
      digitalWrite(LED_BUILTIN, HIGH);
      delay(600);
      while (central.connected() || debug) {
        delay(10);

        //if (digitalRead(D1) == HIGH) {  //if(digitalRead(D2)==HIGH){
        if (digitalRead(receivePin) == HIGH) {
          //Serial.println("ITS HIGH");
          while (digitalRead(receivePin) == HIGH) {}
          //Serial.println("YES ITS HIGH");
          //delay(1); //ADDED WITH THE NEW SEND RECIEVE STUFF 04/14/24
          //pinMode(D0, INPUT); //New
          //digitalWrite(LED_BUILTIN, LOW);

          receiveText();

          //Serial.println("recced");
          /*
          char receivedText[32] = "";
          int index = 0;
          int lastState = LOW;  //digitalRead(D1); //d4
          int curState = lastState;
          totalTimeToRec = millis();
          while (millis() - totalTimeToRec < 10000) {  //cant take longer than 10 seconds
            char receivedChar = receiveChar();
            if (receivedChar == '\0') {
              break;  // End of transmission
            }
            receivedText[index++] = receivedChar;
          }
          if (millis() - totalTimeToRec > 10000) {
            Serial.println("Timed out.");
          }
          receivedText[index] = '\0';  // Add null-terminator for the string
          //if(receivedText[0]==' '){
          memmove(receivedText, receivedText + 1, strlen(receivedText));
          //}
          //digitalWrite(LED_BUILTIN, HIGH);
          */
          if (strlen(receivedTextMAIN) > 2) {
            Serial.println(receivedTextMAIN);
            if (String(receivedTextMAIN) == "disconnect") {
              Serial.println(receivedTextMAIN);
              if (String(receivedTextMAIN) == "disconnect") {
                Serial.println("AAA");
                switchResponseCharacteristic.setValue(receivedTextMAIN);
                if (central.connected()) {
                  Serial.println("Disconnecting...");
                  central.disconnect();
                  disconnectStartTime = millis();  // Record the start time
                  disconnectTimeout = false;       // Reset timeout flag
                  while (central.connected() && !disconnectTimeout) {
                    if (millis() - disconnectStartTime > 10000) {  // Timeout after 10 seconds
                      Serial.println("Disconnect timeout.");
                      disconnectTimeout = true;  // Set timeout flag
                    }
                    central.disconnect();
                    // Add any other necessary operations or checks here
                  }
                  Serial.println("Disconnecting 2...");
                  delay(1000);  // Wait for disconnection to complete
                  if (!central.connected()) {
                    Serial.println("Disconnected successfully.");
                  } else {
                    Serial.println("Failed");
                    BLE.disconnect();
                    delay(1000);  // Wait for disconnection to complete
                    if (!central.connected()) {
                      Serial.println("Failed to disconnect.");
                    }
                  }
                } else {
                  Serial.println("Already disconnected.");
                }
              }
            } else {
              //std::string message = "8015744494;";
              //message += receivedText;
              //20 byte limit
              switchResponseCharacteristic.setValue(receivedTextMAIN);
              Serial.print("Forwarding Data: ");
              Serial.println(receivedTextMAIN);
            }
          }
          delay(200);
        } else {
          //BLEDevice central = BLE.central();
          digitalWrite(LED_BUILTIN, HIGH);
          delay(1);
          digitalWrite(LED_BUILTIN, LOW);
          delay(15);
          //delay(40);
          //digitalWrite(LED_BUILTIN, HIGH);
          //delay(40);
          if (switchCharacteristic.written()) {
            lastByte = millis();
            byte value = switchCharacteristic.value();
            if (valueCount < 356) {
              if (value != 0) {
                receivedValues[valueCount] = value;
                valueCount++;
              }
            } else {
              Serial.println("Ran out of Memory.");
            }

            Serial.println(value);

            if (value == 153) {
              break;
            }
          }
        }
      }  //after first discon

      String receivedString = "";  // Define a String to store the received characters
      Serial.println("Received values: ");
      for (int i = 0; i < valueCount; i++) {
        if (receivedValues[i] != 153) {
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
      if (receivedString == "reset" || receivedString == "flash") {
        if (receivedString == "flash") {
          digitalWrite(D1, LOW);  //reset
          delay(200);
          digitalWrite(D0, LOW);  //boot
          delay(200);
          digitalWrite(D1, HIGH);
          delay(200);
          digitalWrite(D0, HIGH);
        } else {
          digitalWrite(D1, LOW);
          delay(200);
          digitalWrite(D1, HIGH);
        }
      } else {
        sendText(receivedString);  //myObject["text"]); //receivedString
      }
      if (millis() - lastByte > 1000) {
        delay(100);  //but why? OOH BATTERY, thats why
      } else {
        delay(1);
      }
      //20 byte limit
      //to send data
      //Serial.println("Wack");
    }  //after second discon

    Serial.print(F("Disconnected from central: "));
    Serial.println(central.address());
    String receivedString = "{\"tite\": \"con\", \"text\": \"DisC\", \"app\": \"con\"}";
    sendText(receivedString);
  }
}
