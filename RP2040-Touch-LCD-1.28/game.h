#ifndef game_H
#define game_H
extern bool inTransition;
extern bool pauseRender;
extern bool tap;
extern UWORD *BlackImage;
extern std::list<std::string> backgroundApps;
bool swipe(std::string dir, int thresh);
void openApp(std::string app, std::string dir, int start);
#endif


#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>



std::vector<std::vector<int>> board = {
  { 0, 0, 0, 0 },
  { 0, 2, 0, 0 },
  { 0, 0, 2, 0 },
  { 0, 0, 0, 0 }
};



void renderBoard() {
  // Cell size and padding
  int cellSize = 50;
  int padding = 5;

  //for (int i = 0; i < 4; ++i) {
  for (size_t i = 0; i < board.size(); ++i) {
    for (size_t j = 0; j < board[i].size(); ++j) {
      //for (int j = 0; j < 4; ++j) {
      // Calculate position for each cell
      int x = 12 + j * (cellSize + padding);
      int y = 12 + i * (cellSize + padding);

      // Get the value in the current cell
      int cellValue = board[i][j];

      // Set color based on cell value (you can customize this logic)
      uint16_t color;
      switch (cellValue) {
        case 0:
          color = GRAY;
          break;
        case 2:
          color = GREEN;
          break;
        case 4:
          color = RED;
          break;
        case 8:
          color = BLUE;
          break;
        case 16:
          color = BROWN;
          break;
        case 32:
          color = CYAN;
          break;
        case 64:
          color = MAGENTA;
          break;
        case 128:
          color = BRED;
          break;
        case 256:
          color = GBLUE;
          break;
        case 512:
          color = GRED;
          break;
        case 1024:
          color = BRRED;
          break;
        case 2048:
          color = YELLOW;
          break;
        // Add more cases for other values
        default:
          color = WHITE;
      }

      // Render the cell
      Paint_DrawRectangle(x, y, x + cellSize, y + cellSize, color, DOT_PIXEL_1X1, DRAW_FILL_FULL);
      if (cellValue != 0) {
        Paint_DrawString_EN(x + 5, y + 5, (std::to_string(cellValue)).c_str(), &Font12, color, BLACK);
      }
      // You can add additional rendering for the cell value if needed
    }
  }
}


// Function to get a specific column from the board
std::vector<int> getColumn(const std::vector<std::vector<int>> &board, int columnIndex) {
  std::vector<int> column;
  for (const auto &row : board) {
    column.push_back(row[columnIndex]);
  }
  return column;
}

// Function to set a specific column in the board
void setColumn(std::vector<std::vector<int>> &board, int columnIndex, const std::vector<int> &column) {
  for (size_t i = 0; i < board.size(); ++i) {
    board[i][columnIndex] = column[i];
  }
}

void compressLine(std::vector<int> &line, const std::string &direction) {
  int size = line.size();
  std::vector<int> compressedLine(size, 0);

  int index = (direction == "left" || direction == "up") ? 0 : size - 1;
  int step = (direction == "left" || direction == "up") ? 1 : -1;

  for (int i = 0; i < size; ++i) {
    if (line[i] != 0) {
      compressedLine[index] = line[i];
      index += step;
    }
  }

  // Update the original line with the compressed values
  line = compressedLine;
}

void mergeLine(std::vector<int> &line, const std::string &direction) {
  int size = line.size();

  int start = (direction == "left" || direction == "up") ? 0 : size - 1;
  int end = (direction == "left" || direction == "up") ? size - 1 : 0;
  int step = (direction == "left" || direction == "up") ? 1 : -1;

  // Merge similar adjacent elements
  for (int i = start; i != end; i += step) {
    if (line[i] == line[i + step] && line[i] != 0) {
      // Merge the adjacent equal elements
      line[i] *= 2;
      line[i + step] = 0;
    }
  }

  // Compress the line after merging
  compressLine(line, direction);
}

void compressAndMerge(std::vector<std::vector<int>> &board, const std::string &directionA) {
  std::string direction = "left";
  if (directionA == "up") {
    direction = "left";
  } else if (directionA == "down") {
    direction = "right";
  } else if (directionA == "left") {
    direction = "up";
  } else if (directionA == "right") {
    direction = "down";
  }


  int size = board.size();

  // Define the direction-specific indices for iteration
  int start = (direction == "left" || direction == "down") ? 0 : size - 1;
  int end = (direction == "left" || direction == "down") ? size : -1;
  int step = (direction == "left" || direction == "down") ? 1 : -1;

  for (int i = 0; i < size; ++i) {
    std::vector<int> currentLine;
    if (direction == "up" || direction == "down") {
      currentLine = board[i];
    } else {
      currentLine = getColumn(board, i);
    }

    // Compress and merge the line
    compressLine(currentLine, direction);
    mergeLine(currentLine, direction);

    // Update the board based on the modified line
    if (direction == "up" || direction == "down") {
      board[i] = currentLine;
    } else {
      setColumn(board, i, currentLine);
    }
  }
}

void addRandomNumber(std::vector<std::vector<int>> &board) {
  // Seed for random number generation
  std::srand(std::time(0));

  // Find all empty cells on the board
  std::vector<std::pair<int, int>> emptyCells;
  for (int i = 0; i < board.size(); ++i) {
    for (int j = 0; j < board[i].size(); ++j) {
      if (board[i][j] == 0) {
        emptyCells.push_back(std::make_pair(i, j));
      }
    }
  }

  // Check if there are empty cells to add a number
  if (!emptyCells.empty()) {
    // Randomly select an empty cell
    int randomIndex = std::rand() % emptyCells.size();
    int randomValue = 2;  //(std::rand() % 2 + 1) * 2; // Randomly choose between 2 and 4

    // Assign the random value to the selected cell
    board[emptyCells[randomIndex].first][emptyCells[randomIndex].second] = randomValue;
  } else {
    // If no empty cells, set the board to all zeros
    for (int i = 0; i < board.size(); ++i) {
      for (int j = 0; j < board[i].size(); ++j) {
        board[i][j] = 0;
      }
    }
  }
}



void game() {
  renderBoard();

  if (inTransition == false) {

    if (swipe("right", 70)) {
      compressAndMerge(board, "right");
      addRandomNumber(board);
    } else if (swipe("left", 70)) {
      compressAndMerge(board, "left");
      addRandomNumber(board);
    } else if (swipe("down", 70)) {
      compressAndMerge(board, "down");
      addRandomNumber(board);
    } else if (swipe("up", 190)) {
      compressAndMerge(board, "up");
      addRandomNumber(board);
    };
    if (pauseRender == false) {
      //LCD_1IN28_DisplayWindows(0, 0, 240, 240, BlackImage);
      LCD_1IN28_Display(BlackImage);  //Faster????
    }


    //if(Touch_CTS816.y_point > 210 && tapHeld > 5){
    //  openApp("recentApps", "UD", Touch_CTS816.y_point);
    //};
  }
}