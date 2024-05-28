#include <string>
#ifndef mainScreen_H
#define mainScreen_H
extern int CurTime;
extern int last;
extern int tapHeld;
extern int HourMinSize;
extern bool inTransition;
extern bool watchSwipe;
extern bool pauseRender;
extern uint16_t deviceMainColorTheme;
extern uint16_t deviceSecondColorTheme;
extern uint16_t deviceThirdColorTheme;
extern UWORD *BlackImage;
extern bool BLEconnected;
extern std::string weatherTemp;
bool swipe(std::string dir, int thresh);
void saveToEEPROMX(unsigned long data, int addr);
void openApp(std::string app, std::string dir, int start);
#endif

#include <cstring>
#include <sstream>

int stepCount = 0;
float resultButINeedPrivates;

void millisToDate(unsigned long millis, int &year, int &month, int &day, String &dayOfWeek, String &monthAbbr) {
  const int SECONDS_IN_A_DAY = 86400;

  // Starting point: January 1, 2024
  const int START_YEAR = 2024;
  const int START_MONTH = 1;
  const int START_DAY = 1;

  auto daysInMonth = [](int month, int year) -> int {
    switch (month) {
      case 4:
      case 6:
      case 9:
      case 11: return 30;
      case 2: return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) ? 29 : 28;
      default: return 31;
    }
  };

  auto calculateDayOfWeek = [](int year, int month, int day) -> int {
    if (month < 3) {
      month += 12;
      year -= 1;
    }
    int K = year % 100;
    int J = year / 100;
    int f = day + (13 * (month + 1)) / 5 + K + K / 4 + J / 4 + 5 * J;
    return f % 7;
  };

  String monthsAbbr[] = { "JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP", "OCT", "NOV", "DEC" };

  // Calculate total seconds since start
  unsigned long totalSeconds = millis / 1000;
  unsigned long daysPassed = totalSeconds / SECONDS_IN_A_DAY;

  // Start from the base date
  year = START_YEAR;
  month = START_MONTH;
  day = START_DAY;

  // Add days to the base date
  while (daysPassed > 0) {
    int daysInCurrentMonth = daysInMonth(month, year);
    if (daysPassed >= daysInCurrentMonth - (day - 1)) {
      daysPassed -= (daysInCurrentMonth - (day - 1));
      day = 1;
      month++;
      if (month > 12) {
        month = 1;
        year++;
      }
    } else {
      day += daysPassed;
      daysPassed = 0;
    }
  }

  // Calculate day of the week
  int dayIndex = calculateDayOfWeek(year, month, day);
  String daysOfWeek[] = { "SAT", "SUN", "MON", "TUES", "WED", "THURS", "FRI" };
  dayOfWeek = daysOfWeek[dayIndex];

  // Get the month abbreviation
  monthAbbr = monthsAbbr[month - 1];
}

String getOrdinalSuffix(int day) {
  // Get the last two digits of the day
  int lastTwoDigits = day % 100;

  // Get the last digit of the day
  int lastDigit = day % 10;

  // Determine the suffix based on the last digits
  if (lastTwoDigits >= 11 && lastTwoDigits <= 13) {
    return "th";
  }

  switch (lastDigit) {
    case 1: return "st";
    case 2: return "nd";
    case 3: return "rd";
    default: return "th";
  }
}

int get_yshift(int hour) {
  // Base shift for all markers
  const int base_shift = -20;

  // Adjustments based on hour position (if-else statements)
  if (hour == 0 || hour == 12) {
    return base_shift;
  } else if (hour == 1) {
    return -10;
  } else if (hour == 2) {
    return -10;
  } else if (hour == 3) {
    return -10;
  } else if (hour == 4) {  ///////////////////
    return -10;
  } else if (hour == 5) {
    return -5;
  } else if (hour == 6) {
    return -5;
  } else if (hour == 7) {
    return 0;  //base_shift + 12;
  } else if (hour == 8) {
    return -5;  //-5
  } else if (hour == 9) {
    return -10;
  } else if (hour == 10) {  /////////////////
    return -10;
  } else if (hour == 11) {  ////////////////
    return -10;
  }
  return 0;
}


