#include "db.h"
#include <string.h>


int main(int argc, char *argv[]) {
    if (argc != 2 && argc != 3) {
        printf("Использование: %s <имя_файла_базы_данных> [--count]\n", argv[0]);
        return -1;
    }

    CommandsVARKT arr[100];
    if (!strcmp(argv[1], "base.db")) {
        printf("Выбран файл базы данных: %s\n", argv[1]);
        int numObjects = ReadFromBinaryFile(arr, 100, "base.db");
        if (numObjects == -1) {
            printf("Ошибка чтения из базы данных: файла не существует или он пустой.\n");
            return -1;
        }

        printf("Объектов прочитано из БД: %d.\n", numObjects);

        int filterCount = 0;
        if (argc == 3 && !strcmp(argv[2], "--count")) {
            filterCount = 1;
        }
        
        if (filterCount) {
            CommandsVARKT filteredArr[100];
            int j = 0;
            for (int i = 0; i < numObjects; i++) {
                if (arr[i].participants > 3) {
                    filteredArr[j] = arr[i];
                    j++;
                }
            }
            WriteToCsv(filteredArr, j, "table.csv");
            printf("Файл table.csv успешно создан с фильтрацией по полю participants.\n");
        } else {
            WriteToCsv(arr, numObjects, "table.csv");
            printf("Файл table.csv успешно создан.\n");
        }
    } else if (!strcmp(argv[1], "table.csv")) {
        printf("Выбран csv файл: %s\n", argv[1]);
        int numObjects = ReadFromCsv(arr, 100, "table.csv");
        if (numObjects < 0) {
            printf("Ошибка чтения из файла table.csv.\n");
            return -1;
        }

        printf("Объектов прочитано: %d.\n", numObjects);

        int filterCount = 0;
        if (argc == 3 && !strcmp(argv[2], "--count")) {
            filterCount = 1;
        }
        
        if (filterCount) {
            CommandsVARKT filteredArr[100];
            int j = 0;
            for (int i = 0; i < numObjects; i++) {
                if (arr[i].participants > 3) {
                    filteredArr[j] = arr[i];
                    j++;
                }
            }
            WriteToBinaryFile(filteredArr, j, "base.db");
            printf("Данные успешно записаны в базу данных с фильтрацией по полю participants.\n");
        } else {
            WriteToBinaryFile(arr, numObjects, "base.db");
            printf("Данные успешно записаны в базу данных.\n");
        }
    } else {
        printf("Неверное имя файла: %s\n", argv[1]);
        return -1;
    }

    return 0;
}
