#ifndef MYGREP_H
#define MYGREP_H

#define MAX_LEN 100

typedef struct line Line;
typedef struct longestLine LongestLine;

struct line {
    char lineData[MAX_LEN];
    int lineNum;
    int wordNum;
    Line *next;
};

struct longestLine {
    char lineData[MAX_LEN];
    int length;
};

void processFile(FILE *in, Line **current, LongestLine *longest, int *occur, int *lines, char *search);
void outputData(char **args, LongestLine *longest, int lines, int occurs, Line *current); 

#endif
