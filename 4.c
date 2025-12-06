#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>

bool checkLeft(char** grid, int row, int col, int rows, int cols) {
  if (col == 0) return false;
  return grid[row][col-1] == '@';
}

bool checkRight(char** grid, int row, int col, int rows, int cols) {
  if (col == cols - 1) return false;
  return grid[row][col+1] == '@';
}

bool checkTop(char** grid, int row, int col, int rows, int cols) {
  if (row == 0) return false;
  return grid[row-1][col] == '@';
}

bool checkBottom(char** grid, int row, int col, int rows, int cols) {
  if (row == rows - 1) return false;
  return grid[row+1][col] == '@';
}

bool checkLowerLeft(char** grid, int row, int col, int rows, int cols) {
  if (col == 0 || row == rows - 1) return false;
  return grid[row+1][col-1] == '@';
}

bool checkUpperLeft(char** grid, int row, int col, int rows, int cols) {
  if (col == 0 || row == 0) return false;
  return grid[row-1][col-1] == '@';
}

bool checkLowerRight(char** grid, int row, int col, int rows, int cols) {
  if (col == cols - 1 || row == rows - 1) return false;
  return grid[row+1][col+1] == '@';
}

bool checkUpperRight(char** grid, int row, int col, int rows, int cols) {
  if (col == cols - 1 || row == 0) return false;
  return grid[row-1][col+1] == '@';
}

bool canAccess(char** grid, int row, int col, int rows, int cols) {
  int adjacentCount = 0;
  adjacentCount += checkLeft(grid, row, col, rows, cols) ? 1 : 0;
  adjacentCount += checkRight(grid, row, col, rows, cols) ? 1 : 0;
  adjacentCount += checkTop(grid, row, col, rows, cols) ? 1 : 0;
  adjacentCount += checkBottom(grid, row, col, rows, cols) ? 1 : 0;
  adjacentCount += checkLowerLeft(grid, row, col, rows, cols) ? 1 : 0;
  adjacentCount += checkUpperLeft(grid, row, col, rows, cols) ? 1 : 0;
  adjacentCount += checkLowerRight(grid, row, col, rows, cols) ? 1 : 0;
  adjacentCount += checkUpperRight(grid, row, col, rows, cols) ? 1 : 0;

  return adjacentCount < 4;
}

int getLineCount(char* filename) {
  FILE* file = fopen(filename, "r");
  if (!file) {
    printf("failed to open file\n");
    return -1;
  }

  int lineCount = 0;
  char str[256];
  while (fgets(str, sizeof(str), file)) {
    lineCount++;
  }

  fclose(file);

  return lineCount;
}

int main() {
  char* filename = "input/4/long.txt";
  FILE* file = fopen(filename, "r");
  if (!file) {
    printf("Failed to open file\n");
    return -1;
  }
  char line[256];
  int linesIndex = 0;
  int lineCount = getLineCount(filename);
  printf("lineCount: %d\n", lineCount);
  char* grid[lineCount];
  while (fgets(line, sizeof(line), file)) {
    line[strcspn(line, "\n")] = '\0';
    grid[linesIndex] = calloc(256, sizeof(char));
    memcpy(grid[linesIndex], &line, sizeof(line));
    linesIndex++;
  }



  int rows = sizeof(grid)/sizeof(char*);
  int cols = strlen(grid[0]);
  printf("rows=%d\n", rows);
  printf("cols=%d\n", cols);

  int accessibleCount = 0;
  for (int r=0; r<rows; r++) {
    for (int c=0; c<cols; c++) {
      if (grid[r][c] != '@') continue;
      if (canAccess(grid, r, c, rows, cols)) {
        // printf("r=%d c=%d\n", r, c);
        accessibleCount++;
      }
    }
  }
  printf("result=%d\n", accessibleCount);



}
