#include "baselib.h"

#include "object_p.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#define INITIAL_CAPACITY 10
#define FNV_OFFSET 14695981039346656037UL
#define FNV_PRIME 1099511628211UL

typedef struct Bucket Bucket;
typedef struct Element Element;

struct HashMap {
    Object object;
    Bucket** buckets;
    size_t size;
    size_t capacity;
};

struct Bucket {
    Object object;
    LinkedList* elements;
};

struct Element {
    Object object;
    char* key;
    Object* value; 
};

// Virtual Functions

static char* __Bucket_ToString(Object* object) {
    Bucket* bucket = (Bucket*)object;
    char* buf = Object_toString((Object*)bucket->elements);
    size_t size = (strlen(buf) + 1) * sizeof(*buf);
    char* str = (char*)malloc(size + 255);
    strcpy(str, "Bucket ");
    strncat(str, buf, size);
    free(buf);
    return str;
}


static char* __Element_ToString(Object* obj) {
    Element* el = (Element*)obj;
    char* buf = Object_toString((Object*)el->value);
    size_t size = (strlen(buf) + 1) * sizeof(*buf);
    char* str = (char*)malloc(size + 255);
    snprintf(str, size + 255, "{%s : %s}", el->key, buf);
    free(buf);
    return str;
}

static Element* __Element_alloc() {
    return (Element*)malloc(sizeof(Element));
}


static void __Element_ctor(Element* el, const char* key, Object* value) {
    Object_ctor((Object*)el, "HashMap element");
    el->key = (char*)strdup(key);
    el->value = value;

    el->object.toString = __Element_ToString;
}

static void __Element_dtor(Element* el) {
    Object_dtor((Object*)el);
    free(el->key);
    free(el);
}

static Bucket* __Bucket_alloc() {
    return (Bucket*)malloc(sizeof(Bucket));
}

static void __Bucket_ctor(Bucket* bucket) {
    Object_ctor((Object*)bucket, "Bucket");

    LinkedList* list = LinkedList_create();
    bucket->elements = list;

    // Setting V-Table
    bucket->object.toString = __Bucket_ToString;
}

static void __Bucket_dtor(Bucket* bucket) {
    Object_dtor((Object*)bucket);
    for(size_t i = 0; i < LinkedList_getSize(bucket->elements); i++) {
        __Element_dtor(LinkedList_at(bucket->elements, i));
    }
    LinkedList_dtor(bucket->elements);
    free(bucket);
}

HashMap* HashMap_alloc() {
    return (HashMap*)malloc(sizeof(HashMap));
}

void HashMap_ctor(HashMap* hashMap) {
    Object_ctor((Object*)hashMap, "HashMap");
    hashMap->capacity = INITIAL_CAPACITY;
    hashMap->size = 0;
    Bucket** buckets = (Bucket**)malloc(hashMap->capacity * sizeof(Bucket*));
    for(size_t i = 0; i < hashMap->capacity; i++) {
        buckets[i] = __Bucket_alloc();
        __Bucket_ctor(buckets[i]);
    }
    hashMap->buckets = buckets;
}

void HashMap_dtor(HashMap* hashMap) {
    Object_dtor((Object*)hashMap);
    for(size_t i = 0; i < hashMap->capacity; i++) {
        __Bucket_dtor(hashMap->buckets[i]);
    }
    free(hashMap->buckets);
    free(hashMap);
}

HashMap* HashMap_create() {
    HashMap* hashMap = HashMap_alloc();
    HashMap_ctor(hashMap);
    return hashMap;
}

uint64_t __HashMap_hash(const char* key) {
    uint64_t hash = FNV_OFFSET;
    for (const char* p = key; *p; p++) {
        hash ^= (uint64_t)(unsigned char)(*p);
        hash *= FNV_PRIME;
    }
    return hash;
}

int HashMap_add(HashMap* hashMap, const char* key, Object* value) {
    int64_t pos = HashMap_contains(hashMap, key);
    if (pos != -1) {
        size_t bucketNum = __HashMap_hash(key) % hashMap->capacity;
        Element* el = (Element*)LinkedList_at(hashMap->buckets[bucketNum]->elements, pos);
        el->value = value;
        return 0;
    }
    if (hashMap->size / hashMap->capacity >= 0.7) {
        size_t new_capacity = hashMap->capacity * 2;
        Bucket** newBuckets = (Bucket**)malloc(new_capacity * sizeof(Bucket*));
        for(size_t i = 0; i < new_capacity; i++) {
            newBuckets[i] = __Bucket_alloc();
            __Bucket_ctor(newBuckets[i]);
        }
        for (size_t i = 0; i < hashMap->capacity; i++) {
            for(size_t j = 0; j < LinkedList_getSize(hashMap->buckets[i]->elements); j++) {
                Element* el = (Element*)LinkedList_at(hashMap->buckets[i]->elements, j);
                size_t newBucketNum = __HashMap_hash(el->key) % new_capacity;
                LinkedList_insertEnd(newBuckets[newBucketNum]->elements, (Object*)el);
            }
            __Bucket_dtor(hashMap->buckets[i]);
        }
        free(hashMap->buckets);
        hashMap->buckets = newBuckets;
        hashMap->capacity = new_capacity;
    }
    size_t bucketNum = __HashMap_hash(key) % hashMap->capacity;
    Element* el = __Element_alloc();
    __Element_ctor(el, key, value);
    LinkedList_insertEnd(hashMap->buckets[bucketNum]->elements, (Object*)el);
    hashMap->size++;
    return 0;
}

void HashMap_print(HashMap* hashMap) {
    for (size_t i = 0; i < hashMap->capacity; i++) {
        char* buffer = Object_toString((Object*)(hashMap->buckets[i]));
        printf("%s\n", buffer);
        free(buffer);
    }
}

int64_t HashMap_contains(HashMap* hashMap, const char* key) {
    size_t num = __HashMap_hash(key) % hashMap->capacity;
    for(size_t i = 0; i < LinkedList_getSize(hashMap->buckets[num]->elements); i++) {
        if (strcmp(((Element*)LinkedList_at(hashMap->buckets[num]->elements, i))->key, key) == 0) {
            return i;
        }
    }
    return -1;
}