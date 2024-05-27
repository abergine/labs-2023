#ifndef _LIST_H_
#define _LIST_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct List List;
typedef struct ListNode ListNode;
typedef struct Iterator Iterator;

struct List {
    ListNode *head;
    ListNode *barrier;
};

struct ListNode {
    int value;
    ListNode *next;
};

struct Iterator {
    ListNode *node;
};

List *ListCreate();
ListNode *ListNodeCreate(int value);
bool ListIsEmpty(const List *list);
Iterator GetNodeByIndex(List *list, int index);
void ListInsert(Iterator prev, int value);
void ListInsertByIndex(List *list, int value, int index);
Iterator GetLastNode(const List *list);
void ListPushBack(List *list, int value);
void ListPrint(const List *list);
void ListPop(Iterator prev);
void ListPopByIndex(List *list, int index);
void ListPopBack(List *list);
void ListSort(List *list);
void NodesClear(ListNode *node, ListNode *barrier);
void ListClear(List *list);
void ListDelete(List **list);
Iterator First(const List *list);
bool Equal(const Iterator *it1, const Iterator *it2);
bool NotEqual(const Iterator *it1, const Iterator *it2);
Iterator* Next(Iterator *it);
Iterator* Prev(Iterator *it);
int Fetch(Iterator it);
void Store(Iterator it, int value);
bool IsLast(const Iterator *it);
int ListSize(const List *list);
void ClearIfValueExists(List *list, int value);

#endif
