#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "myGrep.h"

#define MAX_LEN 100

int main(int argc, char *argv[]) {
    
    FILE *infile = NULL;
    Line *head = NULL;
    LongestLine longest;
    int numOccur = 0;
    int lineNum = 0;
    longest.length = 0;

    if (argc != 3) { 
        printf("myGrep: improper number of arguments\nUsage: ./a.out <filename> <word>\n");
        return 1;
    }

    infile = fopen(argv[1], "r");
    if (!infile) {
        printf("Unable to open file: %s\n", argv[1]);
        return 1;
    }

    processFile(infile, &head, &longest, &numOccur, &lineNum, argv[2]);
    outputData(argv, &longest, lineNum, numOccur, head);
    return 0;
}

void processFile(FILE *in, Line **current, LongestLine *longest, int *occur, int *lineNum, char *search) {
    
    char lineData[MAX_LEN];
    char countChar[MAX_LEN];

    while(fgets(lineData, MAX_LEN, in)) {
        int length = strlen(lineData);
        char *word = NULL;
        int wordNum = 0;

        if (length > longest->length) {
            longest->length = length;
            strcpy(longest->lineData, lineData);
        }

        strcpy(countChar, lineData);
        word = strtok(countChar, " .,\n");
        while (word) {
            if (strcmp(word, search) == 0) {
                Line *temp = (Line*)malloc(sizeof(Line)); 
                if (!temp) {
                    printf("Cannot allocate required memory");
                    exit(1);
                }
                strcpy(temp->lineData, lineData);
                temp->lineNum = *lineNum;
                temp->wordNum = wordNum;
                temp->next = NULL;
                if (*occur == 0)
                    *current = temp;
                else {
                    (*current)->next = temp;
                    current = &((*current)->next);
                }
                (*occur)++;
            }
            wordNum++;
            word = strtok(NULL, " .,\n");
        }
        (*lineNum)++;
    }
}

void outputData(char **args, LongestLine *longest, int lines, int occurs, Line *current) {
    printf("%s %s %s\n", *args, *(args + 1), *(args + 2));
    printf("longest line: %s", longest->lineData);
    printf("num chars: %d\n", longest->length);
    printf("num lines: %d\n", lines);
    printf("total occurrences of word: %d\n", occurs);
    while(current) {
        printf("line %d; word %d; %s", current->lineNum, current->wordNum, current->lineData);
        current = current->next;
    }
}
