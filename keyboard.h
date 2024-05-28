#include <string>
#ifndef keyboard_H
#define keyboard_H
extern bool inTransition;
extern bool pauseRender;
extern bool tap;
extern int tapHeld;
extern int CurTime;
extern UWORD* BlackImage;
extern std::list<std::string> backgroundApps;
extern std::string keyboardData; //Occurs when Enter Pressed
extern std::string keyboardTyped; //Just in case apps what access to curretnly typed
extern std::string lastUsedAppName;
bool swipe(std::string dir, int thresh);
void openApp(std::string app, std::string dir, int start);
//void sendText(const char* text);
#endif

bool tapDown = false;

//std::string keyboardTyped = "";

//EXAMPLES:
//Paint_DrawString_EN(153, 19, (std::to_string(NUMBER) + "IF YOU WANT TO ADD ANYTHING ELSE").c_str(), &Font12, BLACK, GREEN);
//Paint_DrawString_EN(X, Y, ANY_VARIABLE->c_str(), &Font16, BACKGROUNDCOLOR, TEXTCOLOR);


void renderRow(std::string row[], int rowSize, int keyWidth, int keyHeight, int startX, int startY) {

/*
  for (const auto& notification : notifications) {
    auto title = notification.front();
    if (uniqueTitles.find(title) == uniqueTitles.end()) {
      uniqueTitles.insert(title);
      uniqueNotifications.push_back(notification);
    }
  }
*/

  //FIX TAPPED NOTIF IN FUTUREEEE


  //std::list<std::string> notification = *std::next(uniqueNotifications.begin(), tappedNotif);
  //std::string firstItem = notification.front();
  //std::string lastItem = notification.back();
  //Paint_DrawString_EN(60, 15, lastItem.c_str(), &Font16, BLACK, WHITE);
  Paint_DrawString_EN(50, 35, keyboardTyped.c_str(), &Font16, BLUE, WHITE);
  for (int i = 0; i < rowSize; ++i) {
    if (row[i] != "") {
      int keyStartX = startX + i * (keyWidth + 5);
      int keyEndX = keyStartX + keyWidth;

      int keyStartY = startY;
      int keyEndY = keyStartY + keyHeight;

      if (row[i] == ">>") {
        keyEndX += keyWidth;
        keyStartX += 10;
      }

      Paint_DrawRectangle(keyStartX, keyStartY, keyEndX, keyEndY, DARKGRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);







      int letterX = keyStartX + (keyWidth - 12) / 2;
      int letterY = keyStartY + (keyHeight - 12) / 2;

      if (row[i] == "Space" || row[i] == "<Back") {
        letterX -= 20;
      }

      Paint_DrawString_EN(letterX, letterY, row[i].c_str(), &Font16, DARKGRAY, WHITE);
      if (Touch_CTS816.x_point >= keyStartX - 2 && Touch_CTS816.x_point <= keyStartX + keyWidth + 2 && Touch_CTS816.y_point >= keyStartY - 2 && Touch_CTS816.y_point <= keyStartY + keyHeight + 2) {
        if (tap && tapDown == false) {
          tapDown = true;
          if (row[i] == "<Back") {
            if (keyboardTyped.size() > 0) {
              keyboardTyped.pop_back();
            }
          } else if (row[i] == "Space") {
            keyboardTyped += " ";
          } else if (row[i] == ">>") {
            keyboardData = keyboardTyped;
            keyboardTyped = "";
            openApp(lastUsedAppName,"UD",0);
            /*
            std::string messag = firstItem;  //"8015744494;";
            messag += ";";
            for (char& c : keyboardTyped) {
              c = std::tolower(c);
            }
            messag += keyboardTyped;

            const char* message = messag.c_str();                             // Convert std::string to const char*
            Paint_DrawString_EN(50, 35, "Sending...", &Font16, BLACK, BLUE);  // currently designed to only be used for Messages...
            LCD_1IN28_DisplayWindows(50, 35, 240, 51, BlackImage);
            sendText(message);

            openApp("Messages", "", 0);

            std::list<std::string> newNotification = { firstItem.c_str(), "messages", keyboardTyped, "UserSent" };
            notifications.push_back(newNotification);  //Yes this is how we keep track of convos
            

            keyboardTyped = "";
            */
          } else {
            keyboardTyped += row[i].c_str();
          }
        } else if (tap == false) {
          tapDown = false;
        }
      }
    }
  }
}


void keyboardR() {
  if (startup) {
    startup = false;
    keyboardTyped = "";
    keyboardData = "";
    //pinMode(D27, OUTPUT);  //16
    //pinMode(D28, OUTPUT);  //18 CLOCK!!
    //pinMode(D26, OUTPUT);  //None, Tell other device to listen to me
    //digitalWrite(D28, LOW);
    //digitalWrite(D26, LOW);
    
    
    //pinMode(rxPin, INPUT);
  }
  int keyWidth = 18;
  int keyHeight = 40;
  int rowOffset = 48;  // Adjust this value based on your screen layout

  // Define letters for each row
  std::string row1[] = {
    "Q",
    "W",
    "E",
    "R",
    "T",
    "Y",
    "U",
    "I",
    "O",
    "P",
  };
  std::string row2[] = {
    "A", "S", "D", "F", "G", "H", "J", "K", "L"
  };
  std::string row3[] = {
    "Z", "X", "C", "V", "B", "N", "M", ">>", ""
  };
  std::string row4[] = { "Space", "<Back" };

  // Render keys for each row
  renderRow(row1, sizeof(row1) / sizeof(row1[0]), keyWidth, keyHeight, 4, (rowOffset * 1) + 10);
  renderRow(row2, sizeof(row2) / sizeof(row2[0]), keyWidth, keyHeight, 8, (rowOffset * 2) + 10);
  renderRow(row3, sizeof(row3) / sizeof(row3[0]), keyWidth, keyHeight, 16, (rowOffset * 3) + 10);
  renderRow(row4, 2, 80, 40, 40, 200);  //was 30, 200
  //renderRow(row2, keyWidth, keyHeight, 0, 10+(rowOffset * 2));
  //renderRow(row3, keyWidth, keyHeight, 0, 10+(rowOffset * 3));
  //renderRow(row4, keyWidth, keyHeight, 0, 10+(rowOffset * 4));

  //systemTime();
  if (inTransition == false) {
    //Recommeneded to Open any asked apps After rendering existing scene to prevent double render black bar
    if (swipe("down", 70)) {
      openApp(lastUsedAppName, "UD", Touch_CTS816.y_point);//"Messages"
    }
    if (pauseRender == false) {
      LCD_1IN28_DisplayWindows(0, 0, 240, 51, BlackImage);
    }
  }
}