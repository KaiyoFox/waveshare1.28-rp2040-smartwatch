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
        auto targetFirstTwoItems = std::list<std::string>{ contact.back().c_str(), "messages" };
        int currentIndex = 0;
        int foundIndex = -1;
        for (const auto &notification : notifications) {
          if (std::equal(targetFirstTwoItems.begin(), targetFirstTwoItems.end(), notification.begin())) {
            containsNotification = true;
            break;
          }
        }
        if (containsNotification == false) {
          notifications.push_back({ contact.back().c_str(), "messages", "", contact.front().c_str() });
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
                notifPreviewY -= 16; //should do math for more than 2 lines
              }
            } else {
              Paint_DrawString_EN(30, notifPreviewY - scrollOffset, content.c_str(), &Font16, BLACK, WHITE);
              if(11 * content.length()>240){
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

  //No matter where, when you begin tapping somewhere, Everything else blanks out,
  //And when released, itsn't identified
  //But Only messages app???????????
  //Also it kinda looked like no matter who I selected, the title at the top was always mother

  if (inTransition == false) {
    if (pauseRender == false) {
      if (tappedNotif == -1) {
        LCD_1IN28_DisplayWindows(0, 0, 180, 240, BlackImage);
      } else {
        LCD_1IN28_DisplayWindows(0, 0, 240, 240, BlackImage);
      }
    }


    // Recommended to Open any asked apps After rendering existing scene to prevent double render black bar
    if (tappedNotif != -1) {
      //Serial.println(otherSwipe);
      if (swipe("right", 70)) {
        //Paint_DrawString_EN(70, 2, "True", &Font16, BLUE, WHITE);

        tappedNotif = -1;
        tappedPhoneNumber = "";
        //tap=false;
        //pauseRender = true;
        //openApp("messages","LR",Touch_CTS816.x_point);
        //openApp("notifPane", "LR", Touch_CTS816.x_point);
      }

      Paint_DrawRectangle(0, 195, 240, 225, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
      Paint_DrawString_EN(64, 200, "KEYBOARD", &Font20, WHITE, BLACK);
      if (Touch_CTS816.y_point > 195 && Touch_CTS816.y_point < 225) {
        if (watchSwipe == false && tap) {  // && tapHeld > 10
          if (otherSwipe == false) {
            openApp("keyboard", "DU", 240);
          }
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
  }
}
