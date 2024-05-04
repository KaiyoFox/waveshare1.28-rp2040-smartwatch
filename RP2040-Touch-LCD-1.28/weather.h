#ifndef weather_H
#define weather_H
extern bool inTransition;
extern bool pauseRender;
extern bool tap;
extern bool startup;
extern std::string weatherTemp;  //usually Farenheit but will have a C at the end if it is Celcius
extern std::string weatherDesc;  //if either value is Unkown, then.. its uknown and didn't fetch.
extern int CurTime;
extern UWORD* BlackImage;
extern std::list<std::string> backgroundApps;
typedef void (*ServiceFunction)();
bool swipe(std::string dir, int thresh);
void openApp(std::string app, std::string dir, int start);
void addService(const String& name, ServiceFunction function);
#endif

//EXAMPLES:
//Paint_DrawString_EN(X, Y, (std::to_string(NUMBER) + "IF YOU WANT TO ADD ANYTHING ELSE").c_str(), &Font12, BLACK, GREEN);
//Paint_DrawString_EN(X, Y, ANY_VARIABLE->c_str(), &Font16, BACKGROUNDCOLOR, TEXTCOLOR);
//Paint_DrawRectangle(XSTART, YSTART, XEND, YEND, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
//Paint_DrawLine(XSTART, YSTART, XEND, YEND, WHITE, DOT_PIXEL_4X4, LINE_STYLE_SOLID);
//Paint_DrawCircle(X, Y, RADIUS, WHITE, DOT_PIXEL_4X4, DRAW_FILL_FULL);

void updateWeatherService() {
  Serial.println("running service");
  std::string test = "fetchWeather";
  const char* message = test.c_str();
  sendText(message);
}

