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
    {"Title", "App", "Content", "AppSpecificData"},
    {"Contact1", "Messages", "SomeContent", "Number"},
    {"Contact2", "Messages", "CONTENT2", "Number"},
};
std::list<std::list<std::string>> uniqueNotifications;
std::set<std::string> uniqueTitles;

extern int scrollY;
extern int hoverObject;

void notifPane() {
    if (startup) {
        startup = false;
        scrollY = 0;
        LCD_1IN28_DisplayWindows(180, 0, 240, 240, BlackImage);
    }

    result = DEC_ADC_Read() * (3.3f / (1 << 12) * 2);
    float adjustedResult = std::min(result, 3.11f);

    float notifX = 20;
    float notifY = 50;
    float notifHeight = 35;
    float index = 0;

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
        int adjustedY = notifY + (index * (notifHeight + 10)) - (-scrollY / (240 / ((notifHeight + 10) * number)));
        if (!oneTickPause && adjustedY > 0 && adjustedY < 180 - notifHeight) {
            Paint_DrawRectangle(notifX, std::max(0, std::min(180 - (int)notifHeight, adjustedY)), 
                                (240 - notifX) - 50, std::max(0, std::min(180 - (int)notifHeight, adjustedY + (int)notifHeight)), 
                                0x2121, DOT_PIXEL_1X1, DRAW_FILL_FULL);
            auto lastItem = std::prev(notification.end());
            std::string openAppWith = *std::next(notification.begin(), 1);

            Paint_DrawString_EN(notifX + 5, (adjustedY + notifHeight / 2) - 6, lastItem->c_str(), &Font16, 0x2121, WHITE);

            if (tap && !watchSwipe && !otherSwipe && runningAppName == "notifPane") {
                if (Touch_CTS816.x_point >= notifX && Touch_CTS816.x_point <= 156 &&
                    Touch_CTS816.y_point >= adjustedY && Touch_CTS816.y_point <= adjustedY + notifHeight) {
                    tappedNotif = index;
                    oneTickPause = true;
                    notifHeight = -45;
                    auto it = apps.find(openAppWith);
                    if (it != apps.end()) {
                        openApp(openAppWith, "RL", 240);
                    } else {
                        openApp("previewNotif", "RL", 240);
                    }
                }
            }
        }
        index++;
    }

    if (notifications.empty()) {
        Paint_DrawString_EN(notifX + 5, (notifY + notifHeight / 2) - 6, "No notifications", &Font16, BLACK, WHITE);
    }

    if (!oneTickPause) {
        Paint_DrawImage1(Bat816, 135, 20, 16, 8, GREEN);
        Paint_DrawString_EN(153, 19, (std::to_string(std::min(int(((adjustedResult - 2.29) / (2.4 - 2.25)) * 100), 100)) + "%").c_str(), &Font12, BLACK, GREEN);
    }

    if (notifHeight != -45) {
        Paint_DrawRectangle(83, 190, 156, 222, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        Paint_DrawString_EN(90, 199, "Clear", &Font16, GRAY, RED);

        renderSnack();
        if (!inTransition) {
            if (swipe("up", 190)) {
                openApp("main", "DU", Touch_CTS816.y_point);
            }
            if (!pauseRender && !oneTickPause) {
                LCD_1IN28_DisplayWindows(notifX - 1, 0, 240, 240, BlackImage);
            }

            if (tap && !watchSwipe && !otherSwipe) {
                if (Touch_CTS816.x_point >= 83 && Touch_CTS816.x_point <= 156 &&
                    Touch_CTS816.y_point >= 190 && Touch_CTS816.y_point <= 222) {
                    notifications.clear();
                    uniqueNotifications.clear();
                    uniqueTitles.clear();
                    openApp("main", "UD", 0);
                }
            }
        }
    }
}
