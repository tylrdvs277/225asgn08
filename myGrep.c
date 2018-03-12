#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "myGrep.h"

#define MAX_LEN 100

int main(int argc, char *argv[]) {
    
    FILE *infile = NULL;
    Line head;
    LongestLine longest;
    int numOccur;
    int lineNum;

    if (argc != 3) { 
        printf("myGrep: improper number of arguments\nUsage: ./a.out <filename> <word>\n");
        return 1;
    }

    infile = fopen(argv[1], "r");
    if (infile == NULL) {
        printf("Unable to open file: %s\n", argv[1]);
        return 1;
    }

    processFile(infile, &head, &longest, &numOccur, &lineNum, argv[2]);
    outputData(argv, &longest, lineNum, numOccur, &head);
    return 0;
}

void processFile(FILE *in, Line *current, LongestLine *longest, int *occur, int *lines, char *search) {
    
    char lineData[MAX_LEN];
    char countChar[MAX_LEN];
    
    longest.lineData = "\n";
    longest.length = 0;

    *lines = 0;
    *occur = 0;
    while(fgets(lineData, MAX_LEN, in) != NULL) {
        int length = strlen(lineData);
        char *word = NULL;
        int wordNum;

        if (length > longest->length) {
            longest->length = length;
            strcpy(longest->lineData, lineData);
        }

        wordNum = 0;
        (*lines)++;
        strcpy(countChar, lineData);
        strip(countChar);
        word = strtok(countChar, " ");
        while (word != NULL) {
            if (strcmp(word, search)== 0) {
                (*occur)++;
                addEntry(current, lineData, *lines, wordNum);
                current = current->next;
            }
            wordNum++;
            word = strtok(NULL, " ");
        }
    }
}


void strip(char *chars) {
    while (*chars != '\0') {
        if (!((*chars >= 'a' && *chars <= 'z' )||(*chars >= 'A' && *chars <= 'Z')))
            *chars = ' ';
        chars++;
    }
}

void addEntry(Line *newEntry, char *line, int lineNum, int wordNum) {
    strcpy(newEntry->lineData, line);
    newEntry->lineNum = lineNum;
    newEntry->wordNum = wordNum;
    newEntry->next = (Line*)malloc(sizeof(Line));
}

void outputData(char **args, LongestLine *longest, int lines, int occurs, Line *current) {
    int i;
    printf("%s %s %s\n", *args, *(args + 1), *(args + 2));
    printf("longest line: %s", longest->lineData);
    printf("num chars: %d\n", longest->length);
    printf("num lines: %d\n", lines);
    printf("total occurences of word: %d\n", occurs);
    for (i = 0; i < occurs; i++) {
        printf("line %d; word %d; %s", current->lineNum, current->wordNum, current->lineData);
        current = current->next;
    }
}
