#ifndef recentApps_H
#define recentApps_H
extern bool inTransition;
extern bool pauseRender;
extern bool tap;
extern bool otherSwipe;
extern bool watchSwipe;
extern std::string runningAppName;
extern bool startup;
extern UWORD *BlackImage;
extern std::list<std::string> backgroundApps;
uint16_t findTextColor(const std::string &text);
bool swipe(std::string dir, int thresh);
void openApp(std::string app, std::string dir, int start);
#endif
#include <cstring>
bool arrowHeld = false;
int centerAppIndex = 0;
int buttonSize = 25;
int backButtonX = 0;
int forwardButtonX = 215;
int buttonY = 120; // Adjust this position as needed


void recentApps() {
    if(startup){
      startup=false;
      if (backgroundApps.size() > 0) {
            centerAppIndex=backgroundApps.size()-1;
        //  centerAppIndex = std::distance(backgroundApps.begin(), backgroundApps.end()) / 2;
      }
    }

    if(centerAppIndex > backgroundApps.size() - 1){
        centerAppIndex = backgroundApps.size() -1;
    } else if(centerAppIndex<0){
        centerAppIndex = 0;
    }

    int startX = 120;
    int startY = 120;
    int sizeIncrement = 20;
    int currentIndex = 0;
    // Render back button
    Paint_DrawRectangle(backButtonX, buttonY - buttonSize / 2, backButtonX + buttonSize, buttonY + 40 / 2, RED, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawString_EN(backButtonX + 5, buttonY - 5, "<", &Font24, WHITE, GREEN);

    // Render forward button
    Paint_DrawRectangle(forwardButtonX, buttonY - buttonSize / 2, forwardButtonX + buttonSize, buttonY + 40 / 2, RED, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawString_EN(forwardButtonX + 5, buttonY - 5, ">", &Font24, WHITE, GREEN);

    for (auto it = backgroundApps.begin(); it != backgroundApps.end(); ++it) {
        if (currentIndex >= centerAppIndex - 1 && currentIndex <= centerAppIndex + 1) {
            int currentX = startX + (currentIndex - centerAppIndex) * 60;
            int currentY = startY;
            int size = 40;

            if (currentIndex == centerAppIndex) {
                size = 70; //60 normally
            }

            Paint_DrawRectangle(currentX - size / 2, currentY - size / 2, currentX + size / 2, currentY + size / 2, findTextColor(it->c_str()), DOT_PIXEL_1X1, DRAW_FILL_FULL);

            Paint_DrawString_EN(currentX - (size/2), currentY - (size/2) - 15, it->c_str(), &Font12, BLACK, 0x009688);

            // Kill button
            //Paint_DrawString_EN(currentX - (size/2), currentY + 20, "Close", &Font12, BLACK, RED);

            if (tap) {
              if(watchSwipe == false && otherSwipe == false && runningAppName=="recentApps"){
                if (Touch_CTS816.x_point >= currentX - (size / 2) && Touch_CTS816.x_point <= currentX + (size / 2) &&
                    Touch_CTS816.y_point >= currentY - (size / 2) && Touch_CTS816.y_point <= currentY + (size / 2)) {
                      tap=false;
                      openApp(it->c_str(), "", 0);
                }
              }
            }
        }
        currentIndex++;
    }

    // Clear All button
    Paint_DrawRectangle(83, 190, 156, 222, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawString_EN(90, 199, "Clear", &Font16, GRAY, RED); //63 char in length


    if (inTransition == false) {
        if (pauseRender == false) {
            LCD_1IN28_DisplayWindows(0, 0, 240, 240, BlackImage);
        }

        if (swipe("down", 70)) {
            openApp("main", "UD", Touch_CTS816.y_point);
        }

        if (tap) {
          if(watchSwipe == false && otherSwipe == false){
            if (Touch_CTS816.x_point >= 83 && Touch_CTS816.x_point <= 156 && Touch_CTS816.y_point >= 190 && Touch_CTS816.y_point <= 222) { //broken currently. I think its the openApp afterwards.
                backgroundApps.clear();
                openApp("main", "DU", 240);
            }
          }
          if (Touch_CTS816.x_point >= backButtonX && Touch_CTS816.x_point <= backButtonX + buttonSize &&
                Touch_CTS816.y_point >= buttonY - 40 / 2 && Touch_CTS816.y_point <= buttonY + 40 / 2) {
                  if(arrowHeld==false){
                    if(centerAppIndex > 0){
                      centerAppIndex--;
                      arrowHeld = true;
                    }
                  }
                // Handle back button tap, navigate to the previous set of apps if available
                // Implement your logic here
            } else if (Touch_CTS816.x_point >= forwardButtonX && Touch_CTS816.x_point <= forwardButtonX + buttonSize &&
                Touch_CTS816.y_point >= buttonY - 40 / 2 && Touch_CTS816.y_point <= buttonY + 40 / 2) {
                  if(arrowHeld==false){
                    if(centerAppIndex < backgroundApps.size() - 1){
                      centerAppIndex++;
                      arrowHeld = true;
                    }
                  }
                // Handle forward button tap, navigate to the next set of apps if available
                // Implement your logic here
            }
        } else {
          arrowHeld = false;
        }
    }
}
