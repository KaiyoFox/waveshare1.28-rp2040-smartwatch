#include "LCD_Test.h"
#include "hardware/vreg.h"
#include "pico/stdlib.h"
#include <EEPROM.h>
#include <Arduino.h>
#include <Arduino_JSON.h>
#include <map>
#include <string>
#include <list>

//Builtin-Apps/Processes:
//nclude "home.h"
#include "mainScreen.h"
#include "notifPane.h"
#include "appsPanel.h"
#include "recentApps.h"
//#include "nfc.h"
#include "setTime.h"
#include "previewNotif.h"
#include "keyboard.h"
#include "flashlight.h"
#include "settings.h"


//Apps
#include "flappyBird.h"
#include "game.h"
#include "CountSteps.h"
//#include "TimerApp.h"
#include "messages.h"
#include "developer.h"
//#include "scrollingTest.h"
#include "weather.h"
#include "news.h"
#include "findMyPhone.h"
#include "alarms.h"


int address = 1;
int CurTime;
int last = 0;
int last2 = 0;
int ticksSinceTap = 0;
bool inTransition = false;
bool pauseRender = false;
bool tap = false;
bool speedMode = false;
bool otherSwipe = false;
bool startup = false;
bool medClock = false;
bool turboClock = false;
bool batSaver = false;
bool buttonDown = false;
bool butaction = false;
bool butActionRan = false;
bool dontRunDimAgain = true;
bool BLEconnected = false;
int tapHeld = 0;
int tickTenTen = 0;
int updateHome = 0;
int idleTime = millis();
int lastBatteryCheck = 0;
int frameCount = 0;
int fps = 0;
int lastfpstick = 0;
bool oneTickPause = false;
int buttonPressCount = 0;
const char* message = "";
std::map<std::string, uint16_t> colorCache;
UWORD* BlackImage;
typedef void (*AppPtr)();
AppPtr runningApp;
std::string runningAppName = "boot";
std::string lastUsedAppName = "main";
std::map<std::string, AppPtr> apps;
std::list<float> batVoltages = {};
int autoClock = 15000;  //Auto clock screen
std::string error = "";
std::list<std::string> systemApps = { "home", "main", "notifPane", "appsPanel", "recentApps", "previewNotif", "keyboard", "setTime", "error" };
std::list<std::string> backgroundApps = {};  //{"flappyBird"};
typedef void (*ServiceFunction)();           //services
struct Service {
  String name;
  ServiceFunction function;
};
std::list<Service> services;
//std::vector<Service> services;

const int sendPin = 17;     // 2Pin to send data
const int receivePin = 16;  // 3Pin to receive data

uint8_t flag = 0;
void Touch_INT_callback();
void buttonPress();

uint16_t deviceMainColorTheme = 0x739c;    //0x009688;
uint16_t deviceSecondColorTheme = 0xecfa;  //0xFE6B;
uint16_t deviceThirdColorTheme = 0xc41a;   //0x06d5;
bool aod = false;

void clearEEPROM(int addr) {
  EEPROM.begin(512);  // Initialize EEPROM
  unsigned long clearValue = 0;
  EEPROM.put(addr, clearValue);  // Clear the data in the EEPROM
  EEPROM.commit();               // Store the data to the physical EEPROM
  EEPROM.end();                  // Release the EEPROM
}

void saveToEEPROMX(unsigned long data, int addr) {
  EEPROM.begin(512);       // Initialize EEPROM
  EEPROM.put(addr, data);  // Save the time to EEPROM
  EEPROM.commit();         // Store the data to the physical EEPROM
  EEPROM.end();            // Release the EEPROM
}

unsigned long readFromEEPROM(int addr) {
  EEPROM.begin(512);  // Initialize EEPROM
  unsigned long dataOut;
  EEPROM.get(addr, dataOut);  // Read the time from EEPROM
  EEPROM.end();               // Release the EEPROM
  return dataOut;
}

//void saveToEEPROMX(unsigned long data, int addr) {
//None
//}
//unsigned long readFromEEPROM(int addr) {
//  return 0;
//}





#include <tuple>
#include <chrono>


#include <iostream>
#include <string>
#include <list>
#include <chrono>

int timeSinceLastButton = 0;

const float friction = 0.85;
const float snapThreshold = 5;
int hoverObject = 0;
int scrollY = 0;
float scrollV = 0;

bool draggingScrollE = false;
int initialScroll = 0;
int initialTap = 0;
int uiY = 0;
int currentSnapped = 0;
float snapVel = 0;

int lastSpeedCheckTime = 0;
;
int lastScrollY = 0;

bool wasAbleToCheck = false;
bool scrolling = false;

std::list<int> scrollFunction(int numberOfItems, std::string itemHeaders[], bool visible) {
  // Check scroll speed periodically
  // Handle touch events
  if (tap) {
    if (!draggingScrollE && Touch_CTS816.y_point > scrollY - 5 && Touch_CTS816.y_point < scrollY + 65 && Touch_CTS816.x_point > 180) {
      //Serial.println(true);
      initialTap = Touch_CTS816.y_point;
      initialScroll = scrollY;
      draggingScrollE = true;
      lastSpeedCheckTime = millis();
      lastScrollY = scrollY;
      wasAbleToCheck = false;
    }
    otherSwipe = false;
    watchSwipe = false;
  } else {
    if (draggingScrollE) {
      if (wasAbleToCheck) {
        scrollV = (scrollY - lastScrollY) / 2;  //more percise
        wasAbleToCheck = false;
        Serial.println("Slow");
      } else {
        scrollV = (scrollY - initialScroll) / 1.3;  //likely a quick motion
        Serial.println("Quick");
      }
      scrollY += scrollV;
      scrollV *= friction;
      Paint_DrawCircle(230 - abs((scrollY - (120 - 29)) / 4) + 1, scrollY + 29, 29, deviceMainColorTheme, DOT_PIXEL_2X2, DRAW_FILL_FULL);
      LCD_1IN28_DisplayWindows(180, 0, 240, 240, BlackImage);
      //Serial.println(scrollY,lastScrollY);
      draggingScrollE = false;
    }
  }

  //auto currentTime = std::chrono::system_clock::now();
  int currentTime = millis();
  int elapsedTime = currentTime - lastSpeedCheckTime;
  if (elapsedTime > 450) {  // 400 is good -- Check speed every 0.3 seconds
    if (draggingScrollE) {  // && abs(scrollY-lastScrollY)>20
      //Serial.println("tick");
      //scrollV = scrollY - lastScrollY;
      lastScrollY = scrollY;
      wasAbleToCheck = true;
    }
    lastSpeedCheckTime = currentTime;
  }

  if (draggingScrollE) {
    scrollY = Touch_CTS816.y_point + (initialScroll - initialTap);  // - scrollV;
    //scrollV = (scrollY - lastScrollY) / 5;
  }

  scrollY = std::max(5, std::min(175, scrollY));
  if (oneTickPause == false) {
    Paint_DrawCircle(230 - abs((scrollY - (120 - 29)) / 4) + 1, scrollY + 29, 29, deviceMainColorTheme, DOT_PIXEL_2X2, DRAW_FILL_FULL);
    //LCD_1IN28_DisplayWindows(180, 0, 240, 240, BlackImage);//-abs((scrollY-(120+20))/4)
  }

  // Apply scrolling
  if (draggingScrollE || std::abs(int(scrollV)) > 1 && oneTickPause == false) {
    scrollY += scrollV;
    scrollV *= friction;
    //Paint_DrawCircle(230-abs((scrollY-(120-29))/4)+1, scrollY+29, 29, deviceMainColorTheme, DOT_PIXEL_2X2, DRAW_FILL_FULL);
    LCD_1IN28_DisplayWindows(180, 0, 240, 240, BlackImage);  //-abs((scrollY-(120+20))/4)
  }

  // Clamp scrollY within bounds
  //scrollY = std::max(5, std::min(175, scrollY));
  uiY = 240 - scrollY;
  currentSnapped = scrollY;
  hoverObject = int(scrollY / (180.0 / numberOfItems));

  // Render headers if required
  //bool renderHeaders = false; // Modify this condition based on your requirements
  //if (numberOfItems > 0 && itemHeaders != nullptr && renderHeaders) {
  //    Paint_DrawString_EN(20, 100, itemHeaders[hoverObject].c_str(), &Font12, YELLOW, RED);
  //    LCD_1IN28_DisplayWindows(0, 100, 180, 112, BlackImage);
  //}

  // Determine if scrolling is happening
  scrolling = draggingScrollE || std::abs(int(scrollV)) > 1;

  // Return values
  std::list<int> resultList;
  resultList.push_back(scrollY);
  resultList.push_back(scrolling ? 1 : 0);
  resultList.push_back(hoverObject);

  return resultList;
}


void sendText(const char* text) {  //new
  vreg_set_voltage(VREG_VOLTAGE_1_30);
  delay(5);
  set_sys_clock_khz(400000, true);
  digitalWrite(sendPin, HIGH);
  delay(300);
  digitalWrite(sendPin, LOW);

  lastfpstick = millis();
  //String text = textE;
  //text += '\0';
  //for (int i = 0; i < text.length(); i++) {
  int lastTime = 0;
  delay(5);  //20
  for (int i = 0; text[i] != '\0'; i++) {
    lastfpstick = millis();
    digitalWrite(sendPin, LOW);
    delay(10);  //10
    bool lastA = LOW;
    digitalWrite(sendPin, HIGH);
    delay(5);
    digitalWrite(sendPin, LOW);
    //Serial.println("F");
    for (int j = 0; j < 8; j++) {
      //Serial.println("G");
      if (text[i] & (1 << j)) {
        digitalWrite(sendPin, HIGH);
      } else {
        digitalWrite(sendPin, LOW);
      }
      delay(2);
      //Serial.println("wait for other dude");
      lastTime = millis();
      while (digitalRead(receivePin) == lastA && millis() - lastTime < 100) {}
      lastA = digitalRead(receivePin);
      if (millis() - lastTime >= 100) {
        BLEconnected = false;
        break;
        break;
      } else {
        BLEconnected = true;
      }
    }
    digitalWrite(sendPin, LOW);
  }

  delay(10);
  digitalWrite(sendPin, LOW);
  delay(10);
  lastfpstick = millis();
  bool last = LOW;
  digitalWrite(sendPin, HIGH);
  delay(5);
  digitalWrite(sendPin, LOW);
  for (int j = 0; j < 8; j++) {
    digitalWrite(sendPin, ('\0' >> j) & 1);
    //    if ('\0' & (1 << j)) {
    //      digitalWrite(sendPin, HIGH);
    //    } else {
    //      digitalWrite(sendPin, LOW);
    //    }
    delay(5);
    lastTime = millis();
    while (digitalRead(receivePin) == last && millis() - lastTime < 100) {}
    last = digitalRead(receivePin);
  }
  Serial.println("Done");
  lastfpstick = millis();

  digitalWrite(sendPin, LOW);
}


