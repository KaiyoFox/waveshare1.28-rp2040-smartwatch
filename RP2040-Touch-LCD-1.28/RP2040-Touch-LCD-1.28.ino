#include "LCD_Test.h"
#include "hardware/vreg.h"
#include "pico/stdlib.h"
#include "App.h"
#include <functional>
#include <EEPROM.h>
#include <Arduino.h>
#include <Arduino_JSON.h>
#include <map>
#include <string>
#include <vector>
#include <list>
#include <tuple>
#include <iostream>
#include <chrono>
#include <PulseSensorPlayground.h>

void renderSnack();
bool swipe(std::string dir, int thresh);
void openApp(std::string app, std::string dir, int start);
std::string internet_get(std::string url);
void internet_post(std::string toilet, std::string data);
bool button(int x, int y, const char* text, sFONT* Font, UWORD Color_Foreground, UWORD Color_Background, int size);
std::list<int> scrollFunction(int numberOfItems, std::string itemHeaders[], bool visible);
std::list<int> scrollFunctionFull(int numberOfItems, std::string itemHeaders[], bool visible);
bool checkBox(int x, int y, UWORD OutlineColor, UWORD XColor, std::string id, int size);
int slider(int x, int y, UWORD OutlineColor, UWORD InsideColor, std::string id, int width, int height);
std::string textBox(int x, int y, UWORD OutlineColor, UWORD InsideColor, std::string id, int width, int height, std::string defaultText, bool pass = false);
bool toggle(int x, int y, UWORD OutlineColor, UWORD ToggleColor, std::string id, int size);
bool radio(int x, int y, UWORD OutlineColor, UWORD XColor, std::string id, int size, std::string group);
void snackBar(std::string, UWORD BGC, UWORD TXCOLOR);

std::list<std::string> split(const std::string& s, char seperator);

std::list<std::string> listDir(const char* path);
bool createFolder(const char* path);
bool createFile(const char* path, const char* data);
std::string listFileContents(const char* path);
bool removeFile(const char* path);
bool removeDir(const char* path);
bool fileExists(const char* path, bool fileType);
void initializeFileSystem();
int calculateUsedSpace();
int FileSysCalculateUsedSpace();

//Builtin-Apps/Processes:
//include "home.h"
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

//Apps V2
#include "appVersTwo.h"
#include "appVersTwoTestTwo.h"
#include "devTerm.h"


const int PulseWire = 27;           // PulseSensor PURPLE WIRE connected to ANALOG PIN 0
int Threshold = 550;                //3000;               //510;                //550           // Determine which Signal to "count as a beat" and which to ignore.
PulseSensorPlayground pulseSensor;  // Creates an instance of the PulseSensorPlayground object called "pulseSensor"
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
bool buttonDown = false;
bool butaction = false;
bool butActionRan = false;
bool dontRunDimAgain = true;
bool systemDisplayUpdates = false;
bool BLEconnected = false;
bool resetTransitionAfterTick = false;
int tapHeld = 0;
int tickTenTen = 0;
int updateHome = 0;
int idleTime = millis();
int lastBatteryCheck = 0;
int frameCount = 0;
int fps = 0;
int lastfpstick = 0;
bool oneTickPause = false;
bool miscSwipe = true;
bool typeOfApp = false;
int buttonPressCount = 0;
const char* message = "";
std::string keyboardTyped = "";
std::string keyboardData = "";
std::map<std::string, uint16_t> colorCache;
UWORD* BlackImage;
typedef void (*AppPtr)();
AppPtr runningAppV1;
std::function<void()> runningAppV2;
std::list<std::string> appNames;
std::map<std::string, AppPtr> apps;
std::map<std::string, App*> appsV2;
std::string runningAppName = "boot";
std::string lastUsedAppName = "main";
std::list<float> batVoltages = {};
std::map<std::list<std::string>, int> specialButtons = {};                    //{"APP","ID", "TYPE"}: VALUE
std::map<std::list<std::string>, std::list<float>> specialButtonsExtra = {};  //{"APP","ID", "TYPE"}: {EXTRA}
std::map<std::list<std::string>, std::string> specialButtonsExtraString = {};
int autoClock = 15000;                                                        //Auto clock screen
std::string error = "";
std::string swipeComplete = "";
bool watchSwipe = false;
int swipeStartThreshMain = 120;  //was like. 50
//bool swipeDone = false;
std::string activeDir = "";
std::list<std::string> systemApps = { "home", "main", "notifPane", "appsPanel", "recentApps", "previewNotif", "keyboard", "setTime", "error", "Set Time" };
std::list<std::string> backgroundApps = {};  //{"flappyBird"};
typedef void (*ServiceFunction)();           //services
struct Service {
  String name;
  ServiceFunction function;
};
std::list<Service> services;
void appV2() {
  typeOfApp = true;
  /*
  auto itNew = appsV2.find(runningAppName);
  if (itNew != appsV2.end()) {
    runningAppV2 = [instance = itNew->second]() {
      instance->update();
    };
    runningAppV2();
  }
  */
};

std::list<std::string> appPermissions = {};
std::string appTitle = "";    // Title
std::string appDesc = "";     // Description
std::string appPub = "";      // Publisher
std::string appOthInfo = "";  // Other Info
float appVersion = 0.0;       // Version
int appDatePub = 0;           // Unix Timestamp
std::string appHash = "";     // More Unique Identifier


typedef void (App::*func)();
void runningApp() {
  if (typeOfApp == true) {
    runningAppV2();
  } else {
    runningAppV1();
  }
  if (systemDisplayUpdates) {
    renderSnack();
  }
  if (systemDisplayUpdates && pauseRender == false && inTransition == false) {
    LCD_1IN28_Display(BlackImage);
  }
}
//std::vector<Service> services;

const int sendPin = 17;     // 2Pin to send data
const int receivePin = 16;  // 3Pin to receive data

uint8_t flag = 0;
void Touch_INT_callback();
void buttonPress();


//Some settings
uint16_t deviceMainColorTheme = 0x739c;    //0x009688;
uint16_t deviceSecondColorTheme = 0xecfa;  //0xFE6B;
uint16_t deviceThirdColorTheme = 0xc41a;   //0x06d5;
bool aod = false;
bool batSaver = false;

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









//#define EEPROM_SIZE 512
int EEPROM_SIZE = 512;
int FILE_TABLE_START = 5;
#define MAX_FILES 50     //max bytes for file table
#define MAX_NAME_LEN 15  //Yes its small, Deal with it ABCDEF.EXT (I think this includes folders too, /folder/file.txt ) every character counts towards limit

enum EntryType {
  FILE_TYPE,
  FOLDER_TYPE
};

struct FileTableEntry {
  char name;  //[MAX_NAME_LEN]
  int type;   //folder / file
};


void initializeFileSystem() {
  EEPROM.begin(EEPROM_SIZE);
  for (int i = FILE_TABLE_START; i < EEPROM_SIZE; i++) {
    EEPROM.write(i, 0xFF);
  }
  EEPROM.commit();
  EEPROM.end();

  createFolder("/");
}

struct FileData {
  std::string fileName;
  std::string fileData;
  bool isFile;
};

std::vector<FileData> fileSystemBackup;
void saveFileSystemToRAM() {
  EEPROM.begin(EEPROM_SIZE);
  fileSystemBackup.clear();

  std::string fileName = "";
  std::string fileData = "";
  bool isFile = false;

  for (int i = FILE_TABLE_START; i < EEPROM_SIZE; i++) {
    int val = EEPROM.read(i);
    if (val == 255) {
      if (!fileName.empty()) {
        FileData fileEntry;
        fileEntry.fileName = fileName;
        fileEntry.fileData = fileData;
        fileEntry.isFile = isFile;
        fileSystemBackup.push_back(fileEntry);
        fileName = "";
        fileData = "";
      }
    } else if (val == 254) {
      while (i < EEPROM_SIZE && EEPROM.read(i) != 255) {
        fileData += static_cast<char>(EEPROM.read(i));
        i++;
      }
      i--;
    } else if (val == 0 || val == 1) {
      isFile = (val == 1);
    } else {
      char valChar = static_cast<char>(val);
      fileName += valChar;
    }
  }

  EEPROM.end();
}
void rewriteFileSystemFromRAM() {
  EEPROM.begin(EEPROM_SIZE);

  int currentPos = FILE_TABLE_START + 1;
  for (const auto& fileEntry : fileSystemBackup) {
    EEPROM.write(currentPos++, fileEntry.isFile ? 1 : 0);
    for (char c : fileEntry.fileName) {
      EEPROM.write(currentPos++, c);
    }
    if (fileEntry.isFile) {
      EEPROM.write(currentPos, 254);
      for (char c : fileEntry.fileData) {
        EEPROM.write(currentPos++, c);
      }
    }
    EEPROM.write(currentPos++, 255);
  }

  EEPROM.commit();
  EEPROM.end();
  fileSystemBackup.clear();
}

//MAKE IT SO IN ORDER TO MAKE A FILE / FOLDER INSIDE OF A DIR, THAT DIR MUST EXIST, but make it an optional bool, ObbeyStandard=true default
//RM, AND RMDIR (MAKE RMDIR RECURRISVE,)
bool removeFile(const char* path) {
  std::string pathStr = path;
  saveFileSystemToRAM();
  for (auto it = fileSystemBackup.begin(); it != fileSystemBackup.end(); ++it) {
    if ((it->fileName == pathStr || it->fileName.c_str() == path) && it->isFile == true) {
      fileSystemBackup.erase(it);
      initializeFileSystem();      //Format
      rewriteFileSystemFromRAM();  //Rewrite
      return true;
    }
  }
  return false;
}

//MAKE RECURSIVE
bool removeDir(const char* path) {
  std::string pathStr = path;
  saveFileSystemToRAM();

  // Create a new list to store the items to remove
  std::vector<decltype(fileSystemBackup)::iterator> itemsToRemove;

  // Collect all items that match the path
  for (auto it = fileSystemBackup.begin(); it != fileSystemBackup.end(); ++it) {
    // Check if the item's path starts with the given path
    if (it->fileName.find(pathStr) == 0) {
      if (((it->fileName == pathStr || it->fileName.c_str() == path) && it->isFile == true) == false) {
        itemsToRemove.push_back(it);
      }
    }
  }

  // Remove all collected items from the file system
  for (auto it : itemsToRemove) {
    fileSystemBackup.erase(it);
  }

  // Reinitialize the file system after removal
  initializeFileSystem();      // Format
  rewriteFileSystemFromRAM();  // Rewrite

  return !itemsToRemove.empty();
}

