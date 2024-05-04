#ifndef mainScreen_H
#define mainScreen_H
extern int CurTime;
extern int last;
extern int tapHeld;
extern bool inTransition;
extern bool watchSwipe;
extern bool pauseRender;
extern UWORD *BlackImage;
extern uint16_t deviceMainColorTheme;
extern uint16_t deviceSecondColorTheme;
extern uint16_t deviceThirdColorTheme;
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
  unsigned long minutes = (elapsed_time % 3600000) / 60000;
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


  //Paint_SelectImage((UBYTE*)Bat816);
  //Paint_DrawBitMap((UBYTE*)Bat816);
  Paint_DrawImage1(Bat816, 120, 86, 16, 8, GREEN);
  if (resultButINeedPrivates > 2.9) {
    Paint_DrawString_EN(140, 84, "CHRG", &Font16, BLACK, GREEN);
  } else {
    float adjustedResult = min(resultButINeedPrivates, 3.11);
    int batteryPercentage = min(int(((resultButINeedPrivates - minVoltage) / (operatingVoltage - minVoltage)) * 100), 100);
    Paint_DrawString_EN(140, 84, (std::to_string(batteryPercentage) + "%").c_str(), &Font16, BLACK, GREEN);
  }
  Paint_DrawImage1(RunningPerson, 120, 114, 16, 16, RED);  //stepCount
  Paint_DrawString_EN(140, 114, (std::to_string(stepCount)).c_str(), &Font16, BLACK, RED);
  //Paint_DrawString_EN(140, 114, "---", &Font16, BLACK, RED);

  // void Paint_BmpWindows(unsigned char x,unsigned char y,const unsigned char *pBmp,\
	//				unsigned char chWidth,unsigned char chHeight);


  //sprintf(buffer, "%02d:%02d", hours, minutes);
  char buffer[9];
  sprintf(buffer, "%02d", hours, minutes);
  Paint_DrawString_EN(30, 109, buffer, &Font24, BLACK, deviceMainColorTheme);

  sprintf(buffer, "%02d", minutes, hours);
  Paint_DrawString_EN(30, 131, buffer, &Font24, BLACK, deviceSecondColorTheme);

  Paint_DrawCircle(second_x, second_y, 10, deviceThirdColorTheme, DOT_PIXEL_2X2, DRAW_FILL_FULL);

  Paint_DrawString_EN(70, 190, "May, 25th", &Font16, BLACK, deviceThirdColorTheme);


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
    Paint_DrawImage1(NoConnection, 120 - 8, 185, 16, 16, RED);
  }

  //Stuffs

  if (inTransition == false) {
    if (swipe("right", 70)) {
      openApp("Weather", "LR", Touch_CTS816.x_point);
    } else if (swipe("left", 70)) {
      openApp("News", "RL", Touch_CTS816.x_point);
    } else if (swipe("down", 70)) {
      openApp("notifPane", "UD", Touch_CTS816.y_point);
    };
    //LCD_1IN28_DisplayWindows(30, 109, 64, 159, BlackImage);
    if (pauseRender == false) {
      //LCD_1IN28_DisplayWindows(0, 0, 240, 240, BlackImage);
      LCD_1IN28_Display(BlackImage);
    }
    //LCD_1IN28_DisplayWindows(max(0,second_x-34), max(0,second_y-34), min(second_x+34,240), min(second_y+34,240), BlackImage);
  }
}