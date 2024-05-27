#ifndef __DB__
#define __DB__
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct CommandsVARKT {
    char commandName[100];
    char titleProject[100];
    int participants;
    int createResearchDoc;
    int checkReqsearchDoc;
    int passedProject;
} CommandsVARKT;

void WriteToBinaryFile(CommandsVARKT* arr, int length, char *fileName);
int ReadFromBinaryFile(CommandsVARKT* arr, int MaxObject, char *fileName);
void WriteToCsv(CommandsVARKT* arr, int length, char *fileName);
int ReadFromCsv(CommandsVARKT* arr, int MaxObject, char *fileName);

#endif