bool createFolder(const char* path) {
  if (fileExists(path, false)) {
    return false;
  }
  EEPROM.begin(EEPROM_SIZE);

  bool canWrite = false;
  int freeCount = 0;
  int start = 0;
  for (int i = FILE_TABLE_START; i < EEPROM_SIZE; i++) {
    if (canWrite == false) {
      int val = EEPROM.read(i);
      if (val == 255) {
        freeCount++;
      } else {
        freeCount = 0;
      }
      if (freeCount > 10) {
        canWrite = true;
        i = i - 10;
        start = i;
      }
    } else {
      if (i - start == 1) {
        EEPROM.write(i, 0x00);
      } else {
        if (i - start - 1 <= strlen(path)) {
          char letter = path[i - start - 2];
          EEPROM.write(i, letter);
        } else {
          EEPROM.commit();
          EEPROM.end();
          return true;
        }
      }
    }
  }

  EEPROM.commit();
  EEPROM.end();
  return false;
}

bool isDirectChild(const std::string& parentPath, const std::string& entryPath) {
  std::string parent = parentPath;
  if (parent.back() != '/') {
    parent += '/';
  }
  return entryPath.find(parent) == 0 && entryPath.find('/', parent.length()) == std::string::npos;
}

bool fileExists(const char* path, bool fileType) {
  EEPROM.begin(EEPROM_SIZE);

  std::string fileName = "";
  bool isFile = false;

  std::string pathStr = path;
  size_t pathLength = pathStr.length();


  for (int i = FILE_TABLE_START; i < EEPROM_SIZE; i++) {
    int val = EEPROM.read(i);
    if (val == 255) {
      if (!fileName.empty() && fileName.find(path) == 0 && (fileName == path || fileName == pathStr) && fileType == isFile) {  // && isDirectChild(pathStr, fileName)
        //if (fileName == path || fileName == pathStr) {
        //  EEPROM.end();
        return true;
        //}
      }
      fileName = "";
    } else if (val == 254) {
      while (i < EEPROM_SIZE && EEPROM.read(i) != 255) {
        i++;
      }
      i--;
    } else if (val == 0 || val == 1) {
      isFile = (val == 1);
    } else {
      char valChar = static_cast<char>(val);
      fileName += valChar;
    }
  }

  EEPROM.end();
  return false;
}

std::list<std::string> listDir(const char* path) {
  EEPROM.begin(EEPROM_SIZE);

  std::list<std::string> files;
  std::string fileName = "";
  bool isFile = false;

  std::string pathStr = path;
  size_t pathLength = pathStr.length();


  for (int i = FILE_TABLE_START; i < EEPROM_SIZE; i++) {
    int val = EEPROM.read(i);
    if (val == 255) {
      if (!fileName.empty() && fileName.find(path) == 0 && fileName != path && isDirectChild(pathStr, fileName)) {
        std::string relativePath = fileName.substr(pathStr.length());
        if (relativePath.empty() || relativePath[0] != '/') {
          relativePath = '/' + relativePath;
        }
        if (isFile) {
          files.push_back(relativePath);
        } else {
          files.push_back(relativePath + '/');
        }
      }
      fileName = "";
    } else if (val == 254) {
      while (i < EEPROM_SIZE && EEPROM.read(i) != 255) {
        i++;
      }
      i--;
    } else if (val == 0 || val == 1) {
      isFile = (val == 1);
    } else {
      char valChar = static_cast<char>(val);
      fileName += valChar;
    }
  }

  EEPROM.end();
  return files;
}

bool createFile(const char* path, const char* data) {
  if (fileExists(path, true)) {
    return false;
  }
  EEPROM.begin(EEPROM_SIZE);

  int availableStart = -1;
  for (int i = FILE_TABLE_START; i < EEPROM_SIZE; i++) {
    if (EEPROM.read(i) == 255) {
      int requiredSpace = strlen(path) + strlen(data) + 4;
      int freeSpace = 0;
      for (int j = i; j < EEPROM_SIZE; j++) {
        if (EEPROM.read(j) == 255) {
          freeSpace++;
        } else {
          break;
        }
      }
      if (freeSpace > requiredSpace) {
        availableStart = i + 1;  //was +2
        break;
      }
    }
  }

  if (availableStart == -1) {
    EEPROM.end();
    return false;
  }

  EEPROM.write(availableStart++, 1);
  for (int i = 0; i < strlen(path); i++) {
    EEPROM.write(availableStart++, path[i]);
  }
  EEPROM.write(availableStart++, 254);
  for (int i = 0; i < strlen(data); i++) {
    EEPROM.write(availableStart++, data[i]);
  }
  EEPROM.write(availableStart++, 255);

  EEPROM.commit();
  EEPROM.end();
  return true;
}

std::string listFileContents(const char* path) {
  EEPROM.begin(EEPROM_SIZE);

  std::string pathString = path;
  std::string fileName = "";
  std::string data = "";
  bool isFile = false;

  for (int i = FILE_TABLE_START; i < EEPROM_SIZE; i++) {
    int val = EEPROM.read(i);
    if (val == 255) {
      if (!fileName.empty()) {
        if ((fileName == path || fileName == pathString) && isFile) {
          return data;
        } else {
        }
      }
      fileName = "";
      data = "";
    } else if (val == 254) {
      while (i < EEPROM_SIZE && EEPROM.read(i) != 255) {
        int datVal = EEPROM.read(i);
        if (datVal != 254 && datVal != 255) {
          char valCharDat = static_cast<char>(EEPROM.read(i));
          data += valCharDat;
        }
        i++;
      }
      i--;
    } else if (val == 0 || val == 1) {
      isFile = (val == 1);
    } else {
      char valChar = val;  //static_cast<char>(val)
      fileName += valChar;
    }
  }

  EEPROM.end();
  return "err";
}



int calculateUsedSpace() {
  EEPROM.begin(EEPROM_SIZE);

  int usedSpace = 0;
  Serial.println("Data");
  for (int i = 0; i < EEPROM_SIZE; i++) {
    char chr = EEPROM.read(i);
    Serial.print(chr);
    if (EEPROM.read(i) != 0xFF) {
      usedSpace++;
    }
  }
  Serial.println("");

  EEPROM.end();
  return usedSpace;
}

int FileSysCalculateUsedSpace() {
  EEPROM.begin(EEPROM_SIZE);

  int usedSpace = 0;
  Serial.println("Data");
  for (int i = FILE_TABLE_START; i < EEPROM_SIZE; i++) {
    char chr = EEPROM.read(i);
    Serial.print(chr);
    if (EEPROM.read(i) != 0xFF) {
      usedSpace++;
    }
  }
  Serial.println("");

  EEPROM.end();
  return usedSpace;
}

int calculateFreeSpace() {
  int usedSpace = calculateUsedSpace();
  int freeSpace = EEPROM_SIZE - usedSpace;
  return freeSpace;
}







//void saveToEEPROMX(unsigned long data, int addr) {
//None
//}
//unsigned long readFromEEPROM(int addr) {
//  return 0;
//}

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
int BPM = 0;
int checkBPM = 0;
int lastVal = 0;
int lastValCheck = 0;
int lastBeat = 0;
int beat = 0;
bool BeatTrig = false;

