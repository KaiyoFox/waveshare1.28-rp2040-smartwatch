#include <algorithm>
#include <cstring>
#include <vector>   // Include the vector library
#include <numeric>  // Include the numeric library
#ifndef appsPanel_H
#define appsPanel_H
extern bool inTransition;
extern bool pauseRender;
extern bool tap;
extern bool otherSwipe;
extern bool watchSwipe;
extern bool startup;
extern int tapHeld;
extern int scrollY;  // Added scrollY variable
extern UWORD* BlackImage;
extern std::list<std::string> systemApps;
typedef void (*AppPtr)();
extern std::map<std::string, AppPtr> apps;
bool swipe(std::string dir, int thresh);
void openApp(std::string app, std::string dir, int start);
bool button(int x, int y, std::string text);
uint16_t findTextColor(const std::string& text);
#endif

int appSize = 45;     //35 Adjust as needed
int appLeng = 140;    //140
int startX = 25;      // Adjust as needed
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
      std::vector<int> itemHeights;
      totalHeight = 0;
      for (auto const& [key, val] : apps) {
        if (std::find(systemApps.begin(), systemApps.end(), key) == systemApps.end()) {
          int itemHeight = appSize + spacing;  // Adjust as needed
          totalHeight += itemHeight;
          itemHeights.push_back(itemHeight);
        }
      }
    }
  }
  //appPanelAppCalled = false;
  //Paint_DrawRectangle(50, 0, 190, 240, 0x39E7, DOT_PIXEL_1X1, DRAW_FILL_FULL);

  int count = 0;
  scrollFunction(visibleCount, {}, true);
  visibleCount = 0;  // Track the number of visible apps
  //scrollFunction(apps.size(),{},true);//WARNINGGGGGGGGGGGGGGGGGGGGGG APPS CONTAINS THE HIDDEN APPS< AND MAY BREAK

  //int totalHeight = std::accumulate(itemHeights.begin(), itemHeights.end(), 0);

  // Determine the modified scrollY value
  int scrollYModded = (scrollY / 240.0) * (totalHeight + 20);  // + (itemHeights.size() * spacing)

  // Determine the starting index based on scroll position
  int startIndex = std::max(0, (scrollYModded / (appSize + spacing)) - visibleApps);

  // Render apps in a list, starting from the calculated start index
  for (auto it = std::next(apps.begin(), startIndex); it != apps.end(); ++it) {
    const std::string& key = it->first;
    if (std::find(systemApps.begin(), systemApps.end(), key) == systemApps.end()) {
      int x = startX;
      int y = 20 + startY + (visibleCount + startIndex) * (appSize + spacing) - scrollYModded;
      if (y > -appSize && y < 240 && openingAnApp == false) {
        //Paint_DrawRectangle(x + 3, max(0, min(240, y)), x + appLeng - 3, max(0, min(240, y + appSize)), findTextColor(key.c_str()), DOT_PIXEL_1X1, DRAW_FILL_FULL);

        //Paint_DrawRectangle(x, max(0, min(240, y + 3)), x + 4, max(0, min(240, y + appSize - 3)), findTextColor(key.c_str()), DOT_PIXEL_1X1, DRAW_FILL_FULL);

        //Paint_DrawRectangle(x + appLeng, max(0, min(240, y + 3)), x + appLeng - 4, max(0, min(240, y + appSize - 3)), findTextColor(key.c_str()), DOT_PIXEL_1X1, DRAW_FILL_FULL);


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


        //was font 16


        //y + appSize - (16 + 5)
        //startX + 5
        Paint_DrawString_EN(startX + 5, y + ((appSize / 2) - 8), key.c_str(), &Font16, DARKGRAY, findTextColor(key.c_str()));  //(x + appLeng) - (std::strlen(key.c_str())*11) - 1,font8 0x009688
        if (inTransition == false && !pauseRender) {
          if (Touch_CTS816.x_point >= x && Touch_CTS816.x_point <= x + appLeng && Touch_CTS816.y_point >= y && Touch_CTS816.y_point <= y + appSize) {
            if (tap && !watchSwipe && !otherSwipe) {
              if (tapHeld <= 1) {  //tapHeld > 1
                tap = false;
                tapHeld = 999;
                //appPanelAppCalled=true;
                openApp(key, "", 0);  //RAND
                tap = false;
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

  ///Paint_DrawEdgeEffect(); /too laggy

  //scrollFunction(visibleCount, {}, true);

  if (inTransition == false) {
    if (pauseRender == false && openingAnApp == false) {
      //LCD_1IN28_DisplayWindows(startX - 2, 0, 180, 240, BlackImage);
      LCD_1IN28_DisplayWindows(startX - 2, 0, 240, 240, BlackImage);
      //LCD_1IN28_Display(BlackImage);
    }

    // Recommended to Open any asked apps After rendering existing scene to prevent double render black bar
    //if(swipe("right",70)){
    //    openApp("main", "LR", Touch_CTS816.x_point);
    //}
    //if(Touch_CTS816.y_point > 210 && tapHeld > 5 && inTransition==false){
    //    openApp("recentApps", "UD", Touch_CTS816.y_point);
    //}
  }
}
