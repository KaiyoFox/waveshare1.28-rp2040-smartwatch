#include <string>
#ifndef notifPane_H
#define notifPane_H
extern bool inTransition;
extern bool pauseRender;
extern bool tap;
extern bool startup;
extern bool otherSwipe;
extern bool watchSwipe;
extern std::string runningAppName;
extern int tapHeld;
extern bool oneTickPause;
extern UWORD *BlackImage;
typedef void (*AppPtr)();
extern std::map<std::string, AppPtr> apps;
extern std::list<float> batVoltages;
extern std::string appIn;
bool swipe(std::string dir, int thresh);
void openApp(std::string app, std::string dir, int start);
std::list<int> scrollFunctionFull(int numberOfItems, std::string itemHeaders[], bool visible);
#endif
#include <cstring>
#include <sstream>
#include <list>
#include <set>
#include <algorithm>

float result;
int tappedNotif = -1;

std::list<std::list<std::string>> uniqueNotifications;
std::set<std::string> uniqueTitles;

extern int scrollY;
extern int hoverObject;
extern bool scrolling;
extern std::list<std::list<std::string>> notifications;

std::string calculateTimeAgo(const std::string &timestampStr) {
  // Convert timestamp from string to integer milliseconds
  long long timestamp = std::stoll(timestampStr);

  // Get current time in milliseconds
  auto now = std::chrono::system_clock::now();
  auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
  long long now_time = now_ms.time_since_epoch().count();

  // Calculate time difference
  long long diff = now_time - timestamp;

  // Convert milliseconds to minutes, hours, days
  const long long milliseconds_in_minute = 60 * 1000;
  const long long milliseconds_in_hour = 60 * milliseconds_in_minute;
  const long long milliseconds_in_day = 24 * milliseconds_in_hour;

  if (diff < milliseconds_in_minute) {
    return std::to_string(diff / 1000) + "s";  // Seconds
  } else if (diff < milliseconds_in_hour) {
    return std::to_string(diff / milliseconds_in_minute) + "m";  // Minutes
  } else if (diff < milliseconds_in_day) {
    return std::to_string(diff / milliseconds_in_hour) + "h";  // Hours
  } else {
    return std::to_string(diff / milliseconds_in_day) + "d";  // Days
  }
}

void notifPane() {
  int notifX = 20;
  int notifY = 50;       // Start from bottom and move up
  int notifHeight = 56;  // Adjusted for larger content area
  int spacing = 10;
  int index = 0;

  int number = notifications.size();

  if (startup) {
    startup = false;
    scrollY = -((number * (notifHeight + spacing)) - 2.2 * (notifHeight + spacing));
    LCD_1IN28_DisplayWindows(notifX - 1, 0, notifX + 200, 240, BlackImage);
  }

  result = DEC_ADC_Read() * (3.3f / (1 << 12) * 2);
  float adjustedResult = std::min(result, 3.11f);

  scrollFunctionFull(number, {}, true);

  for (const auto &notification : notifications) {
    int adjustedY = notifY - (-index * (notifHeight + spacing)) + scrollY;

    if (!oneTickPause && adjustedY + notifHeight > 0 && adjustedY < 240) {
      // Drawing the rounded rectangle (reusing from appsPanel)
      //Paint_DrawRectangle(notifX, adjustedY, notifX + 220, adjustedY + notifHeight, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);

      int x = notifX;
      int y = adjustedY;
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


      // Draw the app icon placeholder (red rectangle)
      Paint_DrawRectangle(notifX - 25, adjustedY - 25, notifX + 25, adjustedY + 25, RED, DOT_PIXEL_1X1, DRAW_FILL_FULL);

      // Draw the app name on the top left
      Paint_DrawString_EN(notifX + 30, adjustedY + 5, (*std::next(notification.begin(), 1)).c_str(), &Font16, DARKGRAY, WHITE);

      // Draw the message title below the app name
      Paint_DrawString_EN(notifX + 30, adjustedY + 20, (*std::next(notification.begin(), 0)).c_str(), &Font20, DARKGRAY, WHITE);

      // Draw the timestamp on the top right
      std::string timeAgo = calculateTimeAgo(*std::prev(notification.end()));  // You’ll need to implement this function
      Paint_DrawString_EN(notifX + 150, adjustedY + 5, timeAgo.c_str(), &Font12, DARKGRAY, WHITE);

      if (tap && !watchSwipe && !otherSwipe && !scrolling && runningAppName == "notifPane") {
        if (Touch_CTS816.x_point >= notifX && Touch_CTS816.x_point <= notifX + 194 && Touch_CTS816.y_point >= adjustedY && Touch_CTS816.y_point <= adjustedY + notifHeight) {
          tappedNotif = index;
          oneTickPause = true;
          notifHeight = -45;
          auto it = apps.find(*std::next(notification.begin(), 1));  // Open the app associated with the notification
          if (it != apps.end()) {
            std::string itIn = *std::next(notification.begin(), 3);
            appIn=itIn;
            openApp(it->first, "RL", 240);
          } else {
            openApp("previewNotif", "RL", 240);
          }
        }
      }
    }
    index++;
  }

  // Draw the "Clear All" button at the top after scrolling up
  if (true) {  //if viisable
    Paint_DrawRectangle(83, scrollY + 10, 156, scrollY + 42, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawString_EN(90, scrollY + 19, "Clear All", &Font16, GRAY, RED);

    if (tap && !watchSwipe && !otherSwipe) {
      if (Touch_CTS816.x_point >= 83 && Touch_CTS816.x_point <= 156 && Touch_CTS816.y_point >= scrollY + 10 && Touch_CTS816.y_point <= scrollY + 42) {
        notifications.clear();
        uniqueNotifications.clear();
        uniqueTitles.clear();
        openApp("main", "UD", 0);
      }
    }
  }

  renderSnack();
  if (!inTransition) {
    if (swipe("up", 190)) {
      openApp("main", "DU", Touch_CTS816.y_point);
    }
    if (!pauseRender && !oneTickPause) {
      LCD_1IN28_DisplayWindows(notifX - 1, 0, notifX + 200, 240, BlackImage);
    }
  }
}
