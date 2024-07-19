#include "baselib.h"
#include "object_p.h"

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

typedef struct __Node Node;

struct LinkedList {
    Object object;
    Node* head;
    Node* tail;
    size_t len;
};

struct __Node {
    Object object;
    Object* data;
    Node* next;
    Node* prev;
};

// Overrided V functions
char* __node_ToString(Object* object);

Node* __node_alloc() {
    return (Node*)malloc(sizeof(Node));
}

void __node_ctor(Node* node, Object* data) {
    Object_ctor((Object*)node, "LinkedList Node");
    node->data = data;
    
    // Setting V-Table
    node->object.toString = __node_ToString;
}

void __node_dtor(Node* node) {
    Object_dtor((Object*)node);
    free(node);
}

char* __node_ToString(Object* object) {
    Node* node = (Node*)object;
    char* objStr = Object_toString(node->data);
    size_t bufsize = strlen(objStr) * sizeof(*objStr);
    char* buf = (char*)malloc(bufsize + 255);
    snprintf(buf, bufsize + 255, "Node: prev - %p ; next - %p ; el - %s", node->prev, node->next, objStr);
    free(objStr);
    return buf;
}

void __node_print(Node* node) {
    char* str = Object_toString((Object*)node);
    printf("%s ", str);
    free(str);
}

LinkedList* LinkedList_alloc() {
    return (LinkedList*)malloc(sizeof(LinkedList));
}

void LinkedList_ctor(LinkedList* list) {
    Object_ctor((Object*)list, "LinkedList");
    list->len = 0;
    list->head = NULL;
    list->tail = NULL;
}

void LinkedList_dtor(LinkedList* list) {
    Object_dtor((Object*)list);
    Node* node = list->head;
    while(node != NULL) {
        Node* next = node->next;
        __node_dtor(node);
        node = next;
    }
    free(list);
}

LinkedList* LinkedList_create() {
    LinkedList* list = LinkedList_alloc();
    LinkedList_ctor(list);
    return list;
}

int LinkedList_insertEnd(LinkedList* list, Object* el) {
    if (el == NULL)
        return -1;
    Node* newNode = __node_alloc();
    __node_ctor(newNode, el);
    newNode->next = NULL;
    if (list->len == 0) {
        newNode->prev = NULL;
        list->head = newNode;
        list->tail = newNode;
    }
    else {
        newNode->prev = list->tail;
        list->tail->next = newNode;
        list->tail = newNode;
    }
    list->len++;
    return 0;
}

int LinkedList_insertStart(LinkedList* list, Object* el) {
    if (el == NULL)
        return -1;
    Node* newNode = __node_alloc();
    __node_ctor(newNode, el);
    newNode->prev = NULL;
    if(list->len == 0) {
        newNode->next = NULL;
        list->head = newNode;
        list->tail = newNode;
    }
    else {
        Node* oldHead = list->head;
        list->head = newNode;
        newNode->next = oldHead;
        oldHead->prev = newNode;
    }
    list->len++;
    return 0;
}

void LinkedList_print(LinkedList* list) {
    Node* node = list->head;
    if (node == NULL)
        return;
    while(node != NULL) {
        __node_print(node);
        printf("\n");
        node = node->next;
    }
}