void weather() {
  if (startup) {
    startup = false;
    addService("updateWeather", &updateWeatherService);
  }
  if (weatherDesc == "Sunny") {
    Paint_DrawCircle(120, 115, 30, GOOD_YELLOW, DOT_PIXEL_4X4, DRAW_FILL_FULL);
    for (int i = 0; i < 12; ++i) {
      int x_end = 120 + static_cast<int>(42 * cos(i * 30 * 3.14159 / 180.0));
      int y_end = 115 + static_cast<int>(42 * sin(i * 30 * 3.14159 / 180.0));
      Paint_DrawLine(120, 115, x_end, y_end, GOOD_YELLOW, DOT_PIXEL_3X3, LINE_STYLE_SOLID);  // Ray
    }
    Paint_DrawString_EN(120 - ((weatherTemp.length() * 17) / 2), 25, weatherTemp.c_str(), &Font24, BLACK, YELLOW);
  } else if (weatherDesc == "Clear") {  //at night
    Paint_DrawCircle(120, 100, 40, GRAY, DOT_PIXEL_4X4, DRAW_FILL_FULL);
    Paint_DrawCircle(135, 100, 35, BLACK, DOT_PIXEL_4X4, DRAW_FILL_FULL);

    Paint_DrawString_EN(120 - ((weatherTemp.length() * 17) / 2), 25, weatherTemp.c_str(), &Font24, BLACK, LIGHT_GRAY);
  } else if (weatherDesc == "Partly cloudy") {
    Paint_DrawCircle(110, 90, 23, GOOD_YELLOW, DOT_PIXEL_4X4, DRAW_FILL_FULL);
    for (int i = 0; i < 12; ++i) {
      int x_end = 110 + static_cast<int>(30 * cos(i * 30 * 3.14159 / 180.0));
      int y_end = 90 + static_cast<int>(30 * sin(i * 30 * 3.14159 / 180.0));
      Paint_DrawLine(110, 90, x_end, y_end, GOOD_YELLOW, DOT_PIXEL_1X1, LINE_STYLE_SOLID);  // Ray
    }


    // Draw cloud icon (example)
    Paint_DrawCircle(89 + 40, 119 - 20, 20, WHITE, DOT_PIXEL_4X4, DRAW_FILL_FULL);  // Top right circle
    Paint_DrawCircle(66 + 40, 135 - 20, 25, WHITE, DOT_PIXEL_4X4, DRAW_FILL_FULL);  // Bottom left circle, slightly larger
    Paint_DrawCircle(81 + 40, 108 - 20, 15, WHITE, DOT_PIXEL_4X4, DRAW_FILL_FULL);  // Smaller circle between the two
    Paint_DrawCircle(98 + 40, 126 - 20, 20, WHITE, DOT_PIXEL_4X4, DRAW_FILL_FULL);

    Paint_DrawString_EN(120 - ((weatherTemp.length() * 17) / 2), 25, weatherTemp.c_str(), &Font24, BLACK, LIGHT_GRAY);

  } else if (weatherDesc == "Cloudy" || weatherDesc == "Thundery outbreaks possible") {
    // Draw cloud icon (example)
    Paint_DrawCircle(89 + 40, 119 - 20, 20, GRAY, DOT_PIXEL_4X4, DRAW_FILL_FULL);  // Top right circle
    Paint_DrawCircle(66 + 40, 135 - 20, 25, GRAY, DOT_PIXEL_4X4, DRAW_FILL_FULL);  // Bottom left circle, slightly larger
    Paint_DrawCircle(81 + 40, 108 - 20, 15, GRAY, DOT_PIXEL_4X4, DRAW_FILL_FULL);  // Smaller circle between the two
    Paint_DrawCircle(98 + 40, 126 - 20, 20, GRAY, DOT_PIXEL_4X4, DRAW_FILL_FULL);

    Paint_DrawString_EN(120 - ((weatherTemp.length() * 17) / 2), 25, weatherTemp.c_str(), &Font24, BLACK, GRAY);

  } else if (weatherDesc == "Overcast") {
    // Draw cloud icon (example)
    Paint_DrawCircle(89 + 40, 119 - 20, 20, LIGHT_GRAY, DOT_PIXEL_4X4, DRAW_FILL_FULL);  // Top right circle
    Paint_DrawCircle(66 + 40, 135 - 20, 25, LIGHT_GRAY, DOT_PIXEL_4X4, DRAW_FILL_FULL);  // Bottom left circle, slightly larger
    Paint_DrawCircle(81 + 40, 108 - 20, 15, LIGHT_GRAY, DOT_PIXEL_4X4, DRAW_FILL_FULL);  // Smaller circle between the two
    Paint_DrawCircle(98 + 40, 126 - 20, 20, LIGHT_GRAY, DOT_PIXEL_4X4, DRAW_FILL_FULL);

    Paint_DrawString_EN(120 - ((weatherTemp.length() * 17) / 2), 25, weatherTemp.c_str(), &Font24, BLACK, LIGHT_GRAY);

  } else if (weatherDesc == "Mist") {
    // fog
    //Paint_DrawLine(100+posX, 80+posY, 140+posX, 85+posY, WHITE, DOT_PIXEL_3X3, LINE_STYLE_SOLID);
    //Paint_DrawLine(100+posX, 90+posY, 140+posX, 95+posY, WHITE, DOT_PIXEL_3X3, LINE_STYLE_SOLID);
    //Paint_DrawLine(100+posX, 100+posY, 140+posX, 105+posY, WHITE, DOT_PIXEL_3X3, LINE_STYLE_SOLID);
    //Paint_DrawLine(100+posX, 110+posY, 140+posX, 115+posY, WHITE, DOT_PIXEL_3X3, LINE_STYLE_SOLID);
    int posX = -20;
    int posY = -20;
    Paint_DrawLine(100 + posX, 80 + posY, 140 + posX, 85 + posY, BLUE, DOT_PIXEL_3X3, LINE_STYLE_SOLID);
    Paint_DrawLine(100 + posX, 90 + posY, 140 + posX, 95 + posY, WHITE, DOT_PIXEL_3X3, LINE_STYLE_SOLID);
    Paint_DrawLine(100 + posX, 100 + posY, 140 + posX, 105 + posY, BLUE, DOT_PIXEL_3X3, LINE_STYLE_SOLID);
    Paint_DrawLine(100 + posX, 110 + posY, 140 + posX, 115 + posY, WHITE, DOT_PIXEL_3X3, LINE_STYLE_SOLID);
    posY = 20;
    Paint_DrawLine(100 + posX, 80 + posY, 140 + posX, 85 + posY, WHITE, DOT_PIXEL_3X3, LINE_STYLE_SOLID);
    Paint_DrawLine(100 + posX, 90 + posY, 140 + posX, 95 + posY, BLUE, DOT_PIXEL_3X3, LINE_STYLE_SOLID);
    Paint_DrawLine(100 + posX, 100 + posY, 140 + posX, 105 + posY, WHITE, DOT_PIXEL_3X3, LINE_STYLE_SOLID);
    Paint_DrawLine(100 + posX, 110 + posY, 140 + posX, 115 + posY, BLUE, DOT_PIXEL_3X3, LINE_STYLE_SOLID);
    posX = 20;
    Paint_DrawLine(100 + posX, 80 + posY, 140 + posX, 85 + posY, BLUE, DOT_PIXEL_3X3, LINE_STYLE_SOLID);
    Paint_DrawLine(100 + posX, 90 + posY, 140 + posX, 95 + posY, WHITE, DOT_PIXEL_3X3, LINE_STYLE_SOLID);
    Paint_DrawLine(100 + posX, 100 + posY, 140 + posX, 105 + posY, BLUE, DOT_PIXEL_3X3, LINE_STYLE_SOLID);
    Paint_DrawLine(100 + posX, 110 + posY, 140 + posX, 115 + posY, WHITE, DOT_PIXEL_3X3, LINE_STYLE_SOLID);
    posY = -20;
    Paint_DrawLine(100 + posX, 80 + posY, 140 + posX, 85 + posY, WHITE, DOT_PIXEL_3X3, LINE_STYLE_SOLID);
    Paint_DrawLine(100 + posX, 90 + posY, 140 + posX, 95 + posY, BLUE, DOT_PIXEL_3X3, LINE_STYLE_SOLID);
    Paint_DrawLine(100 + posX, 100 + posY, 140 + posX, 105 + posY, WHITE, DOT_PIXEL_3X3, LINE_STYLE_SOLID);
    Paint_DrawLine(100 + posX, 110 + posY, 140 + posX, 115 + posY, BLUE, DOT_PIXEL_3X3, LINE_STYLE_SOLID);


    Paint_DrawString_EN(120 - ((weatherTemp.length() * 17) / 2), 25, weatherTemp.c_str(), &Font24, BLACK, BLUE);

  } else if (weatherDesc == "Fog") {
    // fog
    //Paint_DrawLine(100+posX, 80+posY, 140+posX, 85+posY, WHITE, DOT_PIXEL_3X3, LINE_STYLE_SOLID);
    //Paint_DrawLine(100+posX, 90+posY, 140+posX, 95+posY, WHITE, DOT_PIXEL_3X3, LINE_STYLE_SOLID);
    //Paint_DrawLine(100+posX, 100+posY, 140+posX, 105+posY, WHITE, DOT_PIXEL_3X3, LINE_STYLE_SOLID);
    //Paint_DrawLine(100+posX, 110+posY, 140+posX, 115+posY, WHITE, DOT_PIXEL_3X3, LINE_STYLE_SOLID);
    int posX = -20;
    int posY = -20;
    Paint_DrawLine(100 + posX, 80 + posY, 140 + posX, 85 + posY, LIGHT_GRAY, DOT_PIXEL_3X3, LINE_STYLE_SOLID);
    Paint_DrawLine(100 + posX, 90 + posY, 140 + posX, 95 + posY, WHITE, DOT_PIXEL_3X3, LINE_STYLE_SOLID);
    Paint_DrawLine(100 + posX, 100 + posY, 140 + posX, 105 + posY, LIGHT_GRAY, DOT_PIXEL_3X3, LINE_STYLE_SOLID);
    Paint_DrawLine(100 + posX, 110 + posY, 140 + posX, 115 + posY, WHITE, DOT_PIXEL_3X3, LINE_STYLE_SOLID);
    posY = 20;
    Paint_DrawLine(100 + posX, 80 + posY, 140 + posX, 85 + posY, WHITE, DOT_PIXEL_3X3, LINE_STYLE_SOLID);
    Paint_DrawLine(100 + posX, 90 + posY, 140 + posX, 95 + posY, LIGHT_GRAY, DOT_PIXEL_3X3, LINE_STYLE_SOLID);
    Paint_DrawLine(100 + posX, 100 + posY, 140 + posX, 105 + posY, WHITE, DOT_PIXEL_3X3, LINE_STYLE_SOLID);
    Paint_DrawLine(100 + posX, 110 + posY, 140 + posX, 115 + posY, LIGHT_GRAY, DOT_PIXEL_3X3, LINE_STYLE_SOLID);
    posX = 20;
    Paint_DrawLine(100 + posX, 80 + posY, 140 + posX, 85 + posY, LIGHT_GRAY, DOT_PIXEL_3X3, LINE_STYLE_SOLID);
    Paint_DrawLine(100 + posX, 90 + posY, 140 + posX, 95 + posY, WHITE, DOT_PIXEL_3X3, LINE_STYLE_SOLID);
    Paint_DrawLine(100 + posX, 100 + posY, 140 + posX, 105 + posY, LIGHT_GRAY, DOT_PIXEL_3X3, LINE_STYLE_SOLID);
    Paint_DrawLine(100 + posX, 110 + posY, 140 + posX, 115 + posY, WHITE, DOT_PIXEL_3X3, LINE_STYLE_SOLID);
    posY = -20;
    Paint_DrawLine(100 + posX, 80 + posY, 140 + posX, 85 + posY, WHITE, DOT_PIXEL_3X3, LINE_STYLE_SOLID);
    Paint_DrawLine(100 + posX, 90 + posY, 140 + posX, 95 + posY, LIGHT_GRAY, DOT_PIXEL_3X3, LINE_STYLE_SOLID);
    Paint_DrawLine(100 + posX, 100 + posY, 140 + posX, 105 + posY, WHITE, DOT_PIXEL_3X3, LINE_STYLE_SOLID);
    Paint_DrawLine(100 + posX, 110 + posY, 140 + posX, 115 + posY, LIGHT_GRAY, DOT_PIXEL_3X3, LINE_STYLE_SOLID);


    Paint_DrawString_EN(120 - ((weatherTemp.length() * 17) / 2), 25, weatherTemp.c_str(), &Font24, BLACK, LIGHT_GRAY);


  } else if (weatherDesc == "Freezing fog") {
    // fog
    //Paint_DrawLine(100+posX, 80+posY, 140+posX, 85+posY, WHITE, DOT_PIXEL_3X3, LINE_STYLE_SOLID);
    //Paint_DrawLine(100+posX, 90+posY, 140+posX, 95+posY, WHITE, DOT_PIXEL_3X3, LINE_STYLE_SOLID);
    //Paint_DrawLine(100+posX, 100+posY, 140+posX, 105+posY, WHITE, DOT_PIXEL_3X3, LINE_STYLE_SOLID);
    //Paint_DrawLine(100+posX, 110+posY, 140+posX, 115+posY, WHITE, DOT_PIXEL_3X3, LINE_STYLE_SOLID);
    int posX = -20;
    int posY = -20;
    Paint_DrawLine(100 + posX, 80 + posY, 140 + posX, 85 + posY, WHITE, DOT_PIXEL_3X3, LINE_STYLE_SOLID);
    Paint_DrawLine(100 + posX, 90 + posY, 140 + posX, 95 + posY, WHITE, DOT_PIXEL_3X3, LINE_STYLE_SOLID);
    Paint_DrawLine(100 + posX, 100 + posY, 140 + posX, 105 + posY, WHITE, DOT_PIXEL_3X3, LINE_STYLE_SOLID);
    Paint_DrawLine(100 + posX, 110 + posY, 140 + posX, 115 + posY, WHITE, DOT_PIXEL_3X3, LINE_STYLE_SOLID);
    posY = 20;
    Paint_DrawLine(100 + posX, 80 + posY, 140 + posX, 85 + posY, WHITE, DOT_PIXEL_3X3, LINE_STYLE_SOLID);
    Paint_DrawLine(100 + posX, 90 + posY, 140 + posX, 95 + posY, BLUE, DOT_PIXEL_3X3, LINE_STYLE_SOLID);
    Paint_DrawLine(100 + posX, 100 + posY, 140 + posX, 105 + posY, WHITE, DOT_PIXEL_3X3, LINE_STYLE_SOLID);
    Paint_DrawLine(100 + posX, 110 + posY, 140 + posX, 115 + posY, BLUE, DOT_PIXEL_3X3, LINE_STYLE_SOLID);
    posX = 20;
    Paint_DrawLine(100 + posX, 80 + posY, 140 + posX, 85 + posY, WHITE, DOT_PIXEL_3X3, LINE_STYLE_SOLID);
    Paint_DrawLine(100 + posX, 90 + posY, 140 + posX, 95 + posY, WHITE, DOT_PIXEL_3X3, LINE_STYLE_SOLID);
    Paint_DrawLine(100 + posX, 100 + posY, 140 + posX, 105 + posY, WHITE, DOT_PIXEL_3X3, LINE_STYLE_SOLID);
    Paint_DrawLine(100 + posX, 110 + posY, 140 + posX, 115 + posY, WHITE, DOT_PIXEL_3X3, LINE_STYLE_SOLID);
    posY = -20;
    Paint_DrawLine(100 + posX, 80 + posY, 140 + posX, 85 + posY, WHITE, DOT_PIXEL_3X3, LINE_STYLE_SOLID);
    Paint_DrawLine(100 + posX, 90 + posY, 140 + posX, 95 + posY, BLUE, DOT_PIXEL_3X3, LINE_STYLE_SOLID);
    Paint_DrawLine(100 + posX, 100 + posY, 140 + posX, 105 + posY, WHITE, DOT_PIXEL_3X3, LINE_STYLE_SOLID);
    Paint_DrawLine(100 + posX, 110 + posY, 140 + posX, 115 + posY, BLUE, DOT_PIXEL_3X3, LINE_STYLE_SOLID);


    Paint_DrawLine(66 + 35, 145 + 0, 80 + 35, 155 + 0, WHITE, DOT_PIXEL_3X3, LINE_STYLE_SOLID);
    Paint_DrawLine(81 + 45, 118 + 20, 92 + 45, 129 + 20, WHITE, DOT_PIXEL_3X3, LINE_STYLE_SOLID);
    Paint_DrawLine(98 + 50, 136 - 5, 110 + 50, 146 - 5, WHITE, DOT_PIXEL_3X3, LINE_STYLE_SOLID);
    Paint_DrawCircle(98 + 60, 136 + 10, 2, WHITE, DOT_PIXEL_4X4, DRAW_FILL_FULL);
    Paint_DrawCircle(80 + 40, 120 + 5, 3, WHITE, DOT_PIXEL_4X4, DRAW_FILL_FULL);
    Paint_DrawCircle(80, 150, 2, WHITE, DOT_PIXEL_4X4, DRAW_FILL_FULL);

    Paint_DrawString_EN(120 - ((weatherTemp.length() * 17) / 2), 25, weatherTemp.c_str(), &Font24, BLACK, LIGHT_GRAY);


  } else if (weatherDesc == "Rainy" || weatherDesc == "Patchy rain possible" || weatherDesc == "Light rain shower" || weatherDesc == "Patchy light rain with thunder" || weatherDesc == "Moderate or heavy rain shower" || weatherDesc == "Torrential rain shower" || weatherDesc == "Patchy light drizzle" || weatherDesc == "Light drizzle" || weatherDesc == "Patchy light rain" || weatherDesc == "Light rain" || weatherDesc == "Moderate rain at times" || weatherDesc == "Moderate rain" || weatherDesc == "Heavy rain at times" || weatherDesc == "Heavy rain" || weatherDesc == "Moderate or heavy rain with thunder") {
    // Draw rain icon (example)

    Paint_DrawCircle(89 + 40, 119 - 20, 20, BLUE, DOT_PIXEL_4X4, DRAW_FILL_FULL);        // Top right circle
    Paint_DrawCircle(66 + 40, 135 - 20, 25, LIGHT_GRAY, DOT_PIXEL_4X4, DRAW_FILL_FULL);  // Bottom left circle, slightly larger
    Paint_DrawCircle(81 + 40, 108 - 20, 15, GRAY, DOT_PIXEL_4X4, DRAW_FILL_FULL);        // Smaller circle between the two
    Paint_DrawCircle(98 + 40, 126 - 20, 20, LIGHT_GRAY, DOT_PIXEL_4X4, DRAW_FILL_FULL);


    Paint_DrawLine(66 + 35, 145 + 0, 80 + 35, 155 + 0, BLUE, DOT_PIXEL_3X3, LINE_STYLE_SOLID);
    Paint_DrawLine(81 + 45, 118 + 20, 92 + 45, 129 + 20, BLUE, DOT_PIXEL_3X3, LINE_STYLE_SOLID);
    Paint_DrawLine(98 + 50, 136 - 5, 110 + 50, 146 - 5, BLUE, DOT_PIXEL_3X3, LINE_STYLE_SOLID);


    Paint_DrawString_EN(120 - ((weatherTemp.length() * 17) / 2), 25, weatherTemp.c_str(), &Font24, BLACK, BLUE);

  } else if (weatherDesc == "Snowy" || weatherDesc == "Patchy light snow with thunder" || weatherDesc == "Moderate or heavy snow with thunder" || weatherDesc == "Light snow showers" || weatherDesc == "Moderate or heavy snow showers" || weatherDesc == "Patchy snow possible" || weatherDesc == "Patchy light snow" || weatherDesc == "Light snow" || weatherDesc == "Patchy moderate snow" || weatherDesc == "Moderate snow" || weatherDesc == "Patchy heavy snow" || weatherDesc == "Heavy snow") {
    // Draw rain icon (example)

    Paint_DrawCircle(89 + 40, 119 - 20, 20, WHITE, DOT_PIXEL_4X4, DRAW_FILL_FULL);       // Top right circle
    Paint_DrawCircle(66 + 40, 135 - 20, 25, LIGHT_GRAY, DOT_PIXEL_4X4, DRAW_FILL_FULL);  // Bottom left circle, slightly larger
    Paint_DrawCircle(81 + 40, 108 - 20, 15, WHITE, DOT_PIXEL_4X4, DRAW_FILL_FULL);       // Smaller circle between the two
    Paint_DrawCircle(98 + 40, 126 - 20, 20, LIGHT_GRAY, DOT_PIXEL_4X4, DRAW_FILL_FULL);


    Paint_DrawLine(66 + 35, 145 + 0, 80 + 35, 155 + 0, WHITE, DOT_PIXEL_3X3, LINE_STYLE_SOLID);
    Paint_DrawLine(81 + 45, 118 + 20, 92 + 45, 129 + 20, WHITE, DOT_PIXEL_3X3, LINE_STYLE_SOLID);
    Paint_DrawLine(98 + 50, 136 - 5, 110 + 50, 146 - 5, WHITE, DOT_PIXEL_3X3, LINE_STYLE_SOLID);
    Paint_DrawCircle(98 + 60, 136 + 10, 2, WHITE, DOT_PIXEL_4X4, DRAW_FILL_FULL);
    Paint_DrawCircle(80 + 40, 120 + 5, 3, WHITE, DOT_PIXEL_4X4, DRAW_FILL_FULL);
    Paint_DrawCircle(80, 150, 2, WHITE, DOT_PIXEL_4X4, DRAW_FILL_FULL);

    Paint_DrawString_EN(120 - ((weatherTemp.length() * 17) / 2), 25, weatherTemp.c_str(), &Font24, BLACK, WHITE);

  } else if (weatherDesc == "Blizzard" || weatherDesc == "Blowing snow") {
    // Draw rain icon (example)

    Paint_DrawCircle(89 + 40, 119 - 20, 20, WHITE, DOT_PIXEL_4X4, DRAW_FILL_FULL);       // Top right circle
    Paint_DrawCircle(66 + 40, 135 - 20, 25, LIGHT_GRAY, DOT_PIXEL_4X4, DRAW_FILL_FULL);  // Bottom left circle, slightly larger
    Paint_DrawCircle(81 + 40, 108 - 20, 15, WHITE, DOT_PIXEL_4X4, DRAW_FILL_FULL);       // Smaller circle between the two
    Paint_DrawCircle(98 + 40, 126 - 20, 20, LIGHT_GRAY, DOT_PIXEL_4X4, DRAW_FILL_FULL);


    Paint_DrawLine(66 + 35, 145 + 0, 80 + 35, 155 + 0, WHITE, DOT_PIXEL_3X3, LINE_STYLE_SOLID);
    Paint_DrawLine(81 + 45, 118 + 20, 92 + 45, 129 + 20, WHITE, DOT_PIXEL_3X3, LINE_STYLE_SOLID);
    Paint_DrawLine(98 + 50, 136 - 5, 110 + 50, 146 - 5, WHITE, DOT_PIXEL_3X3, LINE_STYLE_SOLID);
    Paint_DrawLine(66 + 40, 145 + 10, 80 + 40, 155 + 10, WHITE, DOT_PIXEL_3X3, LINE_STYLE_SOLID);
    Paint_DrawLine(81 + 32, 118 + 28, 92 + 32, 129 + 28, WHITE, DOT_PIXEL_3X3, LINE_STYLE_SOLID);
    Paint_DrawLine(98 + 54, 136 - 0, 110 + 54, 146 - 0, WHITE, DOT_PIXEL_3X3, LINE_STYLE_SOLID);


    Paint_DrawString_EN(120 - ((weatherTemp.length() * 17) / 2), 25, weatherTemp.c_str(), &Font24, BLACK, LIGHT_GRAY);

  } else if (weatherDesc == "Sleet" || weatherDesc == "Light sleet showers" || weatherDesc == "Moderate or heavy sleet showers" || weatherDesc == "Patchy sleet possible" || weatherDesc == "Light sleet" || weatherDesc == "Moderate or heavy sleet" || weatherDesc == "Ice pellets" || weatherDesc == "Light showers of ice pellets" || weatherDesc == "Moderate or heavy showers of ice pellets") {
    // Draw rain icon (example)

    Paint_DrawCircle(89 + 40, 119 - 20, 20, LIGHT_GRAY, DOT_PIXEL_4X4, DRAW_FILL_FULL);  // Top right circle
    Paint_DrawCircle(66 + 40, 135 - 20, 25, GRAY, DOT_PIXEL_4X4, DRAW_FILL_FULL);        // Bottom left circle, slightly larger
    Paint_DrawCircle(81 + 40, 108 - 20, 15, GRAY, DOT_PIXEL_4X4, DRAW_FILL_FULL);        // Smaller circle between the two
    Paint_DrawCircle(98 + 40, 126 - 20, 20, LIGHT_GRAY, DOT_PIXEL_4X4, DRAW_FILL_FULL);


    Paint_DrawLine(66 + 35, 145 + 0, 80 + 35, 155 + 0, WHITE, DOT_PIXEL_3X3, LINE_STYLE_SOLID);
    Paint_DrawLine(81 + 45, 118 + 20, 92 + 45, 129 + 20, WHITE, DOT_PIXEL_3X3, LINE_STYLE_SOLID);
    Paint_DrawLine(98 + 50, 136 - 5, 110 + 50, 146 - 5, WHITE, DOT_PIXEL_3X3, LINE_STYLE_SOLID);
    Paint_DrawCircle(98 + 60, 136 + 10, 4, WHITE, DOT_PIXEL_4X4, DRAW_FILL_FULL);
    Paint_DrawCircle(80 + 40, 120 + 5, 5, WHITE, DOT_PIXEL_4X4, DRAW_FILL_FULL);
    Paint_DrawCircle(80, 150, 3, WHITE, DOT_PIXEL_4X4, DRAW_FILL_FULL);

    Paint_DrawString_EN(120 - ((weatherTemp.length() * 17) / 2), 25, weatherTemp.c_str(), &Font24, BLACK, GRAY);

  } else if (weatherDesc == "Freezing drizzle" || weatherDesc == "Patchy freezing drizzle possible" || weatherDesc == "Heavy freezing drizzle" || weatherDesc == "Light freezing rain" || weatherDesc == "Moderate or heavy freezing rain") {
    // Draw rain icon (example)

    Paint_DrawCircle(89 + 40, 119 - 20, 20, LIGHT_GRAY, DOT_PIXEL_4X4, DRAW_FILL_FULL);  // Top right circle
    Paint_DrawCircle(66 + 40, 135 - 20, 25, LIGHT_GRAY, DOT_PIXEL_4X4, DRAW_FILL_FULL);  // Bottom left circle, slightly larger
    Paint_DrawCircle(81 + 40, 108 - 20, 15, LIGHT_GRAY, DOT_PIXEL_4X4, DRAW_FILL_FULL);  // Smaller circle between the two
    Paint_DrawCircle(98 + 40, 126 - 20, 20, LIGHT_GRAY, DOT_PIXEL_4X4, DRAW_FILL_FULL);


    Paint_DrawLine(66 + 35, 145 + 0, 80 + 35, 155 + 0, BLUE, DOT_PIXEL_3X3, LINE_STYLE_SOLID);
    Paint_DrawLine(81 + 45, 118 + 20, 92 + 45, 129 + 20, WHITE, DOT_PIXEL_3X3, LINE_STYLE_SOLID);
    Paint_DrawLine(98 + 50, 136 - 5, 110 + 50, 146 - 5, BLUE, DOT_PIXEL_3X3, LINE_STYLE_SOLID);
    Paint_DrawCircle(98 + 60, 136 + 10, 4, WHITE, DOT_PIXEL_4X4, DRAW_FILL_FULL);
    Paint_DrawCircle(80 + 40, 120 + 5, 5, BLUE, DOT_PIXEL_4X4, DRAW_FILL_FULL);
    Paint_DrawCircle(80, 150, 3, WHITE, DOT_PIXEL_4X4, DRAW_FILL_FULL);

    Paint_DrawString_EN(120 - ((weatherTemp.length() * 17) / 2), 25, weatherTemp.c_str(), &Font24, BLACK, BLUE);


  } else {
    Paint_DrawString_EN(120 - ((weatherTemp.length() * 17) / 2), 120, weatherTemp.c_str(), &Font24, BLACK, RED);
  }
  Paint_DrawString_EN(120 - ((weatherDesc.length() * 11) / 2), 160, weatherDesc.c_str(), &Font16, BLACK, GRAY);

  if (inTransition == false) {
    if (lastUsedAppName == "main") {
      if (swipe("left", 70)) {
        if (std::find(backgroundApps.begin(), backgroundApps.end(), runningAppName) != backgroundApps.end()) {
          backgroundApps.remove(runningAppName);
        }
        openApp("main", "RL", Touch_CTS816.x_point);
      }
    }
    if (pauseRender == false) {
      LCD_1IN28_DisplayWindows(0, 0, 240, 240, BlackImage);
    }
  }
}
