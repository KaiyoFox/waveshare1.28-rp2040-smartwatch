#ifndef previewNotif_H
#define previewNotif_H
extern bool inTransition;
extern bool pauseRender;
extern bool tap;
extern int CurTime;
extern int tappedNotif;
extern UWORD *BlackImage;
extern std::list<std::string> backgroundApps;
extern std::list<std::list<std::string>> notifications;
bool swipe(std::string dir, int thresh);
void openApp(std::string app, std::string dir, int start);
#endif

//EITHER, APP FLAGS, ORRR. JUST A SINGLE VARIABLE FOR THIS APP.
//ALSO I NEED TO ADD SCROLLING appsPanel

//EXAMPLES:
//Paint_DrawString_EN(153, 19, (std::to_string(NUMBER) + "IF YOU WANT TO ADD ANYTHING ELSE").c_str(), &Font12, BLACK, GREEN);
//Paint_DrawString_EN(X, Y, ANY_VARIABLE->c_str(), &Font16, BACKGROUNDCOLOR, TEXTCOLOR);

void previewNotif() {

  for (const auto &notification : notifications) {
    auto title = notification.front();
    if (uniqueTitles.find(title) == uniqueTitles.end()) {
      uniqueTitles.insert(title);
      uniqueNotifications.push_back(notification);
    }
  }  //NEEDS TO BE FIXED, THIS SHOULDN"T BE NEEDED


  std::list<std::string> notification = *std::next(uniqueNotifications.begin(), tappedNotif);
  int notifPreviewY = 20;
  for (const auto &item : notification) {
    if (notifPreviewY == 20) {
      Paint_DrawString_EN(50, notifPreviewY, item.c_str(), &Font16, BLACK, WHITE);
    } else if (notifPreviewY == 20 + 18) {
      Paint_DrawString_EN(30, notifPreviewY, item.c_str(), &Font12, BLACK, WHITE);
    } else {
      Paint_DrawString_EN(20, notifPreviewY, item.c_str(), &Font12, BLACK, WHITE);
    }
    notifPreviewY += 18;
  }

  //Paint_DrawString_EN(100, 100, "nO", &Font24, BLACK, WHITE);

  renderSnack();
  if (inTransition == false) {
    //Recommeneded to Open any asked apps After rendering existing scene to prevent double render black bar
    if (swipe("right", 70)) {
      openApp("notifPane", "LR", Touch_CTS816.x_point);
    }
    if (pauseRender == false) {
      LCD_1IN28_DisplayWindows(0, 0, 240, 240, BlackImage);
    }
    //if(Touch_CTS816.y_point > 210 && tapHeld > 5){
    //  openApp("recentApps", "UD", Touch_CTS816.y_point);
    //};
  }
}