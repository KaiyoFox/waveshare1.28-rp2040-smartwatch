#ifndef devTerm_H  //Must Include Section:
#define devTerm_H
#include "App.h"
extern bool inTransition;
extern bool pauseRender;
extern bool otherSwipe;
extern bool startup;
extern UWORD* BlackImage;  //Other
extern std::list<std::string> appPermissions;
extern std::string appTitle;
extern std::string appDesc;
extern std::string appPub;
extern std::string appOthInfo;
extern float appVersion;
extern int appDatePub;
extern std::string appHash;  //Config
extern uint16_t deviceMainColorTheme;
extern uint16_t deviceSecondColorTheme;
extern uint16_t deviceThirdColorTheme;  // Device Customization Settings [Optional]
extern int EEPROM_SIZE;
extern int FILE_TABLE_START;

// Settings:
extern bool systemDisplayUpdates;  // Default = True

std::list<std::string> lines;
std::string curDir = "/";

void renderLines() {
  int startX = 30;
  int startY = 40;
  int lineHeight = 18;

  int textBackgroundColor = BLACK;
  int textColor = GREEN;

  int currentY = startY;
  while (lines.size() > 9) {
    if (!lines.empty()) {
      auto it = lines.begin();
      lines.erase(it);
    }
  }
  for (const std::string& line : lines) {
    Paint_DrawString_EN(startX, currentY, line.c_str(), &Font16, textBackgroundColor, textColor);
    currentY += lineHeight;
  }
}


std::list<std::string> getItemsExceptLast(const std::list<std::string>& myList) {
  if (myList.size() <= 1) {
    return myList;
  }
  auto it = std::next(myList.begin(), myList.size() - 1);
  std::list<std::string> result;
  for (const std::string& str : std::list<std::string>(myList.begin(), it)) {
    result.push_back(str);
  }
  return result;
}

std::string join(const std::list<std::string>& list, char separator) {
  std::ostringstream ss;
  bool first = true;
  for (const auto& element : list) {
    if (!first) {
      ss << separator;
    }
    ss << element;
    first = false;
  }
  return ss.str();
}


class devTerm : public App {
public:
  void sysConfig() override {  // Triggers randomly when device needs info
    appPermissions = {};       //Permissions app needs in order to warn user about apps
    //Specify App Settings here

    appTitle = "Terminal";                                 // Title
    appDesc = "Read/Write files frome file system";        // Description
    appPub = "Kaiyo";                                      // Publisher
    appOthInfo = "Website: kaiyo.dev";                     // Other Info
    appVersion = 1.0;                                      // Version
    appDatePub = 1718306891;                               // Unix Timestamp
    appHash = "6017612eb90d5b39b27a12e756a61be852971e8e";  // More Unique Identifier (SHA1)
  }

  void launch() override {  // Triggers upon first time opening app
    lines.clear();
    // ...
  }

