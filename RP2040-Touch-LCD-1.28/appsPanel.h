#include <algorithm>
#include <cstring>
#include <vector> // Include the vector library
#include <numeric> // Include the numeric library
#ifndef appsPanel_H
#define appsPanel_H
extern bool inTransition;
extern bool pauseRender;
extern bool tap;
extern bool otherSwipe;
extern bool watchSwipe;
extern bool startup;
extern int tapHeld;
extern int scrollY; // Added scrollY variable
extern UWORD *BlackImage;
extern std::list<std::string> systemApps;
typedef void (*AppPtr)();
extern std::map<std::string, AppPtr> apps;
bool swipe(std::string dir, int thresh);
void openApp(std::string app, std::string dir, int start);
uint16_t findTextColor(const std::string &text);
#endif

int appSize = 35; // Adjust as needed
int appLeng = 140;
int startX = 25; // Adjust as needed
int startY = 35; // Adjust as needed
int spacing = 10; // Adjust as needed
int columns = 3; // Adjust as needed
int visibleApps = 6; // Number of visible apps in the panel
int scrollStep = 5; // Adjust as needed, controls scrolling speed
//bool appPanelAppCalled = false;

bool openingAnApp = false;

void appsPanel(){
    if(startup){
        openingAnApp=false;
        scrollY=spacing;
    }
    //appPanelAppCalled = false;
    //Paint_DrawRectangle(50, 0, 190, 240, 0x39E7, DOT_PIXEL_1X1, DRAW_FILL_FULL);

    int count = 0;
    int visibleCount = 0; // Track the number of visible apps
    //scrollFunction(apps.size(),{},true);//WARNINGGGGGGGGGGGGGGGGGGGGGG APPS CONTAINS THE HIDDEN APPS< AND MAY BREAK

    // Calculate the total height of items and spacing
    std::vector<int> itemHeights;
    int totalHeight=0;
    for (auto const& [key, val] : apps) {
        if (std::find(systemApps.begin(), systemApps.end(), key) == systemApps.end()) {
            int itemHeight = appSize + spacing; // Adjust as needed
            totalHeight+=itemHeight;
            itemHeights.push_back(itemHeight);
        }
    }
    //int totalHeight = std::accumulate(itemHeights.begin(), itemHeights.end(), 0);

    // Determine the modified scrollY value
    int scrollYModded = (scrollY / 240.0) * (totalHeight);// + (itemHeights.size() * spacing)

    // Determine the starting index based on scroll position
    int startIndex = std::max(0, (scrollYModded / (appSize + spacing)) - visibleApps);

    // Render apps in a list, starting from the calculated start index
    for (auto it = std::next(apps.begin(), startIndex); it != apps.end(); ++it) {
        const std::string& key = it->first;
        if (std::find(systemApps.begin(), systemApps.end(), key) == systemApps.end()) {
            int x = startX;
            int y = startY + (visibleCount + startIndex) * (appSize + spacing) - scrollYModded;
            if(y>-appSize && y<240 && openingAnApp==false){
                Paint_DrawRectangle(x+3, max(0,min(240,y)), x + appLeng - 3,max(0,min(240,y+appSize)), findTextColor(key.c_str()), DOT_PIXEL_1X1, DRAW_FILL_FULL);
                
                Paint_DrawRectangle(x, max(0,min(240,y+3)), x+4, max(0,min(240,y+appSize-3)), findTextColor(key.c_str()), DOT_PIXEL_1X1, DRAW_FILL_FULL);

                Paint_DrawRectangle(x + appLeng, max(0,min(240,y+3)), x + appLeng - 4, max(0,min(240,y+appSize-3)), findTextColor(key.c_str()), DOT_PIXEL_1X1, DRAW_FILL_FULL);

                Paint_DrawString_EN(startX + 5, y + appSize - (16+5), key.c_str(), &Font16, findTextColor(key.c_str()), BLACK);//(x + appLeng) - (std::strlen(key.c_str())*11) - 1,font8 0x009688
                if(inTransition==false && !pauseRender){
                    if (Touch_CTS816.x_point >= x && Touch_CTS816.x_point <= x + appLeng && Touch_CTS816.y_point >= y && Touch_CTS816.y_point <= y + appSize) {
                        if(tap && !watchSwipe && !otherSwipe){
                            if(tapHeld > 1){
                                tap=false;
                                //appPanelAppCalled=true;
                                openApp(key, "", 0);//RAND
                                tap=false;
                                openingAnApp=true;
                                oneTickPause=true;
                            }
                        }
                    }
                }
            } else if(y>240){
                break;
            }

            visibleCount++;
        }
    }

    scrollFunction(visibleCount,{},true);

    if(inTransition==false){
        if(pauseRender==false && openingAnApp==false){
            LCD_1IN28_DisplayWindows(startX-2, 0, 180, 240, BlackImage);
            //LCD_1IN28_Display(BlackImage);
        }

        // Recommended to Open any asked apps After rendering existing scene to prevent double render black bar
        //if(swipe("right",70)){
        //    openApp("main", "LR", Touch_CTS816.x_point);
        //}
        //if(Touch_CTS816.y_point > 210 && tapHeld > 5 && inTransition==false){
        //    openApp("recentApps", "UD", Touch_CTS816.y_point);
        //}
    }
}