void sendTextO_L_D(const char* text) {  //1000 delay works well //same with 50
  vreg_set_voltage(VREG_VOLTAGE_1_30);
  delay(10);
  set_sys_clock_khz(400000, true);
  int lastOne = 0;
  digitalWrite(D28, HIGH);  //SHOULD BE LOW
  delay(2);
  digitalWrite(D27, HIGH);
  delay(20);               //was 700 //was 210? or 110 WAS 20
  digitalWrite(D27, LOW);  //SHOULD BE LOW
  delay(50);               //was2
  //digitalWrite(D26, LOW); //NO LONGER USED
  delay(100);
  for (int bit = 0; bit < 8; bit++) {
    digitalWrite(D27, (' ' >> bit) & 1);
    delay(6);  //was 6
    if (lastOne == 0) {
      lastOne = 1;
      digitalWrite(D28, HIGH);
    } else {
      lastOne = 0;
      digitalWrite(D28, LOW);
    }
    delay(6);  // Adjust this delay as needed
  }
  for (size_t i = 0; text[i] != '\0'; i++) {  //text[i] != '\0';
    //int lastOne = 0;
    //digitalWrite(D18, HIGH);
    for (int bit = 0; bit < 8; bit++) {
      digitalWrite(D27, (text[i] >> bit) & 1);
      delay(5);  //was 5
      if (lastOne == 0) {
        lastOne = 1;
        digitalWrite(D28, HIGH);
      } else {
        lastOne = 0;
        digitalWrite(D28, LOW);
      }
      delay(7);  // Adjust this delay as needed was 6---7
    }
    //digitalWrite(D18, LOW);
  }
  delay(20);
  for (int bit = 0; bit < 8; bit++) {
    digitalWrite(D27, ('\0' >> bit) & 1);
    delay(6);  //was 68
    if (lastOne == 0) {
      lastOne = 1;
      digitalWrite(D28, HIGH);
    } else {
      lastOne = 0;
      digitalWrite(D28, LOW);
    }
    delay(3);  // Adjust this delay as needed8
  }
  delay(20);
  for (int bit = 0; bit < 8; bit++) {
    digitalWrite(D27, ('\0' >> bit) & 1);
    delay(6);  //was 6
    if (lastOne == 0) {
      lastOne = 1;
      digitalWrite(D28, HIGH);
    } else {
      lastOne = 0;
      digitalWrite(D28, LOW);
    }
    delay(3);  // Adjust this delay as needed
  }
  //delay(50);
  //digitalWrite(D28, HIGH);
  delay(50);
  digitalWrite(D28, LOW);

  if (runningAppName == "home") {
    set_sys_clock_khz(32000, true);
    delay(10);
    vreg_set_voltage(VREG_VOLTAGE_0_90);
  }
}





//Bluetooth GPIO RECEIVE
//char receivedText[32] = "";
int lastState;
int curState;
int timeRec = 0;
char receiveCharO_L_D() {
  char receivedChar = 0;
  for (int bit = 0; bit < 8; bit++) {
    timeRec = millis();
    while (lastState == curState && millis() - timeRec < 5000) {
      //Serial.println(lastState);
      //Serial.println(curState);
      curState = digitalRead(17);
      //if(digitalRead(18) == LOW){
      //  break;
      //}
    }
    //Serial.println("newChar");
    lastState = curState;
    receivedChar |= (digitalRead(16) << bit);
    //delayMicroseconds(60); // Adjust this delay as needed
  }
  //Serial.println(receivedChar);
  return receivedChar;
}

char* receivedTextMAIN;
void receiveText() {
  char receivedText[2048] = "";
  int index = 0;
  bool lastForSpeed = LOW;
  bool current = LOW;
  while (true) {
    lastfpstick = millis();
    char receivedChar = 0;
    bool last = LOW;
    digitalWrite(sendPin, LOW);
    //Serial.println("WAiting for Okay");
    while (digitalRead(receivePin) == LOW) {}
    //Serial.println("Okay ACK");
    delay(8);
    for (int i = 0; i < 8; i++) {
      int startSpeed = millis();
      while (millis() - startSpeed <= 8 && digitalRead(receivePin) == lastForSpeed) {}
      if (digitalRead(receivePin) != lastForSpeed) {
        delay(2);
      }
      //delay(8);  //8 to play it safee 7 best 6 100
      current = digitalRead(receivePin);
      receivedChar |= (current << i);
      lastForSpeed = current;
      if (last == HIGH) {
        digitalWrite(sendPin, LOW);
        last = LOW;
      } else {
        digitalWrite(sendPin, HIGH);
        last = HIGH;
      }
    }
    if (receivedChar == '\0') {
      //Serial.print(receivedText);
      break;
    } else {
      receivedText[index++] = receivedChar;
      //Serial.println(receivedChar);
    }
  }
  digitalWrite(sendPin, LOW);
  Serial.println(receivedText);
  receivedTextMAIN = receivedText;
}

char receiveChar() {  //new
  char receivedChar = 0;
  bool last = LOW;
  digitalWrite(sendPin, LOW);
  while (digitalRead(receivePin) == LOW) {}
  delay(15);
  for (int i = 0; i < 8; i++) {
    delay(1);  //100
    receivedChar |= (digitalRead(receivePin) << i);
    if (last == HIGH) {
      digitalWrite(sendPin, LOW);
      last = LOW;
    } else {
      digitalWrite(sendPin, HIGH);
      last = HIGH;
    }
  }
  Serial.println(receivedChar);
  return receivedChar;
}





String removeQuotes(String text) {
  if (text.length() >= 2 && text.charAt(0) == '"' && text.charAt(text.length() - 1) == '"') {
    return text.substring(1, text.length() - 1);  // Remove first and last characters
  }
  return text;
}

std::list<std::string> splitStringA(const std::string& input, char delimiter) {
  std::list<std::string> resultList;
  std::istringstream iss(input);
  std::string token;

  while (std::getline(iss, token, delimiter)) {
    resultList.push_back(token);
  }

  return resultList;
}


std::list<std::string> split(const std::string& s, char seperator) {
  std::list<std::string> output;
  std::string::size_type prev_pos = 0, pos = 0;
  while ((pos = s.find(seperator, pos)) != std::string::npos) {
    std::string substring(s.substr(prev_pos, pos - prev_pos));
    output.push_back(substring);
    prev_pos = ++pos;
  }
  output.push_back(s.substr(prev_pos, pos - prev_pos));  // Last word
  return output;
}

std::list<std::list<std::string>> foundContacts = {
  //Contacts
  { "Person", "PHONENUMBER" },
  { "SOMEGUY", "PHONENUMBER2" },
};

std::string weatherTemp = "Unknown";
std::string weatherDesc = "Unknown";
std::list<std::string> newsTitle = {};

std::string title = "";
std::string content = "";
bool timedOut = false;

