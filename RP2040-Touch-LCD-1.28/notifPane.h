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
std::list<std::list<std::string>> notifications = {
  { "Title", "App", "Content", "AppSpecificData", std::to_string(millis()) },  //(Thee last value is the Time Stamp)
  { "Contact1", "Messages", "SomeContent", "Number", std::to_string(millis()) },
  { "Contact2", "Messages", "CONTENT2", "Number", std::to_string(millis()) },
};
std::list<std::list<std::string>> uniqueNotifications;
std::set<std::string> uniqueTitles;

extern int scrollY;
extern int hoverObject;

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
    return std::to_string(diff / 1000) + "s ago";  // Seconds
  } else if (diff < milliseconds_in_hour) {
    return std::to_string(diff / milliseconds_in_minute) + "min ago";  // Minutes
  } else if (diff < milliseconds_in_day) {
    return std::to_string(diff / milliseconds_in_hour) + "h ago";  // Hours
  } else {
    return std::to_string(diff / milliseconds_in_day) + "d ago";  // Days
  }
}

void notifPane() {
  if (startup) {
    startup = false;
    scrollY = 0;
    LCD_1IN28_DisplayWindows(180, 0, 240, 240, BlackImage);
  }

  result = DEC_ADC_Read() * (3.3f / (1 << 12) * 2);
  float adjustedResult = std::min(result, 3.11f);

  int notifX = 20;
  int notifY = 180;      // Start from bottom and move up
  int notifHeight = 50;  // Adjusted for larger content area
  int spacing = 10;
  int index = 0;

  uniqueNotifications.clear();
  uniqueTitles.clear();
  for (const auto &notification : notifications) {
    auto title = notification.front();
    if (uniqueTitles.find(title) == uniqueTitles.end()) {
      uniqueTitles.insert(title);
      uniqueNotifications.push_back(notification);
    }
  }

  int number = uniqueNotifications.size();
  scrollFunctionFull(number, {}, true);

  for (const auto &notification : uniqueNotifications) {
    int adjustedY = notifY - (index * (notifHeight + spacing)) + scrollY;

    if (!oneTickPause && adjustedY > 0 && adjustedY < 240 - notifHeight) {
      // Drawing the rounded rectangle (reusing from appsPanel)
      Paint_DrawRectangle(notifX, adjustedY, notifX + 220, adjustedY + notifHeight, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);

      // Draw the app icon placeholder (red rectangle)
      Paint_DrawRectangle(notifX - 25, adjustedY - 25, notifX + 25, adjustedY + 25, RED, DOT_PIXEL_1X1, DRAW_FILL_FULL);

      // Draw the app name on the top left
      Paint_DrawString_EN(notifX + 30, adjustedY + 5, (*std::next(notification.begin(), 1)).c_str(), &Font16, DARKGRAY, WHITE);

      // Draw the message title below the app name
      Paint_DrawString_EN(notifX + 30, adjustedY + 20, (*std::next(notification.begin(), 0)).c_str(), &Font20, DARKGRAY, WHITE);

      // Draw the timestamp on the top right
      std::string timeAgo = calculateTimeAgo(*std::prev(notification.end()));  // You’ll need to implement this function
      Paint_DrawString_EN(notifX + 150, adjustedY + 5, timeAgo.c_str(), &Font12, DARKGRAY, WHITE);

      if (tap && !watchSwipe && !otherSwipe && runningAppName == "notifPane") {
        if (Touch_CTS816.x_point >= notifX && Touch_CTS816.x_point <= notifX + 220 && Touch_CTS816.y_point >= adjustedY && Touch_CTS816.y_point <= adjustedY + notifHeight) {
          tappedNotif = index;
          oneTickPause = true;
          notifHeight = -45;
          auto it = apps.find(*std::next(notification.begin(), 1));  // Open the app associated with the notification
          if (it != apps.end()) {
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
      LCD_1IN28_DisplayWindows(notifX - 1, 0, 240, 240, BlackImage);
    }
  }
}
