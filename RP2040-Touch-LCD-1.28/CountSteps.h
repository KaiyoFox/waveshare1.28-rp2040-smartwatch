#ifndef CountSteps_H
#define CountSteps_H
extern bool inTransition;
extern bool pauseRender;
extern bool startup;
extern bool speedMode;
extern bool tap;
extern int CurTime;
extern int BPM;
extern int stepCount;
extern UWORD *BlackImage;
extern std::list<std::string> backgroundApps;
bool swipe(std::string dir, int thresh);
void openApp(std::string app, std::string dir, int start);
void QMI8658_read_xyz(float acc[3], float gyro[3], unsigned int *tim_count);
std::string internet_get(std::string url);
#endif

#include <cmath>

#define THRESHOLD_ACC 1500.5  //1.0
#define THRESHOLD_GYRO 300.0  //250.0//1.0






#define HEART_RATE_THRESHOLD 120.0  // Adjust this threshold based on your data

bool isHeartBeatDetected = false;
int heartRate = 0;
int lastHeartBeatTime = 0;



bool isStepDetected = false;
float acc[3], gyro[3];
unsigned int tim_count = 0;


#define MAX_VARIABLE_VALUES 100
float variable_values[MAX_VARIABLE_VALUES];
int variable_index = 0;

//float highestNumber;
void detectHeartRateOld() {
  // Calculate acceleration magnitude
  float accelerationMagnitude = sqrt(pow(acc[0], 2) + pow(acc[1], 2) + pow(acc[2], 2) - 1);

  // Check if acceleration exceeds threshold indicating a beat
  if (accelerationMagnitude > 135) {
    // Calculate time since last beat
    int currentTime = millis();
    int timeSinceLastBeat = currentTime - lastHeartBeatTime;

    // Update heart rate if time since last beat is reasonable (e.g., between 0.5 to 3 seconds)
    if (timeSinceLastBeat >= 500 && timeSinceLastBeat <= 3000 || timeSinceLastBeat >= 5000) {
      heartRate = 60000 / timeSinceLastBeat;  // Convert milliseconds to beats per minute
      lastHeartBeatTime = currentTime;
      isHeartBeatDetected = true;
    }
  } else {
    isHeartBeatDetected = false;
  }
}

void detectHeartRate() {
  heartRate = BPM;
}


void detectSteps() {

  QMI8658_read_xyz(acc, gyro, &tim_count);

  //openApp("TSETS", "", 0);
  //acc[0] up/down
  //acc[1] left/right
  //acc[2] closer/further

  float accelerationMagnitude = sqrt(pow(acc[0], 2) + pow(acc[1], 2) + pow(acc[2], 2) - 1);
  //Paint_DrawString_EN(153, 19, (std::to_string(accelerationMagnitude)).c_str(), &Font12, BLACK, GREEN);

  // Check gyroscope data to further refine step detection
  float gyroMagnitude = sqrt(pow(gyro[0], 2) + pow(gyro[1], 2) + pow(gyro[2], 2));
  //Paint_DrawString_EN(153, 100, (std::to_string(gyroMagnitude)).c_str(), &Font12, BLACK, RED);

  //if(gyroMagnitude > highestNumber){
  //  highestNumber = gyroMagnitude;
  //}

  //Paint_DrawString_EN(200, 100, (std::to_string(highestNumber)).c_str(), &Font12, BLACK, YELLOW);

  // Simple step detection: check if both acceleration and gyroscope data cross thresholds
  if (accelerationMagnitude > THRESHOLD_ACC && gyroMagnitude > THRESHOLD_GYRO) {
    if (!isStepDetected) {
      // New step detected
      stepCount++;
      isStepDetected = true;
    }
  } else {
    isStepDetected = false;
  }
}
//int beat = 0;
int startTime = 0;
int currentTimeR = 0;
int beatsIn15Sec = 0;

