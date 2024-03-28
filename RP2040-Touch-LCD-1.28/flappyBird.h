#ifndef flappyBird_H
#define flappyBird_H
extern bool inTransition;
extern bool pauseRender;
extern bool tap;
extern bool speedMode;
extern bool startup;
extern UWORD *BlackImage;
bool swipe(std::string dir, int thresh);
void openApp(std::string app, std::string dir, int start);
#endif

int birdY = 100;
float vel = 0;
float gravity = 1;
float drag = 1.1;
int gap = 70;
int gapPosition = 120;
int gapSize = 70;
int score = 0;
bool held = false;

int obstacleX = 0;
int obstacleWidth = 20;
int minObstacleHeight = 50;//80
int maxObstacleHeight = 150;//110

void generateObstacle() {
  if (obstacleX < -obstacleWidth) {
    obstacleX = 240;
    gapPosition = rand() % (240 - maxObstacleHeight) + minObstacleHeight;
  }
}

bool isCollision() {
  // Implement collision detection logic here
  if (birdY < 0 || birdY > 240 || ((birdY < gapPosition || birdY > gapPosition + gapSize) && (obstacleX < 50 + obstacleWidth && obstacleX > 50))) {
    return true;
  }
  return false;
}

void flappyBird() {
  if(startup){
    startup=false;
    speedMode=true;
    Paint_Clear(BLUE);
    Paint_DrawRectangle(0, 0, 240, 240, BLUE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    LCD_1IN28_DisplayWindows(0, 0, 240, 240, BlackImage);
  }
  if (tap) {
    if(held == false){
      held=true;
      vel -= 15; // Adjust the tap velocity here
    }
  } else {
    held = false;
  }
  Paint_DrawRectangle(0, 0, 240, 240, BLUE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(50, birdY, 70, birdY + 20, YELLOW, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(obstacleX, 0, obstacleX + obstacleWidth, gapPosition, GREEN, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(obstacleX, gapPosition + gapSize, obstacleX + obstacleWidth, 240, GREEN, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawString_EN(140, 84, (std::to_string(score)).c_str(), &Font16, BLUE, RED);

  if (inTransition == false) {
    if (pauseRender == false) {
      LCD_1IN28_DisplayWindows(50, max(0, birdY - 20), 70, min(240, birdY + 20 + 20), BlackImage);
      LCD_1IN28_DisplayWindows(max(0, min(240, obstacleX)), 0, max(0, min(240, obstacleX + obstacleWidth + 15)), gapPosition, BlackImage);
      LCD_1IN28_DisplayWindows(max(0, min(240, obstacleX)), gapPosition+gapSize, max(0, min(240, obstacleX + obstacleWidth + 15)), 240, BlackImage);
    }

    vel += gravity;
    vel /= drag;
    birdY += vel;
    obstacleX -= 10;

    if (isCollision()) {
      // Implement game over logic here
      Paint_Clear(BLUE);
      Paint_DrawRectangle(0, 0, 240, 240, BLUE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
      LCD_1IN28_DisplayWindows(0, 0, 240, 240, BlackImage);
      birdY = 100;
      vel = 0;
      Paint_DrawString_EN(140, 84, (std::to_string(score)).c_str(), &Font16, BLUE, RED);
      score = 0;
      obstacleX = 240;
      gapPosition = rand() % (240 - maxObstacleHeight) + minObstacleHeight;
    }

    // Check for scoring
    if (obstacleX + obstacleWidth < 55) {
      score++;
      Paint_DrawString_EN(140, 84, (std::to_string(score)).c_str(), &Font16, BLUE, RED);
      generateObstacle();
    }

    //generateObstacle();
  }
}