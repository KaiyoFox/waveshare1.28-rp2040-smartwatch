#include <string>

extern bool inTransition;
extern bool watchSwipe;
extern bool otherSwipe;
extern bool pauseRender;
extern bool tap;
extern bool startup;
extern uint16_t deviceMainColorTheme;
extern uint16_t deviceSecondColorTheme;
extern uint16_t deviceThirdColorTheme;
extern int scrollY;
extern int CurTime;
extern std::list<std::list<std::string>> notifications;
extern UWORD* BlackImage;
typedef void (*ServiceFunction)();
bool swipe(std::string dir, int thresh);
void openApp(std::string app, std::string dir, int start);
void addService(const String& name, ServiceFunction function);

void millisToHoursMinutes(unsigned long millis, int& hours, int& minutes) {
    hours = millis / 3600000;
    millis %= 3600000;
    minutes = millis / 60000;
}

bool isElementNotInNotifications(const std::string& element) {
    for (const auto& innerList : notifications) {
        if (std::find(innerList.begin(), innerList.end(), element) != innerList.end()) {
            return false;
        }
    }
    return true;
}

std::string modifyString(std::string str) {
    return (str.length() == 1) ? "0" + str : str;
}

int alarmHour = -1;
int alarmMinute = -1;
int SELalarmHour = 0;
int SELalarmMinute = 0;
int btnSizeAlarm = 40;
int buttonMargin = 10;
int buttonColor = WHITE;
int buttonBackgroundColor = RED;

void drawArrow(int x, int y, bool up) {
    int centerX = x + btnSizeAlarm / 2;
    int centerY = y + btnSizeAlarm / 2;
    if (up) {
        Paint_DrawLine(centerX, y + 10, centerX - 10, y + 30, buttonColor, DOT_PIXEL_2X2, LINE_STYLE_SOLID);
        Paint_DrawLine(centerX, y + 10, centerX + 10, y + 30, buttonColor, DOT_PIXEL_2X2, LINE_STYLE_SOLID);
        Paint_DrawLine(centerX - 10, y + 30, centerX + 10, y + 30, buttonColor, DOT_PIXEL_2X2, LINE_STYLE_SOLID);
    } else {
        Paint_DrawLine(centerX, y + 30, centerX - 10, y + 10, buttonColor, DOT_PIXEL_2X2, LINE_STYLE_SOLID);
        Paint_DrawLine(centerX, y + 30, centerX + 10, y + 10, buttonColor, DOT_PIXEL_2X2, LINE_STYLE_SOLID);
        Paint_DrawLine(centerX - 10, y + 10, centerX + 10, y + 10, buttonColor, DOT_PIXEL_2X2, LINE_STYLE_SOLID);
    }
}

void drawButtons() {
    Paint_DrawRectangle(10, 50, 10 + btnSizeAlarm, 50 + btnSizeAlarm, buttonBackgroundColor, DOT_PIXEL_1X1, DRAW_FILL_FULL);     // UP HR
    drawArrow(10, 50, true);
    Paint_DrawRectangle(10, 100, 10 + btnSizeAlarm, 100 + btnSizeAlarm, buttonBackgroundColor, DOT_PIXEL_1X1, DRAW_FILL_FULL);   // DN HR
    drawArrow(10, 100, false);
    Paint_DrawRectangle(70, 50, 70 + btnSizeAlarm, 50 + btnSizeAlarm, buttonBackgroundColor, DOT_PIXEL_1X1, DRAW_FILL_FULL);     // UP MN
    drawArrow(70, 50, true);
    Paint_DrawRectangle(70, 100, 70 + btnSizeAlarm, 100 + btnSizeAlarm, buttonBackgroundColor, DOT_PIXEL_1X1, DRAW_FILL_FULL);   // DN MN
    drawArrow(70, 100, false);
    Paint_DrawRectangle(130, 50, 130 + btnSizeAlarm, 100 + btnSizeAlarm, buttonBackgroundColor, DOT_PIXEL_1X1, DRAW_FILL_FULL);  // SET
    Paint_DrawString_EN(130 + 15, 75, "SET", &Font16, BLACK, buttonColor);
}

