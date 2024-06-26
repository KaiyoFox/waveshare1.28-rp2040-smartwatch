#ifndef __GUI_PAINT_H
#define __GUI_PAINT_H

#include "DEV_Config.h"
#include "fonts.h"

/**
 * Image attributes
**/
typedef struct {
  UBYTE* Image;
  UWORD Width;
  UWORD Height;
  UWORD WidthMemory;
  UWORD HeightMemory;
  UWORD Color;
  UWORD Rotate;
  UWORD Mirror;
  UWORD WidthByte;
  UWORD HeightByte;
  UWORD Scale;
} PAINT;
extern PAINT Paint;

/**
 * Display rotate
**/
#define ROTATE_0 0
#define ROTATE_90 90
#define ROTATE_180 180
#define ROTATE_270 270

/**
 * Display Flip
**/
typedef enum {
  MIRROR_NONE = 0x00,
  MIRROR_HORIZONTAL = 0x01,
  MIRROR_VERTICAL = 0x02,
  MIRROR_ORIGIN = 0x03,
} MIRROR_IMAGE;
#define MIRROR_IMAGE_DFT MIRROR_NONE

/**
 * image color
**/
#define WHITE 0xFFFF
#define BLACK 0x0000
#define BLUE 0x001F
#define BRED 0xF81F
#define GRED 0xFFE0
#define GBLUE 0x07FF
#define RED 0xF800
#define MAGENTA 0xF81F
#define PINK 0xfdff
#define GREEN 0x07E0
#define CYAN 0x7FFF
#define YELLOW 0xFFE0
#define GOOD_YELLOW 0xff6a
#define BROWN 0xBC40
#define BRRED 0xFC07
#define GRAY 0x8430
#define DARKGRAY 0x39c7
#define LIGHT_GRAY 0xbdd7
#define ORANGE 0xfc60
#define LIGHTPURPLE 0xb5bd
#define LIGHTBLUE 0xb69d
#define PURPLE 0xa01a
#define SKYBLUE 0x03ba
#define LIMEY 0xafe0
#define AQUAGREEN 0x07f1
#define DARKGREEN 0x02a6
#define MIDGREEN 0x050b
#define IJUSTWANTGRASS 0x3cee
#define IGIVEUP 0x4c29
#define MAROON 0x40e5
#define BRIGHTPURPLE 0x9274
#define PEACH 0xf637
#define LIGHTBROWN 0xbbed
#define DARKBROWN 0x4963
#define REDTAN 0xc42f
#define TAN 0xf6ba
#define FRIEDYELLOW 0xff96
#define YELLOWORANGE 0xf6b2
#define PAPERGRAY 0xb596
#define HOTPINK 0xe1b1

#define IMAGE_BACKGROUND WHITE
#define FONT_FOREGROUND BLACK
#define FONT_BACKGROUND WHITE

/**
 * The size of the point
**/
typedef enum {
  DOT_PIXEL_1X1 = 1,  // 1 x 1
  DOT_PIXEL_2X2,      // 2 X 2
  DOT_PIXEL_3X3,      // 3 X 3
  DOT_PIXEL_4X4,      // 4 X 4
  DOT_PIXEL_5X5,      // 5 X 5
  DOT_PIXEL_6X6,      // 6 X 6
  DOT_PIXEL_7X7,      // 7 X 7
  DOT_PIXEL_8X8,      // 8 X 8
} DOT_PIXEL;
#define DOT_PIXEL_DFT DOT_PIXEL_1X1  //Default dot pilex

/**
 * Point size fill style
**/
typedef enum {
  DOT_FILL_AROUND = 1,  // dot pixel 1 x 1
  DOT_FILL_RIGHTUP,     // dot pixel 2 X 2
} DOT_STYLE;
#define DOT_STYLE_DFT DOT_FILL_AROUND  //Default dot pilex

/**
 * Line style, solid or dashed
**/
typedef enum {
  LINE_STYLE_SOLID = 0,
  LINE_STYLE_DOTTED,
} LINE_STYLE;

