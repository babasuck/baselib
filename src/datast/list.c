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
};

// Overrided V functions
char* __node_ToString(Object* object);
size_t __node_HashCode(Object* object);

char* __linkedList_ToString(Object* object);
size_t __linkedList_HashCode(Object* object);

Node* __node_alloc() {
    return (Node*)malloc(sizeof(Node));
}

void __node_ctor(Node* node, Object* data) {
    Object_ctor((Object*)node, "LinkedList Node");
    node->data = data;
    
    // Setting V-Table
    node->object.toString = __node_ToString;
    node->object.hashCode = __node_HashCode;
}

void __node_dtor(Node* node) {
    Object_dtor((Object*)node);
    free(node);
}

char* __node_ToString(Object* object) {
    Node* node = (Node*)object;
    char* objStr = Object_toString(node->data);
    size_t bufsize = (strlen(objStr) + 1) * sizeof(*objStr);
    char* buf = (char*)malloc(bufsize + 255);
    snprintf(buf, bufsize + 255, "Node: next - %p ; el - %s", node->next, objStr);
    free(objStr);
    return buf;
}

size_t __node_HashCode(Object* object) {
    Node* node = (Node*)object;
    return Object_hashCode(node->data) + 12345;
}

void __node_print(Node* node) {
    char* str = Object_toString((Object*)node);
    printf("%s ", str);
    free(str);
}

char* __linkedList_ToString(Object* object) {
    LinkedList* list = (LinkedList*)object;
    size_t bufsize = list->len * 64 + 256;
    char* buf = (char*)malloc(bufsize * sizeof(*buf));
    memset(buf, 0, bufsize * sizeof(*buf));
    strcat(buf, "[ ");
    for(int i = 0; i < list->len; i++) {
        char* buffer = Object_toString((Object*)LinkedList_at(list, i));
        strcat(buffer, " ");
        strcat(buf, buffer);
        free(buffer);
    }
    strcat(buf, "] ");
    char fstr[255] = {0};
    sprintf(fstr, "List of size - %zu, hashCode - %zu", list->len, Object_hashCode((Object*)list));
    strcat(buf, fstr);
    return buf;
}

size_t __linkedList_HashCode(Object* object) {
    size_t hash = 0;
    LinkedList* list = (LinkedList*)object;
    Node* node = list->head;
    while(node != NULL) {
        hash ^= Object_hashCode((Object*)node);
        node = node->next;
    }
    return hash;
}

LinkedList* LinkedList_alloc() {
    return (LinkedList*)malloc(sizeof(LinkedList));
}

void LinkedList_ctor(LinkedList* list) {
    Object_ctor((Object*)list, "LinkedList");
    list->len = 0;
    list->head = NULL;
    list->tail = NULL;

    // V-Table
    list->object.toString = __linkedList_ToString;
    list->object.hashCode = __linkedList_HashCode;
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
        list->head = newNode;
        list->tail = newNode;
    }
    else {
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
    if(list->len == 0) {
        newNode->next = NULL;
        list->head = newNode;
        list->tail = newNode;
    }
    else {
        Node* oldHead = list->head;
        list->head = newNode;
        newNode->next = oldHead;
    }
    list->len++;
    return 0;
}

Object* LinkedList_at(LinkedList* list, size_t at) {
    if (at >= list->len)
        return NULL;
    size_t index = 0;
    Node* node = list->head;
    while(node != NULL) {
        if (index == at)
            return node->data;
        node = node->next;
        index++;
    }
    return NULL;
}

size_t LinkedList_getSize(LinkedList* list) {
    return list->len;
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