#ifndef settings_H
#define settings_H
extern int scrollY;
extern bool inTransition;
extern bool pauseRender;
extern bool batSaver;
extern bool tap;
extern int tapHeld;
extern bool startup;
extern std::string weatherTemp;
extern std::string weatherDesc;
extern uint16_t deviceMainColorTheme;
extern uint16_t deviceSecondColorTheme;
extern uint16_t deviceThirdColorTheme;
extern int CurTime;
extern UWORD *BlackImage;
extern const char *message;
extern std::list<std::string> backgroundApps;
extern bool aod;
extern bool BLEconnected;

struct Option {
  std::string name;
  std::string value;
};

extern std::list<Option> optionsList;

bool swipe(std::string dir, int thresh);
void openApp(std::string app, std::string dir, int start);
void sendText(const char *text);
void resetFunc();
void runNextService();
void runAllServices();
std::string internet_get(std::string url);
bool button(int x, int y, const char *text, sFONT *Font, UWORD Color_Foreground, UWORD Color_Background, int size);
#endif

uint16_t rgb_to_uint16(uint8_t r, uint8_t g, uint8_t b) {
  // Ensure values are within 0-255 range
  r = min(max(r, 0), 255);
  g = min(max(g, 0), 255);
  b = min(max(b, 0), 255);

  // Convert RGB to uint16_t value
  uint16_t uint16_value = ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);

  return uint16_value;
}

void uint16_to_rgb(uint16_t color, uint8_t &r, uint8_t &g, uint8_t &b) {
  // Extract red, green, and blue components
  r = (color >> 8) & 0xF8;  // Red component: bits 11-15
  g = (color >> 3) & 0xFC;  // Green component: bits 5-10
  b = (color << 3) & 0xF8;  // Blue component: bits 0-4
}

std::list<Option> optionsList = {
  { "Network", "network" },
  { "Display", "display" },
  { "Battery", "battery" },
  { "Time", "set_time" },
  { "Customize", "customization" },
  { "System", "system" }
};

std::string page = "";

int yp = 0;

uint8_t r = 0;
uint8_t g = 0;
uint8_t b = 0;

int valueChanging = 0;

std::string latest = "";
std::string textT = "Check VERS";