void alarms() {
    int currentHour, currentMinute;
    millisToHoursMinutes(CurTime + millis(), currentHour, currentMinute);

    if (alarmHour != -1 && alarmMinute != -1) {
        Paint_DrawString_EN(20, 150, ("Alarm Time: " + std::to_string(alarmHour) + ":" + modifyString(std::to_string(alarmMinute))).c_str(), &Font16, BLACK, WHITE);
        
        unsigned long elapsed_time = millis() + CurTime;
        unsigned int hours = (elapsed_time % 86400000) / 3600000;
        unsigned int minutes = (elapsed_time % 3600000) / 60000;
        
        std::string elementToCheck = std::to_string(alarmHour) + ":" + modifyString(std::to_string(alarmMinute));
        if (hours == (int)alarmHour && minutes == (int)alarmMinute) {
            Paint_DrawString_EN(20, 100, "Alarm Ringing", &Font16, BLACK, WHITE);
            for (auto it = notifications.begin(); it != notifications.end(); ++it) {
                auto inner_it = it->begin();
                if (*inner_it == elementToCheck) {
                    ++inner_it;
                    if (inner_it != it->end() && *inner_it == "Alarms") {
                        notifications.erase(it);
                        break;
                    }
                }
            }
        } else if ((hours == alarmHour && minutes < alarmMinute) || (hours == (alarmHour - 1) && minutes >= alarmMinute)) {
            if (isElementNotInNotifications(elementToCheck)) {
                notifications.push_back({ elementToCheck, "Alarms", "", (elementToCheck + " Alarm goes off soon.").c_str() });
                digitalWrite(D28, HIGH);
                delay(250);
                digitalWrite(D28, LOW);
                delay(200);
                digitalWrite(D28, HIGH);
                delay(200);
                digitalWrite(D28, LOW);
            }
        }
    } else {
        drawButtons();
        Paint_DrawString_EN(20, 150, ("Set Time: " + std::to_string(SELalarmHour) + ":" + modifyString(std::to_string(SELalarmMinute))).c_str(), &Font16, BLACK, GREEN);
    }

    renderSnack();
    if (!inTransition && !pauseRender) {
        LCD_1IN28_DisplayWindows(0, 0, 240, 240, BlackImage);
    }

    if (tap && !otherSwipe && !watchSwipe && alarmHour == -1 && alarmMinute == -1) {
        if (Touch_CTS816.x_point >= 10 && Touch_CTS816.x_point <= 10 + btnSizeAlarm && Touch_CTS816.y_point >= 50 && Touch_CTS816.y_point <= 50 + btnSizeAlarm) {
            SELalarmHour = (SELalarmHour + 1) % 24;
        }
        if (Touch_CTS816.x_point >= 10 && Touch_CTS816.x_point <= 10 + btnSizeAlarm && Touch_CTS816.y_point >= 100 && Touch_CTS816.y_point <= 100 + btnSizeAlarm) {
            SELalarmHour = (SELalarmHour - 1 + 24) % 24;
        }
        if (Touch_CTS816.x_point >= 70 && Touch_CTS816.x_point <= 70 + btnSizeAlarm && Touch_CTS816.y_point >= 50 && Touch_CTS816.y_point <= 50 + btnSizeAlarm) {
            SELalarmMinute = (SELalarmMinute + 1) % 60;
        }
        if (Touch_CTS816.x_point >= 70 && Touch_CTS816.x_point <= 70 + btnSizeAlarm && Touch_CTS816.y_point >= 100 && Touch_CTS816.y_point <= 100 + btnSizeAlarm) {
            SELalarmMinute = (SELalarmMinute - 1 + 60) % 60;
        }
        if (Touch_CTS816.x_point >= 130 && Touch_CTS816.x_point <= 130 + btnSizeAlarm && Touch_CTS816.y_point >= 50 && Touch_CTS816.y_point <= 100 + btnSizeAlarm) {
            alarmHour = SELalarmHour;
            alarmMinute = SELalarmMinute;
        }
    }
}
