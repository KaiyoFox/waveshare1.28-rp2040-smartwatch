#include <algorithm>
#include <cstring>
#include <vector>   // Include the vector library
#include <numeric>  // Include the numeric library
#ifndef appsPanel_H
#define appsPanel_H
extern bool inTransition;
extern bool pauseRender;
extern bool tap;
extern bool sysTap;
extern bool otherSwipe;
extern bool watchSwipe;
extern bool startup;
extern bool scrolling;
extern int tapHeld;
extern int scrollY;  // Added scrollY variable
extern UWORD* BlackImage;
extern std::string lastUsedAppName;
extern std::string appOut;
extern std::list<std::string> systemApps;
typedef void (*AppPtr)();
extern std::map<std::string, AppPtr> apps;
bool swipe(std::string dir, int thresh);
void openApp(std::string app, std::string dir, int start);
bool button(int x, int y, std::string text);
uint16_t findTextColor(const std::string& text);
#endif

int appSize = 60;     //45;     //35 Adjust as needed
int appLeng = 192;    //140
int startX = 23;      // for old 25;      // Adjust as needed
int startY = 35;      // Adjust as needed
int spacing = 5;      //10  Adjust as needed
int columns = 3;      // Adjust as needed
int visibleApps = 6;  // Number of visible apps in the panel
int scrollStep = 5;   // Adjust as needed, controls scrolling speed
int totalHeight = -1;
int visibleCount = 0;
//bool appPanelAppCalled = false;

bool openingAnApp = false;

void appsPanel() {
  if (startup) {
    openingAnApp = false;
    scrollY = 5;  //spacing;

    if (totalHeight == -1) {
      // Calculate the total height of items and spacing
      totalHeight = 0;
      for (auto const& [key, val] : apps) {
        if (std::find(systemApps.begin(), systemApps.end(), key) == systemApps.end()) {
          totalHeight += appSize + spacing;  // Adjust as needed
        }
      }
    }
  }

  int scrollYModded = -scrollY;
  scrollY = std::min(scrollY, totalHeight + 20);

  int startIndex = std::max(0, (scrollYModded / (appSize + spacing)) - visibleApps);

  if (lastUsedAppName == "main") {
    Paint_DrawString_EN(98, (startY + (0 * (appSize + spacing)) - scrollYModded - 5), "Apps", &Font16, BLACK, WHITE);
  } else {
    Paint_DrawString_EN(65, (startY + (0 * (appSize + spacing)) - scrollYModded - 5), "Select App", &Font16, BLACK, WHITE);
  }

  int count = 0;
  scrollFunctionFull(totalHeight / (appSize + spacing), {}, true);
  visibleCount = 0;

  for (auto it = std::next(apps.begin(), startIndex); it != apps.end(); ++it) {
    const std::string& key = it->first;
    if (std::find(systemApps.begin(), systemApps.end(), key) == systemApps.end()) {
      int x = startX;
      int y = 20 + startY + (visibleCount + startIndex) * (appSize + spacing) - scrollYModded;
      if (y > -appSize && y <= 240 && !openingAnApp) {
        Paint_DrawRectangle(x + 23, y + 1, x + 173, y + 3, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        Paint_DrawRectangle(x + 17, y + 3, x + 179, y + 5, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        Paint_DrawRectangle(x + 13, y + 5, x + 183, y + 7, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        Paint_DrawRectangle(x + 9, y + 7, x + 185, y + 9, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        Paint_DrawRectangle(x + 9, y + 9, x + 187, y + 11, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        Paint_DrawRectangle(x + 7, y + 11, x + 189, y + 13, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        Paint_DrawRectangle(x + 5, y + 13, x + 191, y + 15, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        Paint_DrawRectangle(x + 5, y + 15, x + 191, y + 17, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        Paint_DrawRectangle(x + 3, y + 17, x + 193, y + 19, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        Paint_DrawRectangle(x + 3, y + 19, x + 193, y + 21, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        Paint_DrawRectangle(x + 1, y + 21, x + 193, y + 23, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        Paint_DrawRectangle(x + 1, y + 23, x + 195, y + 25, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        Paint_DrawRectangle(x + 1, y + 25, x + 195, y + 27, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        Paint_DrawRectangle(x + 1, y + 27, x + 195, y + 29, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        Paint_DrawRectangle(x + 1, y + 29, x + 195, y + 31, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        Paint_DrawRectangle(x + 1, y + 31, x + 195, y + 33, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        Paint_DrawRectangle(x + 1, y + 33, x + 195, y + 35, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        Paint_DrawRectangle(x + 1, y + 35, x + 193, y + 37, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        Paint_DrawRectangle(x + 3, y + 37, x + 193, y + 39, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        Paint_DrawRectangle(x + 3, y + 39, x + 193, y + 41, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        Paint_DrawRectangle(x + 3, y + 41, x + 193, y + 43, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        Paint_DrawRectangle(x + 5, y + 43, x + 191, y + 45, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        Paint_DrawRectangle(x + 5, y + 45, x + 189, y + 47, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        Paint_DrawRectangle(x + 7, y + 47, x + 189, y + 49, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        Paint_DrawRectangle(x + 9, y + 49, x + 187, y + 51, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        Paint_DrawRectangle(x + 11, y + 51, x + 185, y + 53, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        Paint_DrawRectangle(x + 13, y + 53, x + 181, y + 55, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        Paint_DrawRectangle(x + 19, y + 55, x + 177, y + 57, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);

        Paint_DrawString_EN(startX + 10, y + ((appSize / 2) - 10), key.c_str(), &Font20, DARKGRAY, findTextColor(key.c_str()));

        if (inTransition == false && !pauseRender) {
          if (Touch_CTS816.x_point >= x && Touch_CTS816.x_point <= x + appLeng && Touch_CTS816.y_point >= y && Touch_CTS816.y_point <= y + appSize) {
            if (tap && !watchSwipe && !otherSwipe && !scrolling) {
              if (tapHeld <= 2) {
                tap = false;
                sysTap=false;
                tapHeld = 999;
                if (lastUsedAppName == "main") {
                  openApp(key, "", 0);
                } else {
                  appOut = key;
                  openApp(lastUsedAppName, "", 0);
                }
                tap = false;
                sysTap=false;
                openingAnApp = true;
                oneTickPause = true;
              }
            }
          }
        }
      } else if (y > 240) {
        break;
      }
      visibleCount++;
    }
  }

  renderSnack();
  if (inTransition == false) {
    if (pauseRender == false && openingAnApp == false) {
      LCD_1IN28_DisplayWindows(startX - 2, 0, startX+appLeng+4, 240, BlackImage);
    }
  }
}
