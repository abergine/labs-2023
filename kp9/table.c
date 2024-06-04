#include "table.h"

// создание списка
List* Create_List() {
    List* l = (List*)malloc(sizeof(List)); //выделяем память под список
    l->head = NULL;                        //инициализируем указатель на первый элемент списка
    l->size = 0;                           //инициализируем количество элементов списка
    l->sorted = 0;                         //инициализируем состояние списка (неотсортирован)
    return l;                              //возвращаем указатель на созданный список
}

void Read_Table(List* l, FILE* fp) {      //поля ключ и значение в файле должны отделяться знаком табуляции
    char line[100];
    while (fgets(line, 100, fp) != NULL) {
        char* key_str = strtok(line, "\t");
        char* value_str = strtok(NULL, "\n");
        char* key = (char*)malloc(7 * sizeof(char));
        strncpy(key, key_str, 6);
        key[6] = '\0';
        char* value = (char*)malloc((strlen(value_str) + 1) * sizeof(char));
        strcpy(value, value_str);
        Node* new_node = (Node*)malloc(sizeof(Node));
        if (!key || !value || !new_node) {
            printf("Memory allocation error!\n");
            exit(1);
        }        
        
        strcpy(new_node->key, key);
        new_node->data = value;
        new_node->next = NULL;
        
        if (l->head == NULL) {
            new_node->prev = NULL;
            l->head = new_node;
        }
        else {
            Node* current = l->head;
            while (current->next != NULL) {
                current = current->next;
            }
            new_node->prev = current;
            current->next = new_node;
        }

        l->size++;
        free(key);
    }
    if (l->size > 14)
        printf("База переполнена. Максимум строк: 14\n");
}

// добавление записи в конец списка
void Add_To_List(List* list, const char* key, const char* data) {
    Node* new_node = (Node*)malloc(sizeof(Node)); //выделяем память под новый элемент списка
    strcpy(new_node->key, key);                   //копируем ключ новой записи в соответствующее поле структуры
    new_node->data = strdup(data);                //копируем данные новой записи в соответствующее поле структуры
    new_node->next = NULL;                        //инициализируем указатель на следующий элемент списка

    if (list->head == NULL) {                     //если список пустой
        new_node->prev = NULL;                    //инициализируем указатель на предыдущий элемент списка
        list->head = new_node;                    //устанавливаем указатель на первый элемент списка
    }
    else {                                        //если список не пустой
        Node* current = list->head;               //устанавливаем указатель на первый элемент списка
        while (current->next != NULL) {           //перебираем элементы списка, пока не найдем последний элемент
            current = current->next;
        }
        new_node->prev = current;                 //устанавливаем указатель на предыдущий элемент списка
        current->next = new_node;                 //устанавливаем указатель на следующий элемент списка
    }

    list->size++;                                 //увеличиваем количество элементов списка на 1
}

// удаление последней записи из списка
void Table_Pop(List* list) {
    if (list->head == NULL) {                     //если список пустой
        return;                                   //выходим из функции
    }

    Node* current = list->head;                   //устанавливаем указатель на первый элемент списка
    while (current->next != NULL) {               //перебираем элементы списка, пока не найдем последний элемент
        current = current->next;
    }

    if (current->prev == NULL) {                  //если удаляемый элемент - единственный в списке
        list->head = NULL;                        //устанавливаем указатель на первый элемент списка в NULL
    } else {                                      //если удаляемый элемент не единственный в списке
        current->prev->next = NULL;               //устанавливаем указатель на следующий элемент предыдущего элемента списка в NULL
    }

    free(current->data);                          //освобождаем память, выделенную под данные удаляемой записи
    free(current);                                //освобождаем память, выделенную под удаляемый элемент списка
    list->size--;                                 //уменьшаем количество элементов списка на 1
}

// получение указателя на первый элемент списка
Node* Begin_List(List* list) {
    if (!list || !list->head) {                   //если список пустой или не существует
        return NULL;                             
    }
    return list->head;                            //возвращаем указатель на первый элемент списка
}

