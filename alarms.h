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

// Function to convert milliseconds to hours and minutes
void millisToHoursMinutes(unsigned long millis, int& hours, int& minutes) {
  hours = millis / 3600000;  // 3600000 milliseconds in an hour
  millis %= 3600000;
  minutes = millis / 60000;  // 60000 milliseconds in a minute
}

bool isElementNotInNotifications(const std::string& element) {
  // Loop through each inner list in the notifications list
  for (const auto& innerList : notifications) {
    // Check if the element exists in the current inner list
    if (std::find(innerList.begin(), innerList.end(), element) != innerList.end()) {
      return false;  // Element found, return false
    }
  }
  return true;  // Element not found in any inner list
}

std::string modifyString(std::string str) {
  if (str.length() == 1) {
    return "0" + str;
  } else {
    return str;
  }
}



// Example function for setting alarm
void setAlarm() {
  // Function to set alarm
}

int alarmHour = -1;               // Initialize alarm hour to -1 indicating alarm not set
int alarmMinute = -1;             // Initialize alarm minute to -1 indicating alarm not set
int SELalarmHour = 0;             // Initialize alarm hour to -1 indicating alarm not set
int SELalarmMinute = 0;           // Initialize alarm minute to -1 indicating alarm not set
int btnSizeAlarm = 40;            // Adjust button size as needed
int buttonMargin = 10;            // Adjust button margin as needed
int buttonColor = WHITE;          // Adjust button color as needed
int buttonBackgroundColor = RED;  // Adjust button background color as needed

void alarms() {
  // Display current time
  int currentHour, currentMinute;
  // Draw rectangles behind each button

  millisToHoursMinutes(CurTime + millis(), currentHour, currentMinute);
  //Paint_DrawString_EN(20, 100, ("Current Time: " + std::to_string(currentHour) + ":" + std::to_string(currentMinute)).c_str(), &Font16, BLACK, WHITE);

  // Check if alarm is set and display it
  if (alarmHour != -1 && alarmMinute != -1) {
    Paint_DrawString_EN(20, 150, ("Alarm Time: " + std::to_string(alarmHour) + ":" + modifyString(std::to_string(alarmMinute))).c_str(), &Font16, BLACK, WHITE);


    unsigned long elapsed_time = millis() + CurTime;  // + 46800000 + 2400000
    unsigned int hours = (elapsed_time % 86400000) / 3600000;
    unsigned int minutes = (elapsed_time % 3600000) / 60000;

    //if (hours == 0) {
    //  hours = 12;
    //}
    //if ((int)alarmHour == 0) {
    //  alarmHour = 12;
    //}

    ////////////////////////////////
    std::string elementToCheck = std::to_string(alarmHour) + ":" + modifyString(std::to_string(alarmMinute));
    if (hours == (int)alarmHour && minutes == (int)alarmMinute) {  //Alarm Iteslf
      Paint_DrawString_EN(20, 100, "Alarm ASDASDASDASDASD", &Font16, BLACK, WHITE);
      for (auto it = notifications.begin(); it != notifications.end(); ++it) {
        auto inner_it = it->begin();  // Start from the beginning of the inner list
        if (*inner_it == elementToCheck) {
          ++inner_it;  // Move to the second element
          if (inner_it != it->end() && *inner_it == "Alarms") {
            notifications.erase(it);  // Erase the outer list
            break;                    // Stop iterating after removing the first occurrence
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
    ////////////////////////////////
  } else {
    Paint_DrawRectangle(10, 50, 10 + btnSizeAlarm, 50 + btnSizeAlarm, buttonBackgroundColor, DOT_PIXEL_1X1, DRAW_FILL_FULL);     // UP HR
    Paint_DrawRectangle(10, 100, 10 + btnSizeAlarm, 100 + btnSizeAlarm, buttonBackgroundColor, DOT_PIXEL_1X1, DRAW_FILL_FULL);   // DN HR
    Paint_DrawRectangle(70, 50, 70 + btnSizeAlarm, 50 + btnSizeAlarm, buttonBackgroundColor, DOT_PIXEL_1X1, DRAW_FILL_FULL);     // UP MN
    Paint_DrawRectangle(70, 100, 70 + btnSizeAlarm, 100 + btnSizeAlarm, buttonBackgroundColor, DOT_PIXEL_1X1, DRAW_FILL_FULL);   // DN MN
    Paint_DrawRectangle(130, 50, 130 + btnSizeAlarm, 100 + btnSizeAlarm, buttonBackgroundColor, DOT_PIXEL_1X1, DRAW_FILL_FULL);  // SET

    Paint_DrawString_EN(20, 150, ("SetTo Time: " + std::to_string(SELalarmHour) + ":" + modifyString(std::to_string(SELalarmMinute))).c_str(), &Font16, BLACK, GREEN);
  }

  renderSnack();
  if (inTransition == false) {
    if (pauseRender == false) {
      LCD_1IN28_DisplayWindows(0, 0, 240, 240, BlackImage);
    }

    if (tap && otherSwipe == false && watchSwipe == false && alarmHour == -1 && alarmMinute == -1) {
      // Check if tap is within the UP button region
      if (Touch_CTS816.x_point >= 10 && Touch_CTS816.x_point <= 10 + btnSizeAlarm && Touch_CTS816.y_point >= 50 && Touch_CTS816.y_point <= 50 + btnSizeAlarm) {
        if (SELalarmHour == -1) SELalarmHour = 0;  // Initialize hour if not set
        SELalarmHour = (SELalarmHour + 1) % 24;    // Increment hour and wrap around if necessary
      }

      // Check if tap is within the DOWN button region
      if (Touch_CTS816.x_point >= 10 && Touch_CTS816.x_point <= 10 + btnSizeAlarm && Touch_CTS816.y_point >= 100 && Touch_CTS816.y_point <= 100 + btnSizeAlarm) {
        if (SELalarmHour == -1) SELalarmHour = 0;  // Initialize hour if not set
        SELalarmHour = (SELalarmHour - 1) % 24;    // Decrement hour and wrap around if necessary
      }

      if (Touch_CTS816.x_point >= 70 && Touch_CTS816.x_point <= 70 + btnSizeAlarm && Touch_CTS816.y_point >= 50 && Touch_CTS816.y_point <= 50 + btnSizeAlarm) {
        if (SELalarmMinute == -1) SELalarmMinute = 0;  // Initialize hour if not set
        SELalarmMinute = (SELalarmMinute + 1) % 60;    // Increment hour and wrap around if necessary
      }

      // Check if tap is within the DOWN button region
      if (Touch_CTS816.x_point >= 70 && Touch_CTS816.x_point <= 70 + btnSizeAlarm && Touch_CTS816.y_point >= 100 && Touch_CTS816.y_point <= 100 + btnSizeAlarm) {
        if (SELalarmMinute == -1) SELalarmMinute = 0;  // Initialize hour if not set
        SELalarmMinute = (SELalarmMinute - 1) % 60;    // Decrement hour and wrap around if necessary
      }

      // Check if tap is within the SET button region
      if (Touch_CTS816.x_point >= 130 && Touch_CTS816.x_point <= 130 + btnSizeAlarm && Touch_CTS816.y_point >= 50 && Touch_CTS816.y_point <= 100 + btnSizeAlarm) {
        alarmHour = SELalarmHour;
        alarmMinute = SELalarmMinute;
        // Function to set the alarm
        //setAlarm();
      }
    }
  }
}
