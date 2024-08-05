#ifndef news_H
#define news_H
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
extern UWORD* BlackImage;
typedef void (*ServiceFunction)();
bool swipe(std::string dir, int thresh);
void openApp(std::string app, std::string dir, int start);
void addService(const String& name, ServiceFunction function);

extern std::list<std::string> newsTitle;
#endif

//EXAMPLES:
//LCD_1IN28_DisplayWindows(startX, startY, endX, endY, BlackImage); //Don't change BlackImage
//Paint_DrawString_EN(X, Y, (std::to_string(NUMBER) + "IF YOU WANT TO ADD ANYTHING ELSE").c_str(), &Font12, BLACK, GREEN);
//Paint_DrawString_EN(X, Y, ANY_VARIABLE->c_str(), &Font16, BACKGROUNDCOLOR, TEXTCOLOR);
//Paint_DrawRectangle(XSTART, YSTART, XEND, YEND, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
//Paint_DrawLine(XSTART, YSTART, XEND, YEND, WHITE, DOT_PIXEL_4X4, LINE_STYLE_SOLID);
//Paint_DrawCircle(X, Y, RADIUS, WHITE, DOT_PIXEL_4X4, DRAW_FILL_FULL);
//scrollFunction(NumberOfValues,{},true); //Dont touch {}, or true. The output is a variable called scrollY, When scrolling Nothing should be rendered past x pos 180
//In order to do buttons, you can get the position of the last/current tap with Touch_CTS816.x_point, Touch_CTS816.y_point
//when doing buttons make sure to check that otherSwipe, watchSwipe, and inTransition are all false, and tap is true.

char* removeLastCharacter(char* str) {
  if (str != nullptr && *str != '\0') {  // Check if the string is not null and not empty
    size_t length = strlen(str);         // Get the length of the string
    if (length > 0) {                    // Check if the length is greater than 0
      str[length - 1] = '\0';            // Overwrite the last character with null terminator
    }
  }
  return str;
}


void updateNewsService() {
  Serial.println("running service");
  std::string test = "fetchNews";
  const char* message = test.c_str();
  sendText(message);
}

void news() {
  if (startup) {
    startup = false;
    addService("updateNews", &updateNewsService);
  }
  Paint_DrawRectangle(0, 0, 240, 55, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawString_EN(43.5, 28, "Top Story", &Font24, DARKGRAY, deviceMainColorTheme);
  char* newsTitleCopy = strdup(newsTitle.front().c_str());
  if (strlen(removeLastCharacter(newsTitleCopy)) < 5) {
    Paint_DrawString_EN(10, 70, "Unknown", &Font20, BLACK, RED);
  } else {
    Paint_DrawString_EN(10, 70, removeLastCharacter(newsTitleCopy), &Font16, BLACK, deviceSecondColorTheme);
  }










  renderSnack();
  if (inTransition == false) {
    if (pauseRender == false) {
      LCD_1IN28_DisplayWindows(0, 0, 240, 240, BlackImage);
    }
  }
}