  void update() override {  // Triggers on each frame
    if (startup) {
      if (keyboardData != "") {
        std::string input = keyboardData;
        keyboardData = "";

        lines.push_back(">" + input);
        std::list<std::string> data = split(input, ' ');
        std::string com = data.front();
        std::string lastData = data.back();


        if (com == "LS") {
          if (lastData == com || lastData == "") {
            lastData = curDir;
          }
          std::list<std::string> dirEntries = listDir(lastData.c_str());
          for (const std::string& entry : dirEntries) {
            if (entry != "") {
              lines.push_back("  -" + entry);
            }
          }
        } else if (com == "MKDIR") {
          bool ae = false;
          if (curDir != "/") {
            ae = createFolder((curDir + "/" + lastData).c_str());
          } else {
            ae = createFolder(("/" + lastData).c_str());
          }
          if (ae) {
            lines.push_back("  -Successful");
          } else {
            lines.push_back("  -Failed");
          }
        } else if (com == "FORMAT") {
          curDir = "/";
          initializeFileSystem();
          lines.push_back("  -Successful");
        } else if (com == "CD") {
          std::string pre = curDir;
          if (lastData != com) {
            if (lastData.at(0) != '/') {
              if (curDir == "/") {
                curDir = curDir + lastData;
              } else {
                curDir = curDir + "/" + lastData;
              }
            } else {
              curDir = lastData;
            }
          } else {
            curDir = join(getItemsExceptLast(split(curDir, '/')), '/');
          }
          if (curDir == "" || curDir == " ") {
            curDir = "/";
          }
          if (fileExists(curDir.c_str(), false) == false) {
            curDir = pre;
            lines.push_back("  -Failed");
          } else {
            lines.push_back("  -" + curDir);
          }
        } else if (com == "WRITE") {
          if (data.size() >= 2) {
            auto itE = data.begin();
            auto it = data.begin();
            std::advance(itE, 1);

            std::string firstElement = *itE;
            std::string sec;
            if (firstElement[0] != '/') {
              if (curDir != "/") {
                sec = curDir + "/" + firstElement;
              } else {
                sec = curDir + firstElement;
              }
            } else {
              sec = firstElement;
            }
            data.erase(itE);
            data.erase(it);

            std::string joinedString = join(data, ' ');

            bool ae = createFile(sec.c_str(), joinedString.c_str());
            if (ae) {
              lines.push_back(" -Successful");
            } else {
              lines.push_back(" -Failed");
            }
          } else {
            lines.push_back(" -Failed more Args needed.");
          }
        } else if (com == "CAT") {
          std::string path = "";
          if (lastData.at(0) != '/') {
            if (curDir == "/") {
              path = curDir + lastData;
            } else {
              path = curDir + "/" + lastData;
            }
          } else {
            path = lastData;
          }
          lines.push_back("  -" + listFileContents(path.c_str()));
        } else if (com == "USED") {
          int used = FileSysCalculateUsedSpace();  //calculateUsedSpace();
          float percent = (float)used / (float)(EEPROM_SIZE - FILE_TABLE_START);
          percent = (float)percent * 100;
          lines.push_back(("  -" + std::to_string(used) + "/" + std::to_string((EEPROM_SIZE - FILE_TABLE_START)) + "B " + std::to_string((int)percent) + "%").c_str());
        } else if (com == "DIR") {
          lines.push_back(" -" + curDir);
        } else if (com == "RM") {
          std::string path = "";
          if (lastData.at(0) != '/') {
            if (curDir == "/") {
              path = curDir + lastData;
            } else {
              path = curDir + "/" + lastData;
            }
          } else {
            path = lastData;
          }
          bool ae = removeFile(path.c_str());
          if (ae) {
            lines.push_back(" -Successful");
          } else {
            lines.push_back(" -Failed");
          }
        } else if (com == "RMDIR") {
          std::string path = "";
          if (lastData.at(0) != '/') {
            if (curDir == "/") {
              path = curDir + lastData;
            } else {
              path = curDir + "/" + lastData;
            }
          } else {
            path = lastData;
          }
          bool ae = removeDir(path.c_str());
          if (ae) {
            lines.push_back(" -Successful");
          } else {
            lines.push_back(" -Failed");
          }
        } else if (com == "FILL") {
          std::string path = "";
          lastData = "FILL";
          if (lastData.at(0) != '/') {
            if (curDir == "/") {
              path = curDir + lastData;
            } else {
              path = curDir + "/" + lastData;
            }
          } else {
            path = lastData;
          }
          bool ae = true;
          while (ae) {
            ae = createFile(path.c_str(), "AA");

            path = "";
            lastData = "FILL" + std::to_string(random(999));
            if (lastData.at(0) != '/') {
              if (curDir == "/") {
                path = curDir + lastData;
              } else {
                path = curDir + "/" + lastData;
              }
            } else {
              path = lastData;
            }
          }
          lines.push_back(" -Filled");
        } else if (com == "RAND") {
          EEPROM.begin(EEPROM_SIZE);
          for (int i = 5; i < EEPROM_SIZE; i++) {
            if (EEPROM.read(i) == 255) {
              EEPROM.write(i, random(255));
            }
          }
          EEPROM.commit();
          EEPROM.end();
          lines.push_back(" -Successful");
        }
      }
    }
    renderLines();
    if (tap && tapHeld > 10) {
      openApp("keyboard", "DU", 0);
    }
  }
};

#endif