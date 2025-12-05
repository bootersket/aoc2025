#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>

/* Helper function to print where null
 * characters are in a string */
void printHardcore(char* str, int length) {
  for (int i=0; i<length; i++) {
    if (str[i] == '\0') printf("\\0");
    else printf("%c", str[i]);
  }
  printf("\n");
}

/* Takes input like "1-2" or "345-499" and 
 * returns (via params) the numbers eg.
 * "1-2"     -> start=1    end=2
 * "345-499" -> start=345  end=499
 * */
void parseRange(char* str, long* start, long* end) {
  // printf("\nparseRange():\n");
  // printf("parseRange str: '%s'\n", str);
  char* ptr;
  ptr = strtok(str, "-");
  while (ptr != NULL) {
    if (*start == -1) *start = atol(ptr);
    else if (*end == -1) *end = atol(ptr);
    ptr = strtok(NULL, "-");
  }
  // printf("start=%d  end=%d\n", *start, *end);
  // printf("\n");
}

typedef struct {
  long start;
  long end;
} ProductIDRange;

int getProductIDRangeCount(char* databaseStr) {
  char* ptr = databaseStr;
  int count = 0;
  while (*ptr != '\0') {
    if (*ptr == '-') count++;
    ptr++;
  }
  return count;
}

ProductIDRange* parseDatabaseStr(char* databaseStr) {
  char* ptr;
  ptr = strtok(databaseStr, ",");

  char* ptrCopy = calloc(64, sizeof(char));

  char* substrings[256];
  int substringIdx = 0;

  /*---------------------
    EXTRACT SUBSTRINGS
  ---------------------*/
  while (ptr != NULL) {
    substrings[substringIdx] = strdup(ptr);
    strcpy(substrings[substringIdx], ptr);

    // printf("substrings[%d] = '%s'\n", substringIdx, substrings[substringIdx]);

    substringIdx++;


    ptr = strtok(NULL, ",");
  }

  /*---------------------
     PARSE SUBSTRINGS
  ---------------------*/
  long start, end;
  ProductIDRange* pirs = malloc(substringIdx * sizeof(ProductIDRange));
  printf("substringIdx: %d\n", substringIdx);
  for (int i=0; i<substringIdx; i++) {
    pirs[i].start = -1;
    pirs[i].end = -1;
    parseRange(substrings[i], &pirs[i].start, &pirs[i].end);
    printf("pirs[i].start= %ld\n", pirs[i].start);
    printf("pirs[i].end= %ld\n", pirs[i].end);
  }

  return pirs;
}

void printPIR(ProductIDRange pir) {
  printf("start=%ld  end=%ld\n", pir.start, pir.end);
}

bool isValid(char* numStr) {
  int length = strlen(numStr);
  if (length % 2 != 0) return true;

  char* p1 = numStr;
  char* p2 = numStr + length/2;

  while (*p2 != '\0') {
    if (*p1 != *p2) return true;
    p1++;
    p2++;
  }
  return false;
}

char* numToStr(long num) {
  /* Count number of digits */ 
  int numOfDigits = ceil(log10(num+1));
  char* s = calloc(numOfDigits, sizeof(char));
  sprintf(s, "%ld", num);
  return s;
}

void checkRange(ProductIDRange pir, long long* invalidSum) {
  printf("checkRange\n");
  printf("pir.start=%ld  pir.end=%ld\n", pir.start, pir.end);
  for (long i=pir.start; i<=pir.end; i++) {
    // printf("i=%ld\n", i);
    char* numStr = numToStr(i);
    if (!isValid(numStr)) *invalidSum += i;
  }
}




int main() {
  printf("LONG_MAX = %ld\n", LONG_MAX);
  FILE* file = fopen("input/2/long.txt", "r");
  if (!file) {
    printf("Failed to open file\n");
    return -1;
  }
  char line[4096];
  fgets(line, sizeof(line), file);
  // printf("%s", line);





  int pirCount = getProductIDRangeCount(line);
  ProductIDRange* pirs = parseDatabaseStr(line);
  long long invalidSum = 0;
  for (int i=0; i<pirCount; i++) {
    printf("main loop i=%d\n", i);
    checkRange(pirs[i], &invalidSum);
  }
  printf("%lld\n", invalidSum);

  return 0;

}
/*
999,999,999,999 is too high
 * */