int lastSpeedCheckTime = 0;
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

    if (draggingScrollE) {
      otherSwipe = false;
      watchSwipe = false;
      miscSwipe = false;
    }
  } else {
    if (draggingScrollE) {
      if (wasAbleToCheck) {
        scrollV = (scrollY - lastScrollY) / 2;  //more percise
        wasAbleToCheck = false;
        //Serial.println("Slow");
      } else {
        scrollV = (scrollY - initialScroll) / 1.3;  //likely a quick motion
        //Serial.println("Quick");
      }
      scrollY += scrollV;
      scrollV *= friction;
      Paint_DrawCircle(230 - abs((scrollY - (120 - 29)) / 4) + 1, scrollY + 29, 29, deviceMainColorTheme, DOT_PIXEL_2X2, DRAW_FILL_FULL);
      ///////////////////////////////////////////////////////////////////////////////////////////LCD_1IN28_DisplayWindows(180, 0, 240, 240, BlackImage);
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

  scrollY = std::max(0, std::min(180, scrollY));
  if (oneTickPause == false) {
    Paint_DrawCircle(230 - abs((scrollY - (120 - 29)) / 4) + 1, scrollY + 29, 29, deviceMainColorTheme, DOT_PIXEL_2X2, DRAW_FILL_FULL);
    //LCD_1IN28_DisplayWindows(180, 0, 240, 240, BlackImage);//-abs((scrollY-(120+20))/4)
  }

  // Apply scrolling
  if (draggingScrollE || std::abs(int(scrollV)) > 1 && oneTickPause == false) {
    scrollY += scrollV;
    scrollV *= friction;
    //Paint_DrawCircle(230-abs((scrollY-(120-29))/4)+1, scrollY+29, 29, deviceMainColorTheme, DOT_PIXEL_2X2, DRAW_FILL_FULL);
    ////////////////////////////////////////////////////////////////////////LCD_1IN28_DisplayWindows(180, 0, 240, 240, BlackImage);  //-abs((scrollY-(120+20))/4)
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
  scrolling = draggingScrollE || std::abs(int(scrollV)) > 2;

  // Return values
  std::list<int> resultList;
  resultList.push_back(scrollY);
  resultList.push_back(scrolling ? 1 : 0);
  resultList.push_back(hoverObject);

  return resultList;
}
























std::list<int> scrollFunctionFull(int numberOfItems, std::string itemHeaders[], bool visible) {
  // Check scroll speed periodically
  // Handle touch events
  if (tap) {
    if (!draggingScrollE) {
      //Serial.println(true);
      initialTap = Touch_CTS816.y_point;
      initialScroll = scrollY;
      draggingScrollE = true;
      lastSpeedCheckTime = millis();
      lastScrollY = scrollY;
      wasAbleToCheck = false;
      //scrolling = true;
    }

    if (draggingScrollE) {
      otherSwipe = false;
      watchSwipe = false;
      miscSwipe = false;
      //scrolling = true;
    }
  } else {
    if (draggingScrollE) {
      if (wasAbleToCheck) {
        scrollV = (scrollY - lastScrollY) / 2.5;  //more percise
        wasAbleToCheck = false;
        //Serial.println("Slow");
      } else {
        scrollV = (scrollY - initialScroll) / 2;  //likely a quick motion
        //Serial.println("Quick");
      }
      scrollY += scrollV;
      scrollV *= friction;
      //Paint_DrawCircle(230 - abs((scrollY - (120 - 29)) / 4) + 1, scrollY + 29, 29, deviceMainColorTheme, DOT_PIXEL_2X2, DRAW_FILL_FULL);
      ///////////////////////////////////////////////////////////////////////////////////////////LCD_1IN28_DisplayWindows(180, 0, 240, 240, BlackImage);
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

  scrollY = std::min(0, scrollY);
  //if (oneTickPause == false) {
  //Paint_DrawCircle(230 - abs((scrollY - (120 - 29)) / 4) + 1, scrollY + 29, 29, deviceMainColorTheme, DOT_PIXEL_2X2, DRAW_FILL_FULL);
  //LCD_1IN28_DisplayWindows(180, 0, 240, 240, BlackImage);//-abs((scrollY-(120+20))/4)
  //}

  // Apply scrolling
  if (draggingScrollE || std::abs(int(scrollV)) > 1 && oneTickPause == false) {
    scrollY += scrollV;
    scrollV *= friction;
    //Paint_DrawCircle(230-abs((scrollY-(120-29))/4)+1, scrollY+29, 29, deviceMainColorTheme, DOT_PIXEL_2X2, DRAW_FILL_FULL);
    ////////////////////////////////////////////////////////////////////////LCD_1IN28_DisplayWindows(180, 0, 240, 240, BlackImage);  //-abs((scrollY-(120+20))/4)
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
  scrolling = std::abs(lastScrollY - scrollY) > 1 || std::abs(int(scrollV)) > 2;  //draggingScrollE ||

  // Return values
  std::list<int> resultList;
  resultList.push_back(scrollY);
  resultList.push_back(scrolling ? 1 : 0);
  resultList.push_back(hoverObject);

  return resultList;
}










































void sendText(const char* text) {  //new
  vreg_set_voltage(VREG_VOLTAGE_1_30);
  delay(1);  //5
  set_sys_clock_khz(400000, true);
  digitalWrite(sendPin, HIGH);
  delay(150);  //300
  digitalWrite(sendPin, LOW);

  lastfpstick = millis();
  //String text = textE;
  //text += '\0';
  //for (int i = 0; i < text.length(); i++) {
  int lastTime = 0;
  delay(2);  //5
  for (int i = 0; text[i] != '\0'; i++) {
    lastfpstick = millis();
    digitalWrite(sendPin, LOW);
    delay(7);  //10
    bool lastA = LOW;
    digitalWrite(sendPin, HIGH);
    delay(5);  //5
    digitalWrite(sendPin, LOW);
    //Serial.println("F");
    for (int j = 0; j < 8; j++) {
      //Serial.println("G");
      if (text[i] & (1 << j)) {
        digitalWrite(sendPin, HIGH);
      } else {
        digitalWrite(sendPin, LOW);
      }
      delay(1);  //2
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

  delay(5);
  digitalWrite(sendPin, LOW);
  delay(5);
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
    delay(2);
    lastTime = millis();
    while (digitalRead(receivePin) == last && millis() - lastTime < 100) {}
    last = digitalRead(receivePin);
  }
  //Serial.println("Done");
  lastfpstick = millis();

  digitalWrite(sendPin, LOW);
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
    delay(7);  //8 05/11/24 changed it to "6"
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

String removeQuotes(String text) {
  if (text.length() >= 2 && text.charAt(0) == '"' && text.charAt(text.length() - 1) == '"') {
    return text.substring(1, text.length() - 1);  // Remove first and last characters
  }
  return text;
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
int checkNotifUpdate = 0;

void checkNotif() {
  if (millis() - checkNotifUpdate > 150) {
    checkNotifUpdate = millis();
    if (digitalRead(18) == HIGH) {  //digitalRead(18) == HIGH
      //Serial.println("HIGH");
      vreg_set_voltage(VREG_VOLTAGE_1_30);
      delay(1);
      set_sys_clock_khz(400000, true);
      Paint_DrawRectangle(10, 215, 230, 235, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
      Paint_DrawString_EN(82, 220, "Device Busy", &Font12, DARKGRAY, RED);  //7
      LCD_1IN28_DisplayWindows(10, 215, 230, 235, BlackImage);
      lastfpstick = millis();
      tapHeld = 0;
      Serial.println("RUN");

      delay(1);
      digitalWrite(sendPin, HIGH);
      delay(5);
      digitalWrite(sendPin, LOW);
      delay(5);


      int a = millis();
      idleTime = millis();
      while (digitalRead(18) == HIGH && millis() - a < 5000) { lastfpstick = millis(); }  //5000 was 10000
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

          notifications.push_back({ phoneNumber, "Messages", content, foundContactName });

          lastfpstick = millis();
          digitalWrite(D28, HIGH);
          delay(250);
          digitalWrite(D28, LOW);
          delay(200);
          digitalWrite(D28, HIGH);
          delay(200);
          digitalWrite(D28, LOW);
          lastfpstick = millis();
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

        if (!BLEconnected) {
          for (const auto& innerList : notifications) {
            if (std::find(innerList.begin(), innerList.end(), "Disconnected") != innerList.end()) {
              bool foundAhck = true;
            }
          }
          bool foundAhck = false;
          if (foundAhck == false) {
            notifications.push_back({ "Disconnected", "Settings", "Device disconnected", "network" });
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
          delay(1);
          vreg_set_voltage(VREG_VOLTAGE_0_90);
        }
      }
    }
  }
}

int slider(int x, int y, UWORD OutlineColor, UWORD InsideColor, std::string id, int width, int height) {  //needs, nicing (HEIGHT IS SCALE!)
  if (specialButtons.find({ runningAppName, id, "slider" }) == specialButtons.end()) {
    specialButtons[{ runningAppName, id, "slider" }] = 0;  //app, id, type   value
  }

  if (!batSaver) {
    Paint_DrawRectangle(((float)(specialButtons[{ runningAppName, id, "slider" }] / 100.0) * width) + x, y + (height / 2) - (height / 10), x + width, y + (height / 2) + (height / 10), OutlineColor, DOT_PIXEL_2X2, DRAW_FILL_FULL);
    Paint_DrawRectangle(x, y + (height / 2) - (height / 10), ((float)(specialButtons[{ runningAppName, id, "slider" }] / 100.0) * width) + x + (height / 3), y + (height / 2) + (height / 10), InsideColor, DOT_PIXEL_2X2, DRAW_FILL_FULL);
  }  //Old end X was x+width

  if (!inTransition && !pauseRender) {
    if (Touch_CTS816.x_point >= x - (height / 2) && Touch_CTS816.x_point <= x + width + (height / 2) && Touch_CTS816.y_point >= y - (height / 2) && Touch_CTS816.y_point <= y + height + (height / 2)) {
      if (tap && !watchSwipe && !otherSwipe && !inTransition && !pauseRender) {
        otherSwipe = false;
        watchSwipe = false;
        miscSwipe = true;
        inTransition = false;
        pauseRender = false;
        scrollV = 0;
        scrollY = 0;
        specialButtons[{ runningAppName, id, "slider" }] = 100.0 * (float)((float)((Touch_CTS816.x_point + height) - x) / (float)(x + width));
        if (!batSaver) {
          Paint_DrawCircle(((float)(specialButtons[{ runningAppName, id, "slider" }] / 100.0) * width) + x + (height / 2), y + (height / 2), (int)((float)height / (float)1.5), DARKGRAY, DOT_PIXEL_2X2, DRAW_FILL_FULL);
        }
      }
    }
  }

  if (batSaver) {
    Paint_DrawRectangle(((float)(specialButtons[{ runningAppName, id, "slider" }] / 100.0) * width) + x, y, ((float)(specialButtons[{ runningAppName, id, "slider" }] / 100.0) * width) + x + height, y + height, InsideColor, DOT_PIXEL_2X2, DRAW_FILL_FULL);
    Paint_DrawRectangle(x, y, x + width, y + height, OutlineColor, DOT_PIXEL_2X2, DRAW_FILL_EMPTY);
  } else {
    Paint_DrawCircle(((float)(specialButtons[{ runningAppName, id, "slider" }] / 100.0) * width) + x + (height / 2), y + (height / 2), (height / 2), InsideColor, DOT_PIXEL_2X2, DRAW_FILL_FULL);
  }
  return specialButtons[{ runningAppName, id, "slider" }];
}

sFONT* getFont(int height) {
    if (height >= 24) return &Font24;
    if (height >= 20) return &Font20;
    if (height >= 16) return &Font16;
    if (height >= 12) return &Font12;
    return &Font8;
}

int encodeText(const std::string& text) {
    std::ostringstream encodedStream;
    encodedStream << "9";
    for (char c : text) {
        encodedStream << std::to_string((int)c);
    }
    return std::stoi(encodedStream.str());
}

std::string maskedText(const std::string& text) {
    std::string masked;
    for (char c : text) {
        masked += '*';
    }
    return masked;
}

std::string decodeText(int encodedInt) {
    std::string encodedText = std::to_string(encodedInt);
    if (encodedText.empty() || encodedText[0] != '9') return "";
    std::string decoded;
    for (size_t i = 1; i < encodedText.size(); i += 2) {
        int charCode = std::stoi(encodedText.substr(i, 2));
        decoded += (char)charCode;
    }
    return decoded;
}

std::string tappedIdTextBox = "";

std::string textBox(int x, int y, UWORD OutlineColor, UWORD InsideColor, std::string id, int width, int height, std::string defaultText, bool pass) {
    static std::string currentText = "";
    bool isTyping = !keyboardTyped.empty();
    sFONT* Font = getFont(height);

    if (specialButtons.find({ runningAppName, id, "textBox" }) == specialButtons.end()) {
        Serial.println("Reset");
        delay(454);
        specialButtons[{ runningAppName, id, "textBox" }] = 0;  // Initialize state
        specialButtonsExtraString[{runningAppName, id, "textBox"}] = "";
        delay(454);
    }

    // Draw the text box
    Paint_DrawRectangle(x, y, x + width, y + height, OutlineColor, DOT_PIXEL_2X2, DRAW_FILL_FULL);
    Paint_DrawRectangle(x + 2, y + 2, x + width - 2, y + height - 2, InsideColor, DOT_PIXEL_2X2, DRAW_FILL_FULL);

        if(tappedIdTextBox == id){
      if(keyboardTyped!="" || keyboardData !=""){
        if(keyboardData!=""){
          keyboardTyped=keyboardData;
        }
        Serial.println("SETTTT");
        specialButtonsExtraString[{ runningAppName, id, "textBox" }] = "45";//encodeText(keyboardTyped);
        keyboardData="";
        keyboardTyped="";
        tappedIdTextBox = "";
      }
    }

    if (!inTransition && !pauseRender) {
        if (Touch_CTS816.x_point >= x && Touch_CTS816.x_point <= x + width && Touch_CTS816.y_point >= y && Touch_CTS816.y_point <= y + height) {
            if (tap && !watchSwipe && !otherSwipe && !inTransition && !pauseRender) {
                otherSwipe = false;
                watchSwipe = false;
                miscSwipe = true;
                inTransition = false;
                pauseRender = false;
                scrollV = 0;
                scrollY = 0;

                // Open the keyboard when the text box is tapped
                if(specialButtonsExtraString[{ runningAppName, id, "textBox" }]!=""){
                  keyboardTyped = specialButtons[{ runningAppName, id, "textBox" }];
                }
                tappedIdTextBox = id;
                openApp("keyboard", "DU", 240);
                keyboardTyped="";
            }
        }
    }

    // Determine text to display
    std::string displayText;
    Serial.println(specialButtonsExtraString[{ runningAppName, id, "textBox" }].c_str());
    if (specialButtonsExtraString[{ runningAppName, id, "textBox" }]!="") {
        displayText = specialButtonsExtraString[{ runningAppName, id, "textBox" }];
        if(pass){
          displayText=maskedText(displayText);
        }
    } else {
        displayText = defaultText;
    }

    // Render the current text in the text box
    Paint_DrawString_EN(x + 5, y + ((height / 2) - (Font->Height / 2)), displayText.c_str(), Font, InsideColor, OutlineColor);


    // Return the current text if not empty, otherwise return an empty string
    return "";
}

bool checkBox(int x, int y, UWORD OutlineColor, UWORD XColor, std::string id, int size = 30) {
  if (specialButtons.find({ runningAppName, id, "checkBox" }) == specialButtons.end()) {
    specialButtons[{ runningAppName, id, "checkBox" }] = 0;  //app, id, type   value
  }

  if (!inTransition && !pauseRender) {
    if (Touch_CTS816.x_point >= x && Touch_CTS816.x_point <= x + size && Touch_CTS816.y_point >= y && Touch_CTS816.y_point <= y + size) {
      if (tap && !watchSwipe && !otherSwipe && !miscSwipe && !inTransition && !pauseRender) {
        if (tapHeld <= 1) {
          tap = false;
          otherSwipe = false;
          watchSwipe = false;
          inTransition = false;
          pauseRender = false;
          scrollV = 0;
          scrollY = 0;
          tapHeld = 999;
          if (specialButtons[{ runningAppName, id, "checkBox" }] == 1) {
            specialButtons[{ runningAppName, id, "checkBox" }] = 0;
          } else {
            specialButtons[{ runningAppName, id, "checkBox" }] = 1;
          }
        }
      }
    }
  }

  if (specialButtons[{ runningAppName, id, "checkBox" }] == 1) {
    Paint_DrawRectangle(x, y, x + size, y + size, XColor, DOT_PIXEL_2X2, DRAW_FILL_FULL);
    Paint_DrawRectangle(x - 1, y - 1, x + size + 2, y + size + 2, 0x2124, DOT_PIXEL_2X2, DRAW_FILL_EMPTY);
    if (batSaver) {
      Paint_DrawLine(x + 5, y + 5, x + size - 5, y + size - 5, WHITE, DOT_PIXEL_2X2, LINE_STYLE_SOLID);
      Paint_DrawLine(x + size - 5, y + 5, x + 5, y + size - 5, WHITE, DOT_PIXEL_2X2, LINE_STYLE_SOLID);
    } else {
      int margin = 7;
      int startX = x + margin;
      int startY = y + size - margin;
      int midX = x + size / 2;
      int midY = y + size - size / 2;  //3
      int endX = x + size - margin;
      int endY = y + margin;
      Paint_DrawLine(endX, endY, midX, startY, WHITE, DOT_PIXEL_2X2, LINE_STYLE_SOLID);
      Paint_DrawLine(midX, startY, startX, midY, WHITE, DOT_PIXEL_2X2, LINE_STYLE_SOLID);
    }
  } else {
    Paint_DrawRectangle(x, y, x + size, y + size, OutlineColor, DOT_PIXEL_2X2, DRAW_FILL_FULL);
    Paint_DrawRectangle(x - 1, y - 1, x + size + 2, y + size + 2, 0x2124, DOT_PIXEL_2X2, DRAW_FILL_EMPTY);
  }

  return specialButtons[{ runningAppName, id, "checkBox" }];
}

bool radio(int x, int y, UWORD OutlineColor, UWORD XColor, std::string id, int size, std::string group) {
  if (specialButtons.find({ runningAppName, id, "radio" + group }) == specialButtons.end()) {
    bool firstOfMyKind = true;
    for (auto& [key, value] : specialButtons) {
      std::string appName = key.front();
      std::string buttonGroup = key.back();
      auto it = std::next(key.begin(), 1);
      std::string butId = *it;

      if (appName == runningAppName && buttonGroup == "radio" + group) {
        firstOfMyKind = false;
      }
    }
    if (firstOfMyKind == true) {
      specialButtons[{ runningAppName, id, "radio" + group }] = 1;  //app, id, type   value
    } else {
      specialButtons[{ runningAppName, id, "radio" + group }] = 0;
    }
  }

  if (specialButtons[{ runningAppName, id, "radio" + group }] == 1) {  //Make Circle, in circle, if selected, if not, Only Outline Circle
    Paint_DrawCircle(x + (size / 2), y + (size / 2), (size / 2), XColor, DOT_PIXEL_2X2, DRAW_FILL_EMPTY);
    Paint_DrawCircle(x + (size / 2), y + (size / 2), (size / 4.5), XColor, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  } else {
    Paint_DrawCircle(x + (size / 2), y + (size / 2), (size / 2), OutlineColor, DOT_PIXEL_2X2, DRAW_FILL_EMPTY);
  }

  if (!inTransition && !pauseRender) {
    if (Touch_CTS816.x_point >= x && Touch_CTS816.x_point <= x + size && Touch_CTS816.y_point >= y && Touch_CTS816.y_point <= y + size) {
      if (tap && !watchSwipe && !otherSwipe && !miscSwipe && !inTransition && !pauseRender) {
        if (tapHeld <= 1) {
          tap = false;
          otherSwipe = false;
          watchSwipe = false;
          inTransition = false;
          pauseRender = false;
          scrollV = 0;
          scrollY = 0;
          tapHeld = 999;

          for (auto& [key, value] : specialButtons) {
            std::string appName = key.front();
            std::string buttonGroup = key.back();
            auto it = std::next(key.begin(), 1);
            std::string butId = *it;

            if (appName == runningAppName && buttonGroup == "radio" + group) {
              specialButtons[{ appName, butId, "radio" + group }] = 0;
            }
          }
          specialButtons[{ runningAppName, id, "radio" + group }] = 1;
        }
      }
    }
  }

  return specialButtons[{ runningAppName, id, "radio" + group }];
}

//{"APP","ID", "TYPE"}: {EXTRA}
bool toggle(int x, int y, UWORD OutlineColor, UWORD ToggleColor, std::string id, int size = 30) {
  //Paint_DrawRectangle(x, y, x + size + size, y + size, OutlineColor, DOT_PIXEL_2X2, DRAW_FILL_EMPTY);
  if (specialButtons.find({ runningAppName, id, "toggle" }) == specialButtons.end()) {
    specialButtons[{ runningAppName, id, "toggle" }] = 0;  //app, id, type   value
    specialButtonsExtra[{ runningAppName, id, "toggle" }] = { 0, 0 };
  }

  if (!batSaver) {
    specialButtonsExtra[{ runningAppName, id, "toggle" }] = { (float)specialButtonsExtra[{ runningAppName, id, "toggle" }].front() / (float)1.5, specialButtonsExtra[{ runningAppName, id, "toggle" }].back() + specialButtonsExtra[{ runningAppName, id, "toggle" }].front() };
  }

  if (!inTransition && !pauseRender) {
    if (Touch_CTS816.x_point >= x && Touch_CTS816.x_point <= x + size + size && Touch_CTS816.y_point >= y && Touch_CTS816.y_point <= y + size) {
      if (tap && !watchSwipe && !otherSwipe && !inTransition && !pauseRender) {
        if (tapHeld <= 1) {
          tap = false;
          otherSwipe = false;
          watchSwipe = false;
          inTransition = false;
          miscSwipe = true;
          pauseRender = false;
          scrollV = 0;
          scrollY = 0;
          tapHeld = 999;
          float ae = size;
          if (specialButtons[{ runningAppName, id, "toggle" }] == 1) {
            if (batSaver) {
              specialButtonsExtra[{ runningAppName, id, "toggle" }] = { 0.0, 0.0 };
            } else {
              specialButtonsExtra[{ runningAppName, id, "toggle" }] = { (float)-ae / (float)3.0, ae };
            }
            specialButtons[{ runningAppName, id, "toggle" }] = 0;
          } else {
            if (batSaver) {
              specialButtonsExtra[{ runningAppName, id, "toggle" }] = { 0.0, ae };
            } else {
              specialButtonsExtra[{ runningAppName, id, "toggle" }] = { (float)ae / (float)3.0, 0 };
            }
            specialButtons[{ runningAppName, id, "toggle" }] = 1;
          }
        }
      }
    }
  }

  if (batSaver) {
    if (specialButtons[{ runningAppName, id, "toggle" }]) {
      Paint_DrawRectangle(x, y, x + size + size, y + size, ToggleColor, DOT_PIXEL_2X2, DRAW_FILL_FULL);
    } else {
      Paint_DrawRectangle(x, y, x + size + size, y + size, OutlineColor, DOT_PIXEL_2X2, DRAW_FILL_FULL);
    }
    Paint_DrawRectangle(x + specialButtonsExtra[{ runningAppName, id, "toggle" }].back(), y, x + size + specialButtonsExtra[{ runningAppName, id, "toggle" }].back(), y + size, WHITE, DOT_PIXEL_2X2, DRAW_FILL_FULL);

    if (specialButtons[{ runningAppName, id, "toggle" }]) {
      Paint_DrawRectangle(x, y, x + size + size, y + size, ToggleColor, DOT_PIXEL_2X2, DRAW_FILL_EMPTY);
    } else {
      Paint_DrawRectangle(x, y, x + size + size, y + size, OutlineColor, DOT_PIXEL_2X2, DRAW_FILL_EMPTY);
    }
  } else {
    if (specialButtons[{ runningAppName, id, "toggle" }]) {
      Paint_DrawRectangle(x + (size / 2), y, x + size + (size / 2), y + size, ToggleColor, DOT_PIXEL_2X2, DRAW_FILL_FULL);

      Paint_DrawCircle(x + size + (size / 2), y + (size / 2), (size / 2), ToggleColor, DOT_PIXEL_2X2, DRAW_FILL_FULL);
      Paint_DrawCircle(x + (size / 2), y + (size / 2), (size / 2), ToggleColor, DOT_PIXEL_2X2, DRAW_FILL_FULL);
    } else {
      Paint_DrawRectangle(x + (size / 2), y, x + size + (size / 2), y + size, OutlineColor, DOT_PIXEL_2X2, DRAW_FILL_FULL);

      Paint_DrawCircle(x + size + (size / 2), y + (size / 2), (size / 2), OutlineColor, DOT_PIXEL_2X2, DRAW_FILL_FULL);
      Paint_DrawCircle(x + (size / 2), y + (size / 2), (size / 2), OutlineColor, DOT_PIXEL_2X2, DRAW_FILL_FULL);
    }

    Paint_DrawCircle(x + specialButtonsExtra[{ runningAppName, id, "toggle" }].back() + (size / 2), y + (size / 2), (size / 2), WHITE, DOT_PIXEL_2X2, DRAW_FILL_FULL);
    //Paint_DrawRectangle(x + (size / 2), y, x + size + (size / 2), y + size, OutlineColor, DOT_PIXEL_3X3, DRAW_FILL_EMPTY);
  }

  return specialButtons[{ runningAppName, id, "toggle" }];
}

//TODO Upon App First time open, Reset all Per App Toggle Values to 0 //DONE
//Maybe add drop down select things https://mui.com/material-ui/react-select/ ////////////////////////////////////////////////////////////////

//TODO Add Alerts, little popups at bottom of screen that go above system running app, andd, Yeah, display for X time https://mui.com/material-ui/react-snackbar/ //DONE

//////////////////////
//TODO Add Linear and Circular Progress Bars, and give both Continuous? Options, If continous it just spins/loops forever until not rendering, if Not continuous, it needs a value from 0-100 to show percentage
//https://mui.com/material-ui/react-progress/

//AFTER FIXING BUTTONS AS TODO SAYS, Add "Toggle Buttons" press the button, stays on, deselect, etc
bool button(int x, int y, const char* text, sFONT* Font, UWORD Color_Foreground, UWORD Color_Background, int size) {  //TODO Make size more variable
  appSize = 45;                                                                                                       //35 Adjust as needed
  appLeng = 140;                                                                                                      //140

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
      if (tap && !watchSwipe && !otherSwipe && !miscSwipe && !inTransition && !pauseRender) {
        if (tapHeld <= 1) {
          tap = false;
          otherSwipe = false;
          watchSwipe = false;
          inTransition = false;
          pauseRender = false;
          scrollV = 0;
          scrollY = 0;
          tapHeld = 999;
          return true;
        }
      }
    }
  }
  return false;
}

int snackDisplayed = 0;
int snackYp = 240;
float snackYv = 0;
std::string currentSnack = "";
UWORD currrntSnackBack;
UWORD currentSnackText;

void snackBar(std::string text, UWORD BGC, UWORD TXCOLOR) {
  currentSnack = text;
  currrntSnackBack = BGC;
  currentSnackText = TXCOLOR;
  snackDisplayed = millis();
  snackYv = -35.0;
  snackYp = 240;
}

void renderSnack() {
  int size = 150;
  int ysize = 30;
  if (batSaver) {
    if (snackYv < -1) {
      snackYp = 205 - ysize;
    } else {
      snackYp = 250;
    }
  } else {
    snackYv = snackYv / 1.6;
    if (abs(snackYv) < 1) {
      snackYv = 0;
    }
    snackYp = snackYp + snackYv;
  }
  if (currentSnack != "") {
    //miscSwipe = true;
    int x = 120 - (size / 2);
    int y = snackYp;  //205 - ysize;

    if (batSaver) {
      Paint_DrawRectangle(x, min(y, 240), x + size, min(240, y + ysize), currrntSnackBack, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    } else {
      Paint_DrawCircle(x + (ysize / 2), y + (ysize / 2), (ysize / 2), currrntSnackBack, DOT_PIXEL_2X2, DRAW_FILL_FULL);
      Paint_DrawCircle(x + size - (ysize / 2), y + (ysize / 2), (ysize / 2), currrntSnackBack, DOT_PIXEL_2X2, DRAW_FILL_FULL);
      Paint_DrawRectangle(x + (ysize / 2), min(240, y), x + size - (ysize / 2), min(240, y + ysize), currrntSnackBack, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    }
    Paint_DrawString_EN(x + 10, min(240, y + ((ysize - 24) / 2)), currentSnack.c_str(), &Font24, currrntSnackBack, currentSnackText);
  }

  if (millis() - snackDisplayed > 6000) {
    snackDisplayed = millis() - 6000;
    snackYv = 40;
  }
  if (snackYp > 240) {
    currentSnack = "";
    //miscSwipe = false;
    snackYp = 240;
  }
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
  lastfpstick = millis();
  std::string text = "inet" + toilet + ";" + data;
  message = text.c_str();
  sendText(message);
  lastfpstick = millis();

  LCD_1IN28_DisplayWindows(10, 215, 230, 235, BlackImage);
  delay(100);
  //Note: No response!
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

std::function<void()> funcA;
void transitionLR(std::string app, int begin = 0, bool typeOfApp = false) {
  AppPtr func = apps[app];
  inTransition = true;
  int transP = begin;
  //I commented out the lower lines a while back for some odd reason
  //Paint_DrawRectangle(0, 0, min(max(transP, 0), 240), 240, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  if (typeOfApp == true) {
    auto itNew = appsV2.find(app);
    if (itNew != appsV2.end()) {
      funcA = [instance = itNew->second]() {
        instance->update();
      };
      //funcA();
    }
  } else {
    //func();
  }
  //LCD_1IN28_DisplayWindows(0, 0, begin, 240, BlackImage);
  //Paint_DrawRectangle(0, 0, min(max(transP, 0), 240), 240, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  //func();
  //LCD_1IN28_DisplayWindows(0, 0, begin, 240, BlackImage);
  float radius = 0;
  float radVel = 50;
  while (radVel > 1 && radius <= 240) {
    radVel = radVel / 1.1;
    radius += radVel;
    if (typeOfApp) {
      funcA();  //new
    } else {
      func();
    }
    LCD_1IN28_DisplayWindows(min(240, max(0, radius - 100)), 0, min(240, max(0, radius)), 240, BlackImage);
    //LCD_1IN28_DrawCircle(60, 120, radius, radius, BlackImage);
    //LCD_1IN28_DisplayCircle(begin,120,radius,BlackImage);
  }
}

void transitionRL(std::string app, int begin = 240, bool typeOfApp = false) {
  AppPtr func = apps[app];
  inTransition = true;
  int transP = begin;
  //I commented out the lower lines a while back for some odd reason
  //Paint_DrawRectangle(240, 0, min(max(transP, 0), 240), 240, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  if (typeOfApp == true) {
    auto itNew = appsV2.find(app);
    if (itNew != appsV2.end()) {
      funcA = [instance = itNew->second]() {
        instance->update();
      };
      //funcA();
    }
  } else {
    //func();
  }
  //LCD_1IN28_DisplayWindows(begin, 0, 240, 240, BlackImage);
  inTransition = true;

  //Paint_DrawRectangle(0, 0, min(max(transP, 0), 240), 240, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  //func();
  //LCD_1IN28_DisplayWindows(0, 0, begin, 240, BlackImage);
  float radius = 240;
  float radVel = 50;
  while (radVel > 1 && radius >= 0) {
    radVel = radVel / 1.1;
    radius -= radVel;
    if (typeOfApp) {
      funcA();  //new
    } else {
      func();
    }
    LCD_1IN28_DisplayWindows(min(240, max(0, radius)), 0, min(240, max(0, radius + 100)), 240, BlackImage);
    //LCD_1IN28_DrawCircle(60, 120, radius, radius, BlackImage);
    //LCD_1IN28_DisplayCircle(begin,120,radius,BlackImage);
  }
}

void transitionUD(std::string app, int begin = 0, bool typeOfApp = false) {
  AppPtr func = apps[app];
  inTransition = true;
  int transP = begin;
  //I commented out the lower lines a while back for some odd reason
  //Paint_DrawRectangle(0, 0, 240, min(max(transP, 0), 240), BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  if (typeOfApp == true) {
    auto itNew = appsV2.find(app);
    if (itNew != appsV2.end()) {
      funcA = [instance = itNew->second]() {
        instance->update();
      };
      //funcA();
    }
  } else {
    //func();
  }
  //LCD_1IN28_DisplayWindows(0, begin, 240, 240, BlackImage);
  inTransition = true;
  //Paint_DrawRectangle(0, 0, min(max(transP, 0), 240), 240, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  //func();
  //LCD_1IN28_DisplayWindows(0, 0, begin, 240, BlackImage);
  float radius = 0;
  float radVel = 50;
  while (radVel > 1 && radius <= 240) {
    radVel = radVel / 1.1;
    radius += radVel;
    if (typeOfApp) {
      funcA();  //new
    } else {
      func();
    }
    LCD_1IN28_DisplayWindows(0, min(240, max(0, radius - 100)), 240, min(240, max(0, radius)), BlackImage);
    //LCD_1IN28_DrawCircle(60, 120, radius, radius, BlackImage);
    //LCD_1IN28_DisplayCircle(begin,120,radius,BlackImage);
  }
}

void transitionDU(std::string app, int begin = 240, bool typeOfApp = false) {
  AppPtr func = apps[app];
  std::function<void()> funcA;
  inTransition = true;
  int transP = begin;
  //I commented out the lower lines a while back for some odd reason
  //Paint_DrawRectangle(0, 0, min(max(transP, 0), 240), 240, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  if (typeOfApp == true) {
    auto itNew = appsV2.find(app);
    if (itNew != appsV2.end()) {
      funcA = [instance = itNew->second]() {
        instance->update();
      };
      //funcA();
    }
  } else {
    //func();
  }
  //LCD_1IN28_DisplayWindows(0, 0, begin, 240, BlackImage);
  inTransition = true;

  float radius = 240;
  float radVel = 50;
  while (radVel > 1 && radius >= 0) {
    radVel = radVel / 1.1;
    radius -= radVel;
    if (typeOfApp) {
      funcA();  //new
    } else {
      func();
    }
    LCD_1IN28_DisplayWindows(0, min(240, max(0, radius)), 240, min(240, max(0, radius + 100)), BlackImage);
    //LCD_1IN28_DrawCircle(60, 120, radius, radius, BlackImage);
    //LCD_1IN28_DisplayCircle(begin,120,radius,BlackImage);
  }
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

void transitionRAND(std::string app, bool typeOfApp = false) {  //good
  AppPtr func = apps[app];
  std::function<void()> funcA;
  inTransition = true;
  if (typeOfApp == true) {
    auto itNew = appsV2.find(app);
    if (itNew != appsV2.end()) {
      std::function<void()> funcA = [instance = itNew->second]() {
        instance->update();
      };
      Paint_DrawRectangle(0, 0, 240, 240, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
      funcA();
    } else {
      Paint_DrawRectangle(0, 0, 240, 240, RED, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    }
  } else {
    Paint_DrawRectangle(0, 0, 240, 240, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    func();
  }
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

void transitionDOWNRAND(std::string app, bool typeOfApp = false) {  //good?
  AppPtr func = apps[app];
  std::function<void()> funcA;
  inTransition = true;
  if (typeOfApp == true) {
    auto itNew = appsV2.find(app);
    if (itNew != appsV2.end()) {
      std::function<void()> funcA = [instance = itNew->second]() {
        instance->update();
      };
      Paint_DrawRectangle(0, 0, 240, 240, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
      funcA();
    } else {
      Paint_DrawRectangle(0, 0, 240, 240, RED, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    }
  } else {
    Paint_DrawRectangle(0, 0, 240, 240, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    func();
  }
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

AppPtr funcER;
void openApp(std::string app, std::string dir = "", int start = -1) {
  vreg_set_voltage(VREG_VOLTAGE_1_30);
  delay(5);
  set_sys_clock_khz(400000, true);

  otherSwipe = false;
  watchSwipe = false;
  miscSwipe = false;
  swipeComplete = "";
  watchSwipe = false;
  activeDir = "";

  speedMode = false;
  idleTime = millis();

  if (app == "home") {
    DEV_SET_PWM(50);
  } else {
    if (runningAppName == "home") {
      DEV_SET_PWM(50);
    }
  }  //DEV_Delay_ms(1);
  inTransition = true;
  pauseRender = true;
  resetTransitionAfterTick = true;
  funcER = apps[app];
  std::function<void()> appLaunch;     // for v2 apps
  std::function<void()> appSysConfig;  // for v2 apps

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
  timeSinceLastButton = millis();

  typeOfApp = false;

  //Set Settings to default
  appPermissions = {};
  systemDisplayUpdates = false;  //default for v1 apps

  funcER = apps[app];
  funcER();

  if (typeOfApp == false) {    //v1
    appPermissions = { "*" };  //Unsafe
    appTitle = app;
    appDesc = "Unkown";
    appPub = "Unknown";
    appOthInfo = "Unknown";
    appVersion = 1.0;
    appDatePub = 0;
    appHash = "bc7819b34ff87570745fbe461e36a16f80e562ce";
  } else {                        //v2
    systemDisplayUpdates = true;  //Default for v2 apps
  }
  if (typeOfApp == true) {
    auto itNew = appsV2.find(app);
    auto it = std::find(backgroundApps.begin(), backgroundApps.end(), app);
    if (itNew != appsV2.end()) {
      appSysConfig = [instance = itNew->second]() {
        instance->sysConfig();
      };
      appLaunch = [instance = itNew->second]() {
        instance->launch();
      };

      appSysConfig();
      if (it == backgroundApps.end()) {
        /*
        for (auto& [key, value] : specialButtons) {
          std::string appName = key.front();
          std::string buttonGroup = key.back();
          auto it = std::next(key.begin(), 1);
          std::string butId = *it;

          if (appName == app) {
            specialButtons[{ app, butId, buttonGroup }] = 0;
            if (buttonGroup == "toggle") {
              specialButtonsExtra[{ app, butId, "toggle" }] = { 0, 0 };
            }
          }
        }
        */
        Serial.println("hardreset");
        //specialButtons = {};       //{"APP","ID", "TYPE"}: VALUE
        //specialButtonsExtra = {};  //{"APP","ID", "TYPE"}: {EXTRA}
        appLaunch();
      }
    }
    //Serial.println("V2 App");
  } else if (app != "keyboard" && app != "error" && app != "main" && app != "home" && app != "appsPanel" && app != "Developer" && app != "recentApps") {  //example get angy for outdated apps
    error = "Warning! App is out-dated and cannot be identified.";
    //app = "error";
  }
  if (start == -1) {
    if (dir == "DU" || dir == "RL") {
      start = 240;
    } else {
      start = 0;
    }
  }
  //Significantly slows down stuff (All transition stuff)
  funcER();
  if (dir == "LR") {
    transitionLR(app, start, typeOfApp);
  } else if (dir == "RL") {
    transitionRL(app, start, typeOfApp);
  } else if (dir == "UD") {
    transitionUD(app, start, typeOfApp);
  } else if (dir == "DU") {
    transitionDU(app, start, typeOfApp);
  } else if (dir == "RAND") {
    transitionRAND(app, typeOfApp);  //transitionDOWNRAND(app);
  }

  lastUsedAppName = runningAppName;

  runningAppV1 = apps[app];  //wait so if I define with a type does it make it "local"?
  if (typeOfApp == true) {
    auto itNew = appsV2.find(app);
    //if (itNew != appsV2.end()) {
    runningAppV2 = [instance = itNew->second]() {  //std::function<void()>  runningApp
      instance->update();
    };
    //}
  }

  runningAppName = app;
  //Serial.println(app.c_str());
  if (std::find(systemApps.begin(), systemApps.end(), app) == systemApps.end()) {
    if (std::find(backgroundApps.begin(), backgroundApps.end(), app) == backgroundApps.end()) {
      backgroundApps.push_back(app);
      if (backgroundApps.size() > 5) {
        backgroundApps.erase(backgroundApps.begin());
      }
    }
  }
  //Paint_Clear(BLACK);
  //DEV_Delay_ms(1);
  last = 0;
  last2 = 0;
  inTransition = true;
  /////Not needed?? Paint_DrawRectangle(0, 0, 240, 240, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  runningApp();                                          ///////Temp for testing? maybe may stay just needs to run smoother
  LCD_1IN28_DisplayWindows(0, 0, 240, 240, BlackImage);  ////^^
  runningApp();                                          ///////Temp for testing? maybe may stay just needs to run smoother
  LCD_1IN28_DisplayWindows(0, 0, 240, 240, BlackImage);  ////^^
  //runningApp();  //extra

  //DEV_Delay_ms(1);
  tickTenTen = 80;
  startup = false;
  pauseRender = false;
  otherSwipe = false;
  watchSwipe = false;

  last = 0;
  last2 = 0;
  if (app == "home") {
    set_sys_clock_khz(80000, true);
    delay(1);
    vreg_set_voltage(VREG_VOLTAGE_0_90);
    last2 = millis() + 99999999999;
  } else {
    if (speedMode == false) {
      medClock = true;
      turboClock = false;
      //set_sys_clock_khz(32000, true);
      //vreg_set_voltage(VREG_VOLTAGE_0_90);

      vreg_set_voltage(VREG_VOLTAGE_1_30);
      delay(1);
      set_sys_clock_khz(150000, true);  //120000
    } else {
      vreg_set_voltage(VREG_VOLTAGE_1_30);
      delay(1);
      set_sys_clock_khz(400000, true);
    }
  }
  //runningApp();////////////////////////////////////////
  //DEV_Delay_ms(1);

  inTransition = true;
  pauseRender = true;
  resetTransitionAfterTick = true;
  idleTime = millis();
  timeSinceLastButton = millis();
  //buttonPressCount = 0;
  //runningApp();  //extra
  //Why does pauseRender even exist.
  //typeOfApp = false;
  if (app == "home") {
    DEV_SET_PWM(5);
  } else {
    DEV_SET_PWM(100);
  }
}

bool swipe(std::string dir, int thresh) {
  int swipeStartThresh = 40;
  if(dir=="left" || dir=="right"){
    swipeStartThresh = max(min(thresh - 10, swipeStartThreshMain), 0);
  }
  bool swipeDone = false;
  if (inTransition == false && miscSwipe == false) {
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
            if (swipeComplete != "") {
              //pauseRender = true;
              //Paint_DrawRectangle(0, Touch_CTS816.y_point, 240, min(Touch_CTS816.y_point + 5, 240), deviceSecondColorTheme, DOT_PIXEL_1X1, DRAW_FILL_FULL);  // + 10
              //LCD_1IN28_DisplayWindows(0, max(0, Touch_CTS816.y_point - 25), 240, min(Touch_CTS816.y_point + 5, 240), BlackImage);
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
              //pauseRender = true;
              //Paint_DrawRectangle(0, max(Touch_CTS816.y_point - 5, 0), 240, Touch_CTS816.y_point, deviceSecondColorTheme, DOT_PIXEL_1X1, DRAW_FILL_FULL);
              //LCD_1IN28_DisplayWindows(0, max(Touch_CTS816.y_point - 5, 0), 240, min(Touch_CTS816.y_point + 25, 240), BlackImage);
            }
          }
          //if (Touch_CTS816.y_point > 110 && Touch_CTS816.y_point < 200 && watchSwipe == false) {
          //watch swipe is retired
          if (Touch_CTS816.y_point > 240 - swipeStartThresh) {
            otherSwipe = true;
            activeDir = "up";
          }
        } else if (dir == "right" && (activeDir == "" || activeDir == dir)) {
          //Serial.println("Raw");
          if (otherSwipe) {
            //Serial.println("AA");
            if (Touch_CTS816.x_point > thresh) {
              swipeComplete = dir;
            } else {
              swipeComplete = "";
            }
            if (swipeComplete != "") {
              //pauseRender = true;
              //Paint_DrawRectangle(Touch_CTS816.x_point, 0, max(min(Touch_CTS816.x_point + 5, 240), 0), 240, deviceSecondColorTheme, DOT_PIXEL_1X1, DRAW_FILL_FULL);
              //LCD_1IN28_DisplayWindows(max(0, Touch_CTS816.x_point - 25), 0, min(Touch_CTS816.x_point + 5, 240), 240, BlackImage);
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
            if (swipeComplete != "") {
              //pauseRender = true;
              //Paint_DrawRectangle(max(min(Touch_CTS816.x_point - 5, 240), 0), 0, Touch_CTS816.x_point, 240, deviceSecondColorTheme, DOT_PIXEL_1X1, DRAW_FILL_FULL);
              //LCD_1IN28_DisplayWindows(max(0, Touch_CTS816.x_point - 5), 0, min(Touch_CTS816.x_point + 25, 240), 240, BlackImage);  //and the other - should be -10
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
          }
        }
      }
    }

    if (swipeDone == false && swipeComplete == dir && tap == false) {  //just in case override
      swipeDone = true;
      swipeComplete = "";
      activeDir = "";
    }

    if (otherSwipe && watchSwipe == false && swipeComplete != "") {  //swipeComplete thing new cuz whenever I tap on side it paused .. so yuck
      //pauseRender = true;
    } else {
      pauseRender = false;
    }

    if (otherSwipe) {
      scrollV = 0;
    }

    if (swipeDone) {
      scrollY = 0;
      scrollV = 0;
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
    delay(5000);
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

void homeExec() {
  AppPtr funcHome = apps["main"];
  inTransition = true;
  funcHome();
}

void homeExecOld() {
  //resultButINeedPrivates = DEC_ADC_Read() * (3.3f / (1 << 12) * 2);
  unsigned long elapsed_time = millis() + CurTime;
  unsigned long hours = (elapsed_time % 86400000) / 3600000;
  unsigned long minutes = (elapsed_time % 3600000);
  unsigned long seconds = (elapsed_time % 60000);
  unsigned long days = int(elapsed_time / 86400000) / 24;  //um
  int year, month, day;
  String dayOfWeek;
  String monthName;
  millisToDate(elapsed_time, year, month, day, dayOfWeek, monthName);

  int second_x = 120 - (105 * sin(((seconds / 166.666666666) + 180) * PI / 180));
  int second_y = 120 + (105 * cos(((seconds / 166.666666666) + 180) * PI / 180));

  if (hours > 12) {
    hours = hours - 12;
  }
  preHours = hours;
  if (hours == 0) {
    hours = 12;
  }

  uint16_t minute_x = 120 + (110 * sin(((minutes / 10000)) * PI / 180));
  uint16_t minute_y = 120 - (110 * cos(((minutes / 10000)) * PI / 180));
  //uint16_t minute_x_short = 120 + (90 * sin(((minutes / 10000)) * PI / 180));
  //uint16_t minute_y_short = 120 - (90 * cos(((minutes / 10000)) * PI / 180));

  //  Paint_DrawLine(minute_x_short, minute_y_short, (uint16_t)minute_x, (uint16_t)minute_y, deviceSecondColorTheme, DOT_PIXEL_4X4, LINE_STYLE_SOLID);  // Replace 0x009688 with your chosen color

  //Paint_DrawLine(120, 120, (uint16_t)minute_x, (uint16_t)minute_y, deviceSecondColorTheme, DOT_PIXEL_2X2, LINE_STYLE_SOLID);

  //Paint_DrawCircle((uint16_t)minute_x, (uint16_t)minute_y, 4, WHITE, DOT_PIXEL_4X4, DRAW_FILL_FULL); // Replace 0x009688 with your chosen color
  //Paint_DrawCircle((uint16_t)minute_x_short, (uint16_t)minute_y_short, 4, WHITE, DOT_PIXEL_4X4, DRAW_FILL_FULL); // Replace 0x009688 with your chosen color
  //was 4

  uint16_t hour_x = 120 + (60 * sin(((hours % 12) * 30 + 0) * PI / 180));
  uint16_t hour_y = 120 - (60 * cos(((hours % 12) * 30 + 0) * PI / 180));

  //uint16_t hour_x_cent = 120 + (4 * sin(((hours % 12) * 30 + 0) * PI / 180));
  //uint16_t hour_y_cent = 120 - (4 * cos(((hours % 12) * 30 + 0) * PI / 180));

  //uint16_t hour_x_circle = 120 + (59 * sin(((hours % 12) * 30 + 0) * PI / 180));
  //uint16_t hour_y_circle = 120 - (59 * cos(((hours % 12) * 30 + 0) * PI / 180));

  int weathLen = weatherTemp.length();
  Paint_DrawImage1(Sun, 120 - 8, 140, 16, 16, YELLOW);
  Paint_DrawString_EN(120 - ((weathLen * 7) / 2), 156, weatherTemp.c_str(), &Font12, BLACK, GRAY);

  String dateStr = dayOfWeek + ", " + monthName + " " + day;
  int lengthOfDate = dateStr.length();
  Paint_DrawString_EN((int)120 - ((lengthOfDate * 11) / 2), 19, dateStr.c_str(), &Font16, BLACK, deviceMainColorTheme);


  Paint_DrawLine(120, 120, (uint16_t)hour_x, (uint16_t)hour_y, deviceMainColorTheme, DOT_PIXEL_2X2, LINE_STYLE_SOLID);  // Replace 0x00796F with your chosen color
  Paint_DrawLine(120, 120, (uint16_t)minute_x, (uint16_t)minute_y, deviceSecondColorTheme, DOT_PIXEL_2X2, LINE_STYLE_SOLID);

  //Paint_DrawCircle((uint16_t)hour_x_circle, (uint16_t)hour_y_circle, 6, 0x009688, DOT_PIXEL_6X6, DRAW_FILL_FULL); // Replace 0x00796F with your chosen color
  Paint_DrawCircle(120, 120, 3, deviceMainColorTheme, DOT_PIXEL_3X3, DRAW_FILL_FULL);  // Replace 0x00796F with your chosen color





  for (int i = 0; i < 12; ++i) {
    uint16_t hour_x_tic = 120 + (80 * sin(((i % 12) * 30 + 0) * PI / 180));
    uint16_t hour_y_tic = 120 - (80 * cos(((i % 12) * 30 + 0) * PI / 180));

    uint16_t hour_x_tic_short = 120 + (75 * sin(((i % 12) * 30 + 0) * PI / 180));
    uint16_t hour_y_tic_short = 120 - (75 * cos(((i % 12) * 30 + 0) * PI / 180));

    if (i == preHours) {
      uint16_t hour_x_mark = 120 + (90 * sin(((i % 12) * 30 + 0) * PI / 180));
      uint16_t hour_y_mark = 120 - (90 * cos(((i % 12) * 30 + 0) * PI / 180));
      //int lengthOfHr = std::to_string(hours).length();
      //Paint_DrawString_EN(hour_x_mark - ((lengthOfHr * 14) / 2), hour_y_mark + get_yshift(preHours), std::to_string(hours).c_str(), &Font20, BLACK, deviceMainColorTheme);
      Paint_DrawLine(hour_x_tic_short, hour_y_tic_short, (uint16_t)hour_x_tic, (uint16_t)hour_y_tic, deviceMainColorTheme, DOT_PIXEL_2X2, LINE_STYLE_SOLID);
    } else {
      Paint_DrawLine(hour_x_tic_short, hour_y_tic_short, (uint16_t)hour_x_tic, (uint16_t)hour_y_tic, GRAY, DOT_PIXEL_2X2, LINE_STYLE_SOLID);
    }
  }

  //was 8
  //Paint_DrawCircle(second_x, second_y, 7, deviceThirdColorTheme, DOT_PIXEL_2X2, DRAW_FILL_FULL);

  //  Paint_DrawString_EN(70, 190, (std::to_string(day)).c_str(), &Font16, BLACK, deviceThirdColorTheme);

  //sprintf(buffer, "%02d", days, hours);
  //Paint_DrawString_EN(100, 131, buffer, &Font24, BLACK, WHITE);
  //Dates are weird, fix later

  if (elapsed_time - last > 15000) {
    last = elapsed_time;
    saveToEEPROMX(last, 1);
  }

  if (!BLEconnected) {
    Paint_DrawImage1(NoConnection, 120 - 8, 210, 16, 16, RED);
  }
}


void home() {  //https://i.pinimg.com/736x/75/60/81/756081eafa27af63b55aad1eebf10eec.jpg
  float resultButINeedPrivates = DEC_ADC_Read() * (3.3f / (1 << 12) * 2);
  unsigned long elapsed_time = millis() + CurTime;  // + 46800000 + 2400000
  //unsigned long hours = (elapsed_time % 86400000) / 3600000;
  //unsigned long minutes = (elapsed_time % 3600000);
  //unsigned long seconds = (elapsed_time % 60000);


  lastfpstick = millis();

  if (batSaver == false) {
    checkNotif();
    lastfpstick = millis();
  }

  //ALSO DISPLAY BAT PERCENT.
  if (aod && batSaver == false) {
    if (elapsed_time - last2 > homeAppLowPower || inTransition) {
      homeExec();
      lastfpstick = millis();
    }
    if (resultButINeedPrivates > 2.9) {
      Paint_DrawCircle(120, 120, 118, GREEN, DOT_PIXEL_2X2, DRAW_FILL_EMPTY);
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
      lastfpstick = millis();
      LCD_1IN28_Display(BlackImage);
      lastfpstick = millis();
    }
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
      //LCD_1IN28_DisplayWindows(10, 100, 240, 240, BlackImage);
      LCD_1IN28_DisplayWindows(0, 0, 240, 240, BlackImage);
    }

    if (butaction) {
      butaction = false;
      saveToEEPROMX(1, 2);
      openApp("main", "", 0);
      buttonPressCount = 0;
    }
  }
}


void setup() {
  vreg_set_voltage(VREG_VOLTAGE_1_30);
  delay(10);
  set_sys_clock_khz(400000, true);  //set_sys_clock_khz(300000, true);
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

  //Apps V1
  apps["home"] = &home;
  apps["main"] = &mainScreen;
  apps["notifPane"] = &notifPane;
  apps["appsPanel"] = &appsPanel;
  apps["recentApps"] = &recentApps;
  //apps["nfc"] = &nfc;
  apps["Set Time"] = &setTime;
  apps["previewNotif"] = &previewNotif;
  apps["keyboard"] = &keyboardR;
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

  //Apps V2
  apps["appVersTwo"] = &appV2;
  appsV2["appVersTwo"] = new appVersTwo();

  apps["appVersTwoTestTwo"] = &appV2;
  appsV2["appVersTwoTestTwo"] = new appVersTwoTestTwo();

  apps["devTerm"] = &appV2;
  appsV2["devTerm"] = new devTerm();
  //updateAppNames();

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

  //pinMode(27, OUTPUT);
  pinMode(28, OUTPUT);

  pulseSensor.analogInput(PulseWire);  //27
  pulseSensor.setThreshold(Threshold);
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

    while (counter < 5) {  //300 //was 360
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
    //error = "TAP thread detected an application was  not responding.";
  } else if (errorCode == 3) {
    //error = "BUT thread detected an application was  not responding.";
  }
  //} else {
  //  error = "An error occured and the device had to  reset." + std::to_string(errorCode);
  //}
  if (error != "") {
    openApp("error", "", 0);
  } else {
    openApp("appsPanel", "RAND");
  }

  buttonPressCount = 0;

  std::string test = "DevStart";
  message = test.c_str();
  sendText(message);
}


int initalYPos = -1;
int shouldConsiderUpdating = 0;
int timeInTrans = 0;
bool alreadySet = true;

void loop() {  //bare min
  if (runningAppName == "home") {
    if (millis() - updateHome > 300000) {
      updateHome = millis();
      runningApp();
    }
  } else {
    runningApp();
  }
  //checkNotif();  //Check for incoming data

  //Do heart rate stuff, and some little battery saver stuff

  frameCount++;
  oneTickPause = false;
  if (millis() - lastfpstick >= 2000) {
    lastfpstick = millis();
    fps = (int)frameCount / 2;
    frameCount = 0;

    if (runningAppName == "home") {  //Lower Clock
      set_sys_clock_khz(32000, true);
      vreg_set_voltage(VREG_VOLTAGE_0_90);
    } else {  //consider batSaver
      DEV_SET_PWM(100);
      vreg_set_voltage(VREG_VOLTAGE_1_30);
      set_sys_clock_khz(400000, true);

      /*
      if (millis() - idleTime > autoClock) {
        //lastUsedAppName = runningAppName;
        openApp("home", "RAND");
        idleTime = millis();
      }
      */
    }
  }
  if (resetTransitionAfterTick) {
    inTransition = false;
    pauseRender = false;
    resetTransitionAfterTick = false;
  }
  if (millis() - serviceLastRan > 1800000) {  //Services
    serviceLastRan = millis();
    runNextService();
  }
  if (millis() - timeSinceLastButton > 200 && buttonPressCount > 0) {  //Button Press
    if (buttonPressCount == 1) {
      if (runningAppName == "main") {
        openApp("appsPanel", "DU");
      } else {
        openApp("main", "RAND");
      }
    } else if (buttonPressCount == 2) {
      openApp("recentApps", "DU");
    } else if (buttonPressCount >= 3) {
      if (!backgroundApps.empty()) {
        openApp(backgroundApps.back(), "RAND");
      }
    }
    buttonPressCount = 0;
    timeSinceLastButton = millis();
  }


  if (ticksSinceTap > 1 && tap) {  //Tap Stuff
    tap = false;
    watchSwipe = false;
    otherSwipe = false;
    miscSwipe = false;
    ticksSinceTap = 0;
    tapHeld = 0;
    activeDir = "";
  } else if (tap) {
    tapHeld++;
    idleTime = millis();
    ticksSinceTap++;
  }
}



void loopOLD() {
  //Touch_INT_callback();
  ///> 3000 ,,,,,,, > 10
  if (millis() - shouldConsiderUpdating > 5000 || (millis() - shouldConsiderUpdating > 50 && (scrolling || tap || otherSwipe || watchSwipe || inTransition || miscSwipe))) {
    shouldConsiderUpdating = millis();
    if (batSaver == false) {
      if (speedMode == false) {
        if ((tap && tapHeld > 3) || scrolling || otherSwipe || watchSwipe || inTransition || miscSwipe) {
          if (turboClock == false) {
            turboClock = true;
            medClock = false;
            vreg_set_voltage(VREG_VOLTAGE_1_30);
            delay(1);
            set_sys_clock_khz(400000, true);
            alreadySet = true;
          }
        } else if (runningAppName != "home") {
          if (medClock == false) {
            medClock = true;
            turboClock = false;
            //set_sys_clock_khz(32000, true);
            //vreg_set_voltage(VREG_VOLTAGE_0_90);
            if (alreadySet) {
              vreg_set_voltage(VREG_VOLTAGE_1_30);
              delay(1);
              set_sys_clock_khz(150000, true);  //120000
              alreadySet = false;
            }
          }
        }
      }
    } else {
      if (runningAppName != "home") {
        if (tap) {
          medClock = true;
          turboClock = false;
          if (alreadySet) {
            vreg_set_voltage(VREG_VOLTAGE_1_10);
            set_sys_clock_khz(78000, true);
            alreadySet = false;
          }
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


  if (ticksSinceTap > 1 && tap) {  //was >1
    tap = false;
    //otherSwipe=false;//WAS TURNED OFF, for some reason
    watchSwipe = false;
    otherSwipe = false;
    miscSwipe = false;
    ticksSinceTap = 0;
    activeDir = "";
    //Serial.println("Releasse");
  } else if (tap) {
    ticksSinceTap++;
  }

  if (runningAppName == "home") {
    if (millis() - updateHome > 300000) {
      updateHome = millis();
      runningApp();
    }
  } else {  // if (buttonDown == false) {
    runningApp();
  }

  if (resetTransitionAfterTick) {
    inTransition = false;
    pauseRender = false;
    resetTransitionAfterTick = false;
  }

  /*
  //try {
  if (runningAppName == "home") {
    if (millis() - updateHome > 300000) {
      updateHome = millis();
      runningApp();
    }
  } else if (buttonDown == false) {
    runningApp();
  }
/*/

  //Serial.print(appTitle.c_str());
  //Serial.println(appDatePub);

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
  } else if (millis() - timeInTrans > 4000) {
    inTransition = false;
    pauseRender = false;
    timeInTrans = millis() + 30000;
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




    if (millis() - timeSinceLastButton > 200 && buttonPressCount > 0) {
      if (batSaver == false) {
        turboClock = true;
        medClock = false;
        vreg_set_voltage(VREG_VOLTAGE_1_30);
        set_sys_clock_khz(400000, true);
      }

      if (buttonPressCount == 1) {
        if (runningAppName == "main") {
          openApp("appsPanel", "DU");
        } else {
          openApp("main", "RAND");
        }
      } else if (buttonPressCount == 2) {
        openApp("recentApps", "DU");
      } else if (buttonPressCount >= 3) {
        if (!backgroundApps.empty()) {
          openApp(backgroundApps.back(), "RAND");
        }
      }
      buttonPressCount = 0;
      timeSinceLastButton = millis();
    }

    if (butaction) {
      butaction = false;
      timeSinceLastButton = millis();
      //was stuff herre,.. not anymore
    }
  }

  tickTenTen++;



  //Handle Swipe up to home
  if (runningAppName != "home") {
    if (tap) {  //flag==1
                //  flag=0;
      tapHeld++;
      //tap=true;
      idleTime = millis();
      if (runningAppName != "home") {
        if (watchSwipe == true && otherSwipe == false && miscSwipe == false) {  // && pauseRender==false
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
            //inTransition = false;
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
                //delay(10);
                openApp("home", "RAND", Touch_CTS816.y_point);
                //delay(200);//200
              } else {
                //delay(10);
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
        delay(1);  //10
        vreg_set_voltage(VREG_VOLTAGE_0_90);
      }
    } else if (speedMode && batSaver == false) {
      DEV_SET_PWM(100);
      vreg_set_voltage(VREG_VOLTAGE_1_30);
      delay(1);
      set_sys_clock_khz(400000, true);
      dontRunDimAgain = true;
    } else {
      DEV_SET_PWM(100);
      dontRunDimAgain = true;
    }
  }


  int val = analogRead(PulseWire);

  //int val2 = val / 10;
  //Serial.println(val);

  /* <<Works SUPER well with finger
  if (val < 2060 && BeatTrig == false) {//2500
    beat++;
    BeatTrig = true;
    Serial.print("Beat");
    Serial.println(beat);
  }
  if(val > 2100){
    BeatTrig = false;
  }
*/
  Serial.print("change:");
  Serial.println((int)min(max(-5, val - lastVal), 50) / 4);
  if ((int)min(max(-5, val - lastVal), 50) / 4 > 4 && !BeatTrig && millis() - lastBeat > 600) {  //20
    beat++;
    BeatTrig = true;
    lastBeat = millis();
    Serial.print("Beat:");
    Serial.println(30);
  } else if (BeatTrig && (int)min(max(-5, val - lastVal), 50) / 4 < 1) {  //-15
    BeatTrig = false;
  } else {
    Serial.print("Beat:");
    Serial.println(0);
  }
  if (millis() - lastValCheck > 400) {  //150
    lastValCheck = millis();
    lastVal = val;
  }
  if (millis() - checkBPM > 15000) {
    checkBPM = millis();
    BPM = beat * 4;
    beat = 0;
  }
  Serial.print("bpm:");
  Serial.println(BPM);



  //if(millis()-checkBPM>10000){
  if (pulseSensor.sawStartOfBeat()) {
    checkBPM = millis();
    BPM = pulseSensor.getBeatsPerMinute();
    Serial.println(BPM);
    if (BPM > 200) {
      BPM = 200;
    }
  }


  if (runningAppName == "home") {
    if (dontRunDimAgain == false) {
      //DEV_Delay_ms(1000);  //500 ///////////1000 05/19/24
      if (runningAppName == "home") {
        DEV_Delay_ms(1000);
      } else {  // if (buttonDown == false) {
        inTransition = false;
        pauseRender = false;
        runningApp();
      }
      if (runningAppName == "home") {  //THESE REPEATED COMMANDS ENSURE SMOOTH TRANSITION BETWEEN HOME AND MAIN, WHILST SAVING BATTERY WHEN IT CAN
        DEV_Delay_ms(1000);
      } else {  // if (buttonDown == false) {
        inTransition = false;
        pauseRender = false;
        runningApp();
      }
      if (runningAppName == "home") {
        DEV_Delay_ms(1000);
      } else {  // if (buttonDown == false) {
        inTransition = false;
        pauseRender = false;
        runningApp();
      }
      if (runningAppName == "home") {
        DEV_Delay_ms(1000);
      } else {  // if (buttonDown == false) {
        inTransition = false;
        pauseRender = false;
        runningApp();
      }
      if (runningAppName == "home") {
        DEV_Delay_ms(1000);
      } else {  // if (buttonDown == false) {
        inTransition = false;
        pauseRender = false;
        runningApp();
      }
    }
  } else if (runningAppName == "Step Tracker") {
    autoClock = 3600000;
  } else {
    autoClock = 15000;
  }
  /*
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
*/
  //renderSnack();



  frameCount++;
  if (millis() - lastfpstick >= 2000) {
    lastfpstick = millis();
    fps = (int)frameCount / 2;
    frameCount = 0;
  }

  oneTickPause = false;
  if (!otherSwipe && !watchSwipe && pauseRender) {
    pauseRender = false;
  }

  if (buttonDown) {
    timeSinceLastButton = millis();
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
    openApp("main", "RAND", 0);
    updateHome = 0;
  }
  if (millis() - lastfpstick >= 10000 && runningAppName != "boot") {
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

int lastPress = 0;

void buttonPress() {
  timeSinceLastButton = millis();

  if (digitalRead(26) == HIGH) {
    if (millis() - lastPress > 2) {  //10
      lastPress = millis();
      //buttonPressCount += 1;
      timeSinceLastButton = millis();
      if (buttonDown == false) {
        buttonDown = true;
        //buttonPressCount += 1;
        if (runningAppName == "home") {
          DEV_SET_PWM(100);
          vreg_set_voltage(VREG_VOLTAGE_1_30);
          delay(1);
          set_sys_clock_khz(400000, true);
          openApp("main", "RAND", 0);
          buttonPressCount = 0;
        } else {
          butaction = true;
          buttonPressCount += 1;
        }
      }
    }
  } else {
    buttonDown = false;
    lastPress = millis();
  }
  if (millis() - lastfpstick >= 10000 && runningAppName != "boot") {
    Serial.println("Something broke..");
    saveToEEPROMX(3, 2);
    resetFunc();
    //error="App Timed Out.";
    //vreg_set_voltage(VREG_VOLTAGE_0_90);
    //set_sys_clock_khz(420000, true);
    openApp("main", "", 0);
  }
  timeSinceLastButton = millis();

  //delay(1);
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
  //Serial.println("PRESS");
}


//420000 was the old peak