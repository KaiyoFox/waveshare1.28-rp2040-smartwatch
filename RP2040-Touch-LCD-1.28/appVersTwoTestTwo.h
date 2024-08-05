#ifndef appVersTwoTestTwo_H  //Must Include Section:
#define appVersTwoTestTwo_H
#include "App.h"
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

//Extra Libs
#include <string>

// Settings:
extern bool systemDisplayUpdates;  // Default = True

class appVersTwoTestTwo : public App {
public:
  void sysConfig() override {  // Triggers randomly when device needs info
    appPermissions = {};       //Permissions app needs in order to warn user about apps
    //Specify App Settings here

    appTitle = "Test App2";                                // Title
    appDesc = "Testing Reasons";                           // Description
    appPub = "Kaiyo";                                      // Publisher
    appOthInfo = "Website: kaiyo.dev";                     // Other Info
    appVersion = 1.0;                                      // Version
    appDatePub = 1716084259;                               // Unix Timestamp
    appHash = "6017612eb90d5b39b27a12e756a61be852971e8e";  // More Unique Identifier (SHA1)
  }

  void launch() override {  // Triggers upon first time opening app
    snackBar("rwar", WHITE, BLACK);
    // ...
  }

  void update() override {  // Triggers on each frame
    Paint_DrawRectangle(0, 0, 100, 100, RED, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    if (swipe("left", 70)) {
      openApp("keyboard", "", 0);
    }
  }
};

#endif
