#ifndef findMyPhone_H
#define findMyPhone_H
extern bool inTransition;
extern bool watchSwipe;
extern bool otherSwipe;
extern bool pauseRender;
extern bool tap;
extern bool startup;
extern uint16_t deviceMainColorTheme;
extern uint16_t deviceSecondColorTheme;
extern uint16_t deviceThirdColorTheme;
extern const char* message;
extern int scrollY;
extern UWORD* BlackImage;
bool swipe(std::string dir, int thresh);
void openApp(std::string app, std::string dir, int start);
void sendText(const char* text);
#endif

//EXAMPLES:
//LCD_1IN28_DisplayWindows(startX, startY, endX, endY, BlackImage); //Don't change BlackImage
//Paint_DrawString_EN(X, Y, (std::to_string(NUMBER) + "IF YOU WANT TO ADD ANYTHING ELSE").c_str(), &Font12, BLACK, GREEN);
//Paint_DrawString_EN(X, Y, ANY_VARIABLE->c_str(), &Font16, BACKGROUNDCOLOR, TEXTCOLOR);
//Paint_DrawRectangle(XSTART, YSTART, XEND, YEND, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
//Paint_DrawLine(XSTART, YSTART, XEND, YEND, WHITE, DOT_PIXEL_4X4, LINE_STYLE_SOLID);
//Paint_DrawCircle(X, Y, RADIUS, WHITE, DOT_PIXEL_4X4, DRAW_FILL_FULL);
//scrollFunction(NumberOfValues,{},true); //Dont touch {}, or true. The output is a variable called scrollY, When scrolling Nothing should be rendered past x 180
//In order to do buttons, you can get the position of the last/current tap with Touch_CTS816.x_point, Touch_CTS816.y_point
//when doing buttons make sure to check that otherSwipe, watchSwipe, and inTransition are all false, and tap is true.

bool ringing = false;
//const char* message = "";

void findMyPhone() {
  if (ringing) {
    Paint_DrawRectangle(0, 0, 240, 240, YELLOW, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawString_EN(4, 108, "Phone ringing", &Font24, YELLOW, BLACK);
  } else {
    Paint_DrawString_EN(33, 108, "Ring Phone", &Font24, BLACK, WHITE);
  }

  Paint_DrawEdgeEffect();

  renderSnack();
  if (inTransition == false) {
    if (pauseRender == false) {
      LCD_1IN28_DisplayWindows(0, 0, 240, 240, BlackImage);
    }

    if (tap && tapHeld < 1) {
      if (ringing) {
        ringing = false;
        std::string test = "stopRing";
        message = test.c_str();
        sendText(message);
      } else {
        ringing = true;
        std::string test = "ring";
        message = test.c_str();
        sendText(message);
      }
    }
  }
}