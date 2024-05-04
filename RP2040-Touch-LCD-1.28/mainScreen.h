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
bool swipe(std::string dir, int thresh);
void saveToEEPROMX(unsigned long data, int addr);
void openApp(std::string app, std::string dir, int start);
#endif

#include <cstring>
#include <sstream>

int stepCount = 0;
float resultButINeedPrivates;



float operatingVoltage = 2.4;  // Replace with your actual operating voltage
float minVoltage = 2.29;       // Replace with your actual minimum voltage

void mainScreen() {
  resultButINeedPrivates = DEC_ADC_Read() * (3.3f / (1 << 12) * 2);
  unsigned long elapsed_time = millis() + CurTime;
  unsigned long hours = (elapsed_time % 86400000) / 3600000;
  unsigned long minutes = (elapsed_time % 3600000);
  unsigned long seconds = (elapsed_time % 60000);
  unsigned long days = int(elapsed_time / 86400000) / 24;  //um

  int second_x = 120 - (105 * sin(((seconds / 166.666666666) + 180) * PI / 180));
  int second_y = 120 + (105 * cos(((seconds / 166.666666666) + 180) * PI / 180));

  if (hours > 12) {
    hours = hours - 12;
  }
  if (hours == 0) {
    hours = 12;
  }

  uint16_t minute_x = 120 + (65 * sin(((minutes / 10000)) * PI / 180));
  uint16_t minute_y = 120 - (65 * cos(((minutes / 10000)) * PI / 180));
  uint16_t minute_x_short = 120 + (90 * sin(((minutes / 10000)) * PI / 180));
  uint16_t minute_y_short = 120 - (90 * cos(((minutes / 10000)) * PI / 180));

  Paint_DrawLine(minute_x_short, minute_y_short, (uint16_t)minute_x, (uint16_t)minute_y, deviceSecondColorTheme, DOT_PIXEL_4X4, LINE_STYLE_SOLID);  // Replace 0x009688 with your chosen color
  //Paint_DrawCircle((uint16_t)minute_x, (uint16_t)minute_y, 4, WHITE, DOT_PIXEL_4X4, DRAW_FILL_FULL); // Replace 0x009688 with your chosen color
  //Paint_DrawCircle((uint16_t)minute_x_short, (uint16_t)minute_y_short, 4, WHITE, DOT_PIXEL_4X4, DRAW_FILL_FULL); // Replace 0x009688 with your chosen color
  //was 4

  uint16_t hour_x = 120 + (58 * sin(((hours % 12) * 30 + 0) * PI / 180));
  uint16_t hour_y = 120 - (58 * cos(((hours % 12) * 30 + 0) * PI / 180));

  uint16_t hour_x_cent = 120 + (4 * sin(((hours % 12) * 30 + 0) * PI / 180));
  uint16_t hour_y_cent = 120 - (4 * cos(((hours % 12) * 30 + 0) * PI / 180));

  //uint16_t hour_x_circle = 120 + (59 * sin(((hours % 12) * 30 + 0) * PI / 180));
  //uint16_t hour_y_circle = 120 - (59 * cos(((hours % 12) * 30 + 0) * PI / 180));

  Paint_DrawLine(hour_x_cent, hour_y_cent, (uint16_t)hour_x, (uint16_t)hour_y, deviceMainColorTheme, DOT_PIXEL_7X7, LINE_STYLE_SOLID);  // Replace 0x00796F with your chosen color
  //Paint_DrawCircle((uint16_t)hour_x_circle, (uint16_t)hour_y_circle, 6, 0x009688, DOT_PIXEL_6X6, DRAW_FILL_FULL); // Replace 0x00796F with your chosen color
  Paint_DrawCircle(120, 120, 8, deviceMainColorTheme, DOT_PIXEL_7X7, DRAW_FILL_FULL);  // Replace 0x00796F with your chosen color
                                                                                       //was 8

  Paint_DrawCircle(second_x, second_y, 7, deviceThirdColorTheme, DOT_PIXEL_2X2, DRAW_FILL_FULL);


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

  if(!BLEconnected){
    Paint_DrawImage1(NoConnection, 120-8, 185, 16, 16, RED);
  }

  //Stuffs

  if (inTransition == false) {
    //LCD_1IN28_DisplayWindows(30, 109, 64, 159, BlackImage);
    if (swipe("right", 70)) {
      openApp("Weather", "LR", Touch_CTS816.x_point);
    } else if (swipe("left", 70)) {
      openApp("News", "RL", Touch_CTS816.x_point);
    } else if (swipe("down", 70)) {
      openApp("notifPane", "UD", Touch_CTS816.y_point);
    };
    if (pauseRender == false) {
      //LCD_1IN28_DisplayWindows(0, 0, 240, 240, BlackImage);
      LCD_1IN28_Display(BlackImage);
    }
    //LCD_1IN28_DisplayWindows(max(0,second_x-34), max(0,second_y-34), min(second_x+34,240), min(second_y+34,240), BlackImage);
  }
}