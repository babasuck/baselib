#pragma once

#include <stdint.h>

// Wrapper for int

typedef struct Integer Integer;

Integer* Integer_create(uint64_t data); /* alloc + ctor */
Integer* Integer_alloc();
void Integer_ctor(Integer* integer, uint64_t data);
void Integer_dtor(Integer* integer);
uint64_t Integer_getInt(Integer* integer);