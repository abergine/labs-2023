#include "db.h"

void WriteToBinaryFile(CommandsVARKT* arr, int length, char *fileName) {
    FILE *f = fopen(fileName, "w+");
    if (f == NULL){
        exit(-1);
    }
    fwrite(arr, sizeof(CommandsVARKT), length, f);

    fclose(f);
}

int ReadFromBinaryFile(CommandsVARKT* arr, int MaxObject, char *fileName) {
    FILE *f = fopen(fileName, "rb"); // открываем файл для чтения в бинарном режиме
    if (f == NULL){
        return -1;
    }

    // Считываем данные по одной записи и сдвигаем позицию указателя файла после каждой записи
    int i = 0;
    while (fread(&arr[i], sizeof(CommandsVARKT), 1, f)) {
        i++;
        if (i >= MaxObject) // если достигнуто максимальное количество объектов, прекращаем чтение
            break;
    }

    fclose(f);

    return i; // возвращаем количество считанных объектов
}


void WriteToCsv(CommandsVARKT* arr, int length, char *fileName) {
    FILE *f = fopen(fileName, "w+");
    if (f == NULL){
        exit(-1);
    }
    for (int i = 0; i < length; i++) {
        fprintf(f, "%s %s %d %d %d %d\n", arr[i].commandName, arr[i].titleProject, arr[i].participants, arr[i].createResearchDoc, arr[i].checkReqsearchDoc, arr[i].passedProject);
    }

    fclose(f);
}


int ReadFromCsv(CommandsVARKT* arr, int MaxObject, char *fileName) {
    FILE *f = fopen(fileName, "r");
    if (f == NULL) {
        return -1;
    }

    int i = 0;
    while (fscanf(f, "%s %s %d %d %d %d", arr[i].commandName, arr[i].titleProject, &arr[i].participants, &arr[i].createResearchDoc, &arr[i].checkReqsearchDoc, &arr[i].passedProject) == 6) {
        i++;
        if (i >= MaxObject) // если достигнуто максимальное количество объектов, прекращаем чтение
            break;
    }

    fclose(f);

    return i; // возвращаем количество считанных объектов
}
