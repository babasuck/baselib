#include "baselib.h"

#include "object_p.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define INITIAL_CAPACITY 100

typedef struct Bucket Bucket;

struct Bucket {
    Object object;
    LinkedList* elements;
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

struct HashSet {
    Object object;
    Bucket** buckets;
    size_t size;
    size_t capacity;
};

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
    LinkedList_dtor(bucket->elements);
    free(bucket);
}

HashSet* HashSet_alloc() {
    return (HashSet*)malloc(sizeof(HashSet));
}

void HashSet_ctor(HashSet* hashSet) {
    Object_ctor((Object*)hashSet, "HashSet");
    hashSet->capacity = INITIAL_CAPACITY;
    hashSet->size = 0;
    Bucket** buckets = (Bucket**)malloc(hashSet->capacity * sizeof(Bucket*));
    for(size_t i = 0; i < hashSet->capacity; i++) {
        buckets[i] = __Bucket_alloc();
        __Bucket_ctor(buckets[i]);
    }
    hashSet->buckets = buckets;
}

void HashSet_dtor(HashSet* hashSet) {
    Object_dtor((Object*)hashSet);
    for(size_t i = 0; i < hashSet->capacity; i++) {
        __Bucket_dtor(hashSet->buckets[i]);
    }
    free(hashSet->buckets);
    free(hashSet);
}

HashSet* HashSet_create() {
    HashSet* hashSet = HashSet_alloc();
    HashSet_ctor(hashSet);
    return hashSet;
}

int HashSet_add(HashSet* hashSet, Object* el) {
    if (HashSet_contains(hashSet, el)) {
        return -1;
    }
    if (hashSet->size / hashSet->capacity >= 0.7) {
        size_t new_capacity = hashSet->capacity * 2;
        Bucket** newBuckets = (Bucket**)malloc(new_capacity * sizeof(Bucket*));
        for(size_t i = 0; i < new_capacity; i++) {
            newBuckets[i] = __Bucket_alloc();
            __Bucket_ctor(newBuckets[i]);
        }
        for (size_t i = 0; i < hashSet->capacity; i++) {
            for(size_t j = 0; j < LinkedList_getSize(hashSet->buckets[i]->elements); j++) {
                Object* el = LinkedList_at(hashSet->buckets[i]->elements, j);
                size_t newBucketNum = Object_hashCode(el) % new_capacity;
                LinkedList_insertEnd(newBuckets[newBucketNum]->elements, el);
            }
            __Bucket_dtor(hashSet->buckets[i]);
        }
        free(hashSet->buckets);
        hashSet->buckets = newBuckets;
        hashSet->capacity = new_capacity;
    }
    size_t bucketNum = Object_hashCode(el) % hashSet->capacity;
    LinkedList_insertEnd(hashSet->buckets[bucketNum]->elements, el);
    hashSet->size++;
    return 0;
}

void HashSet_print(HashSet* hashSet) {
    for (size_t i = 0; i < hashSet->capacity; i++) {
        char* buffer = Object_toString((Object*)(hashSet->buckets[i]));
        printf("%s\n", buffer);
        free(buffer);
    }
}

bool HashSet_contains(HashSet* hashSet, Object* object) {
    size_t num = Object_hashCode(object) % hashSet->capacity;
    for(size_t i = 0; i < LinkedList_getSize(hashSet->buckets[num]->elements); i++) {
        if (Object_EqualsTo(LinkedList_at(hashSet->buckets[num]->elements, i), object)) {
            return true;
        }
    }
    return false;
}

void HashSet_forAll(HashSet* hs, FuncForAll func) {
    for (size_t i = 0; i < hs->capacity; i++) {
        for(size_t j = 0; j < LinkedList_getSize(hs->buckets[i]->elements); j++) {
            Object* el = LinkedList_at(hs->buckets[i]->elements, j);
            func(el);
        }
    }
}