/**
 * Whether the graphic is filled
**/
typedef enum {
  DRAW_FILL_EMPTY = 0,
  DRAW_FILL_FULL,
} DRAW_FILL;

/**
 * Custom structure of a time attribute
**/
typedef struct {
  UWORD Year;   //0000
  UBYTE Month;  //1 - 12
  UBYTE Day;    //1 - 30
  UBYTE Hour;   //0 - 23
  UBYTE Min;    //0 - 59
  UBYTE Sec;    //0 - 59
} PAINT_TIME;
extern PAINT_TIME sPaint_time;

//init and Clear
void Paint_NewImage(UBYTE* image, UWORD Width, UWORD Height, UWORD Rotate, UWORD Color);
void Paint_SelectImage(UBYTE* image);
void Paint_SetRotate(UWORD Rotate);
void Paint_SetMirroring(UBYTE mirror);
void Paint_SetPixel(UWORD Xpoint, UWORD Ypoint, UWORD Color);
void Paint_SetScale(UBYTE scale);

void Paint_Clear(UWORD Color);
void Paint_ClearWindows(UWORD Xstart, UWORD Ystart, UWORD Xend, UWORD Yend, UWORD Color);

//Drawing
void Paint_DrawPoint(UWORD Xpoint, UWORD Ypoint, UWORD Color, DOT_PIXEL Dot_Pixel, DOT_STYLE Dot_FillWay);
void Paint_DrawLine(UWORD Xstart, UWORD Ystart, UWORD Xend, UWORD Yend, UWORD Color, DOT_PIXEL Line_width, LINE_STYLE Line_Style);
void Paint_DrawRectangle(UWORD Xstart, UWORD Ystart, UWORD Xend, UWORD Yend, UWORD Color, DOT_PIXEL Line_width, DRAW_FILL Draw_Fill);
void Paint_DrawCircle(UWORD X_Center, UWORD Y_Center, UWORD Radius, UWORD Color, DOT_PIXEL Line_width, DRAW_FILL Draw_Fill);
void Paint_DrawCircleTrans(UWORD Xcenter, UWORD Ycenter, UWORD Radius, uint8_t transparency, DOT_PIXEL Line_width, DRAW_FILL Draw_Fill);
void Paint_DrawEdgeEffect();
void Paint_DrawRectangleTrans(UWORD Xstart, UWORD Ystart, UWORD Xend, UWORD Yend, uint8_t transparency, DOT_PIXEL Line_width, DRAW_FILL Draw_Fill);

//Display string
void Paint_DrawChar(UWORD Xstart, UWORD Ystart, const char Acsii_Char, sFONT* Font, UWORD Color_Foreground, UWORD Color_Background);
void Paint_DrawString_EN(UWORD Xstart, UWORD Ystart, const char* pString, sFONT* Font, UWORD Color_Foreground, UWORD Color_Background);
void Paint_DrawString_CN(UWORD Xstart, UWORD Ystart, const char* pString, cFONT* font, UWORD Color_Foreground, UWORD Color_Background);
void Paint_DrawNum(UWORD Xpoint, UWORD Ypoint, double Nummber, sFONT* Font, UWORD Digit, UWORD Color_Foreground, UWORD Color_Background);
void Paint_DrawTime(UWORD Xstart, UWORD Ystart, PAINT_TIME* pTime, sFONT* Font, UWORD Color_Foreground, UWORD Color_Background);

//pic
void Paint_DrawBitMap(const unsigned char* image_buffer);
void Paint_DrawBitMap_Block(const unsigned char* image_buffer, UBYTE Region);

void Paint_DrawImage(const unsigned char* image, UWORD xStart, UWORD yStart, UWORD W_Image, UWORD H_Image);
void Paint_DrawImage1(const unsigned char* image, UWORD xStart, UWORD yStart, UWORD W_Image, UWORD H_Image, UWORD Color_Foreground);
void Paint_BmpWindows(unsigned char x, unsigned char y, const unsigned char* pBmp,
                      unsigned char chWidth, unsigned char chHeight);


#endif
