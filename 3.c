#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>

typedef struct {
  char* bankStr;
  struct {
    int index;
    int value;
  } battery1;
  struct {
    int index;
    int value;
  } battery2;
} BatteryBank;

typedef BatteryBank BB;

BatteryBank parseLine(char* line) {
  BB bb;
  bb.bankStr = line;
  bb.battery1.index = -1;
  bb.battery1.value = -1;
  bb.battery2.index = -1;
  bb.battery2.value = -1;

  return bb;

}

int getLinesFromFile(char* filename, char** lines) {
  FILE* file = fopen(filename, "r");
  if (!file) {
    printf("Failed to open file\n");
    return -1;
  }

  char line[256];
  int linesIndex = 0;
  while (fgets(line, sizeof(line), file)) {
    line[strcspn(line, "\n")] = '\0';
    lines[linesIndex] = calloc(256, sizeof(char));
    memcpy(lines[linesIndex], &line, sizeof(line));
    linesIndex++;
  }

  return linesIndex;

}

void findBatteries(BB* bb) {
  char* ptr = bb->bankStr;
  int i = 0;
  /*------------------------------------
    First loop to find max num
  ------------------------------------*/
  // todo could clean this up and not have two loops.
  while (*ptr != '\0' && *(ptr+1) != '\0') {
    int currentValue = *ptr - '0'; // Convert current char into int eg. '1' -> 1
    if (currentValue > bb->battery1.value) {
      bb->battery1.value = currentValue;
      bb->battery1.index = i;
    }
    ptr++;
    i++;
  }

  /*------------------------------------
    Second loop to find max num after
    first max num
  ------------------------------------*/
  ptr = bb->bankStr + bb->battery1.index + 1;
  i = ptr - bb->bankStr;
  while (*ptr != '\0') {
    int currentValue = *ptr - '0'; // Convert current char into int eg. '1' -> 1
    if (currentValue > bb->battery2.value && i != bb->battery1.index) {
      bb->battery2.value = currentValue;
      bb->battery2.index = i;
    }
    ptr++;
    i++;
  }
  printf("%s -> %d%d\n", bb->bankStr, bb->battery1.value, bb->battery2.value);

}

void printBatteryBank(BB bb) {
  printf("BatteryBank: '%s' -> %d@%d  %d@%d\n",
      bb.bankStr,
      bb.battery1.value,
      bb.battery1.index,
      bb.battery2.value,
      bb.battery2.index
      );
}

int main() {
  char* lines[500];
  int linesRead = getLinesFromFile("input/3/long.txt", lines);
  BB bbs[linesRead];
  for (int i=0; i<linesRead; i++) {
    bbs[i] = parseLine(lines[i]);
  }

  int totalJoltage = 0;
  for (int i=0; i<linesRead; i++) {
    // printBatteryBank(bbs[i]);
    findBatteries(&bbs[i]);
    int b1Value = bbs[i].battery1.value;
    int b2Value = bbs[i].battery2.value;

    totalJoltage += b1Value*10 + b2Value;
  }

  printf("total joltage: %d\n", totalJoltage);

  // BB bb;
  // bb.bankStr = "811111111111119\n";
  // bb.battery1.index = -1;
  // bb.battery1.value = -1;
  // bb.battery2.index = -1;
  // bb.battery2.value = -1;
  // findBatteries(&bb);
  // printf("manual: %s -> %d%d", bb.bankStr, bb.battery1.value, bb.battery2.value);
  //



}
