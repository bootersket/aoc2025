#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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
void parseRange(char* str, int* start, int* end) {
  // printf("\nparseRange():\n");
  // printf("parseRange str: '%s'\n", str);
  char* ptr;
  ptr = strtok(str, "-");
  while (ptr != NULL) {
    if (*start == -1) *start = atoi(ptr);
    else if (*end == -1) *end = atoi(ptr);
    ptr = strtok(NULL, "-");
  }
  // printf("start=%d  end=%d\n", *start, *end);
  // printf("\n");
}

typedef struct {
  int start;
  int end;
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
  int start, end;
  ProductIDRange* pirs = malloc(substringIdx * sizeof(ProductIDRange));
  for (int i=0; i<substringIdx; i++) {
    pirs[i].start = -1;
    pirs[i].end = -1;
    parseRange(substrings[i], &pirs[i].start, &pirs[i].end);
  }

  return pirs;
}

void printPIR(ProductIDRange pir) {
  printf("start=%d  end=%d\n", pir.start, pir.end);
}

bool isValid(char* numStr) {
  printf("\nnumStr: %s\n", numStr);
  int length = strlen(numStr);
  if (length % 2 != 0) return true;

  printf("length/2 = %d\n", length/2);
  // char firstHalf[length/2];
  // char firstHalf[2];
  // char secondHalf[length/2];
  // memset(firstHalf, 0, sizeof(char)*length/2);
  char* firstHalf = calloc(length, sizeof(char));

  int firstHalfIndex = 0;

  for (int i=0; i<length/2; i++) {
    firstHalf[firstHalfIndex++] = numStr[i];
  }
  printf("firstHalf: '%s'\n", firstHalf);

}


// WILO: resolved: issue was that arr[n] gives you n characters.
// if you then plan on using all of those chars for firstHalf, then
// you have no null character. 
// i.e. firstHalf needs to be length/2 + 1, and ditto for the memset.


int main() {
  // char str[] = "1-2,3-4,5-6";
  // int pirCount = getProductIDRangeCount(str);
  // ProductIDRange* pirs = parseDatabaseStr(str);
  // for (int i=0; i<pirCount; i++) {
  //   printPIR(pirs[i]);
  // }

  // printf("%s -> %s\n", "123", isValid("123") ? "valid" : "invalid");
  // printf("%s -> %s\n", "1", isValid("1") ? "valid" : "invalid");
  // printf("%s -> %s\n", "11", isValid("11") ? "valid" : "invalid");
  printf("%s -> %s\n", "4545", isValid("4545") ? "valid" : "invalid");
  // printf("%s -> %s\n", "1188511885", isValid("1188511885") ? "valid" : "invalid");
  // printf("%s -> %s\n", "446446", isValid("446446") ? "valid" : "invalid");



  return 0;

}
