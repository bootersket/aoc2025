#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>

int main() {
  printf("LONG_MAX = %ld\n", LONG_MAX);
  FILE* file = fopen("input/2/long.txt", "r");
  if (!file) {
    printf("Failed to open file\n");
    return -1;
  }
  char line[4096];
  fgets(line, sizeof(line), file);


}
