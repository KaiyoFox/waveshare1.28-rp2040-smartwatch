#ifndef messages_H
#define messages_H
extern bool inTransition;
extern bool pauseRender;
extern bool tap;
extern bool startup;
extern int CurTime;
extern int tappedNotif;
extern bool otherSwipe;
extern bool watchSwipe;
extern UWORD *BlackImage;
extern std::list<std::string> backgroundApps;
extern std::list<std::list<std::string>> notifications;
bool swipe(std::string dir, int thresh);
void openApp(std::string app, std::string dir, int start);
bool button(int x, int y, const char *text, sFONT *Font, UWORD Color_Foreground, UWORD Color_Background, int size);
#endif

//EXAMPLES:
//Paint_DrawString_EN(153, 19, (std::to_string(NUMBER) + "IF YOU WANT TO ADD ANYTHING ELSE").c_str(), &Font12, BLACK, GREEN);
//Paint_DrawString_EN(X, Y, ANY_VARIABLE->c_str(), &Font16, BACKGROUNDCOLOR, TEXTCOLOR);

extern std::list<std::list<std::string>> foundContacts;

std::string tappedPhoneNumber = "";

void messages() {
  if (startup) {
    Serial.begin(9600);
    startup = false;
    scrollY = 0;

    if (keyboardData != "") {



      for (const auto &notification : notifications) {
        auto title = notification.front();
        if (uniqueTitles.find(title) == uniqueTitles.end()) {
          uniqueTitles.insert(title);
          uniqueNotifications.push_back(notification);
        }
      }

      //FIX TAPPED NOTIF IN FUTUREEEE


      std::list<std::string> notification = *std::next(uniqueNotifications.begin(), tappedNotif);
      std::string firstItem = notification.front();
      std::string lastItem = notification.back();






      std::string messag = firstItem;  //"8015744494;";
      messag += ";";
      for (char &c : keyboardData) {
        c = std::tolower(c);
      }
      messag += keyboardData;

      const char *message = messag.c_str();                             // Convert std::string to const char*
      Paint_DrawString_EN(50, 35, "Sending...", &Font16, BLACK, BLUE);  // currently designed to only be used for Messages...
      LCD_1IN28_DisplayWindows(50, 35, 240, 51, BlackImage);
      sendText(message);

      //openApp("Messages", "", 0);
      keyboardData = "";

      std::list<std::string> newNotification = { firstItem.c_str(), "messages", keyboardTyped, "UserSent" };
      notifications.push_back(newNotification);  //Yes this is how we keep track of convos
    }
  }
  if (tappedNotif >= notifications.size()) {
    tappedNotif = -1;
  }
  if (notifications.size() < 0) {
    tappedNotif = -1;
  }
  if (tappedNotif == -1) {  // && tappedPhoneNumber == ""
    Paint_DrawString_EN(76, 10, "Messages", &Font16, BLACK, BLUE);

    // Display foundContacts
    int contactY = 40;
    scrollFunction(foundContacts.size(), {}, true);
    int scrollOffset = (scrollY / 240.0) * (foundContacts.size() * (45 + 5));  //*35

    //int scrollYModded = (scrollY / 240.0) * (totalHeight + 20);  // + (itemHeights.size() * spacing)

    for (const auto &contact : foundContacts) {
      //Paint_DrawString_EN(50, contactY-scrollOffset, contact.front().c_str(), &Font24, BLACK, GREEN);

      //if (tap && inTransition == false && pauseRender == false && watchSwipe == false &&
      //Touch_CTS816.x_point >= 50 && Touch_CTS816.x_point <= 200 && Touch_CTS816.y_point-scrollOffset >= contactY && Touch_CTS816.y_point-scrollOffset <= contactY + 28) {
      if (button(10, contactY - scrollOffset, contact.front().c_str(), &Font20, DARKGRAY, WHITE, 1)) {
        bool containsNotification = false;
        auto targetFirstTwoItems = std::list<std::string>{ contact.back().c_str(), "Messages" };
        int currentIndex = 0;
        int foundIndex = -1;
        for (const auto &notification : notifications) {
          if (std::equal(targetFirstTwoItems.begin(), targetFirstTwoItems.end(), notification.begin())) {
            containsNotification = true;
            break;
          }
        }
        if (containsNotification == false) {
          notifications.push_back({ contact.back().c_str(), "Messages", "", contact.front().c_str() });
        }
        for (const auto &notification : notifications) {
          auto title = notification.front();
          if (uniqueTitles.find(title) == uniqueTitles.end()) {
            uniqueTitles.insert(title);
            uniqueNotifications.push_back(notification);
          }
        }
        currentIndex = 0;
        for (const auto &notification : uniqueNotifications) {
          //if (notification == targetNotification) {
          if (std::equal(targetFirstTwoItems.begin(), targetFirstTwoItems.end(), notification.begin())) {
            foundIndex = currentIndex;
            break;
          }
          currentIndex++;
        }
        tappedNotif = foundIndex;  //uniqueNotifications.size()-1;
                                   //tappedPhoneNumber = contact.back().c_str(); // Assuming the phone number is the last element in the contact list
      }
      contactY += 45 + 5;
    }
  } else {


    for (const auto &notification : notifications) {
      auto title = notification.front();
      if (uniqueTitles.find(title) == uniqueTitles.end()) {
        uniqueTitles.insert(title);
        uniqueNotifications.push_back(notification);
      }
    }

    std::list<std::string> selectedNotification = *std::next(uniqueNotifications.begin(), tappedNotif);
    std::string selectedTitle;

    if (!selectedNotification.empty()) {
      selectedTitle = selectedNotification.front();
    }

    int notifPreviewY = 20;

    // Draw the text
    Paint_DrawString_EN((240 - selectedNotification.back().size() * 11) / 2, 2, selectedNotification.back().c_str(), &Font16, BLACK, BLUE);

    int lineHeight = 18;

    int totalTextHeight = notifications.size() * lineHeight;
    int scrollOffset = 0;  //(totalTextHeight - 190);//(totalTextHeight > 190) ? (totalTextHeight - 190) : 0;

    notifPreviewY = 190 - lineHeight;  // Start rendering from the bottom of the display

    for (auto notificationIter = notifications.rbegin(); notificationIter != notifications.rend(); ++notificationIter) {
      const auto &notification = *notificationIter;

      if (!notification.empty() && notification.front() == selectedTitle) {
        if (notification.size() >= 3) {
          std::string content = *std::next(notification.begin(), 2);
          std::string special = *std::next(notification.begin(), 3);

          // Display content part
          if (!content.empty() && notifPreviewY - scrollOffset > 20) {
            // Render the text with the scroll offset applied
            if (special == "UserSent") {
              Paint_DrawString_EN(max(0, (240 - 30) - (11 * content.length())), notifPreviewY - scrollOffset, content.c_str(), &Font16, BLACK, BLUE);
              if ((240 - 30) - (11 * content.length()) < 0) {
                notifPreviewY -= 16;  //should do math for more than 2 lines
              }
            } else {
              Paint_DrawString_EN(30, notifPreviewY - scrollOffset, content.c_str(), &Font16, BLACK, WHITE);
              if (11 * content.length() > 240) {
                notifPreviewY -= 16;
              }
            }

            // Update the Y position for the next notification
            notifPreviewY -= lineHeight;
            if (notifPreviewY < 20) {
              break;  // Stop rendering if the top of the display is reached
            }
          } else if (notifPreviewY - scrollOffset >= 20) {
            break;
          }
        }
      }
    }
  }

  Paint_DrawRectangle(101, 195, 139, 196, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(100, 196, 140, 197, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(99, 197, 141, 198, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(98, 198, 103, 199, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(137, 198, 142, 199, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(98, 199, 102, 200, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(138, 199, 142, 200, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(98, 200, 102, 201, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(138, 200, 142, 201, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(98, 201, 102, 202, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(138, 201, 142, 202, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(98, 202, 102, 203, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(138, 202, 142, 203, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(98, 203, 102, 204, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(106, 203, 110, 204, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(114, 203, 118, 204, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(122, 203, 126, 204, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(130, 203, 134, 204, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(138, 203, 142, 204, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(98, 204, 102, 205, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(106, 204, 110, 205, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(114, 204, 118, 205, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(122, 204, 126, 205, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(130, 204, 134, 205, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(138, 204, 142, 205, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(98, 205, 102, 206, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(106, 205, 109, 206, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(114, 205, 117, 206, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(123, 205, 126, 206, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(131, 205, 134, 206, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(138, 205, 142, 206, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(98, 206, 102, 207, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(138, 206, 142, 207, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(98, 207, 102, 208, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(138, 207, 142, 208, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(98, 208, 102, 209, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(138, 208, 142, 209, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(98, 209, 102, 210, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(138, 209, 142, 210, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(98, 210, 102, 211, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(116, 210, 124, 211, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(138, 210, 142, 211, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(98, 211, 102, 212, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(106, 211, 110, 212, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(114, 211, 126, 212, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(130, 211, 134, 212, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(138, 211, 142, 212, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(98, 212, 102, 213, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(106, 212, 110, 213, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(114, 212, 126, 213, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(130, 212, 134, 213, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(138, 212, 142, 213, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(98, 213, 102, 214, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(106, 213, 109, 214, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(115, 213, 125, 214, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(138, 213, 142, 214, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(98, 214, 102, 215, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(138, 214, 142, 215, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(98, 215, 102, 216, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(138, 215, 142, 216, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(98, 216, 102, 217, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(138, 216, 142, 217, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(98, 217, 102, 218, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(138, 217, 142, 218, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(98, 218, 142, 219, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(99, 219, 141, 220, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(100, 220, 140, 221, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(103, 198, 137, 199, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);



  //No matter where, when you begin tapping somewhere, Everything else blanks out,
  //And when released, itsn't identified
  //But Only messages app???????????
  //Also it kinda looked like no matter who I selected, the title at the top was always mother

  if (inTransition == false) {
    // Recommended to Open any asked apps After rendering existing scene to prevent double render black bar
    if (tappedNotif != -1) {
      //Serial.println(otherSwipe);
      if (swipe("right", 70)) {
        //Paint_DrawString_EN(70, 2, "True", &Font16, BLUE, WHITE);
        scrollY = 0;
        tappedNotif = -1;
        tappedPhoneNumber = "";
        scrollFunction(foundContacts.size(), {}, true);
        LCD_1IN28_DisplayWindows(180, 0, 240, 240, BlackImage);
        scrollFunction(foundContacts.size(), {}, true);  //run twice, because of the dang white bar-
        LCD_1IN28_DisplayWindows(180, 0, 240, 240, BlackImage);
        //tap=false;
        //pauseRender = true;
        //openApp("messages","LR",Touch_CTS816.x_point);
        //openApp("notifPane", "LR", Touch_CTS816.x_point);
      }

      //Paint_DrawRectangle(0, 195, 240, 225, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
      //Paint_DrawString_EN(64, 200, "KEYBOARD", &Font20, WHITE, BLACK);




      //KEYBOARD ICON WAS HERE

      if (Touch_CTS816.y_point > 195 && Touch_CTS816.y_point < 220) {
        if (watchSwipe == false && tap && otherSwipe == false) {  // && tapHeld > 10
          openApp("keyboard", "DU", 240);
        }
      }

      //if (swipe("right", 70)) {
      //    tappedNotif = -1;
      //    tappedPhoneNumber = "";
      //    tap=false;
      //    pauseRender = true;
      //    //openApp("messages","LR",Touch_CTS816.x_point);
      //    //openApp("notifPane", "LR", Touch_CTS816.x_point);
      //}
    }
    if (pauseRender == false) {
      //if (tappedNotif == -1) {
      //  LCD_1IN28_DisplayWindows(0, 0, 180, 240, BlackImage);
      //} else {
      LCD_1IN28_DisplayWindows(0, 0, 240, 240, BlackImage);
      //}
    }
  }
}
