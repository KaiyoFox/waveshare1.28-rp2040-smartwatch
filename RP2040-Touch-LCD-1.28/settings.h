#ifndef settings_H
#define settings_H
extern int scrollY;
extern bool inTransition;
extern bool pauseRender;
extern bool tap;
extern int tapHeld;
extern bool startup;
extern std::string weatherTemp;//usually Farenheit but will have a C at the end if it is Celcius
extern std::string weatherDesc;//if either value is Unkown, then.. its uknown and didn't fetch.
extern uint16_t deviceMainColorTheme;
extern uint16_t deviceSecondColorTheme;
extern uint16_t deviceThirdColorTheme;
extern int CurTime;
extern UWORD *BlackImage;
extern std::list<std::string> backgroundApps;
extern bool aod;
bool swipe(std::string dir, int thresh);
void openApp(std::string app, std::string dir, int start);
#endif

uint16_t rgb_to_uint16(uint8_t r, uint8_t g, uint8_t b) {
    // Ensure values are within 0-255 range
    r = min(max(r, 0), 255);
    g = min(max(g, 0), 255);
    b = min(max(b, 0), 255);
    
    // Convert RGB to uint16_t value
    uint16_t uint16_value = ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
    
    return uint16_value;
}

void uint16_to_rgb(uint16_t color, uint8_t &r, uint8_t &g, uint8_t &b) {
    // Extract red, green, and blue components
    r = (color >> 8) & 0xF8; // Red component: bits 11-15
    g = (color >> 3) & 0xFC; // Green component: bits 5-10
    b = (color << 3) & 0xF8; // Blue component: bits 0-4
}

//EXAMPLES:
//Paint_DrawString_EN(X, Y, (std::to_string(NUMBER) + "IF YOU WANT TO ADD ANYTHING ELSE").c_str(), &Font12, BLACK, GREEN);
//Paint_DrawString_EN(X, Y, ANY_VARIABLE->c_str(), &Font16, BACKGROUNDCOLOR, TEXTCOLOR);
//Paint_DrawRectangle(XSTART, YSTART, XEND, YEND, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
//Paint_DrawLine(XSTART, YSTART, XEND, YEND, WHITE, DOT_PIXEL_4X4, LINE_STYLE_SOLID);
//Paint_DrawCircle(X, Y, RADIUS, WHITE, DOT_PIXEL_4X4, DRAW_FILL_FULL);
//Touch_CTS816.x_point, and y_point

std::string page = "";

int yp = 0;

uint8_t r = 0;
uint8_t g = 0;
uint8_t b = 0;

int valueChanging = 0;