void awareNess() {
  vreg_set_voltage(VREG_VOLTAGE_1_30);
  delay(5);
  set_sys_clock_khz(400000, true);
  Paint_DrawRectangle(10, 215, 230, 235, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawString_EN(82, 220, "Check Aware", &Font12, DARKGRAY, YELLOW);  //7
  LCD_1IN28_DisplayWindows(10, 215, 230, 235, BlackImage);
}

void checkNotif() {
  if (digitalRead(18) == HIGH) {  //digitalRead(18) == HIGH
    //Serial.println("HIGH");
    vreg_set_voltage(VREG_VOLTAGE_1_30);
    delay(5);
    set_sys_clock_khz(400000, true);
    Paint_DrawRectangle(10, 215, 230, 235, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawString_EN(82, 220, "Device Busy", &Font12, DARKGRAY, RED);  //7
    LCD_1IN28_DisplayWindows(10, 215, 230, 235, BlackImage);
    lastfpstick = millis();
    tapHeld = 0;
    Serial.println("RUN");

    delay(5);
    digitalWrite(sendPin, HIGH);
    delay(5);
    digitalWrite(sendPin, LOW);
    delay(5);
    //tap=false;
    // LISTEN TO DATA


    /*
    char receivedText[2048] = "";
    int index = 0;
    int lastState = 0;  //digitalRead(17);
    int curState = lastState;
    timedOut = false;
    //digitalWrite(26, HIGH);
    //delay(500);
    //digitalWrite(26, LOW);
    //delay(5);
    //runningApp();
    int totalTimeToRec = millis();
    while (millis() - totalTimeToRec < 60000) {  //can't take longer than 30seconds to receieve
      //runningApp(); //If an app is too laggy / slow it will cause issues, and yeah
      char receivedChar = receiveChar();
      if (receivedChar == '\0') {
        break;  // End of transmission
      }
      if (receivedChar != '\2') {
        receivedText[index++] = receivedChar;
      }
    }
    if (millis() - totalTimeToRec > 60000) {
      timedOut = true;
      Serial.println("Took too long.");
    }
    */
    //char receivedText[2048] = "";
    int a = millis();
    idleTime = millis();
    while (digitalRead(18) == HIGH && millis() - a < 10000) { lastfpstick = millis(); }
    lastfpstick = millis();
    if (millis() - a < 10000) {
      receiveText();
      idleTime = millis();
      lastfpstick = millis();

      Serial.print("DATA GOT");
      Serial.println(receivedTextMAIN);
      //runningApp(); //certainly, not recommened anymore, because of internet


      JSONVar myObject = JSON.parse(receivedTextMAIN);
      std::string appNotif = removeQuotes(JSON.stringify(myObject["app"])).c_str();
      title = removeQuotes(JSON.stringify(myObject["title"])).c_str();
      content = removeQuotes(JSON.stringify(myObject["text"])).c_str();
      //NO LONGER NEEDED?????????????????? receivedText[index] = '\0';

      Serial.println(receivedTextMAIN);

      //runningApp(); //certainly, not recommened anymore, because of internet

      if (receivedTextMAIN != "" && receivedTextMAIN != " " && myObject != "") {
        BLEconnected = true;
      }
      if (appNotif == "messages") {
        std::string phoneNumber = title;
        std::string foundContactName;

        for (const auto& contact : foundContacts) {
          if (contact.size() >= 2 && contact.back() == phoneNumber) {
            foundContactName = contact.front();
            break;
          }
        }

        if (foundContactName.empty()) {
          foundContactName = phoneNumber;
        }
        Serial.println(removeQuotes(JSON.stringify(myObject["app"])).c_str());

        notifications.push_back({ phoneNumber, "messages", content, foundContactName });
        //Paint_DrawString_EN(100, 100, receivedText, &Font16, BLACK, RED);
        //Serial.println(receivedText); // Print received NFC data

        //if (runningAppName == "home") {
        //  Paint_DrawRectangle(0, 0, 240, 240, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        //  Paint_DrawRectangle(120 - ((17 * content.length()) / 2) - 10, 100, ((17 * content.length()) / 2) + 10, 134, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        //  Paint_DrawString_EN(120 - ((17 * content.length()) / 2), 110, content.c_str(), &Font24, DARKGRAY, WHITE);
        //  LCD_1IN28_Display(BlackImage);
        //}
        digitalWrite(D28, HIGH);
        delay(250);
        digitalWrite(D28, LOW);
        delay(200);
        digitalWrite(D28, HIGH);
        delay(200);
        digitalWrite(D28, LOW);
        //DEV_SET_PWM(2);
        //delay(100);
        //DEV_SET_PWM(100);
        //delay(200);
        //DEV_SET_PWM(2);
        //delay(400);
        //DEV_SET_PWM(100);
        //delay(300);
      } else if (appNotif == "weather") {
        weatherTemp = content;
        weatherDesc = title;
      } else if (appNotif == "news") {
        Serial.println(content.c_str());
        String newsTitleString = content.c_str();
        newsTitle = split(content, '\242');
        Serial.println(newsTitle.front().c_str());
      } else if (appNotif == "con") {
        if (content == "con") {
          BLEconnected = true;
        } else {
          BLEconnected = false;
        }
      } else {
        if (BLEconnected) {
          Serial.println("Unknown Data");
          BLEconnected = false;
        }
      }
      lastfpstick = millis();
      idleTime = millis();
      LCD_1IN28_DisplayWindows(10, 215, 230, 235, BlackImage);
      if (runningAppName == "home") {
        if (aod && batSaver == false) {
          DEV_SET_PWM(2);
        } else {
          LCD_1IN28_Clear(BLACK);
          DEV_SET_PWM(0);
        }
        set_sys_clock_khz(32000, true);
        delay(10);
        vreg_set_voltage(VREG_VOLTAGE_0_90);
      }
    }
  }
}

bool button(int x, int y, const char* text, sFONT* Font, UWORD Color_Foreground, UWORD Color_Background, int size) {
  appSize = 45;   //35 Adjust as needed
  appLeng = 140;  //140

  if (size == 0) {
    Paint_DrawRectangle(x + 18, y + 0, x + 123, y + 1, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 12, y + 1, x + 128, y + 2, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 11, y + 2, x + 129, y + 3, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 9, y + 3, x + 131, y + 4, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 8, y + 4, x + 132, y + 5, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 7, y + 5, x + 133, y + 6, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 7, y + 6, x + 134, y + 7, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 6, y + 7, x + 135, y + 8, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 5, y + 8, x + 136, y + 9, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 5, y + 9, x + 136, y + 10, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 4, y + 10, x + 137, y + 11, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 4, y + 11, x + 137, y + 12, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 4, y + 12, x + 138, y + 13, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 3, y + 13, x + 138, y + 14, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 2, y + 14, x + 138, y + 15, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 2, y + 15, x + 139, y + 16, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 2, y + 16, x + 139, y + 17, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 2, y + 17, x + 139, y + 18, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 2, y + 18, x + 139, y + 19, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 1, y + 19, x + 139, y + 20, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 1, y + 20, x + 139, y + 21, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 1, y + 21, x + 139, y + 22, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 1, y + 22, x + 139, y + 23, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 2, y + 23, x + 139, y + 24, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 2, y + 24, x + 139, y + 25, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 2, y + 25, x + 139, y + 26, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 2, y + 26, x + 139, y + 27, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 2, y + 27, x + 139, y + 28, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 2, y + 28, x + 139, y + 29, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 3, y + 29, x + 138, y + 30, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 3, y + 30, x + 138, y + 31, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 3, y + 31, x + 138, y + 32, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 4, y + 32, x + 137, y + 33, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 4, y + 33, x + 137, y + 34, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 5, y + 34, x + 136, y + 35, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 5, y + 35, x + 136, y + 36, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 6, y + 36, x + 135, y + 37, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 7, y + 37, x + 134, y + 38, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 8, y + 38, x + 133, y + 39, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 9, y + 39, x + 132, y + 40, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 11, y + 40, x + 131, y + 41, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 11, y + 41, x + 130, y + 42, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 13, y + 42, x + 128, y + 43, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 15, y + 43, x + 127, y + 44, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  } else {
    Paint_DrawRectangle(x + 19, y + 2, x + 141, y + 3, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 13, y + 3, x + 147, y + 4, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 12, y + 4, x + 148, y + 5, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 10, y + 5, x + 151, y + 6, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 9, y + 6, x + 152, y + 7, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 8, y + 7, x + 153, y + 8, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 7, y + 8, x + 154, y + 9, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 7, y + 9, x + 155, y + 10, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 6, y + 10, x + 156, y + 11, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 6, y + 11, x + 157, y + 12, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 5, y + 12, x + 158, y + 13, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 5, y + 13, x + 158, y + 14, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 4, y + 14, x + 159, y + 15, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 4, y + 15, x + 159, y + 16, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 3, y + 16, x + 159, y + 17, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 3, y + 17, x + 160, y + 18, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 3, y + 18, x + 160, y + 19, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 3, y + 19, x + 160, y + 20, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 3, y + 20, x + 160, y + 21, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 3, y + 21, x + 160, y + 22, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 2, y + 22, x + 161, y + 23, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 2, y + 23, x + 161, y + 24, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 2, y + 24, x + 161, y + 25, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 3, y + 25, x + 160, y + 26, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 3, y + 26, x + 160, y + 27, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 3, y + 27, x + 160, y + 28, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 3, y + 28, x + 160, y + 29, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 3, y + 29, x + 160, y + 30, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 3, y + 30, x + 159, y + 31, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 4, y + 31, x + 159, y + 32, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 4, y + 32, x + 159, y + 33, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 4, y + 33, x + 158, y + 34, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 5, y + 34, x + 158, y + 35, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 5, y + 35, x + 157, y + 36, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 6, y + 36, x + 157, y + 37, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 6, y + 37, x + 156, y + 38, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 7, y + 38, x + 155, y + 39, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 8, y + 39, x + 154, y + 40, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 9, y + 40, x + 153, y + 41, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 10, y + 41, x + 152, y + 42, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 12, y + 42, x + 151, y + 43, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 12, y + 43, x + 149, y + 44, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 14, y + 44, x + 147, y + 45, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 16, y + 45, x + 145, y + 46, Color_Foreground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  }
  Paint_DrawString_EN(x + 5, y + ((appSize / 2) - 8), text, Font, Color_Foreground, Color_Background);  //(x + appLeng) - (std::strlen(key.c_str())*11) - 1,font8 0x009688
  if (inTransition == false && !pauseRender) {
    if (Touch_CTS816.x_point >= x && Touch_CTS816.x_point <= x + appLeng && Touch_CTS816.y_point >= y && Touch_CTS816.y_point <= y + appSize) {
      if (tap && !watchSwipe && !otherSwipe && !inTransition && !pauseRender) {
        if (tapHeld <= 1) {
          tap = false;
          tapHeld = 999;
          return true;
        }
      }
    }
  }
  return false;
}

//Cleaned up some code
//Notification Pane; changed "No new notifications" to "No notifications"
//Minor Error Handling and Resetting
//**Battery Saver** and more settings
//Reset on self
//Notification Popup when device is off
//Stability, and Battery Adjustments
//Faster and Smoother Experience
//**Better Comunication between Seeed and RP2040**
//**Networking/Internet** (Use of networking can be found in Settings -> System -> Check VERS
//Releasing DEV Mobile App for Testing (Required for Texting, Networking, Weather, News, Etc)
//Fonts

//Must use toilets from https://ptsv3.com/ because of data transmission limits
int networkTimeOut = 0;
void internet_post(std::string toilet, std::string data) {
  lastfpstick = millis();
  Paint_DrawRectangle(10, 215, 230, 235, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawString_EN(82, 220, "Netwrk Busy", &Font12, DARKGRAY, RED);  //7
  LCD_1IN28_DisplayWindows(10, 215, 230, 235, BlackImage);
}

std::string internet_get(std::string toilet) {
  lastfpstick = millis();
  Paint_DrawRectangle(10, 215, 230, 235, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawString_EN(82, 220, "Netwrk Busy", &Font12, DARKGRAY, RED);  //7
  LCD_1IN28_DisplayWindows(10, 215, 230, 235, BlackImage);
  //delay(100);  //1200
  lastfpstick = millis();
  std::string text = "inet" + toilet;
  message = text.c_str();
  sendText(message);
  lastfpstick = millis();
  //delay(100);  //500
  //lastfpstick = millis();
  title = "";
  content = "";
  timedOut = false;
  lastfpstick = millis();
  networkTimeOut = millis();
  while (title != "iNet" && timedOut == false && millis() - networkTimeOut < 15000) {
    checkNotif();
    lastfpstick = millis();
    delay(10);
  }
  lastfpstick = millis();  //don't ask questions, its me being lazy
  Serial.println(content.c_str());
  if (timedOut || millis() - networkTimeOut >= 15000) {
    content = "Timed Out.";
  }
  //delay(100);  //1200
  lastfpstick = millis();
  idleTime = millis();
  LCD_1IN28_DisplayWindows(10, 215, 230, 235, BlackImage);
  return content;
}


void transitionLR(std::string app, int begin = 0) {
  AppPtr func = apps[app];
  inTransition = true;
  int transP = begin;
  Paint_DrawRectangle(0, 0, min(max(transP, 0), 240), 240, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  func();
  LCD_1IN28_DisplayWindows(0, 0, begin, 240, BlackImage);
  float transV = 50;  ///((begin/240)+1);//25-(25*(begin/240)); //pos
  while (transP < 246) {
    transV = transV / 1.18;
    //Paint_DrawRectangle(0, 0, min(max(transP, 0),240), 240, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    func();
    //Paint_DrawRectangle(min(max(transP, 0),240), 0, min(transP+6, 240), 240, 0xF81F, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    //func();
    LCD_1IN28_DisplayWindows(max(0, int(transP - (transV * 1.2))), 0, min(transP + 1, 240), 240, BlackImage);
    transP += transV;
  }
  inTransition = false;
  //func();
}
void transitionRL(std::string app, int begin = 240) {  //bad
  AppPtr func = apps[app];
  inTransition = true;
  int transP = begin;
  Paint_DrawRectangle(240, 0, min(max(transP, 0), 240), 240, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  func();
  LCD_1IN28_DisplayWindows(begin, 0, 240, 240, BlackImage);
  float transV = -50;  ///(((240-begin)/240)+1);//-(25-(25*((240-begin)/240))); //neg;
  while (transP > -6) {
    transV = transV / 1.18;
    //Paint_DrawRectangle(240, 0, min(max(transP, 0),240), 240, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    func();
    //Paint_DrawRectangle(min(max(transP, 0),240), 0, max(0,transP-6), 240, 0xF81F, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    //func();
    LCD_1IN28_DisplayWindows(max(0, transP - 1), 0, min(int(transP + (-transV * 1.2)), 240), 240, BlackImage);
    transP += transV;
  }
  inTransition = false;
  //func();
}
void transitionUD(std::string app, int begin = 0) {
  AppPtr func = apps[app];
  inTransition = true;
  int transP = begin;
  Paint_DrawRectangle(0, 0, 240, min(max(transP, 0), 240), BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  func();
  LCD_1IN28_DisplayWindows(0, 0, 240, begin, BlackImage);
  float transV = 50;  ///((begin/240)+1);//25-(25*(begin/240)); //pos
  while (transP < 246) {
    transV = transV / 1.18;  //1.08 @ 25
    //Paint_DrawRectangle(0, 0, 240, min(max(transP, 0),240), BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    func();
    //Paint_DrawRectangle(0, min(max(transP, 0),240), 240, min(transP+6, 240), 0xF81F, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    //func();
    LCD_1IN28_DisplayWindows(0, max(0, int(transP - (transV * 1.2))), 240, min(transP + 1, 240), BlackImage);
    transP += transV;
  }
  inTransition = false;
  //func();
}
void transitionDU(std::string app, int begin = 240) {  //bad
  AppPtr func = apps[app];
  inTransition = true;
  int transP = begin;  //240 -
  Paint_DrawRectangle(0, 0, min(max(transP, 0), 240), 240, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  func();
  LCD_1IN28_DisplayWindows(0, begin, 240, 240, BlackImage);
  float transV = -50;  ///(((240-begin)/240)+1);//-(25-(25*((240-begin)/240))); //neg;
  while (transP > -6) {
    transV = transV / 1.18;
    //Paint_DrawRectangle(0, 0, min(max(transP, 0),240), 240, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    func();
    //Paint_DrawRectangle(0, min(max(transP, 0),240), 240, max(0,transP-6), 0xF81F, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    //func();
    LCD_1IN28_DisplayWindows(0, max(0, transP - 1), 240, min(int(transP + (-transV * 1.2)), 240), BlackImage);
    transP += transV;
  }
  inTransition = false;
  //func();
}

void smallDelay() {
  asm volatile(
    "nop \n\t"  // No operation
    "nop \n\t"  // No operation
    "nop \n\t"  // No operation
    "nop \n\t"  // No operation
    "nop \n\t"  // No operation
    "nop \n\t"  // No operation
    "nop \n\t"  // No operation
    "nop \n\t"  // No operation
  );
}

void transitionRAND(std::string app) {  //bad
  AppPtr func = apps[app];
  inTransition = true;
  Paint_DrawRectangle(0, 0, 240, 240, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  func();
  bool rendered[240][240] = { false };
  for (int y = 0; y < 120; y++) {
    for (int x = 0; x < 120; x++) {
      int randX, randY;
      // Find a random pixel that hasn't been rendered yet
      do {
        randX = random(0, 120) * 2;
        randY = random(0, 120) * 2;
      } while (rendered[randX][randY]);
      //Serial.println(randX);

      LCD_1IN28_DisplayWindows(randX, randY, randX + 2, randY + 2, BlackImage);
      rendered[randX][randY] = true;
      //delay(1);
      //smallDelay();
    }
  }
  inTransition = false;
  //func();
}

void transitionDOWNRAND(std::string app) {  //bad
  AppPtr func = apps[app];
  inTransition = true;
  Paint_DrawRectangle(0, 0, 240, 240, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  func();
  bool rendered[240][240] = { false };
  for (int y = 0; y < 240; y++) {
    for (int x = 0; x < 120; x++) {
      int randX;
      // Find a random pixel that hasn't been rendered yet
      do {
        randX = random(0, 120) * 2;
      } while (rendered[randX][y * 1]);
      //Serial.println(randX);

      LCD_1IN28_DisplayWindows(randX, y * 2, randX + 2, (y * 1) + 2, BlackImage);
      rendered[randX][y * 1] = true;
      //delay(1);
      //smallDelay();
    }
  }
  inTransition = false;
  //func();
}

void openApp(std::string app, std::string dir = "", int start = -1) {
  vreg_set_voltage(VREG_VOLTAGE_1_30);
  delay(10);
  set_sys_clock_khz(400000, true);
  idleTime = millis();
  speedMode = false;
  if (app == "home") {
    DEV_SET_PWM(5);
  } else {
    DEV_SET_PWM(100);
  }
  //DEV_Delay_ms(1);
  inTransition = true;
  AppPtr func = apps[app];
  tap = false;
  tapHeld = 0;
  flag = 0;
  last = 0;
  scrollY = 0;
  scrollV = 0;
  last2 = 0;
  startup = true;
  otherSwipe = false;
  watchSwipe = false;
  if (runningAppName != "boot") {
    runningApp();
  }
  if (start == -1) {
    if (dir == "DU" || dir == "RL") {
      start = 240;
    } else {
      start = 0;
    }
  }
  if (dir == "LR") {
    transitionLR(app, start);
  } else if (dir == "RL") {
    transitionRL(app, start);
  } else if (dir == "UD") {
    transitionUD(app, start);
  } else if (dir == "DU") {
    transitionDU(app, start);
    //transitionDOWNRAND(app);
  } else if (dir == "RAND") {
    transitionRAND(app);
  }
  //DEV_Delay_ms(1);
  lastUsedAppName = runningAppName;
  runningApp = apps[app];
  runningAppName = app;
  if (std::find(systemApps.begin(), systemApps.end(), app) == systemApps.end()) {
    if (std::find(backgroundApps.begin(), backgroundApps.end(), app) == backgroundApps.end()) {
      backgroundApps.push_back(app);
    }
  }
  //Paint_Clear(BLACK);
  //DEV_Delay_ms(1);
  last = 0;
  last2 = 0;
  inTransition = true;
  Paint_DrawRectangle(0, 0, 240, 240, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  runningApp();
  LCD_1IN28_DisplayWindows(0, 0, 240, 240, BlackImage);

  //DEV_Delay_ms(1);
  inTransition = false;
  //Paint_Clear(BLACK);
  //runningApp();
  //LCD_1IN28_DisplayWindows(0, 0, 240, 240, BlackImage);

  last = 0;
  last2 = 0;
  if (app == "home") {
    LCD_1IN28_DisplayWindows(0, 0, 240, 240, BlackImage);
    DEV_Delay_ms(1);
    LCD_1IN28_DisplayWindows(0, 0, 240, 240, BlackImage);
    set_sys_clock_khz(80000, true);
    delay(10);
    vreg_set_voltage(VREG_VOLTAGE_0_90);
    last2 = millis() + 99999999999;
  } else {
    if (speedMode == false) {
      medClock = true;
      turboClock = false;
      //set_sys_clock_khz(32000, true);
      //vreg_set_voltage(VREG_VOLTAGE_0_90);

      vreg_set_voltage(VREG_VOLTAGE_1_30);
      delay(10);
      set_sys_clock_khz(150000, true);  //120000
    } else {
      vreg_set_voltage(VREG_VOLTAGE_1_30);
      delay(10);
      set_sys_clock_khz(400000, true);
    }
  }
  runningApp();
  //DEV_Delay_ms(1);
  idleTime = millis();
  tickTenTen = 80;
  startup = false;
  otherSwipe = false;
  watchSwipe = false;
  pauseRender = true;
}

std::string swipeComplete = "";
bool watchSwipe = false;
int swipeStartThresh = 50;
//bool swipeDone = false;
std::string activeDir = "";
bool swipe(std::string dir, int thresh) {
  bool swipeDone = false;
  if (tap == false && otherSwipe == true && swipeComplete == "") {

    activeDir = "";
  }
  if (watchSwipe == false) {
    if (tap == false) {
      //activeDir="";
      otherSwipe = false;
    } else {
      if (dir == "down" && (activeDir == "" || activeDir == dir)) {
        if (otherSwipe) {
          if (Touch_CTS816.y_point > thresh) {
            swipeComplete = dir;
          } else {
            swipeComplete = "";
          }
          if (swipeComplete == "") {
            /////////////////////////////////////////////////////////////////////////
            //Paint_DrawRectangle(0, Touch_CTS816.y_point, 240, min(Touch_CTS816.y_point+10,240), 0xFE6B, DOT_PIXEL_1X1, DRAW_FILL_FULL);
            //TURN OFF CUZ IT CAUSES GLITCHY      LCD_1IN28_DisplayWindows(0, max(0, Touch_CTS816.y_point - 25), 240, min(Touch_CTS816.y_point + 10, 240), BlackImage);
            /////////////////////////////////////////////////////////////////////////

            //            Paint_DrawRectangle(0, Touch_CTS816.y_point, 240, max(min(Touch_CTS816.y_point-10,240),0), 0xF81F, DOT_PIXEL_1X1, DRAW_FILL_FULL);
            //            LCD_1IN28_DisplayWindows(0, max(0, Touch_CTS816.y_point-10), 240, min(Touch_CTS816.y_point+25,240), BlackImage);
          } else {
            pauseRender = true;
            Paint_DrawRectangle(0, Touch_CTS816.y_point, 240, min(Touch_CTS816.y_point + 5, 240), deviceSecondColorTheme, DOT_PIXEL_1X1, DRAW_FILL_FULL);  // + 10
            LCD_1IN28_DisplayWindows(0, max(0, Touch_CTS816.y_point - 25), 240, min(Touch_CTS816.y_point + 5, 240), BlackImage);


            //Paint_DrawRectangle(0, Touch_CTS816.y_point, 240, max(min(Touch_CTS816.y_point-10,240),0), 0xFE6B, DOT_PIXEL_1X1, DRAW_FILL_FULL);
            //LCD_1IN28_DisplayWindows(0, max(0, Touch_CTS816.y_point-10), 240, min(Touch_CTS816.y_point+25,240), BlackImage);
          }
        }
        if (Touch_CTS816.y_point < swipeStartThresh) {
          otherSwipe = true;
          activeDir = "down";
        }
      } else if (dir == "up" && (activeDir == "" || activeDir == dir)) {
        if (otherSwipe) {
          if (Touch_CTS816.y_point < 240 - thresh) {
            swipeComplete = dir;
          } else {
            swipeComplete = "";
          }
          if (swipeComplete != "") {
            //if(tapHeld>5){
            //  Paint_DrawRectangle(0, Touch_CTS816.y_point, 240, min(Touch_CTS816.y_point+10,240), 0xF81F, DOT_PIXEL_1X1, DRAW_FILL_FULL);
            //  LCD_1IN28_DisplayWindows(0, max(0, Touch_CTS816.y_point-20), 240, min(Touch_CTS816.y_point+60,240), BlackImage);
            //}
            //} else{
            //if(tapHeld>10){

            pauseRender = true;
            Paint_DrawRectangle(0, max(Touch_CTS816.y_point - 5, 0), 240, Touch_CTS816.y_point, deviceSecondColorTheme, DOT_PIXEL_1X1, DRAW_FILL_FULL);
            LCD_1IN28_DisplayWindows(0, max(Touch_CTS816.y_point - 5, 0), 240, min(Touch_CTS816.y_point + 25, 240), BlackImage);

            //Paint_DrawRectangle(0, Touch_CTS816.y_point, 240, max(min(Touch_CTS816.y_point-10,240),0), 0xFE6B, DOT_PIXEL_1X1, DRAW_FILL_FULL);
            //LCD_1IN28_DisplayWindows(0, max(0, Touch_CTS816.y_point-10), 240, min(Touch_CTS816.y_point+25,240), BlackImage);

            //}
          }
        }
        if (Touch_CTS816.y_point > 110 && Touch_CTS816.y_point < 200 && watchSwipe == false) {
          otherSwipe = true;
          activeDir = "up";
        }
      } else if (dir == "right" && (activeDir == "" || activeDir == dir)) {
        if (otherSwipe) {
          if (Touch_CTS816.x_point > thresh) {
            swipeComplete = dir;
          } else {
            swipeComplete = "";
          }
          if (swipeComplete == "") {
            /////////////////////////////////////////////////////////////////////////
            //Paint_DrawRectangle(Touch_CTS816.x_point, 0, min(Touch_CTS816.x_point+10,240), 240, 0xF81F, DOT_PIXEL_1X1, DRAW_FILL_FULL);
            //TURN OFF CUZ IT CAUSES GLITCHY       LCD_1IN28_DisplayWindows(max(0, Touch_CTS816.x_point - 25), 0, min(Touch_CTS816.x_point + 10, 240), 240, BlackImage);  //-25, and +10
            /////////////////////////////////////////////////////////////////////////
          } else {
            pauseRender = true;
            Paint_DrawRectangle(Touch_CTS816.x_point, 0, max(min(Touch_CTS816.x_point + 5, 240),0), 240, deviceSecondColorTheme, DOT_PIXEL_1X1, DRAW_FILL_FULL);
            LCD_1IN28_DisplayWindows(max(0, Touch_CTS816.x_point - 25), 0, min(Touch_CTS816.x_point + 5, 240), 240, BlackImage);
          }
        }
        if (Touch_CTS816.x_point < swipeStartThresh) {
          otherSwipe = true;
          activeDir = "right";
        }
      } else if (dir == "left" && (activeDir == "" || activeDir == dir)) {
        if (otherSwipe) {
          if (Touch_CTS816.x_point < 240 - thresh) {
            swipeComplete = dir;
          } else {
            swipeComplete = "";
          }
          if (swipeComplete == "") {
            /////////////////////////////////////////////////////////////////////////
            //Paint_DrawRectangle(Touch_CTS816.x_point, 0, max(min(Touch_CTS816.x_point-10,240),0), 240, 0xF81F, DOT_PIXEL_1X1, DRAW_FILL_FULL);
            //TURN OFF CUZ IT CAUSES GLITCHY STUFF WHEN HOLDING STILL   LCD_1IN28_DisplayWindows(max(0, Touch_CTS816.x_point - 10), 0, min(Touch_CTS816.x_point + 25, 240), 240, BlackImage);  //should be +25
            /////////////////////////////////////////////////////////////////////////
          } else {
            pauseRender = true;
            Paint_DrawRectangle(max(min(Touch_CTS816.x_point - 5, 240), 0), 0, Touch_CTS816.x_point, 240, deviceSecondColorTheme, DOT_PIXEL_1X1, DRAW_FILL_FULL);
            LCD_1IN28_DisplayWindows(max(0, Touch_CTS816.x_point - 5), 0, min(Touch_CTS816.x_point + 25, 240), 240, BlackImage);  //and the other - should be -10
          }
        }
        if (Touch_CTS816.x_point > 240 - swipeStartThresh) {
          otherSwipe = true;
          activeDir = "left";
        }
      }
    }
    if (swipeComplete == activeDir && activeDir != "") {
      if (tap == false) {
        if (dir == "down" && (activeDir == "" || activeDir == dir)) {
          if (Touch_CTS816.y_point > thresh) {
            swipeDone = true;
            swipeComplete = "";
            activeDir = "";
          } else {
            swipeComplete = "";
            activeDir = "";
          }
        } else if (dir == "up" && (activeDir == "" || activeDir == dir)) {
          if (Touch_CTS816.y_point < 240 - thresh) {
            swipeDone = true;
            swipeComplete = "";
            activeDir = "";
          } else {
            swipeComplete = "";
            activeDir = "";
          }
        } else if (dir == "right" && (activeDir == "" || activeDir == dir)) {
          if (Touch_CTS816.x_point > thresh) {
            swipeDone = true;
            swipeComplete = "";
            activeDir = "";
          } else {
            swipeComplete = "";
            activeDir = "";
          }
        } else if (dir == "left" && (activeDir == "" || activeDir == dir)) {
          if (Touch_CTS816.x_point < 240 - thresh) {
            swipeDone = true;
            swipeComplete = "";
            activeDir = "";
          } else {
            swipeComplete = "";
            activeDir = "";
          }
        }  // else {
        //  swipeComplete="";
        //}
      }
    }
  }

  if (swipeDone == false && swipeComplete == dir && tap == false) {
    swipeDone = true;
    swipeComplete = "";
    activeDir = "";
  }

  if (otherSwipe && watchSwipe == false && swipeComplete != "") {  //swipeComplete thing new cuz whenever I tap on side it paused .. so yuck
    pauseRender = true;
  } else {
    pauseRender = false;
  }

  //if(swipeDone==false){
  //  if(tap){
  //    activeDir=dir;
  //  }
  //}

  //if(activeDir!=""){
  //  inTransition = true;
  //} else{
  //  inTransition = false;
  //}

  if (tap == false && otherSwipe == true && swipeComplete == "" && swipeDone == false) {
    if (swipeComplete == "") {
      if (activeDir != "up") {
        if (tapHeld == 0) {
          Paint_Clear(BLACK);
        }
        //LCD_1IN28_DisplayWindows(0, 0, 240, 240, BlackImage);
      } else if (tapHeld > 8) {
        Paint_Clear(BLACK);
        //LCD_1IN28_DisplayWindows(0, 0, 240, 240, BlackImage);
      }
    }
  }

  return swipeDone;
}

uint16_t findTextColor(const std::string& text) {
  if (colorCache.find(text) != colorCache.end()) {
    return colorCache[text];
  } else {
    std::hash<std::string> hasher;
    size_t hashValue = hasher(text);

    // Incorporate text length
    size_t lengthFactor = text.length();

    // Apply non-linear transformation to the hash value
    hashValue = hashValue * hashValue;  // Square the hash value

    // Multiply hash value by length factor
    hashValue *= lengthFactor;

    // Extract color components from the modified hash value
    uint8_t red = static_cast<uint8_t>((hashValue >> 16) & 0xFF);
    uint8_t green = static_cast<uint8_t>((hashValue >> 8) & 0xFF);
    uint8_t blue = static_cast<uint8_t>(hashValue & 0xFF);

    // Ensure the color is not too dark
    if (red + green + blue < 400) {
      red = max(50, red);
      green = max(80, green);
      blue = max(70, blue);
      if (red < 120 && green < 120 && blue < 120) {
        red = 120;
        green = 120;
        blue = 120;
      }
    }

    // Combine color components into uint16_t format
    uint16_t color = (red << 11) | (green << 5) | blue;
    colorCache[text] = color;

    return color;
  }
}

void runNextService() {
  if (!services.empty()) {
    Service nextService = services.front();  // Get the next service
    services.pop_front();                    // Remove the next service from the front
    services.push_back(nextService);         // Move the next service to the back
    Serial.print("Running service: ");
    Serial.println(nextService.name);
    nextService.function();  // Call the function
  }
}

void runAllServices() {
  Paint_DrawRectangle(10, 215, 230, 235, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawString_EN(82, 220, "Device Busy", &Font12, DARKGRAY, RED);  //7
  LCD_1IN28_DisplayWindows(10, 215, 230, 235, BlackImage);
  int numServices = services.size();
  for (int i = 0; i < numServices; ++i) {
    Serial.print("Running service ");
    Serial.print(i + 1);
    Serial.print(" of ");
    Serial.println(numServices);
    runNextService();
    delay(1000);
  }
  LCD_1IN28_DisplayWindows(10, 215, 230, 235, BlackImage);
}

void addService(const String& name, ServiceFunction function) {
  // Check if the service already exists
  for (const auto& service : services) {
    if (service.name == name) {
      Serial.print("Service '");
      Serial.print(name);
      Serial.println("' already exists, skipping addition.");
      return;  // Exit the function if the service already exists
    }
  }

  // Add the new service if it doesn't exist
  services.push_back({ name, function });
  Serial.print("Added new service: ");
  Serial.println(name);
}
int serviceLastRan = 0;

int homeAppLowPower = 1000;
int HourMinSize = 4;
void home() {
  float resultButINeedPrivates = DEC_ADC_Read() * (3.3f / (1 << 12) * 2);
  unsigned long elapsed_time = millis() + CurTime;  // + 46800000 + 2400000
  unsigned long hours = (elapsed_time % 86400000) / 3600000;
  unsigned long minutes = (elapsed_time % 3600000);
  unsigned long seconds = (elapsed_time % 60000);

  lastfpstick = millis();

  if (batSaver == false) {
    checkNotif();
  }

  //ALSO DISPLAY BAT PERCENT.
  if (aod && batSaver == false) {
    if (resultButINeedPrivates > 2.9) {
      Paint_DrawCircle(120, 120, 118, GREEN, DOT_PIXEL_2X2, DRAW_FILL_EMPTY);
    }

    if (elapsed_time - last2 > homeAppLowPower || inTransition) {
      //uint16_t second_x = 120 - (int)(110 * sin((seconds * 6 + 180) * PI / 180));
      //uint16_t second_y = 120 + (int)(110 * cos((seconds * 6 + 180) * PI / 180));
      //Paint_DrawLine(120, 120, (uint16_t)second_x, (uint16_t)second_y, 0x009688, DOT_PIXEL_2X2, LINE_STYLE_SOLID); // Replace 0x4CAF50 with your chosen color
      //Paint_DrawCircle((uint16_t)second_x, (uint16_t)second_y, 3, 0x009688, DOT_PIXEL_1X1, DRAW_FILL_FULL); // Replace 0x4CAF50 with your chosen color
      //for power saving reasons, comment out

      uint16_t minute_x = 120 + (65 * sin(((minutes / 10000)) * PI / 180));
      uint16_t minute_y = 120 - (65 * cos(((minutes / 10000)) * PI / 180));
      uint16_t minute_x_short = 120 + (90 * sin(((minutes / 10000)) * PI / 180));
      uint16_t minute_y_short = 120 - (90 * cos(((minutes / 10000)) * PI / 180));

      Paint_DrawLine(minute_x_short, minute_y_short, (uint16_t)minute_x, (uint16_t)minute_y, deviceSecondColorTheme, DOT_PIXEL_4X4, LINE_STYLE_SOLID);  // Replace 0x009688 with your chosen color
      //Paint_DrawCircle((uint16_t)minute_x, (uint16_t)minute_y, 4, WHITE, DOT_PIXEL_4X4, DRAW_FILL_FULL); // Replace 0x009688 with your chosen color
      //Paint_DrawCircle((uint16_t)minute_x_short, (uint16_t)minute_y_short, 4, WHITE, DOT_PIXEL_4X4, DRAW_FILL_FULL); // Replace 0x009688 with your chosen color
      //was 4

      uint16_t hour_x = 120 + (58 * sin(((hours % 12) * 30 + 0) * PI / 180));
      uint16_t hour_y = 120 - (58 * cos(((hours % 12) * 30 + 0) * PI / 180));

      uint16_t hour_x_cent = 120 + (4 * sin(((hours % 12) * 30 + 0) * PI / 180));
      uint16_t hour_y_cent = 120 - (4 * cos(((hours % 12) * 30 + 0) * PI / 180));

      //uint16_t hour_x_circle = 120 + (59 * sin(((hours % 12) * 30 + 0) * PI / 180));
      //uint16_t hour_y_circle = 120 - (59 * cos(((hours % 12) * 30 + 0) * PI / 180));

      Paint_DrawLine(hour_x_cent, hour_y_cent, (uint16_t)hour_x, (uint16_t)hour_y, deviceMainColorTheme, DOT_PIXEL_7X7, LINE_STYLE_SOLID);  // Replace 0x00796F with your chosen color
      //Paint_DrawCircle((uint16_t)hour_x_circle, (uint16_t)hour_y_circle, 6, 0x009688, DOT_PIXEL_6X6, DRAW_FILL_FULL); // Replace 0x00796F with your chosen color
      Paint_DrawCircle(120, 120, 8, deviceMainColorTheme, DOT_PIXEL_7X7, DRAW_FILL_FULL);  // Replace 0x00796F with your chosen color
                                                                                           //was 8
    }
  }

  if (elapsed_time - last > 60000) {
    last = elapsed_time;
    homeAppLowPower = 60000;
    saveToEEPROMX(last, address);
  }

  if (inTransition == false) {
    if (elapsed_time - last2 > homeAppLowPower) {
      last2 = elapsed_time;
      LCD_1IN28_Display(BlackImage);
      //LCD_1IN28_DisplayWindows(0, 0, 240, 240, BlackImage);
    }

    //Recommeneded to Open any asked apps After rendering existing scene to prevent double render black bar
    //if(tap){
    //if(tapHeld>2){
    //  homeAppLowPower = 1000;
    //  openApp(lastUsedAppName, "", 240);
    //}
  }
}

void resetFunc() {
  vreg_set_voltage(VREG_VOLTAGE_0_85);
  set_sys_clock_khz(410000, true);
}

void errorHandle() {
  lastfpstick = millis();
  Paint_DrawRectangle(0, 0, 240, 80, RED, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(0, 80, 240, 160, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(0, 160, 240, 240, RED, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawString_EN(10, 100, error.c_str(), &Font16, DARKGRAY, WHITE);
  if (inTransition == false) {
    if (pauseRender == false) {
      LCD_1IN28_DisplayWindows(10, 100, 240, 240, BlackImage);
    }

    if (butaction) {
      butaction = false;
      saveToEEPROMX(1, 2);
      openApp("main", "", 0);
    }
  }
}

void setup() {
  vreg_set_voltage(VREG_VOLTAGE_1_30);
  delay(10);
  set_sys_clock_khz(300000, true);
  Serial.begin(9600);
  if (DEV_Module_Init() != 0)
    Serial.println("GPIO Init Fail!");
  else
    Serial.println("GPIO Init successful!");
  LCD_1IN28_Init(HORIZONTAL);
  LCD_1IN28_Clear(BLACK);
  DEV_SET_PWM(0);
  UDOUBLE Imagesize = LCD_1IN28_HEIGHT * LCD_1IN28_WIDTH * 2;
  //UWORD *BlackImage;
  if ((BlackImage = (UWORD*)malloc(Imagesize)) == NULL) {
    Serial.println("Failed to apply for black memory...");
    exit(0);
  }
  Paint_NewImage((UBYTE*)BlackImage, LCD_1IN28.HEIGHT, LCD_1IN28.WIDTH, 0, WHITE);
  Paint_SetScale(65);
  Paint_SetRotate(ROTATE_0);
  Paint_Clear(WHITE);
  LCD_1IN28_Display(BlackImage);
  DEV_Delay_ms(100);
  CST816S_init(CST816S_Point_Mode);
  DEV_KEY_Config(Touch_INT_PIN);
  attachInterrupt(Touch_INT_PIN, &Touch_INT_callback, LOW);  //CHANGE
  //attachInterrupt(digitalPinToInterrupt(18), &checkNotif, HIGH);
  //attachInterrupt(digitalPinToInterrupt(18), &awareNess, HIGH);
  //attachInterrupt(digitalPinToInterrupt(26), &buttonPress, HIGH);
  //attachInterrupt(digitalPinToInterrupt(26), &buttonRelease, LOW);
  CurTime = readFromEEPROM(address);
  DEV_Delay_ms(10);


  apps["home"] = &home;
  apps["main"] = &mainScreen;
  apps["notifPane"] = &notifPane;
  apps["appsPanel"] = &appsPanel;
  apps["recentApps"] = &recentApps;
  //apps["nfc"] = &nfc;
  apps["Set Time"] = &setTime;
  apps["previewNotif"] = &previewNotif;
  apps["keyboard"] = &keyboard;
  apps["Settings"] = &settings;
  apps["error"] = &errorHandle;

  apps["Flappy Bird"] = &flappyBird;
  apps["2048 Puzzle"] = &game;
  apps["Step Tracker"] = &CountSteps;
  //apps["TimerApp"] = &TimerApp;
  apps["Messages"] = &messages;
  apps["Developer"] = &developer;
  apps["Flashlight"] = &flashlight;
  apps["Weather"] = &weather;
  apps["News"] = &news;
  apps["FindMyPhone"] = &findMyPhone;
  apps["Alarms"] = &alarms;
  //apps["scrollingTest"] = &scrollingTest;

  //BLUETOOTH CRAP
  pinMode(17, OUTPUT);  // --USED? (Incoming Clock?),. Yeah Incoming
  digitalWrite(17, LOW);
  delay(10);  //One second delay for Waveshare rp2040 to setup FIRST Very important  (Not really anymore)
  //OUTDATED AS OF 04/14/24 //pinMode(16, INPUT);  //data in --USED (Share Data in future????)
  //OUTDATED AS OF 04/14/24 //pinMode(17, INPUT);  //clock --USED (Share Clock in future????)
  pinMode(18, INPUT);  //WATH FOR DATA --USED (Battery Reasons)
  pinMode(26, INPUT);  //Tell other device, it is listening --UNUSED, NOW BUTTON? Yeah
                       // digitalWrite(26, LOW);

  pinMode(sendPin, OUTPUT);
  pinMode(receivePin, INPUT);

  pinMode(27, OUTPUT);
  pinMode(28, OUTPUT);
  //pins 27, and 28 are Data Out, and Clock

  int errorCode = readFromEEPROM(2);
  if (errorCode != 2 and errorCode != 3) {

    DEV_SET_PWM(100);

    Paint_DrawRectangle(0, 0, 240, 240, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    LCD_1IN28_DisplayWindows(0, 0, 240, 240, BlackImage);

    delay(200);

    float vel = 10;
    int xPos = 0;  //120-(17+17);
    float counter = 0;
    while (int(vel) > 0) {
      vel = vel / 1.09;
      xPos += vel;
      Paint_DrawRectangle(0, 120, xPos + (17 * 4), 152, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
      Paint_DrawString_EN(xPos + (17 * 0), 120, "W", &Font24, BLACK, 0xfb0c);
      Paint_DrawString_EN(xPos + (17 * 1), 120, "a", &Font24, BLACK, 0x69bf);
      Paint_DrawString_EN(xPos + (17 * 2), 120, "r", &Font24, BLACK, 0xf9b8);
      Paint_DrawString_EN(xPos + (17 * 3), 120, "p", &Font24, BLACK, 0x58df);
      LCD_1IN28_DisplayWindows(0, 120, xPos + (17 * 4), 150, BlackImage);
      delay(1);
    }

    //std::string test = "DevStart";
    //const char* message = test.c_str();
    //sendText(message);

    Paint_DrawRectangle(0, 0, 240, 240, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);

    xPos = 120 - (17 + 17);
    Paint_DrawString_EN(xPos + (17 * 0), 120, "W", &Font24, BLACK, 0xfb0c);
    Paint_DrawString_EN(xPos + (17 * 1), 120, "a", &Font24, BLACK, 0x69bf);
    Paint_DrawString_EN(xPos + (17 * 2), 120, "r", &Font24, BLACK, 0xf9b8);
    Paint_DrawString_EN(xPos + (17 * 3), 120, "p", &Font24, BLACK, 0x58df);
    LCD_1IN28_DisplayWindows(0, 0, 240, 240, BlackImage);
    float loadV = 15;
    int pos = 0;

    while (counter < 300) {  //was 360
      loadV = loadV / 1.015;
      pos += loadV;
      if (loadV < 1.8) {
        loadV = 15;
      }
      //Paint_DrawString_EN(xPos+(17*0), 120, "W", &Font24, BLACK, 0xfb0c);
      //Paint_DrawString_EN(xPos+(17*1), 120, "a", &Font24, BLACK, 0x69bf);
      //Paint_DrawString_EN(xPos+(17*2), 120, "r", &Font24, BLACK, 0xf9b8);
      //Paint_DrawString_EN(xPos+(17*3), 120, "p", &Font24, BLACK, 0x58df);

      uint16_t dot_x = 120 - (int)(110 * sin((pos * 1 + 180) * PI / 180));
      uint16_t dot_y = 120 + (int)(110 * cos((pos * 1 + 180) * PI / 180));
      //Paint_DrawLine(120, 120, (uint16_t)second_x, (uint16_t)second_y, 0x009688, DOT_PIXEL_2X2, LINE_STYLE_SOLID); // Replace 0x4CAF50 with your chosen color

      Paint_DrawRectangle(max(0, min(240, dot_x - 45)), max(0, min(240, dot_y - 45)), max(0, min(240, dot_x + 45)), max(0, min(240, dot_y + 47)), BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
      Paint_DrawCircle((uint16_t)dot_x, (uint16_t)dot_y, 15, deviceMainColorTheme, DOT_PIXEL_1X1, DRAW_FILL_FULL);  // Replace 0x4CAF50 with your chosen color///0x58df
      LCD_1IN28_DisplayWindows(max(0, min(240, dot_x - 45)), max(0, min(240, dot_y - 45)), max(0, min(240, dot_x + 45)), max(0, min(240, dot_y + 45)), BlackImage);

      counter += 0.5;
    }
  }

  //attachInterrupt(digitalPinToInterrupt(18), &checkNotif, HIGH);
  //attachInterrupt(digitalPinToInterrupt(18), &awareNess, HIGH);
  attachInterrupt(digitalPinToInterrupt(26), &buttonPress, CHANGE);
  //attachInterrupt(digitalPinToInterrupt(26), &buttonRelease, LOW);

  Paint_DrawRectangle(0, 0, 240, 240, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  LCD_1IN28_DisplayWindows(0, 0, 240, 240, BlackImage);

  lastfpstick = millis();
  //int errorCode = readFromEEPROM(2);
  //if (errorCode != 1) {
  if (errorCode == 2) {
    error = "TAP thread detected an application was  not responding.";
  } else if (errorCode == 3) {
    error = "BUT thread detected an application was  not responding.";
  }
  //} else {
  //  error = "An error occured and the device had to  reset." + std::to_string(errorCode);
  //}
  if (error != "") {
    openApp("error", "", 0);
  } else {
    openApp("home", "RAND");
  }

  std::string test = "DevStart";
  message = test.c_str();
  sendText(message);
  //const char* message = messag.c_str();
  //  test = "DevStart";
  //  message = test.c_str();
  //  sendText(message);
}


int initalYPos = -1;



#ifdef __arm__
// should use uinstd.h to define sbrk but Due causes a conflict
extern "C" char* sbrk(int incr);
#else   // __ARM__
extern char* __brkval;
#endif  // __arm__

int freeMemory() {
  char top;
#ifdef __arm__
  return &top - reinterpret_cast<char*>(sbrk(0));
#elif defined(CORE_TEENSY) || (ARDUINO > 103 && ARDUINO != 151)
  return &top - __brkval;
#else   // __arm__
  return __brkval ? &top - __brkval : &top - __malloc_heap_start;
#endif  // __arm__
}


int shouldConsiderUpdating = 0;
int timeInTrans = 0;

void loop() {  //IMPLEMENT A SYSTEM TO CHECK HOW LONG IT TOOK TO RUN, AND IF ITS LESS THAN X AMMOUNT OF TIME, THEN RUN DEV_DELAY FOR TIME LEFT
  //DEV_Delay_ms(4); //kinda needed for touches to work best!
  //Touch_INT_callback();
  if (millis() - shouldConsiderUpdating > 3000 || scrolling || tap || otherSwipe || watchSwipe) {
    shouldConsiderUpdating = millis();
    if (batSaver == false) {
      if (speedMode == false) {
        if ((tap && tapHeld > 3) || scrolling || otherSwipe || watchSwipe) {
          if (turboClock == false) {
            turboClock = true;
            medClock = false;
            vreg_set_voltage(VREG_VOLTAGE_1_30);
            //delay(10);
            set_sys_clock_khz(400000, true);
          }
        } else if (runningAppName != "home") {
          if (medClock == false) {
            medClock = true;
            turboClock = false;
            //set_sys_clock_khz(32000, true);
            //vreg_set_voltage(VREG_VOLTAGE_0_90);

            vreg_set_voltage(VREG_VOLTAGE_1_30);
            //delay(10);
            set_sys_clock_khz(150000, true);  //120000
          }
        }
      }
    } else {
      if (runningAppName != "home") {
        if (tap) {
          medClock = true;
          turboClock = false;
          vreg_set_voltage(VREG_VOLTAGE_1_10);
          set_sys_clock_khz(78000, true);
        }
      }
    }
  }

  //if(millis()-serviceLastRan>180000){ //3600000 every hour , 180000 every 30 minute
  //  serviceLastRan=millis();
  //  for (const auto& service : services) {
  //          Serial.print("Running service: ");
  //          Serial.println(service.name);
  //          service.function(); // Call the function
  //      }
  //      //for the time being, I am making service's display behind the main app, if there is a display.
  //}


  if (millis() - serviceLastRan > 1800000) {  // 1800000 milliseconds = 30 minutes
    serviceLastRan = millis();
    runNextService();
  }

  //try {
  if (runningAppName == "home") {
    if (millis() - updateHome > 300000) {
      updateHome = millis();
      runningApp();
    }
  } else if (buttonDown == false) {
    runningApp();
  }

  //if (initalYPos > 210 && Touch_CTS816.y_point > 210 && tapHeld > 50 && inTransition == false && otherSwipe == false && watchSwipe == false) {
  //  openApp("recentApps", "UD", Touch_CTS816.y_point);
  //} //NOW DOUBLE PRESS
  checkNotif();
  //} catch (const std::exception& e) {
  //  Paint_DrawRectangle(0, 0, 240, 240, RED, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  //  Paint_DrawString_EN(10, 96, "APP CRASHED", &Font24, BLACK, 0x69bf);
  //  LCD_1IN28_DisplayWindows(0, 0, 240, 240, BlackImage);
  //  delay(10000);
  //  openApp("home", "UD");
  //}

  if (!inTransition && !pauseRender) {
    timeInTrans = millis();
  } else if (millis() - timeInTrans > 5000) {
    inTransition = false;
    pauseRender = false;
    timeInTrans = millis();
  }

  if (runningAppName != "home") {
    dontRunDimAgain = true;
    if (millis() - idleTime > autoClock) {
      //lastUsedAppName = runningAppName;
      openApp("home", "RAND");
      idleTime = millis();
    }  //batVoltages
    if (millis() - lastBatteryCheck > 300000) {
      lastBatteryCheck = millis();
      if (batVoltages.size() >= 3) {
        batVoltages.pop_front();  // Remove the oldest value
      }
      if (DEC_ADC_Read() * (3.3f / (1 << 12) * 2) > 1) {
        batVoltages.push_back(DEC_ADC_Read() * (3.3f / (1 << 12) * 2));
      }
    }
  }

  tickTenTen++;

  if (runningAppName == "CountSteps") {
    autoClock = 3600000;
  } else {
    autoClock = 15000;
  }



  //Handle Swipe up to home
  if (tap) {  //flag==1
              //  flag=0;
    tapHeld++;
    //tap=true;
    idleTime = millis();
    if (runningAppName != "home") {
      if (watchSwipe == true && otherSwipe == false) {  // && pauseRender==false
                                                        //pauseRender=true;

        //if(tapHeld > 2){
        Paint_DrawRectangle(45, 225, 195, 235, deviceSecondColorTheme, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        //A little broke? //LCD_1IN28_DisplayWindows(45, max(0,Touch_CTS816.y_point-2), 195, min(Touch_CTS816.y_point+6,240), BlackImage);Paint_DrawRectangle(45, Touch_CTS816.y_point, 195, min(Touch_CTS816.y_point+7,240), 0xF81F, DOT_PIXEL_1X1, DRAW_FILL_FULL);

        //tap=true;
        //inTransition=true;//runningApp();
        //pauseRender = true;
        //while(tap){Paint_DrawRectangle(45, Touch_CTS816.y_point, 195, min(Touch_CTS816.y_point+12,240), 0xF81F, DOT_PIXEL_1X1, DRAW_FILL_FULL);LCD_1IN28_DisplayWindows(45, max(240,Touch_CTS816.y_point-5), 195, min(Touch_CTS816.y_point+13,240), BlackImage);if(flag==1){tap=true;flag=0;}else{tap=false;}DEV_Delay_ms(1);}
        //////////inTransition=true;
        //pauseRender=true;
        //pauseRender = true;
        //tap = false;
        //}
        if (Touch_CTS816.y_point < 70) {  //was 190
          inTransition = false;
          //tap=true;
          //inTransition=true;//runningApp();
          //pauseRender = true;//Paint_DrawRectangle(40, Touch_CTS816.y_point, 200, min(Touch_CTS816.y_point+6,240), 0xFE6B, DOT_PIXEL_1X1, DRAW_FILL_FULL);
          //while(tap){runningApp();LCD_1IN28_DisplayWindows(0, 0, 240, 240, BlackImage);if(flag==1){tap=true;flag=0;}else{tap=false;}DEV_Delay_ms(1);}//if(flag==1){tap=true;flag=0;}else{tap=false;}
          //inTransition=false;
          //pauseRender = false;
          tap = false;  //WAS ENABLEDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD
          if (std::find(backgroundApps.begin(), backgroundApps.end(), runningAppName) != backgroundApps.end()) {
            backgroundApps.remove(runningAppName);
          }
          if (Touch_CTS816.y_point < 70) {  //check if drag passed point
            if (runningAppName == "main") {
              delay(10);
              openApp("home", "RAND", Touch_CTS816.y_point);
              delay(200);
            } else {
              delay(10);
              openApp("main", "DU", 240);
            }
            watchSwipe = false;
            tap = false;
          }
          watchSwipe = false;
        }
      }
      if (Touch_CTS816.y_point > 225) {  //check if at bottom
        watchSwipe = true;
        //inTransition=true;
      }
    }
  } else {
    tapHeld = 0;
    initalYPos = -1;
    //tap=false;
    if (watchSwipe == true) {
      inTransition = false;
      //pauseRender = false;
    }
    watchSwipe = false;
  }

  if (tickTenTen > 100 || runningAppName == "home") {  //was 100, and 6    // || (runningAppName=="home" && tickTenTen > 1000) I forgot its not seconds  && runningAppName!="home") || (tickTenTen > 10000 && runningAppName=="home")
    tickTenTen = 0;
    if (runningAppName == "home") {
      if (dontRunDimAgain) {
        dontRunDimAgain = false;
        if (aod && batSaver == false) {
          DEV_SET_PWM(2);
        } else {
          LCD_1IN28_Clear(BLACK);
          DEV_SET_PWM(0);
        }
        set_sys_clock_khz(32000, true);
        delay(10);
        vreg_set_voltage(VREG_VOLTAGE_0_90);
      }
    } else if (speedMode && batSaver == false) {
      DEV_SET_PWM(100);
      vreg_set_voltage(VREG_VOLTAGE_1_30);
      delay(10);
      set_sys_clock_khz(400000, true);
      dontRunDimAgain = true;
    } else {
      DEV_SET_PWM(100);
      dontRunDimAgain = true;
    }
  }

  if (runningAppName == "home") {
    if (dontRunDimAgain == false) {
      DEV_Delay_ms(500);
    }
  }

  if (millis() - timeSinceLastButton > 300 && buttonPressCount >= 1) {
    if (buttonPressCount == 1) {
      if (runningAppName == "main") {
        openApp("appsPanel", "DU");
      } else {
        openApp("main", "RAND");
      }
    } else if (buttonPressCount == 2) {
      openApp("recentApps", "DU");
    }
    buttonPressCount = 0;
  }

  if (butaction) {
    butaction = false;
    //was stuff herre,.. not anymore
  }

  if (ticksSinceTap > 1 && tap) {  //was >1
    tap = false;
    //otherSwipe=false;//WAS TURNED OFF, for some reason
    watchSwipe = false;
    ticksSinceTap = 0;
    activeDir = "";
    //Serial.println("Releasse");
  } else if (tap) {
    ticksSinceTap++;
  }

  frameCount++;
  if (millis() - lastfpstick >= 1000) {
    lastfpstick = millis();
    fps = frameCount;
    frameCount = 0;
  }

  oneTickPause = false;
  if(!otherSwipe && !watchSwipe && pauseRender){
    pauseRender = false;
  }
  //Paint_DrawString_EN(53, 19, (std::to_string(fps) + " FPS").c_str(), &Font12, BLACK, BLUE);
}

void Touch_INT_callback() {
  if (inTransition == false) {  // && runningAppName!="home"
    CST816S_Get_Point();
    tap = true;
    ticksSinceTap = 0;
    flag = 1;
    if (initalYPos == -1) {
      initalYPos = Touch_CTS816.y_point;
    }
  }

  if (runningAppName == "home") {
    homeAppLowPower = 1000;
    //openApp(lastUsedAppName, "", 240);
    openApp("main");
    updateHome = 0;
  }
  if (millis() - lastfpstick >= 3000 && runningAppName != "boot") {
    Serial.println("Something broke..");
    saveToEEPROMX(2, 2);
    resetFunc();
    //error="App Timed Out."; //Mem could be maxxed out...
    //vreg_set_voltage(VREG_VOLTAGE_0_90);
    //set_sys_clock_khz(420000, true);  //reset
    //openApp("error","",0);//WEll, yes and no
    openApp("main", "", 0);
  }
}

void buttonPress() {
  if (digitalRead(26) == HIGH) {
    if (buttonDown == false) {
      buttonDown = true;
      if (runningAppName == "home") {
        DEV_SET_PWM(100);
        vreg_set_voltage(VREG_VOLTAGE_1_30);
        delay(10);
        set_sys_clock_khz(400000, true);
        openApp("main");
      } else {
        butaction = true;
      }
      buttonPressCount += 1;
      timeSinceLastButton = millis();
    }
  } else {
    buttonDown = false;
  }
  if (millis() - lastfpstick >= 2500 && runningAppName != "boot") {
    Serial.println("Something broke..");
    saveToEEPROMX(3, 2);
    resetFunc();
    //error="App Timed Out.";
    //vreg_set_voltage(VREG_VOLTAGE_0_90);
    //set_sys_clock_khz(420000, true);
    openApp("main", "", 0);
  }
  delay(2);
  /*if(digitalRead(26)==HIGH){
        if(buttonDown == false){
            buttonDown=true;
            if(runningAppName=="main"){
                openApp("appsPanel");
            } else if(runningAppName=="home"){
                DEV_SET_PWM(100);
                vreg_set_voltage(VREG_VOLTAGE_1_30);
                set_sys_clock_khz(400000, true);
                openApp("main");
                //openApp("main");
            } else{
                openApp("main");
            }
        }
    } else{
        buttonDown=false;
    }
    */
  Serial.println("PRESS");
}


//420000 was the old peak