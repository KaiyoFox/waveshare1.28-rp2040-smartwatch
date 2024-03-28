#ifndef flashlight_H
#define flashlight_H
extern bool inTransition;
extern bool pauseRender;
extern bool tap;
extern int CurTime;
extern UWORD *BlackImage;
extern std::list<std::string> backgroundApps;
bool swipe(std::string dir, int thresh);
void openApp(std::string app, std::string dir, int start);
#endif

bool FlashtapDown = false;
int color = 0;

//EXAMPLES:
//Paint_DrawString_EN(153, 19, (std::to_string(NUMBER) + "IF YOU WANT TO ADD ANYTHING ELSE").c_str(), &Font12, BLACK, GREEN);
//Paint_DrawString_EN(X, Y, ANY_VARIABLE->c_str(), &Font16, BACKGROUNDCOLOR, TEXTCOLOR);
//Paint_DrawRectangle(0, 0, 0, 0, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);

void flashlight(){
  if(tap && FlashtapDown == false && watchSwipe==false){
    FlashtapDown = true;
    color+=1;
    if(color>2){
        color = 0;
    }
  } else if(tap==false && FlashtapDown){
    FlashtapDown=false;
  }
  if(color==0){
    Paint_DrawRectangle(0, 0, 240, 240, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  } else if(color==1){
    Paint_DrawRectangle(0, 0, 240, 240, RED, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  } else if(color==2){
    Paint_DrawRectangle(0, 0, 240, 240, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  }

Paint_DrawRectangle(118, 39, 121, 40, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(118, 40, 122, 41, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(118, 41, 122, 42, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(96, 42, 99, 43, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(118, 42, 122, 43, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(141, 42, 144, 43, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(96, 43, 100, 44, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(118, 43, 122, 44, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(140, 43, 144, 44, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(96, 44, 100, 45, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(118, 44, 122, 45, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(139, 44, 143, 45, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(97, 45, 101, 46, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(118, 45, 122, 46, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(139, 45, 143, 46, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(97, 46, 101, 47, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(118, 46, 122, 47, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(138, 46, 142, 47, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(98, 47, 102, 48, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(118, 47, 122, 48, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(138, 47, 142, 48, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(99, 48, 102, 49, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(118, 48, 122, 49, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(137, 48, 141, 49, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(99, 49, 103, 50, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(118, 49, 122, 50, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(137, 49, 141, 50, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(100, 50, 104, 51, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(118, 50, 122, 51, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(136, 50, 140, 51, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(100, 51, 104, 52, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(118, 51, 122, 52, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(136, 51, 140, 52, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(101, 52, 105, 53, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(118, 52, 122, 53, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(135, 52, 139, 53, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(101, 53, 105, 54, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(118, 53, 121, 54, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(134, 53, 138, 54, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(102, 54, 106, 55, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(134, 54, 138, 55, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(102, 55, 106, 56, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(134, 55, 137, 56, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(95, 66, 144, 67, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(94, 67, 145, 68, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(94, 68, 145, 69, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(94, 69, 145, 70, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(94, 70, 98, 71, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(142, 70, 145, 71, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(94, 71, 98, 72, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(142, 71, 145, 72, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(94, 72, 98, 73, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(142, 72, 145, 73, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(94, 73, 98, 74, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(142, 73, 145, 74, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(94, 74, 98, 75, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(142, 74, 145, 75, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(94, 75, 98, 76, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(142, 75, 145, 76, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(94, 76, 98, 77, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(142, 76, 145, 77, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(94, 77, 98, 78, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(142, 77, 145, 78, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(94, 78, 98, 79, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(142, 78, 145, 79, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(94, 79, 98, 80, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(142, 79, 145, 80, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(94, 80, 98, 81, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(142, 80, 145, 81, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(94, 81, 145, 82, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(94, 82, 145, 83, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(94, 83, 145, 84, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(95, 84, 145, 85, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(95, 85, 99, 86, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(141, 85, 144, 86, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(96, 86, 100, 87, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(140, 86, 144, 87, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(96, 87, 100, 88, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(140, 87, 143, 88, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(97, 88, 101, 89, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(139, 88, 143, 89, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(97, 89, 101, 90, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(139, 89, 142, 90, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(98, 90, 101, 91, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(138, 90, 142, 91, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(98, 91, 102, 92, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(138, 91, 142, 92, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(99, 92, 102, 93, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(137, 92, 141, 93, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(99, 93, 103, 94, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(137, 93, 141, 94, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(100, 94, 103, 95, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(136, 94, 140, 95, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(100, 95, 104, 96, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(136, 95, 140, 96, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(100, 96, 104, 97, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(135, 96, 139, 97, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(101, 97, 105, 98, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(135, 97, 139, 98, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(101, 98, 105, 99, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(135, 98, 138, 99, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(102, 99, 106, 100, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(134, 99, 138, 100, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(102, 100, 137, 101, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(103, 101, 137, 102, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(103, 102, 137, 103, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(103, 103, 106, 104, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(133, 103, 137, 104, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(103, 104, 106, 105, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(133, 104, 137, 105, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(103, 105, 106, 106, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(133, 105, 137, 106, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(103, 106, 106, 107, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(133, 106, 137, 107, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(103, 107, 106, 108, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(133, 107, 137, 108, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(103, 108, 106, 109, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(133, 108, 137, 109, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(103, 109, 106, 110, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(133, 109, 137, 110, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(103, 110, 106, 111, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(133, 110, 137, 111, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(103, 111, 106, 112, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(133, 111, 137, 112, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(103, 112, 106, 113, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(133, 112, 137, 113, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(103, 113, 106, 114, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(133, 113, 137, 114, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(103, 114, 106, 115, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(116, 114, 124, 115, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(133, 114, 137, 115, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(103, 115, 106, 116, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(115, 115, 125, 116, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(133, 115, 137, 116, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(103, 116, 106, 117, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(114, 116, 126, 117, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(133, 116, 137, 117, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(103, 117, 106, 118, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(114, 117, 118, 118, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(122, 117, 126, 118, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(133, 117, 137, 118, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(103, 118, 106, 119, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(113, 118, 117, 119, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(123, 118, 127, 119, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(133, 118, 137, 119, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(103, 119, 106, 120, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(113, 119, 116, 120, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(123, 119, 127, 120, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(133, 119, 137, 120, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(103, 120, 106, 121, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(113, 120, 116, 121, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(124, 120, 127, 121, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(133, 120, 137, 121, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(103, 121, 106, 122, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(113, 121, 116, 122, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(123, 121, 127, 122, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(133, 121, 137, 122, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(103, 122, 106, 123, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(113, 122, 116, 123, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(124, 122, 127, 123, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(133, 122, 137, 123, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(103, 123, 106, 124, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(113, 123, 116, 124, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(124, 123, 127, 124, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(133, 123, 137, 124, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(103, 124, 106, 125, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(113, 124, 116, 125, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(123, 124, 127, 125, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(133, 124, 137, 125, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(103, 125, 106, 126, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(113, 125, 116, 126, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(123, 125, 127, 126, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(133, 125, 137, 126, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(103, 126, 106, 127, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(113, 126, 116, 127, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(123, 126, 127, 127, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(133, 126, 137, 127, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(103, 127, 106, 128, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(113, 127, 116, 128, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(124, 127, 127, 128, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(133, 127, 137, 128, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(103, 128, 106, 129, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(113, 128, 116, 129, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(124, 128, 127, 129, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(133, 128, 137, 129, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(103, 129, 106, 130, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(113, 129, 116, 130, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(123, 129, 127, 130, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(133, 129, 137, 130, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(103, 130, 106, 131, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(113, 130, 116, 131, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(124, 130, 127, 131, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(103, 131, 106, 132, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(113, 131, 116, 132, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(124, 131, 127, 132, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(133, 131, 137, 132, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(103, 132, 106, 133, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(113, 132, 116, 133, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(123, 132, 127, 133, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(133, 132, 137, 133, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(103, 133, 106, 134, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(113, 133, 117, 134, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(123, 133, 127, 134, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(133, 133, 137, 134, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(103, 134, 106, 135, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(113, 134, 117, 135, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(123, 134, 127, 135, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(133, 134, 137, 135, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(103, 135, 106, 136, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(114, 135, 118, 136, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(122, 135, 126, 136, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(133, 135, 137, 136, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(103, 136, 106, 137, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(114, 136, 126, 137, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(133, 136, 137, 137, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(103, 137, 106, 138, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(115, 137, 125, 138, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(133, 137, 137, 138, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(103, 138, 106, 139, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(116, 138, 123, 139, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(103, 139, 106, 140, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(133, 139, 137, 140, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(103, 140, 106, 141, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(133, 140, 137, 141, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(103, 141, 106, 142, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(133, 141, 137, 142, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(103, 142, 106, 143, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(133, 142, 137, 143, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(103, 143, 106, 144, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(133, 143, 137, 144, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(103, 144, 106, 145, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(133, 144, 137, 145, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(103, 145, 106, 146, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(133, 145, 137, 146, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(103, 146, 106, 147, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(133, 146, 137, 147, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(103, 147, 106, 148, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(133, 147, 137, 148, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(103, 148, 106, 149, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(133, 148, 137, 149, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(103, 149, 106, 150, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(133, 149, 137, 150, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(103, 150, 106, 151, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(133, 150, 137, 151, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(103, 151, 106, 152, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(133, 151, 137, 152, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(103, 152, 106, 153, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(133, 152, 137, 153, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(103, 153, 106, 154, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(133, 153, 137, 154, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(103, 154, 107, 155, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(133, 154, 137, 155, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(103, 155, 107, 156, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(133, 155, 136, 156, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(104, 156, 107, 157, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(132, 156, 136, 157, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(104, 157, 108, 158, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(132, 157, 136, 158, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(104, 158, 108, 159, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(131, 158, 135, 159, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(105, 159, 109, 160, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(131, 159, 135, 160, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(105, 160, 110, 161, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(130, 160, 134, 161, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(106, 161, 111, 162, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(129, 161, 134, 162, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(107, 162, 112, 163, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(128, 162, 133, 163, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(108, 163, 113, 164, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(126, 163, 132, 164, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(109, 164, 116, 165, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(124, 164, 131, 165, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(110, 165, 130, 166, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(112, 166, 128, 167, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(114, 167, 126, 168, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(133, 130, 137, 131, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
Paint_DrawRectangle(133, 138, 137, 139, GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);

  if(inTransition==false){
    if(pauseRender==false){
      LCD_1IN28_DisplayWindows(0, 0, 240, 240, BlackImage);
    }

    //Recommeneded to Open any asked apps After rendering existing scene to prevent double render black bar
    if(swipe("down",70)){
      openApp("main", "UD", Touch_CTS816.y_point);
    }
    //if(Touch_CTS816.y_point > 210 && tapHeld > 5){
    //  openApp("recentApps", "UD", Touch_CTS816.y_point);
    //};
  }
}