void settings() {
  if (startup) {
    scrollY = 1;
    startup = false;
    page = "";
    scrollFunction(5, {}, true);
    LCD_1IN28_DisplayWindows(180, 0, 240, 240, BlackImage);
  }
  if (page == "") {
    scrollFunction(5, {}, true);
    yp = 50 + (-scrollY);

    int index = 0;
    for (const auto &option : optionsList) {
      if (button(10, yp + (50 * index), option.name.c_str(), &Font20, DARKGRAY, WHITE, 1)) {
        page = option.value;
        scrollY = 0;
        break;
      };
      //Paint_DrawRectangle(10, yp + (40 * index), 180, yp + 30 + (40 * index), DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
      //Paint_DrawString_EN(20, yp + 5 + (40 * index), option.name.c_str(), &Font20, DARKGRAY, WHITE);
      ++index;
    }

    /*
    if (inTransition == false && watchSwipe == false && otherSwipe == false && tap == true && tapHeld == 1) {
      if (Touch_CTS816.x_point >= 10 && Touch_CTS816.x_point < 180) {
        index = 0;
        for (const auto &option : optionsList) {
          if (Touch_CTS816.y_point >= yp + (40 * index) && Touch_CTS816.y_point < yp + 30 + (40 * index)) {
            page = option.value;
            scrollY = 0;
            break;
          }
          ++index;
        }
      }
    }
    */
  } else if (page == "network") {
    yp = 45;
    //Paint_DrawRectangle(10, yp, 180, yp + 30, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    //Paint_DrawString_EN(20, yp + 5, "Disconnect", &Font20, DARKGRAY, WHITE);
    //if (inTransition == false && watchSwipe == false && otherSwipe == false && tap == true && tapHeld == 1) {
    //  if (Touch_CTS816.x_point >= 10 && Touch_CTS816.x_point < 180) {
    //    if (Touch_CTS816.y_point >= yp && Touch_CTS816.y_point < yp + 30) {
    if(BLEconnected){
      Paint_DrawString_EN(25, yp, "Connected", &Font12, BLACK, GREEN);
      if (button(10, yp+15, "Disconnect", &Font20, DARKGRAY, RED, 1)) {
        //Paint_DrawRectangle(10, yp, 180, yp + 30, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        //Paint_DrawString_EN(20, yp + 5, "Disconnecting", &Font20, DARKGRAY, WHITE);
        button(10, yp+15, "Disconnected", &Font20, DARKGRAY, RED, 1);
        LCD_1IN28_DisplayWindows(10, yp+15, 180, yp+65, BlackImage);
        std::string test = "disconnect";
        message = test.c_str();
        sendText(message);
        BLEconnected = false;
        //Paint_DrawRectangle(10, yp, 180, yp + 30, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        //Paint_DrawString_EN(20, yp + 5, "Disconnect", &Font20, DARKGRAY, WHITE);
        button(10, yp+15, "Disconnect", &Font20, DARKGRAY, RED, 1);
        //}
        //}
      }
    } else{
      Paint_DrawString_EN(25, yp, "Disconnected", &Font12, BLACK, RED);
      Paint_DrawString_EN(15, yp+15, "Listening...", &Font16, BLACK, WHITE);
    }

  } else if (page == "display") {
    yp = 45;
    if (button(10, yp, (aod ? "AOD: On" : "AOD: Off"), &Font20, DARKGRAY, WHITE, 1)) {
      aod = !aod;
    }
  } else if (page == "set_time") {
    openApp("Set Time", "", 0);
  } else if (page == "customization") {
    int shift = 60;
    yp = 45;
    if (valueChanging != 0) {
      Paint_DrawRectangle(0, 0, 240, 240, rgb_to_uint16(r, g, b), DOT_PIXEL_1X1, DRAW_FILL_FULL);

      Paint_DrawRectangle(shift, yp, shift + 37, yp + 30, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
      Paint_DrawString_EN(shift + 10, yp + 5, "+", &Font24, DARKGRAY, WHITE);

      Paint_DrawRectangle(shift + 90, yp, shift + 90 + 37, yp + 30, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
      Paint_DrawString_EN(shift + 100, yp + 5, "-", &Font24, DARKGRAY, WHITE);

      Paint_DrawRectangle(shift, yp + 40, shift + 37, yp + 70, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
      Paint_DrawString_EN(shift + 10, yp + 45, "+", &Font24, DARKGRAY, WHITE);

      Paint_DrawRectangle(shift + 90, yp + 40, shift + 90 + 37, yp + 70, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
      Paint_DrawString_EN(shift + 100, yp + 45, "-", &Font24, DARKGRAY, WHITE);

      Paint_DrawRectangle(shift, yp + 80, shift + 37, yp + 110, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
      Paint_DrawString_EN(shift + 10, yp + 85, "+", &Font24, DARKGRAY, WHITE);

      Paint_DrawRectangle(shift + 90, yp + 80, shift + 90 + 37, yp + 110, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
      Paint_DrawString_EN(shift + 100, yp + 85, "-", &Font24, DARKGRAY, WHITE);

      Paint_DrawRectangle(0, 190, shift + 180, 220, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
      Paint_DrawString_EN(shift + 30, 195, "Save", &Font20, DARKGRAY, WHITE);

      //Paint_DrawString_EN(shift + 40, 180, ("R: " + std::to_string(r)).c_str(), &Font12, BLACK, GREEN);
      //Paint_DrawString_EN(shift + 40, 200, ("G: " + std::to_string(g)).c_str(), &Font12, BLACK, GREEN);
      //Paint_DrawString_EN(shift + 40, 220, ("B: " + std::to_string(b)).c_str(), &Font12, BLACK, GREEN);

      // Handle button taps
      if (inTransition == false && watchSwipe == false && otherSwipe == false && tap == true) {
        if (Touch_CTS816.x_point >= shift && Touch_CTS816.x_point < shift + 37) {
          if (Touch_CTS816.y_point >= yp && Touch_CTS816.y_point < yp + 30) {
            // Increase R button tapped
            r = std::min(r + 20, 255);  // Increase R value, ensuring it stays within 0-255 range
          } else if (Touch_CTS816.y_point >= yp + 40 && Touch_CTS816.y_point < yp + 70) {
            // Increase G button tapped
            g = std::min(g + 20, 255);  // Increase G value, ensuring it stays within 0-255 range
          } else if (Touch_CTS816.y_point >= yp + 80 && Touch_CTS816.y_point < yp + 110) {
            // Increase B button tapped
            b = std::min(b + 20, 255);  // Increase B value, ensuring it stays within 0-255 range
          } else if (Touch_CTS816.y_point >= 190 && Touch_CTS816.y_point < 220) {
            // Save button tapped
            // Add code here to save the changes
          }
        } else if (Touch_CTS816.x_point >= shift + 90 && Touch_CTS816.x_point < shift + 90 + 37) {
          if (Touch_CTS816.y_point >= yp && Touch_CTS816.y_point < yp + 30) {
            // Decrease R button tapped
            r = std::max(r - 20, 0);  // Decrease R value, ensuring it stays within 0-255 range
          } else if (Touch_CTS816.y_point >= yp + 40 && Touch_CTS816.y_point < yp + 70) {
            // Decrease G button tapped
            g = std::max(g - 20, 0);  // Decrease G value, ensuring it stays within 0-255 range
          } else if (Touch_CTS816.y_point >= yp + 80 && Touch_CTS816.y_point < yp + 110) {
            // Decrease B button tapped
            b = std::max(b - 20, 0);  // Decrease B value, ensuring it stays within 0-255 range
          }
        } else if (Touch_CTS816.x_point >= 0 && Touch_CTS816.x_point < 240 && Touch_CTS816.y_point >= 190 && Touch_CTS816.y_point < 220) {
          if (valueChanging == 1) {
            deviceMainColorTheme = rgb_to_uint16(r, g, b);
          } else if (valueChanging == 2) {
            deviceSecondColorTheme = rgb_to_uint16(r, g, b);
          } else if (valueChanging == 3) {
            deviceThirdColorTheme = rgb_to_uint16(r, g, b);
          }
          valueChanging = 0;
        }
      }
    } else {
      Paint_DrawString_EN(15, yp + 50, ("Main Color: " + std::to_string(deviceMainColorTheme)).c_str(), &Font12, BLACK, deviceMainColorTheme);
      Paint_DrawString_EN(15, yp + 50 + 60, ("Second Color: " + std::to_string(deviceSecondColorTheme)).c_str(), &Font12, BLACK, deviceSecondColorTheme);
      Paint_DrawString_EN(15, yp + 50 + 120, ("Third Color: " + std::to_string(deviceThirdColorTheme)).c_str(), &Font12, BLACK, deviceThirdColorTheme);

      if (button(10, yp, "Change Main Color", &Font12, DARKGRAY, WHITE, 1)) {
        valueChanging = 1;
        tap=false;
        delay(6);
        uint16_to_rgb(deviceMainColorTheme, r, g, b);
      }

      if (button(10, yp + 62, "Change Second Color", &Font12, DARKGRAY, WHITE, 1)) {
        valueChanging = 2;
        tap=false;
        delay(6);
        uint16_to_rgb(deviceSecondColorTheme, r, g, b);
      }

      if (button(10, yp + 124, "Change Third Color", &Font12, DARKGRAY, WHITE, 1)) {
        valueChanging = 3;
        tap=false;
        delay(6);
        uint16_to_rgb(deviceThirdColorTheme, r, g, b);
      }
    }
  } else if (page == "battery") {
    yp = 45;
    if (button(10, yp, (batSaver ? "BATSAV: On" : "BATSAV: Off"), &Font20, DARKGRAY, WHITE, 1)) {
      batSaver = !batSaver;
    }
    Paint_DrawString_EN(25, yp + 50, "Battery Saver turns", &Font12, BLACK, WHITE);
    Paint_DrawString_EN(25, yp + 50 + 13, "off AOD and limits", &Font12, BLACK, WHITE);
    Paint_DrawString_EN(25, yp + 50 + 13 + 13, "peak clock speed.", &Font12, BLACK, WHITE);
  } else if (page == "system") {
    yp = 45;
    if (latest == "") {
      textT = "Check VERS";
      //Paint_DrawString_EN(20, yp + 5, "Check VERS", &Font20, DARKGRAY, WHITE);
    } else {
      textT = latest;
      //Paint_DrawString_EN(20, yp + 5, latest.c_str(), &Font20, DARKGRAY, WHITE);
    }

    if (button(10, yp + 50, "Run ALL-SRV", &Font20, DARKGRAY, WHITE, 1)) {
      runAllServices();
    }

    if (button(10, yp + 50 + 50, "Restart", &Font20, DARKGRAY, WHITE, 1)) {
      resetFunc();
    }

    if (button(10, yp, textT.c_str(), &Font20, DARKGRAY, WHITE, 1)) {
      //Paint_DrawString_EN(20, yp + 5, "Checking...", &Font20, DARKGRAY, WHITE);
      button(10, yp, "Checking...", &Font20, DARKGRAY, WHITE, 1);
      LCD_1IN28_DisplayWindows(10, yp, 180, yp + 45, BlackImage);
      //Paint_DrawRectangle(10, yp, 180, yp + 30, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
      latest = internet_get("watch");
      std::string textT = latest;
      button(10, yp, textT.c_str(), &Font20, DARKGRAY, WHITE, 1);
      //Paint_DrawString_EN(20, yp + 5, latest.c_str(), &Font20, DARKGRAY, WHITE);
      tap = false;
      tapHeld = 0;
    }
  }



  if (inTransition == false) {
    if (swipe("right", 70)) {
      page = "";
    }
    if (pauseRender == false) {
      if (page == "customization") {  // && valueChanging != 0
        LCD_1IN28_DisplayWindows(0, 0, 240, 240, BlackImage);
      } else {
        LCD_1IN28_DisplayWindows(0, 0, 180, 240, BlackImage);
      }
    }

    //Recommeneded to Open any asked apps After rendering existing scene to prevent double render black bar
    //if(swipe("down",70)){ //example swipe action, (70 is how far away the tap needs to be before it is registered as Complete)
    //  openApp("main", "UD", Touch_CTS816.y_point);
    //}
  }
}