void settings(){
    if(startup){
        scrollY=0;
        startup=false;
        scrollFunction(5,{},true);
        LCD_1IN28_DisplayWindows(180, 0, 240, 240, BlackImage);
    }
    if(page==""){
        scrollFunction(5,{},true);
        yp = 50 + (-scrollY);

        Paint_DrawRectangle(10, yp, 180, yp+30, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        Paint_DrawString_EN(20, yp+5, "Display", &Font20, GRAY, WHITE);

        Paint_DrawRectangle(10, yp+0+(40*1), 180, yp+30+(40*1), GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        Paint_DrawString_EN(20, yp+5+(40*1), "Battery", &Font20, GRAY, WHITE);

        Paint_DrawRectangle(10, yp+0+(40*2), 180, yp+30+(40*2), GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        Paint_DrawString_EN(20, yp+5+(40*2), "Time", &Font20, GRAY, WHITE);
    
        Paint_DrawRectangle(10, yp+0+(40*3), 180, yp+30+(40*3), GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        Paint_DrawString_EN(20, yp+5+(40*3), "Customize", &Font20, GRAY, WHITE);
        
        Paint_DrawRectangle(10, yp+0+(40*4), 180, yp+30+(40*4), GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        Paint_DrawString_EN(20, yp+5+(40*4), "System", &Font20, GRAY, WHITE);

        if(inTransition==false && watchSwipe==false && otherSwipe==false && tap==true && tapHeld==1){
            if(Touch_CTS816.x_point >= 10 && Touch_CTS816.x_point < 180){
                if(Touch_CTS816.y_point >= yp && Touch_CTS816.y_point < yp+30){
                    // Display button touched
                    page = "display";
                    scrollY=0;
                } else if(Touch_CTS816.y_point >= yp+0+(40*1) && Touch_CTS816.y_point < yp+30+(40*1)){
                    // Time button touched
                    page = "battery";
                    scrollY=0;
                } else if(Touch_CTS816.y_point >= yp+0+(40*2) && Touch_CTS816.y_point < yp+30+(40*2)){
                    // Customization button touched
                    openApp("setTime","",0);
                    scrollY=0;
                } else if(Touch_CTS816.y_point >= yp+0+(40*3) && Touch_CTS816.y_point < yp+30+(40*3)){
                    // System button touched
                    page = "customization";
                    scrollY=0;
                } else if(Touch_CTS816.y_point >= yp+0+(40*4) && Touch_CTS816.y_point < yp+30+(40*4)){
                    // System button touched
                    page = "system";
                    scrollY=0;
                }
            }
        }
    } else if(page=="display"){
        yp=50;
        Paint_DrawRectangle(10, yp, 180, yp+30, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        if(aod){
            Paint_DrawString_EN(20, yp+5, "AOD: On", &Font20, GRAY, WHITE);
        } else{
            Paint_DrawString_EN(20, yp+5, "AOD: Off", &Font20, GRAY, WHITE);
        }
        if(inTransition==false && watchSwipe==false && otherSwipe==false && tap==true && tapHeld==1){
            if(Touch_CTS816.x_point >= 10 && Touch_CTS816.x_point < 180){
                if(Touch_CTS816.y_point >= yp && Touch_CTS816.y_point < yp+30){
                    if(aod==true){
                        aod=false;
                    } else{
                        aod=true;
                    }
                }
            }
        }
    } else if(page=="customization"){
        int shift = 50;
        yp=50;
        if(valueChanging!=0){
            Paint_DrawRectangle(0, 0, 180, 240, rgb_to_uint16(r, g, b), DOT_PIXEL_1X1, DRAW_FILL_FULL);
            
            Paint_DrawRectangle(shift, yp, shift+37, yp+30, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
            Paint_DrawString_EN(shift+10, yp+5, "+", &Font24, GRAY, WHITE);
            
            Paint_DrawRectangle(shift+90, yp, shift+90+37, yp+30, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
            Paint_DrawString_EN(shift+100, yp+5, "-", &Font24, GRAY, WHITE);
            
            Paint_DrawRectangle(shift, yp+40, shift+37, yp+70, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
            Paint_DrawString_EN(shift+10, yp+45, "+", &Font24, GRAY, WHITE);
            
            Paint_DrawRectangle(shift+90, yp+40, shift+90+37, yp+70, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
            Paint_DrawString_EN(shift+100, yp+45, "-", &Font24, GRAY, WHITE);
            
            Paint_DrawRectangle(shift, yp+80, shift+37, yp+110, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
            Paint_DrawString_EN(shift+10, yp+85, "+", &Font24, GRAY, WHITE);
            
            Paint_DrawRectangle(shift+90, yp+80, shift+90+37, yp+110, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
            Paint_DrawString_EN(shift+100, yp+85, "-", &Font24, GRAY, WHITE);
            
            Paint_DrawRectangle(shift, 190, shift+180, 220, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
            Paint_DrawString_EN(shift+70, 195, "Save", &Font20, GRAY, WHITE);

            Paint_DrawString_EN(shift+40, 180, ("R: " + std::to_string(r)).c_str(), &Font12, BLACK, GREEN);
            Paint_DrawString_EN(shift+40, 200, ("G: " + std::to_string(g)).c_str(), &Font12, BLACK, GREEN);
            Paint_DrawString_EN(shift+40, 220, ("B: " + std::to_string(b)).c_str(), &Font12, BLACK, GREEN);

            // Handle button taps
            if(inTransition==false && watchSwipe==false && otherSwipe==false && tap==true){
                if(Touch_CTS816.x_point >= shift && Touch_CTS816.x_point < shift+37){
                    if(Touch_CTS816.y_point >= yp && Touch_CTS816.y_point < yp+30){
                        // Increase R button tapped
                        r = std::min(r + 20, 255); // Increase R value, ensuring it stays within 0-255 range
                    } else if(Touch_CTS816.y_point >= yp+40 && Touch_CTS816.y_point < yp+70){
                        // Increase G button tapped
                        g = std::min(g + 20, 255); // Increase G value, ensuring it stays within 0-255 range
                    } else if(Touch_CTS816.y_point >= yp+80 && Touch_CTS816.y_point < yp+110){
                        // Increase B button tapped
                        b = std::min(b + 20, 255); // Increase B value, ensuring it stays within 0-255 range
                    } else if(Touch_CTS816.y_point >= 190 && Touch_CTS816.y_point < 220){
                        // Save button tapped
                        // Add code here to save the changes
                    }
                } else if(Touch_CTS816.x_point >= shift+90 && Touch_CTS816.x_point < shift+90+37){
                    if(Touch_CTS816.y_point >= yp && Touch_CTS816.y_point < yp+30){
                        // Decrease R button tapped
                        r = std::max(r - 20, 0); // Decrease R value, ensuring it stays within 0-255 range
                    } else if(Touch_CTS816.y_point >= yp+40 && Touch_CTS816.y_point < yp+70){
                        // Decrease G button tapped
                        g = std::max(g - 20, 0); // Decrease G value, ensuring it stays within 0-255 range
                    } else if(Touch_CTS816.y_point >= yp+80 && Touch_CTS816.y_point < yp+110){
                        // Decrease B button tapped
                        b = std::max(b - 20, 0); // Decrease B value, ensuring it stays within 0-255 range
                    }
                } else if(Touch_CTS816.x_point >= 10 && Touch_CTS816.x_point < 180 && Touch_CTS816.y_point >= 190 && Touch_CTS816.y_point < 220){
                    if(valueChanging==1){
                        deviceMainColorTheme=rgb_to_uint16(r, g, b);
                    } else if(valueChanging==2){
                        deviceSecondColorTheme=rgb_to_uint16(r, g, b);
                    } else if(valueChanging==3){
                        deviceThirdColorTheme=rgb_to_uint16(r, g, b);
                    }
                    valueChanging=0;
                }
            }
        } else{
            Paint_DrawString_EN(shift+10, yp+10, ("Main Color: " + std::to_string(deviceMainColorTheme)).c_str(), &Font12, BLACK, GREEN);
            Paint_DrawString_EN(shift+10, yp+10+40, ("Second Color: " + std::to_string(deviceSecondColorTheme)).c_str(), &Font12, BLACK, GREEN);
            Paint_DrawString_EN(shift+10, yp+10+80, ("Third Color: " + std::to_string(deviceThirdColorTheme)).c_str(), &Font12, BLACK, GREEN);
            if(Touch_CTS816.x_point >= shift+0 && Touch_CTS816.x_point < shift+50){
                if(Touch_CTS816.y_point >= yp && Touch_CTS816.y_point < yp+30){
                    valueChanging=1;
                    uint16_to_rgb(deviceMainColorTheme,r,g,b);
                } else if(Touch_CTS816.y_point >= yp+40 && Touch_CTS816.y_point < yp+30+40){
                    valueChanging=2;
                    uint16_to_rgb(deviceSecondColorTheme,r,g,b);
                } else if(Touch_CTS816.y_point >= yp+80 && Touch_CTS816.y_point < yp+30+80){
                    valueChanging=3;
                    uint16_to_rgb(deviceThirdColorTheme,r,g,b);
                }
            }
        }
    } else{
        Paint_DrawString_EN(100, 100, page.c_str(), &Font16, BLACK, RED);
    }



  if(inTransition==false){
    if(pauseRender==false){
      LCD_1IN28_DisplayWindows(0, 0, 180, 240, BlackImage);
    }

    //Recommeneded to Open any asked apps After rendering existing scene to prevent double render black bar
    //if(swipe("down",70)){ //example swipe action, (70 is how far away the tap needs to be before it is registered as Complete)
    //  openApp("main", "UD", Touch_CTS816.y_point);
    //}
    if(swipe("right",70)){
        page="";
    }
    if(tap || tapHeld > 5){
        //example with tap and tap held
    }
  }
}