float operatingVoltage = 2.4;  // Replace with your actual operating voltage
float minVoltage = 2.29;       // Replace with your actual minimum voltage

int preHours;
void mainScreen() {
  resultButINeedPrivates = DEC_ADC_Read() * (3.3f / (1 << 12) * 2);
  unsigned long elapsed_time = millis() + CurTime;
  unsigned long hours = (elapsed_time % 86400000) / 3600000;
  unsigned long minutes = (elapsed_time % 3600000);
  unsigned long seconds = (elapsed_time % 60000);
  unsigned long days = int(elapsed_time / 86400000) / 24;  //um
  int year, month, day;
  String dayOfWeek;
  String monthName;
  millisToDate(elapsed_time, year, month, day, dayOfWeek, monthName);

  int second_x = 120 - (105 * sin(((seconds / 166.666666666) + 180) * PI / 180));
  int second_y = 120 + (105 * cos(((seconds / 166.666666666) + 180) * PI / 180));

  if (hours > 12) {
    hours = hours - 12;
  }
  preHours = hours;
  if (hours == 0) {
    hours = 12;
  }

  uint16_t minute_x = 120 + (110 * sin(((minutes / 10000)) * PI / 180));
  uint16_t minute_y = 120 - (110 * cos(((minutes / 10000)) * PI / 180));
  //uint16_t minute_x_short = 120 + (90 * sin(((minutes / 10000)) * PI / 180));
  //uint16_t minute_y_short = 120 - (90 * cos(((minutes / 10000)) * PI / 180));

  //  Paint_DrawLine(minute_x_short, minute_y_short, (uint16_t)minute_x, (uint16_t)minute_y, deviceSecondColorTheme, DOT_PIXEL_4X4, LINE_STYLE_SOLID);  // Replace 0x009688 with your chosen color

  //Paint_DrawLine(120, 120, (uint16_t)minute_x, (uint16_t)minute_y, deviceSecondColorTheme, DOT_PIXEL_2X2, LINE_STYLE_SOLID);

  //Paint_DrawCircle((uint16_t)minute_x, (uint16_t)minute_y, 4, WHITE, DOT_PIXEL_4X4, DRAW_FILL_FULL); // Replace 0x009688 with your chosen color
  //Paint_DrawCircle((uint16_t)minute_x_short, (uint16_t)minute_y_short, 4, WHITE, DOT_PIXEL_4X4, DRAW_FILL_FULL); // Replace 0x009688 with your chosen color
  //was 4

  uint16_t hour_x = 120 + (60 * sin(((hours % 12) * 30 + 0) * PI / 180));
  uint16_t hour_y = 120 - (60 * cos(((hours % 12) * 30 + 0) * PI / 180));

  //uint16_t hour_x_cent = 120 + (4 * sin(((hours % 12) * 30 + 0) * PI / 180));
  //uint16_t hour_y_cent = 120 - (4 * cos(((hours % 12) * 30 + 0) * PI / 180));

  //uint16_t hour_x_circle = 120 + (59 * sin(((hours % 12) * 30 + 0) * PI / 180));
  //uint16_t hour_y_circle = 120 - (59 * cos(((hours % 12) * 30 + 0) * PI / 180));

  int weathLen = weatherTemp.length();
  Paint_DrawImage1(Sun, 120 - 8, 140, 16, 16, YELLOW);
  Paint_DrawString_EN(120 - ((weathLen * 7) / 2), 156, weatherTemp.c_str(), &Font12, BLACK, GRAY);

  String dateStr = dayOfWeek + ", " + monthName + " " + day;
  int lengthOfDate = dateStr.length();
  Paint_DrawString_EN((int)120 - ((lengthOfDate * 11) / 2), 19, dateStr.c_str(), &Font16, BLACK, deviceMainColorTheme);


  Paint_DrawLine(120, 120, (uint16_t)hour_x, (uint16_t)hour_y, deviceMainColorTheme, DOT_PIXEL_2X2, LINE_STYLE_SOLID);  // Replace 0x00796F with your chosen color
  Paint_DrawLine(120, 120, (uint16_t)minute_x, (uint16_t)minute_y, deviceSecondColorTheme, DOT_PIXEL_2X2, LINE_STYLE_SOLID);

  //Paint_DrawCircle((uint16_t)hour_x_circle, (uint16_t)hour_y_circle, 6, 0x009688, DOT_PIXEL_6X6, DRAW_FILL_FULL); // Replace 0x00796F with your chosen color
  Paint_DrawCircle(120, 120, 3, deviceMainColorTheme, DOT_PIXEL_3X3, DRAW_FILL_FULL);  // Replace 0x00796F with your chosen color





  for (int i = 0; i < 12; ++i) {
    uint16_t hour_x_tic = 120 + (80 * sin(((i % 12) * 30 + 0) * PI / 180));
    uint16_t hour_y_tic = 120 - (80 * cos(((i % 12) * 30 + 0) * PI / 180));

    uint16_t hour_x_tic_short = 120 + (75 * sin(((i % 12) * 30 + 0) * PI / 180));
    uint16_t hour_y_tic_short = 120 - (75 * cos(((i % 12) * 30 + 0) * PI / 180));

    if (i == preHours) {
      uint16_t hour_x_mark = 120 + (90 * sin(((i % 12) * 30 + 0) * PI / 180));
      uint16_t hour_y_mark = 120 - (90 * cos(((i % 12) * 30 + 0) * PI / 180));
      //int lengthOfHr = std::to_string(hours).length();
      //Paint_DrawString_EN(hour_x_mark - ((lengthOfHr * 14) / 2), hour_y_mark + get_yshift(preHours), std::to_string(hours).c_str(), &Font20, BLACK, deviceMainColorTheme);
      Paint_DrawLine(hour_x_tic_short, hour_y_tic_short, (uint16_t)hour_x_tic, (uint16_t)hour_y_tic, deviceMainColorTheme, DOT_PIXEL_2X2, LINE_STYLE_SOLID);
    } else {
      Paint_DrawLine(hour_x_tic_short, hour_y_tic_short, (uint16_t)hour_x_tic, (uint16_t)hour_y_tic, GRAY, DOT_PIXEL_2X2, LINE_STYLE_SOLID);
    }
  }

  //was 8
  Paint_DrawCircle(second_x, second_y, 7, deviceThirdColorTheme, DOT_PIXEL_2X2, DRAW_FILL_FULL);

  //  Paint_DrawString_EN(70, 190, (std::to_string(day)).c_str(), &Font16, BLACK, deviceThirdColorTheme);

  //sprintf(buffer, "%02d", days, hours);
  //Paint_DrawString_EN(100, 131, buffer, &Font24, BLACK, WHITE);
  //Dates are weird, fix later

  if (elapsed_time - last > 15000) {
    last = elapsed_time;
    saveToEEPROMX(last, 1);
  }

  if (resultButINeedPrivates > 2.9) {
    Paint_DrawCircle(120, 120, 118, GREEN, DOT_PIXEL_2X2, DRAW_FILL_EMPTY);
  }

  if (!BLEconnected) {
    Paint_DrawImage1(NoConnection, 120 - 8, 210, 16, 16, RED);
  }

  //Stuffs

  renderSnack();
  if (inTransition == false) {
    //Bruh I thought I moved this already.-- Swipe MUST be above renders. Why, Because thats how I designed it to run
    //BRUHH this didn't fix it.
    if (swipe("right", 70)) {
      openApp("Weather", "LR", Touch_CTS816.x_point);
    } else if (swipe("left", 70)) {
      openApp("News", "RL", Touch_CTS816.x_point);
    } else if (swipe("down", 70)) {
      openApp("notifPane", "UD", Touch_CTS816.y_point);
    };

    //LCD_1IN28_DisplayWindows(30, 109, 64, 159, BlackImage);
    if (pauseRender == false) {
      LCD_1IN28_DisplayWindows(0, 0, 240, 240, BlackImage);
      //LCD_1IN28_Display(BlackImage); //Istg if this is why it breaks
    }
    //LCD_1IN28_DisplayWindows(max(0,second_x-34), max(0,second_y-34), min(second_x+34,240), min(second_y+34,240), BlackImage);
  }
}