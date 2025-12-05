#include <stdio.h>
#include <stdlib.h>
#include <string.h>


enum {
  LEFT,
  RIGHT
};

typedef struct {
  int direction; // LEFT or RIGHT
  int distance;
} DialEntry;

int max(int a, int b) {
  if (a >= b) return a;
  else return b;
}

DialEntry parseLine(char* line) {
  DialEntry dialEntry;
  if (line[0] == 'L') {
    dialEntry.direction = LEFT;
  }
  else {
    dialEntry.direction = RIGHT;
  }
  dialEntry.distance = strtol(line+1, NULL, 10);
  return dialEntry;
}

int getLinesFromFile(char* filename, char** lines) {
  FILE* file;
  file = fopen(filename, "r");
  if (file == NULL) {
    printf("ERROR: unable to open file '%s'\n", filename);
    return -1;
  }

  char line[256];
  int linesIndex = 0;
  while (fgets(line, sizeof(line), file)) {
    // printf("A%sB", line);
    lines[linesIndex] = calloc(256, sizeof(char));
    memcpy(lines[linesIndex], &line, sizeof(line));
    linesIndex++;
  }
  return linesIndex;
}

void printDialEntry(DialEntry de) {
  printf("direction = %s\n", de.direction == LEFT ? "LEFT" : "RIGHT");
  printf("distance = %d\n", de.distance);
}

void part1(DialEntry dialEntries[], int dialEntriesCount) {
  /* THE ACTUAL PROBLEM */
  int DIAL_SIZE = 100;
  int dialValue = 50;
  int zeroCount = 0;
  for (int i=0; i<dialEntriesCount; i++) {
    DialEntry de = dialEntries[i];
    if (de.direction == LEFT) {
      dialValue -= de.distance % DIAL_SIZE;
    }
    else {
      dialValue += de.distance % DIAL_SIZE;
    }

    printf("Move %s %d\n",
        de.direction == LEFT ? "left" : "right",
        de.distance);

    // Account for wrapping
    if (dialValue < 0) dialValue += DIAL_SIZE;
    dialValue %= DIAL_SIZE;

    printf("Now at %d\n\n", dialValue);
    if (dialValue == 0) zeroCount++;
  }
  printf("zeroCount = %d\n", zeroCount);
}

void part2(DialEntry dialEntries[], int dialEntriesCount) {
  /* THE ACTUAL PROBLEM */
  int DIAL_SIZE = 100;
  int dialValue = 50;
  int zeroCount = 0;
  int prevDialValue;

  for (int i=0; i<dialEntriesCount; i++) {
    printf("\n");
    DialEntry de = dialEntries[i];
    printDialEntry(de);
    prevDialValue = dialValue;



wilo: cant figure this out for the life of me.
        I at least have simple test cases where I can see the issue. sort of.
        The problematic test cases are things like:
        Ln/2
        Rn

        and

        Rn/2
        Ln

        but if I modify the logic to get these to work, then my short.txt
        doesn't work.

        need to take a break because the semantic fatigue is bad.
        
        but part of the issue is something to do with having fullcircles
        and landing on zero. because in some cases, it's necessary to check
        if we're currently on zero to count that as a zero tick.
          but also if there's a fullcircle involved (eg. start at 0, move n,
              end at 0) then to count the fullcircle AND the final 0 position,
              it causes a double count.
        Very confused, but I hope a break will help it be more approachable.

    /*-----------------
           LEFT
    -----------------*/
    if (de.direction == LEFT) {
      dialValue -= de.distance % DIAL_SIZE;
      printf("Move -%d\n", de.distance % DIAL_SIZE);
      int fullCircles = de.distance / DIAL_SIZE;
      printf("Full circles: %d\n", fullCircles);
      if (dialValue < 0) {
        dialValue += DIAL_SIZE;
        zeroCount++;
        printf("zc +1\n");
      }
      zeroCount += fullCircles;
    }

    /*-----------------
           RIGHT
    -----------------*/
    else if (de.direction == RIGHT) {
      dialValue += de.distance % DIAL_SIZE;
      printf("Move +%d\n", de.distance % DIAL_SIZE);
      int fullCircles = de.distance / DIAL_SIZE;
      printf("Full circles: %d\n", fullCircles);
      if (dialValue >= DIAL_SIZE) {
        dialValue -= DIAL_SIZE;
        zeroCount++;
        printf("zc +1\n");
      }
      zeroCount += fullCircles;
    }
    // if (dialValue == 0) {
    //   printf("dv = 0 so zc++\n");
    //   zeroCount++;
    // }
    dialValue %= DIAL_SIZE;
    printf("dialValue: %d\n", dialValue);
  }
  printf("\nFinal zeroCount = %d\n\n", zeroCount);
}

int main() {
  /* PARSE INPUT */ 
  char* lines[10000];
  int linesRead = getLinesFromFile("input/1/short.txt", lines);
  // printf("linesRead = %d\n", linesRead);
  DialEntry dialEntries[linesRead];
  for (int i=0; i<linesRead; i++) {
    dialEntries[i] = parseLine(lines[i]);
  }

  /* THE PROBLEM */
  // part1(dialEntries, linesRead);
  part2(dialEntries, linesRead);

  DialEntry dialEntries1[] = {
    { .direction = LEFT,  .distance = 50 },
    { .direction = RIGHT, .distance = 100 }
  };
  DialEntry dialEntries2[] = {
    { .direction = RIGHT, .distance = 50 },
    { .direction = LEFT,  .distance = 100 }
  };
  // part2(dialEntries1, 2);
  // printf("\n\n\n");
  // part2(dialEntries2, 2);


  // todo: probably should free memory 
}
