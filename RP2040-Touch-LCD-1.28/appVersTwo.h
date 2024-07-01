#ifndef APPVERSTWO_H
#define APPVERSTWO_H

//Extra Libs
#include <string>

//Must Include:
#include "App.h"
extern std::string appTitle;    // Title
extern std::string appDesc;     // Description
extern std::string appPub;      // Publisher
extern std::string appOthInfo;  // Other Info
extern float appVersion;        // Version
extern int appDatePub;          // Unix Timestamp
extern std::string appHash;     // More Unique Identifier

// Settings:
extern bool systemDisplayUpdates;

// Needed if using systemDisplayUpdates is false
extern bool inTransition;
extern bool pauseRender;

// Old Button Stuff, Hopefully gets retired soon
extern bool watchSwipe;
extern bool otherSwipe;
//extern bool tap;

// Device Customization Settings [Optional]
extern uint16_t deviceMainColorTheme;
extern uint16_t deviceSecondColorTheme;
extern uint16_t deviceThirdColorTheme;
extern UWORD* BlackImage;

class appVersTwo : public App {
public:
  void sysConfig() override {                    // Triggers randomly when device needs info
    std::list<std::string> appPermissions = {};  //Permissions app needs in order to warn user about apps
    systemDisplayUpdates = false;                // Allow System to handle screen Refresh [Default: false]
    // ...

    appTitle = "Test App";                                 // Title
    appDesc = "Testing Reasons";                           // Description
    appPub = "Kaiyo";                                      // Publisher
    appOthInfo = "Website: kaiyo.dev";                     // Other Info
    appVersion = 1.1;                                      // Version
    appDatePub = 1716054259;                               // Unix Timestamp
    appHash = "6017612eb90d5b39b27a12e756a61be852541e8e";  // More Unique Identifier (SHA1)
  }

  void launch() override {  // Triggers upon first time opening app
    bool tap = false;       //local var test
    // ...
  }

  void update() override {  // Triggers on each frame
    Paint_DrawRectangle(0, 0, 100, 100, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);

    renderSnack();                                        //If using snackBar
    if (inTransition == false && pauseRender == false) {  // Only needed if systemUpdates is True
      LCD_1IN28_DisplayWindows(0, 0, 240, 240, BlackImage);
    }
  }
};

#endif
