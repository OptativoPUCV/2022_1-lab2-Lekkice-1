#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
  Node * node = (Node *) malloc (sizeof(Node));
  node->data = data;
  node->next = NULL;
  node->prev = NULL;
  return node;
  }

List * createList() {
  List * list = (List *) malloc (sizeof(List));
  list->head = NULL;
  list->tail = NULL;
  list->current = NULL;
  return list;
}

void * firstList(List * list) {
  if (list->head == NULL) return NULL;
  list->current = list->head;
  return list->head->data;
}

void * nextList(List * list) {
  if (list->current == NULL || list->current->next == NULL) return NULL;
  list->current = list->current->next;
  return list->current->data;
}

void * lastList(List * list) {
   if (list->tail == NULL) return NULL;
  list->current = list->tail;
  return list->tail->data;
}

void * prevList(List * list) {
  if (list->current == NULL || list->current->prev == NULL) return NULL;
  list->current = list->current->prev;
  return list->current->data;
}

void pushFront(List * list, void * data) {
  if (list->head != NULL)
  {
    list->current = list->head;
    list->current = list->tail;
  }
  
  Node * node = createNode(data);
  if (list->head == NULL) 
  {
    list->head = node;
    list->tail = node;
    return;
  }
  list->head->prev = node;
  node->next = list->head;
  list->head = node;
}

void pushBack(List * list, void * data) {
  if (list->head != NULL)
  {
    list->current = list->tail;
  }
  pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
  Node * node = createNode(data);
  if (list->head == NULL) 
  {
    list->head = node;
    list->tail = node;
    return;
  }
  if (list->current == list->tail) list->tail = node;
  node->prev = list->current;
  node->next = list->current->next;

  if (list->current->next) list->current->next->prev = node;
  list->current->next = node;
}

void * popFront(List * list) {
  list->current = list->head;
  return popCurrent(list);
}

void * popBack(List * list) {
  list->current = list->tail;
  return popCurrent(list);
}

void * popCurrent(List * list) {
  if (list->current == NULL) return NULL;
  Node * node = list->current;
  if (node == list->head)
  {
    list->head = node->next;
    list->head->prev = NULL;
    list->current = list->head;
  }
  else
  {
    if (node == list->tail)
    {
      list->tail = node->prev;
      list->tail->next = NULL;
      list->current = list->tail;
    }
    else
    {
      node->prev = node->next;
      node->next = node->prev;
      list->current = node->next;
    }
  }

  return node->data;
}

void cleanList(List * list) {
  while (list->head != NULL) {
      popFront(list);
  }
}