void CountSteps() {
  if (startup) {
    startup = false;
    speedMode = true;
    startTime = millis();
    QMI8658_init();
  }

  detectSteps();

  /*
  //Serial.print("Variable_1:");
  //Serial.println((round(gyro[2]/1)*1));
  if ((round(gyro[2] / 1) * 1) < 0 || (round(gyro[2] / 1) * 1) > 4) {
    if (isHeartBeatDetected == false) {
      beat += 1;
      Serial.println(beat);
      isHeartBeatDetected = true;
    }
  } else {
    isHeartBeatDetected = false;
  }
  currentTimeR = millis() - startTime;
  if (currentTimeR >= 15000) {
    beatsIn15Sec = beat;
    beat = 0;              // Reset step count for the next 15 seconds
    startTime = millis();  // Reset the start time
  }
  int heartRate = beatsIn15Sec * 4;
  */
  //^^ REAL OLD

  //detectHeartRate();
  heartRate = BPM;

  Paint_DrawRectangle(156, 26, 162, 27, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(153, 27, 165, 28, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(151, 28, 167, 29, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(149, 29, 168, 30, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(148, 30, 169, 31, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(147, 31, 170, 32, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(146, 32, 171, 33, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(145, 33, 172, 34, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(144, 34, 172, 35, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(143, 35, 173, 36, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(142, 36, 173, 37, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(141, 37, 174, 38, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(140, 38, 174, 39, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(140, 39, 174, 40, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(139, 40, 175, 41, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(138, 41, 175, 42, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(138, 42, 175, 43, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(137, 43, 175, 44, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(136, 44, 176, 45, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(136, 45, 176, 46, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(135, 46, 176, 47, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(135, 47, 176, 48, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(134, 48, 176, 49, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(134, 49, 176, 50, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(133, 50, 176, 51, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(133, 51, 176, 52, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(133, 52, 176, 53, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(132, 53, 177, 54, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(132, 54, 177, 55, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(131, 55, 177, 56, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(131, 56, 176, 57, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(77, 57, 83, 58, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(131, 57, 176, 58, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(74, 58, 86, 59, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(131, 58, 176, 59, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(72, 59, 88, 60, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(130, 59, 176, 60, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(71, 60, 90, 61, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(130, 60, 176, 61, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(70, 61, 91, 62, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(130, 61, 176, 62, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(69, 62, 92, 63, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(130, 62, 176, 63, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(68, 63, 93, 64, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(129, 63, 176, 64, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(67, 64, 94, 65, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(129, 64, 176, 65, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(67, 65, 95, 66, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(129, 65, 176, 66, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(66, 66, 96, 67, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(129, 66, 175, 67, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(66, 67, 97, 68, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(129, 67, 175, 68, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(65, 68, 98, 69, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(129, 68, 175, 69, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(65, 69, 99, 70, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(129, 69, 175, 70, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(65, 70, 99, 71, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(129, 70, 175, 71, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(64, 71, 100, 72, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(130, 71, 174, 72, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(64, 72, 101, 73, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(130, 72, 174, 73, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(64, 73, 101, 74, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(130, 73, 174, 74, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(64, 74, 102, 75, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(130, 74, 173, 75, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(63, 75, 103, 76, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(63, 76, 103, 77, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(130, 76, 173, 77, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(63, 77, 104, 78, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(130, 77, 172, 78, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(63, 78, 104, 79, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(130, 78, 172, 79, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(63, 79, 105, 80, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(130, 79, 171, 80, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(63, 80, 105, 81, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(130, 80, 170, 81, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(63, 81, 106, 82, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(130, 81, 170, 82, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(63, 82, 106, 83, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(131, 82, 169, 83, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(62, 83, 106, 84, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(131, 83, 168, 84, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(62, 84, 107, 85, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(131, 84, 168, 85, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(62, 85, 107, 86, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(132, 85, 167, 86, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(62, 86, 107, 87, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(132, 86, 166, 87, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(62, 87, 108, 88, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(133, 87, 166, 88, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(62, 88, 108, 89, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(134, 88, 165, 89, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(63, 89, 108, 90, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(136, 89, 164, 90, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(63, 90, 109, 91, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(63, 91, 109, 92, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(140, 91, 163, 92, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(63, 92, 109, 93, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(143, 92, 162, 93, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(63, 93, 109, 94, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(147, 93, 160, 94, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(63, 94, 110, 95, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(152, 94, 157, 95, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(63, 95, 110, 96, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(63, 96, 110, 97, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(127, 96, 131, 97, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(64, 97, 110, 98, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(125, 97, 133, 98, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(64, 98, 110, 99, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(125, 98, 136, 99, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(64, 99, 110, 100, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(124, 99, 138, 100, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(64, 100, 110, 101, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(124, 100, 141, 101, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(64, 101, 110, 102, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(124, 101, 144, 102, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(65, 102, 109, 103, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(123, 102, 151, 103, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(65, 103, 109, 104, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(123, 103, 157, 104, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(65, 104, 109, 105, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(123, 104, 158, 105, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(66, 105, 109, 106, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(123, 105, 159, 106, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(66, 106, 109, 107, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(123, 106, 159, 107, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(66, 107, 109, 108, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(123, 107, 160, 108, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(67, 108, 109, 109, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(123, 108, 159, 109, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(67, 109, 109, 110, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(123, 109, 159, 110, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(68, 110, 109, 111, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(123, 110, 159, 111, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(69, 111, 109, 112, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(123, 111, 159, 112, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(69, 112, 109, 113, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(123, 112, 159, 113, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(70, 113, 108, 114, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(123, 113, 158, 114, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(71, 114, 108, 115, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(123, 114, 158, 115, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(71, 115, 108, 116, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(124, 115, 158, 116, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(72, 116, 107, 117, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(124, 116, 157, 117, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(73, 117, 107, 118, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(125, 117, 157, 118, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(73, 118, 106, 119, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(125, 118, 156, 119, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(74, 119, 105, 120, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(126, 119, 155, 120, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(75, 120, 103, 121, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(126, 120, 154, 121, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(75, 121, 101, 122, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(127, 121, 154, 122, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(76, 122, 99, 123, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(128, 122, 153, 123, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(77, 123, 96, 124, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(129, 123, 151, 124, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(79, 124, 92, 125, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(130, 124, 150, 125, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(82, 125, 87, 126, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(132, 125, 148, 126, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(134, 126, 146, 127, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(108, 127, 112, 128, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(137, 127, 143, 128, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(106, 128, 114, 129, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(103, 129, 114, 130, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(101, 130, 115, 131, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(98, 131, 115, 132, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(95, 132, 115, 133, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(88, 133, 116, 134, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(82, 134, 116, 135, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(80, 135, 116, 136, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(80, 136, 116, 137, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(80, 137, 116, 138, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(79, 138, 116, 139, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(79, 139, 116, 140, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(80, 140, 116, 141, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(80, 141, 116, 142, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(80, 142, 116, 143, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(80, 143, 116, 144, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(81, 144, 116, 145, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(81, 145, 115, 146, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(81, 146, 115, 147, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(82, 147, 115, 148, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(82, 148, 114, 149, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(83, 149, 114, 150, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(84, 150, 113, 151, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(85, 151, 113, 152, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(85, 152, 112, 153, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(86, 153, 111, 154, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(88, 154, 110, 155, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(89, 155, 109, 156, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(91, 156, 107, 157, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(93, 157, 105, 158, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(96, 158, 102, 159, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(138, 90, 163, 91, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(130, 75, 173, 76, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);



  Paint_DrawString_EN(120 - ((17 * std::to_string(stepCount).length()) / 2), 200, (std::to_string(stepCount)).c_str(), &Font24, BLACK, WHITE);

  Paint_DrawString_EN(120 - ((17 * std::to_string(heartRate).length()) / 2), 175, (std::to_string(heartRate) + " BPM").c_str(), &Font24, BLACK, WHITE);

  //Paint_DrawString_EN(10, 120, internet_get("watch").c_str(), &Font16, RED, WHITE);
  //Serial.println(internet_get("watch").c_str());

  renderSnack();
  if (inTransition == false) {
    if (pauseRender == false) {
      //LCD_1IN28_DisplayWindows(0, 0, 240, 240, BlackImage);
      LCD_1IN28_Display(BlackImage);
    }

    // Recommended to Open any asked apps After rendering existing scene to prevent double render black bar
    //if (swipe("down", 70)) {
    //    openApp("main", "UD", Touch_CTS816.y_point);
    //}
    //if (Touch_CTS816.y_point > 210 && tapHeld > 5) {
    //    openApp("recentApps", "UD", Touch_CTS816.y_point);
    //}
  }
}
