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
std::list<int> scrollFunction(int numberOfItems, std::string itemHeaders[], bool visible);
#endif
#include <cstring>
#include <sstream>
#include <list>
#include <sstream>
#include <set>
float result;
int tappedNotif = -1;

std::list<std::list<std::string>> notifications = {
  { "Title", "App", "Content", "AppSpecificData" },
  { "Contact1", "Messages", "SomeContent", "Number" },
  { "Contact2", "Messages", "CONTENT2", "Number" },
};

std::list<std::list<std::string>> uniqueNotifications;
std::set<std::string> uniqueTitles;

//float scrollV = 0;
//int scrollY = 0;
//int initalPoint = -1;
//int inittappos=-1;

extern int scrollY;
extern int hoverObject;

void notifPane() {
  if (startup) {
    startup = false;
    scrollY = 0;
    LCD_1IN28_DisplayWindows(180, 0, 240, 240, BlackImage);
    //  tappedNotif = -1;
  }
  result = DEC_ADC_Read() * (3.3f / (1 << 12) * 2);
  float adjustedResult = min(result, 3.11);
  //Paint_DrawRectangle(50, 0, 190, 240, 0x39E7, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  //Paint_DrawImage1(Bat816, 135, 20, 16, 8, GREEN);
  //Paint_DrawString_EN(153, 19, (std::to_string(min(int(((adjustedResult-2.29)/(2.4-2.25))*100),100)) + "%").c_str(), &Font12, BLACK, GREEN);

  //scrollV = scrollV / 1.5;
  //scrollY+=scrollV;
  float notifX = 20;  //was 40
  float notifY = 50;
  float notifHeight = 35;
  float index = 0;

  for (const auto &notification : notifications) {
    auto title = notification.front();
    if (uniqueTitles.find(title) == uniqueTitles.end()) {
      uniqueTitles.insert(title);
      uniqueNotifications.push_back(notification);
    }
  }


  int number = uniqueNotifications.size();
  //std::string values[number+1] = {};
  //for (int i = 0; i <= number; ++i) {
  //    values[i] = "Page " + std::to_string(i + 1);
  //}
  scrollFunction(uniqueNotifications.size(), {}, true);

  for (const auto &notification : uniqueNotifications) {
    //int adjustedY = notifY + (index - (scrollY/(240/uniqueNotifications.size()))) * (notifHeight + 10); // Adjust Y position based on scroll
    //int adjustedY = notifY + ((index-hoverObject)*(notifHeight+10));// + (240-scrollY);


    int adjustedY = notifY + ((index) * (notifHeight + 10)) - ((scrollY) / (240 / ((notifHeight + 10) * number)));
    //if (adjustedY < 180-notifHeight) {  // Check if the notification is within the visible area
    if (oneTickPause == false) {  //OLD METHOD BETTER FOR EFFICENECY              adjustedY > 0 &&
      Paint_DrawRectangle(notifX, max(0, min(180 - notifHeight, adjustedY)), (240 - notifX) - 50, max(0, min(180 - notifHeight, adjustedY + notifHeight)), 0x2121, DOT_PIXEL_1X1, DRAW_FILL_FULL);
      auto itemIter = notification.begin();
      auto lastItem = std::prev(notification.end());
      std::string openAppWith = *std::next(notification.begin(), 1);


      if (adjustedY > 0 && adjustedY < 180 - notifHeight) {
        if (openAppWith == "messages") {
          Paint_DrawString_EN(notifX + 5, (adjustedY + notifHeight / 2) - 6, lastItem->c_str(), &Font16, 0x2121, WHITE);
          Paint_DrawImage1(Msg816, ((240 - notifX) - 50) - 20, adjustedY + 10, 16, 8, WHITE);
        } else {
          Paint_DrawString_EN(notifX + 5, (adjustedY + notifHeight / 2) - 6, itemIter->c_str(), &Font16, 0x2121, WHITE);
          Paint_DrawImage1(Alarm88, ((240 - notifX) - 50) - 16, adjustedY + 10, 8, 8, WHITE);
        }
      }

      // Handle tap event
      if (tap && !watchSwipe && !otherSwipe && runningAppName == "notifPane") {
        if (Touch_CTS816.x_point >= notifX && Touch_CTS816.x_point <= 156 && Touch_CTS816.y_point >= adjustedY && Touch_CTS816.y_point <= adjustedY + notifHeight) {
          tappedNotif = index;
          oneTickPause = true;
          notifHeight = -45;
          auto it = apps.find(openAppWith);
          if (it != apps.end()) {
            //if (openAppWith == "messages") {
            //openApp("Messages", "LR", 0);
            openApp(openAppWith, "RL", 240);  //idea: Instead alawys display preiewNotif, and if there is an app for it, then add a Open In App button, and go from there, so we have notif content, and notif data (in app)
          } else {
            openApp("previewNotif", "RL", 240);
          }
        }
      }
    }

    index++;
  }
  if (notifications.size() == 0) {
    Paint_DrawString_EN(notifX + 5, (notifY + notifHeight / 2) - 6, "No notifications", &Font16, BLACK, WHITE);
  }

  if (oneTickPause == false) {
    Paint_DrawImage1(Bat816, 135, 20, 16, 8, GREEN);
    Paint_DrawString_EN(153, 19, (std::to_string(min(int(((adjustedResult - 2.29) / (2.4 - 2.25)) * 100), 100)) + "%").c_str(), &Font12, BLACK, GREEN);
  }

  if (notifHeight != -45) {  //tappedNotif==-1
    Paint_DrawRectangle(83, 190, 156, 222, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawString_EN(90, 199, "Clear", &Font16, GRAY, RED);  //63 char in length

    renderSnack();
    if (inTransition == false) {
      //Recommeneded to Open any asked apps After rendering existing scene to prevent double render black bar
      if (swipe("up", 190)) {
        openApp("main", "DU", Touch_CTS816.y_point);
      }
      if (pauseRender == false) {
        if (oneTickPause == false) {
          //LCD_1IN28_DisplayWindows(notifX - 1, 0, 180, 180, BlackImage);
          LCD_1IN28_DisplayWindows(notifX - 1, 0, 240, 240, BlackImage);
        }
      }

      if (tap) {
        if (watchSwipe == false && otherSwipe == false) {
          if (Touch_CTS816.x_point >= 83 && Touch_CTS816.x_point <= 156 && Touch_CTS816.y_point >= 190 && Touch_CTS816.y_point <= 222) {
            notifications.clear();
            uniqueNotifications.clear();
            uniqueTitles.clear();
            openApp("main", "UD", 0);
          }
        }
      }
    }
  }
}