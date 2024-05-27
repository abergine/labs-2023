#include "db.h"
#include <string.h>

int main() {
    CommandsVARKT arr[2]; // Создаем массив структур для хранения данных

    // Заполняем тестовыми данными
    strcpy(arr[0].commandName, "command1");
    strcpy(arr[0].titleProject, "project1");
    arr[0].participants = 4;
    arr[0].createResearchDoc = 1;
    arr[0].checkReqsearchDoc = 1;
    arr[0].passedProject = 1;

    strcpy(arr[1].commandName, "command2");
    strcpy(arr[1].titleProject, "project2");
    arr[1].participants = 3;
    arr[1].createResearchDoc = 0;
    arr[1].checkReqsearchDoc = 1;
    arr[1].passedProject = 0;

    // Записываем данные в базу данных
    WriteToBinaryFile(arr, 2, "base.db");

    return 0;
}
