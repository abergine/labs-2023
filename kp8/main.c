#include "list.h"
#include <stdio.h>

enum Command { EXIT, PUSH, PUSH_BACK, POP, POP_BACK, PRINT, CLEAR_IF_EXISTS, DELETE };

void MenuPrint() {
    printf("\n================================\n");
    printf("|| 0. exit                    ||\n"
           "|| 1. push by index           ||\n"
           "|| 2. push back               ||\n"
           "|| 3. pop by index            ||\n"
           "|| 4. pop back                ||\n"
           "|| 5. print list              ||\n"
           "|| 6. clear if value exists   ||\n"
           "|| 7. delete list             ||\n");
    printf("================================\n");
    printf("\nEnter a command: ");
}

int Menu() {
    List *list = ListCreate();
    while (1) {
        enum Command cmd;
        int index = 0;
        int value = 0;
        MenuPrint();
        scanf("%d", &cmd);
        switch (cmd) {
        case EXIT:
            printf("\nExiting the program...\n");
            return 0;
        case PUSH_BACK:
            printf("Enter a value: \n");
            scanf("%d", &value);
            ListPushBack(list, value);
            ListPrint(list);
            break;
        case PUSH:
            printf("Enter the index and value: \n");
            scanf("%d %d", &index, &value);
            ListInsertByIndex(list, value, index);
            ListPrint(list);
            break;
        case PRINT:
            ListPrint(list);
            break;
        case POP:
            printf("Enter an index: \n");
            scanf("%d", &index);
            ListPopByIndex(list, index);
            ListPrint(list);
            break;
        case POP_BACK:
            ListPopBack(list);
            ListPrint(list);
            break;
        case CLEAR_IF_EXISTS:
            printf("Enter a value: \n");
            scanf("%d", &value);
            ClearIfValueExists(list, value);
            ListPrint(list);
            break;
        case DELETE:
            ListDelete(&list);
            return 0;
        default:
            break;
        }
        printf("\n");
    }
}

int main() {
    Menu();
    return 0;
}
