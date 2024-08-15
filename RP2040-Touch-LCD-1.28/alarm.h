#include <string>
#include <list>

extern bool inTransition;
extern bool watchSwipe;
extern bool otherSwipe;
extern bool pauseRender;
extern bool tap;
extern bool startup;
extern std::list<std::list<long unsigned int>> systemAlarms;
extern uint16_t deviceMainColorTheme;
extern uint16_t deviceSecondColorTheme;
extern uint16_t deviceThirdColorTheme;
extern int scrollY;
extern UWORD* BlackImage;

int SELalarmHour = 0;
int SELalarmMinute = 0;
int btnSizeAlarm = 40;
int buttonMargin = 10;
int buttonColor = WHITE;
int buttonBackgroundColor = RED;

void millisToHoursMinutes(unsigned long millis, int& hours, int& minutes) {
  hours = millis / 3600000;
  millis %= 3600000;
  minutes = millis / 60000;
}

std::string formatTime(int hours, int minutes) {
  std::string h = (hours < 10) ? "0" + std::to_string(hours) : std::to_string(hours);
  std::string m = (minutes < 10) ? "0" + std::to_string(minutes) : std::to_string(minutes);
  return h + ":" + m;
}

void drawPlusButton(int x, int y, int width, int height) {
  int centerX = x + width / 2;
  int centerY = y + height / 2;
  Paint_DrawLine(centerX - 10, centerY, centerX + 10, centerY, buttonColor, DOT_PIXEL_2X2, LINE_STYLE_SOLID);
  Paint_DrawLine(centerX, centerY - 10, centerX, centerY + 10, buttonColor, DOT_PIXEL_2X2, LINE_STYLE_SOLID);
}

void drawDeleteButton(int x, int y, int size) {
  Paint_DrawLine(x, y, x + size, y + size, buttonColor, DOT_PIXEL_2X2, LINE_STYLE_SOLID);
  Paint_DrawLine(x + size, y, x, y + size, buttonColor, DOT_PIXEL_2X2, LINE_STYLE_SOLID);
}

void drawToggleButton(int x, int y, bool enabled) {
  int color = enabled ? GREEN : RED;
  Paint_DrawCircle(x, y, 10, color, DOT_PIXEL_2X2, DRAW_FILL_FULL);
}

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

void drawTimeSetting() {
  Paint_DrawString_EN(20, 100, ("Set Time: " + formatTime(SELalarmHour, SELalarmMinute)).c_str(), &Font16, BLACK, WHITE);

  // Draw Hour Up/Down Arrows
  Paint_DrawRectangle(10, 50, 10 + btnSizeAlarm, 50 + btnSizeAlarm, buttonBackgroundColor, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  drawArrow(10, 50, true);
  Paint_DrawRectangle(10, 100, 10 + btnSizeAlarm, 100 + btnSizeAlarm, buttonBackgroundColor, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  drawArrow(10, 100, false);

  // Draw Minute Up/Down Arrows
  Paint_DrawRectangle(70, 50, 70 + btnSizeAlarm, 50 + btnSizeAlarm, buttonBackgroundColor, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  drawArrow(70, 50, true);
  Paint_DrawRectangle(70, 100, 70 + btnSizeAlarm, 100 + btnSizeAlarm, buttonBackgroundColor, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  drawArrow(70, 100, false);
}

void drawAlarmList() {
  int y = 140;
  for (auto it = systemAlarms.begin(); it != systemAlarms.end(); ++it) {
    int alarmTime = (*it).front();         // Get the alarm time (assumed to be the first element)
    int dismissed = *(++(*it).begin());    // Get the second element for 'dismissed'
    int enabled = *(++(++(*it).begin()));  // Get the third element for 'enabled'

    // Convert the alarmTime to hours and minutes
    int hours, minutes;
    millisToHoursMinutes(alarmTime, hours, minutes);
    std::string timeString = formatTime(hours, minutes);

    Paint_DrawString_EN(20, y, timeString.c_str(), &Font16, BLACK, WHITE);
    drawDeleteButton(200, y, 20);
    drawToggleButton(230, y, enabled);

    y += 40;
  }
}

void dismissAlarm(unsigned long alarmId) {
  for (auto it = systemAlarms.begin(); it != systemAlarms.end(); ++it) {
    if ((*it).front() == alarmId) {  // Compare with the alarm ID
      *(++(*it).begin()) = 1;        // Mark as dismissed
    }
  }
} //alarms need to be reset after a day!

void alarm() {
  if (startup) {
    startup = false;

    if (appIn != "") {
      unsigned long alarmId = std::stoul(appIn);
      dismissAlarm(alarmId);
      Serial.println(appIn.c_str());
    }
  }

  drawTimeSetting();
  drawPlusButton(180, 20, 40, 40);
  drawAlarmList();

  if (!inTransition && !pauseRender) {
    LCD_1IN28_DisplayWindows(0, 0, 240, 240, BlackImage);
  }

  if (tap && !otherSwipe && !watchSwipe) {
    if (Touch_CTS816.x_point >= 180 && Touch_CTS816.x_point <= 220 && Touch_CTS816.y_point >= 20 && Touch_CTS816.y_point <= 60) {
      unsigned long alarmTime = SELalarmHour * 3600000 + SELalarmMinute * 60000;
      systemAlarms.push_back({ alarmTime, 0, 1 });
    }

    if (Touch_CTS816.x_point >= 10 && Touch_CTS816.x_point <= 10 + btnSizeAlarm) {
      if (Touch_CTS816.y_point >= 50 && Touch_CTS816.y_point <= 50 + btnSizeAlarm) {
        SELalarmHour = (SELalarmHour + 1) % 24;
      } else if (Touch_CTS816.y_point >= 100 && Touch_CTS816.y_point <= 100 + btnSizeAlarm) {
        SELalarmHour = (SELalarmHour - 1 + 24) % 24;
      }
    }

    if (Touch_CTS816.x_point >= 70 && Touch_CTS816.x_point <= 70 + btnSizeAlarm) {
      if (Touch_CTS816.y_point >= 50 && Touch_CTS816.y_point <= 50 + btnSizeAlarm) {
        SELalarmMinute = (SELalarmMinute + 1) % 60;
      } else if (Touch_CTS816.y_point >= 100 && Touch_CTS816.y_point <= 100 + btnSizeAlarm) {
        SELalarmMinute = (SELalarmMinute - 1 + 60) % 60;
      }
    }

    int y = 140;
    for (auto it = systemAlarms.begin(); it != systemAlarms.end(); ++it, y += 40) {
      if (Touch_CTS816.x_point >= 200 && Touch_CTS816.x_point <= 220 && Touch_CTS816.y_point >= y && Touch_CTS816.y_point <= y + 20) {
        it = systemAlarms.erase(it);
        if (it == systemAlarms.end()) break;
      }
      if (Touch_CTS816.x_point >= 230 && Touch_CTS816.x_point <= 240 && Touch_CTS816.y_point >= y && Touch_CTS816.y_point <= y + 20) {
        auto inner_it = ++(++(*it).begin());  // Get to the 'enabled' field
        *inner_it = (*inner_it == 1) ? 0 : 1;
      }
    }
  }
}
