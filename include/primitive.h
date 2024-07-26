#pragma once

#include <stdint.h>

typedef struct Primitive Primitive;

Primitive* Primitive_Integer_create(int64_t data);
Primitive* Primitive_Double_create(long double data);

#define Primitive_create(X) _Generic((X),                       \
                            int64_t: Primitive_Integer_create,  \
                            int: Primitive_Integer_create,      \
                            double: Primitive_Double_create,    \
                            float: Primitive_Double_create,     \
                            long double: Primitive_Double_create \
                            )(X)
