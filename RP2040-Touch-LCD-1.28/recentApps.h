#include <algorithm>
#include <cstring>
#include <vector>
#include <numeric>
#include <map>
#include <list>

#ifndef recentApps_H
#define recentApps_H

extern bool inTransition;
extern bool pauseRender;
extern bool tap;
extern bool otherSwipe;
extern bool watchSwipe;
extern bool startup;
extern int tapHeld;
extern std::string lastUsedAppName;
extern std::list<std::string> backgroundApps;
extern int scrollY;
extern UWORD* BlackImage;
extern std::list<std::string> systemApps;
typedef void (*AppPtr)();
extern std::map<std::string, AppPtr> apps;

bool swipe(std::string dir, int thresh);
void openApp(std::string app, std::string dir, int start);
bool button(int x, int y, std::string text);
uint16_t findTextColor(const std::string& text);

#endif

int totalHeightRecents = 0;
bool recentAppTappedOn = false;

void recentApps() {
  if (startup) {
    openingAnApp = false;
    scrollY = 5;

    if (totalHeightRecents == -1) {
      std::vector<int> itemHeightsRecents;
      totalHeightRecents = 0;
      for (auto const& key : backgroundApps) {
        if (std::find(systemApps.begin(), systemApps.end(), key) == systemApps.end()) {
          int itemHeight = appSize + spacing;
          totalHeightRecents += itemHeight;
          itemHeightsRecents.push_back(itemHeight);
        }
      }
    }
  }

  int count = 0;
  scrollFunction(visibleCount, {}, true);
  visibleCount = 0;

  int scrollYModded = (scrollY / 240.0) * (totalHeightRecents + 20);
  int startIndex = std::max(0, (scrollYModded / (appSize + spacing)) - visibleApps);

  for (auto it = std::next(backgroundApps.begin(), startIndex); it != backgroundApps.end(); ++it) {
    const std::string& key = *it;
    if (std::find(systemApps.begin(), systemApps.end(), key) == systemApps.end()) {
      int x = startX;
      int y = 20 + startY + (visibleCount + startIndex) * (appSize + spacing) - scrollYModded;
      if (y > -appSize && y < 240 && openingAnApp == false) {
        // Drawing rectangles for app design
        Paint_DrawRectangle(x + 18, y + 0, x + 123, y + 1, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        Paint_DrawRectangle(x + 12, y + 1, x + 128, y + 2, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        Paint_DrawRectangle(x + 11, y + 2, x + 129, y + 3, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        Paint_DrawRectangle(x + 9, y + 3, x + 131, y + 4, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        Paint_DrawRectangle(x + 8, y + 4, x + 132, y + 5, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        Paint_DrawRectangle(x + 7, y + 5, x + 133, y + 6, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        Paint_DrawRectangle(x + 7, y + 6, x + 134, y + 7, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        Paint_DrawRectangle(x + 6, y + 7, x + 135, y + 8, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        Paint_DrawRectangle(x + 5, y + 8, x + 136, y + 9, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        Paint_DrawRectangle(x + 5, y + 9, x + 136, y + 10, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        Paint_DrawRectangle(x + 4, y + 10, x + 137, y + 11, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        Paint_DrawRectangle(x + 4, y + 11, x + 137, y + 12, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        Paint_DrawRectangle(x + 4, y + 12, x + 138, y + 13, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        Paint_DrawRectangle(x + 3, y + 13, x + 138, y + 14, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        Paint_DrawRectangle(x + 2, y + 14, x + 138, y + 15, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        Paint_DrawRectangle(x + 2, y + 15, x + 139, y + 16, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        Paint_DrawRectangle(x + 2, y + 16, x + 139, y + 17, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        Paint_DrawRectangle(x + 2, y + 17, x + 139, y + 18, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        Paint_DrawRectangle(x + 2, y + 18, x + 139, y + 19, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        Paint_DrawRectangle(x + 1, y + 19, x + 139, y + 20, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        Paint_DrawRectangle(x + 1, y + 20, x + 139, y + 21, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        Paint_DrawRectangle(x + 1, y + 21, x + 139, y + 22, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        Paint_DrawRectangle(x + 1, y + 22, x + 139, y + 23, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        Paint_DrawRectangle(x + 2, y + 23, x + 139, y + 24, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        Paint_DrawRectangle(x + 2, y + 24, x + 139, y + 25, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        Paint_DrawRectangle(x + 2, y + 25, x + 139, y + 26, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        Paint_DrawRectangle(x + 2, y + 26, x + 139, y + 27, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        Paint_DrawRectangle(x + 2, y + 27, x + 139, y + 28, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        Paint_DrawRectangle(x + 2, y + 28, x + 139, y + 29, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        Paint_DrawRectangle(x + 3, y + 29, x + 138, y + 30, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        Paint_DrawRectangle(x + 3, y + 30, x + 138, y + 31, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        Paint_DrawRectangle(x + 3, y + 31, x + 138, y + 32, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        Paint_DrawRectangle(x + 4, y + 32, x + 137, y + 33, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        Paint_DrawRectangle(x + 4, y + 33, x + 137, y + 34, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        Paint_DrawRectangle(x + 5, y + 34, x + 136, y + 35, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        Paint_DrawRectangle(x + 5, y + 35, x + 136, y + 36, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        Paint_DrawRectangle(x + 6, y + 36, x + 135, y + 37, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        Paint_DrawRectangle(x + 7, y + 37, x + 134, y + 38, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        Paint_DrawRectangle(x + 8, y + 38, x + 133, y + 39, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        Paint_DrawRectangle(x + 9, y + 39, x + 132, y + 40, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        Paint_DrawRectangle(x + 11, y + 40, x + 131, y + 41, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        Paint_DrawRectangle(x + 11, y + 41, x + 130, y + 42, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        Paint_DrawRectangle(x + 13, y + 42, x + 128, y + 43, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        Paint_DrawRectangle(x + 15, y + 43, x + 127, y + 44, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);

        Paint_DrawString_EN(startX + 5, y + ((appSize / 2) - 8), key.c_str(), &Font16, DARKGRAY, findTextColor(key.c_str()));

        if (inTransition == false && !pauseRender) {
          if (Touch_CTS816.x_point >= x && Touch_CTS816.x_point <= x + appLeng && Touch_CTS816.y_point >= y && Touch_CTS816.y_point <= y + appSize) {
            if (tap && !watchSwipe && !otherSwipe) {
              if (tapHeld <= 1) {
                tap = false;
                tapHeld = 999;
                openApp(key, "", 0);
                tap = false;
                recentAppTappedOn = true;
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

  if (!recentAppTappedOn) {
    Paint_DrawRectangle(83, 190, 156, 222, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawString_EN(90, 199, "Clear", &Font16, GRAY, RED);  //63 char in length
    if (tap) {
      if (watchSwipe == false && otherSwipe == false) {
        if (Touch_CTS816.x_point >= 83 && Touch_CTS816.x_point <= 156 && Touch_CTS816.y_point >= 190 && Touch_CTS816.y_point <= 222) {  //broken currently. I think its the openApp afterwards.
          backgroundApps.clear();
          openApp("main", "DU", 240);
        }
      }
    }
  }

  if (inTransition == false) {
    if (swipe("down", 70)) {
      openApp(lastUsedAppName, "UD", Touch_CTS816.y_point);
    }
    if (pauseRender == false && recentAppTappedOn == false) {
      LCD_1IN28_DisplayWindows(startX - 2, 0, 180, 240, BlackImage);
    }
  }
}