// печать списка
void Table_Print(List* list) {
    printf("\n");
    if (list->size == 0) {
        printf("List is empty\n");
        return;
    }
    Node* n = Begin_List(list);
    for (int i = 0; i < list->size; i++) {
        printf("%s\t%s\n", n->key, n->data);
        n = n->next;
    }
    printf("\n");
}

void Free_List(List* list) {
    Node* current = list->head;
    while (current != NULL) {
        Node* next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
    free(list);
}

int List_Size (List* list) {
    return list->size;
}

Node* Plus(Node* n, int x) {
    for (int i = 0; i < x; i++) {
        n = n->next;
    }
    return n;
}

// обмен двух элементов списка
void Swap (List* list, int x, int y) {
    Node* n_x = Begin_List(list);
    n_x = Plus(n_x, x);
    Node* n_y = Begin_List(list);
    n_y = Plus(n_y, y);

    char key[7];
    char* data;

    strncpy(key, n_x->key, 6);
    key[6] = '\0';
    data = n_x->data;

    strncpy(n_x->key, n_y->key, 6);
    n_x->key[6] = '\0';
    n_x->data = n_y->data;

    strncpy(n_y->key, key, 6);
    n_y->key[6] = '\0';
    n_y->data = data;
}

int Compare_Keys(char* key1, char* key2) {
    return strncmp(key1, key2, 6);
}

Node* Find(List* list, int position) {
    Node* a = Begin_List(list);
    for (int i = 0; i<position; i++){
        a = a->next;
    }
    return a;
}

void Selection_Sort(List* list) {
    if (list == NULL || list->size <= 1) {
        return; // Нечего сортировать
    }

    Node* current = list->head;

    while (current != NULL) {
        Node* min_node = current;
        Node* search_node = current->next;

        // Находим узел с минимальным ключом
        while (search_node != NULL) {
            if (Compare_Keys(search_node->key, min_node->key) < 0) {
                min_node = search_node;
            }
            search_node = search_node->next;
        }

        // Обмениваем текущий узел с узлом, содержащим минимальный ключ
        if (min_node != current) {
            // Обмен ключей
            char temp_key[7];
            strcpy(temp_key, current->key);
            strcpy(current->key, min_node->key);
            strcpy(min_node->key, temp_key);

            // Обмен данных
            char* temp_data = current->data;
            current->data = min_node->data;
            min_node->data = temp_data;
        }

        current = current->next;
    }
}

char* Binary_Search(List* list, char key[7]) {
    if (!list || !list->head) {
        printf("List is empty!");
        return NULL;
    }

    Node* left = list->head;
    Node* right = left;

    while (right->next && strcmp(right->key, key) < 0) {
        left = right;
        right = right->next;
    }

    if (!strcmp(right->key, key)) {
        return right->data;
    }

    return NULL;
}

void Reverse_List(List* list) {
    Node* current = list->head;
    Node* temp = NULL;

    while (current != NULL) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }

    if (temp != NULL) {
        list->head = temp->prev;
    }
}

void Write_List(FILE* fp, List* list) {
    Node* current = list->head;
    while (current) {
        fprintf(fp, "%s\t%s\n", current->key, current->data);
        current = current->next;
    }
}

bool Is_List_Sorted(List* list, bool asc_order) {
  if (list == NULL || list->size == 0) {
    return true;
  }

  Node* current = list->head;
  int compare_result = strcmp(current->key, current->next->key);

  if (asc_order) {
    for (; current->next != NULL; current = current->next) {
      compare_result = strcmp(current->key, current->next->key);
      if (compare_result > 0) {
        return false;
      }
    }
  } else {
    for (; current->next != NULL; current = current->next) {
      compare_result = strcmp(current->key, current->next->key);
      if (compare_result < 0) {
        return false;
      }
    }
  }
  return true;
}

// Функция для печати меню
void print_menu() {                                       
    printf("print - Напечатать таблицу\n");
    printf("add [ключ] [значение] - добавить запись в таблицу\n");
    printf("remove - удалить последнюю запись\n");
    printf("find [ключ] - найти значение по ключу\n");
    printf("sort - отсортировать таблицу\n");
    printf("issort - отсортирован ли список?\n");
    printf("overwriting - перерзаписать файл\n");
    printf("exit - завершение программы\n");
}