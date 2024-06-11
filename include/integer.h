#pragma once

// Just a demmy object, wrapper for int

typedef struct Integer Integer;

Integer* Integer_alloc();
void Integer_ctor(Integer* integer, int data);
void Integer_dtor(Integer* integer);
