#ifndef setTime_H
#define setTime_H
extern bool inTransition;
extern bool pauseRender;
extern bool tap;
extern bool watchSwipe;
extern int CurTime;
extern UWORD *BlackImage;
extern std::list<std::string> backgroundApps;
bool swipe(std::string dir, int thresh);
void openApp(std::string app, std::string dir, int start);
#endif

int NewHours;


void setTime() {
  unsigned long elapsed_time = millis() + CurTime;
  unsigned long hours = (elapsed_time % 86400000) / 3600000;
  unsigned long minutes = (elapsed_time % 3600000) / 60000;
  unsigned long seconds = (elapsed_time % 60000) / 1000;
  unsigned long days = int(elapsed_time / 86400000) / 24;  //um

  uint16_t second_x = 120 - (int)(105 * sin((seconds * 6 + 180) * PI / 180));
  uint16_t second_y = 120 + (int)(105 * cos((seconds * 6 + 180) * PI / 180));

  if (hours > 12) {
    NewHours = hours - 12;
  } else {
    NewHours = hours;
  }
  if (NewHours == 0) {
    NewHours = 12;
  }

  //sprintf(buffer, "%02d:%02d", hours, minutes);
  char buffer[9];
  sprintf(buffer, "%02d", NewHours, minutes);
  Paint_DrawString_EN(100, 109, buffer, &Font24, BLACK, 0x009688);

  sprintf(buffer, "%02d", hours, minutes);
  Paint_DrawString_EN(130, 109, buffer, &Font12, BLACK, 0x009688);

  sprintf(buffer, "%02d", minutes, hours);
  Paint_DrawString_EN(100, 131, buffer, &Font24, BLACK, WHITE);

  Paint_DrawCircle((uint16_t)second_x, (uint16_t)second_y, 10, 0x009688, DOT_PIXEL_2X2, DRAW_FILL_FULL);


  if (tap) {
    if (Touch_CTS816.x_point > 220) {
      CurTime += 15000;
    } else if (Touch_CTS816.x_point < 20) {
      CurTime -= 15000;
    } else if (Touch_CTS816.y_point < 20 && watchSwipe == false) {
      CurTime += 1800000;
    } else if (Touch_CTS816.y_point > 100 && Touch_CTS816.y_point < 200 && watchSwipe == false) {
      CurTime -= 1800000;
    }
  }
  //Paint_DrawRectangle(0, 50, 240, 190, RED, DOT_PIXEL_1X1, DRAW_FILL_FULL);

  renderSnack();
  if (inTransition == false) {
    if (pauseRender == false) {
      LCD_1IN28_DisplayWindows(0, 0, 240, 240, BlackImage);
    }

    //Recommeneded to Open any asked apps After rendering existing scene to prevent double render black bar
    //if(swipe("down",70)){
    //  openApp("main", "UD", Touch_CTS816.y_point);
    //}
  }
}