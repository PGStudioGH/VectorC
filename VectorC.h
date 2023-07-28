#ifndef VECTOR_C_H
#define VECTOR_C_H

/** How install VectorC.h? **
 * 1. Just download VectorC.h and put on own project C
 * 2. Include VectorC.h using code: #include "VectorC.h"
 * 3. Done
 *
 * This header can be work only in many compiler for C (C89 and latest) and C++ (C++98 and latest).
 **/

/** How use vector? **
 * 1. Use macro "template_vector(type);" before using vector
 * 2. Create vector using macro "vector(type, name_vector);"
 * 3. You can use methods: "name_vector.name_method(...);"
 * 4. You can use operator [], just use macro "DATA(name_vector, type)[index]" or create temporary variable "type* name_variable = DATA(name_vector, type); name_variable[index] = ...;"
 * 5. With enjoy :)
 * 6. But dont forget to free vector using macro "free_vector(name_vector);", because C don't have auto-deconstructor
 *
 * Methods:
 * restart(self);
 * clear(self);
 * reserve(self, capacity);
 * push(self, value);
 * pop(self);
 * insert(self, index, value);
 * erase(self, index);
 * size(self);
 * capacity(self);
 * print_data(self);
 *
 * How use self?
 * - Just write "name_vector.self"
 *
 * How use type struct?
 * - You need use typedef struct
 *
 * P.S. Please look file example.c
 **/

#ifdef __cplusplus
extern "C" {
#endif

/* Includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Declarations */
struct _vector_data;
void _restart_vector(void* self);
void _clear_vector(void* self);
void _pop_back_vector(void* self);
unsigned int _size_vector(void* self);
unsigned int _capacity_vector(void* self);
#define _TEMPLATE_FUNCTION(T)\
  void _reserve_vector_##T(void* self, unsigned int capacity);\
  void _push_back_vector_##T(void* self, T data);\
  void _insert_vector_##T(void* self, unsigned int index, T data);\
  void _erase_vector_##T(void* self, unsigned int index);\
  void _print_data_vector_##T(void* self);\
  struct _vector_##T;

/* Struct classic vector */
struct _vector_data
{
  unsigned int size;
  unsigned int capacity;
  void* data;
};

/* Functions without template */
void _restart_vector(void* self)
{
  struct _vector_data* vec = (struct _vector_data*)self;
  vec->size = 0;
  vec->capacity = 0;
  free(vec->data);
  vec->data = NULL;
}
void _clear_vector(void* self)
{
  struct _vector_data* vec = (struct _vector_data*)self;
  vec->size = 0;
}
void _pop_back_vector(void* self)
{
  struct _vector_data* vec = (struct _vector_data*)self;
  if (vec->size > 0)
  {
    vec->size--;
  }
}
unsigned int _size_vector(void* self)
{
  struct _vector_data* vec = (struct _vector_data*)self;
  if (vec->data != NULL)
  {
    return vec->size;
  }
  return 0;
}
unsigned int _capacity_vector(void* self)
{
  struct _vector_data* vec = (struct _vector_data*)self;
  if (vec->data != NULL)
  {
    return vec->capacity;
  }
  return 0;
}

/* Functions with template */
#define vector(T, V)\
  const struct _vector_##T V =\
  {\
    calloc(1, sizeof(struct _vector_data)),\
    _restart_vector, _clear_vector,\
    _reserve_vector_##T, _push_back_vector_##T,\
    _pop_back_vector,\
    _insert_vector_##T, _erase_vector_##T,\
    _size_vector, _capacity_vector,\
    _print_data_vector_##T\
  };

#define free_vector(V)\
  free(((struct _vector_data*)V.self)->data);\
  free(V.self);

#define DATA(V, T)\
  ((T*)((struct _vector_data*)V.self)->data)

#define template_vector(T)\
  _TEMPLATE_FUNCTION(T)\
  void _reserve_vector_##T(void* self, unsigned int capacity)\
  {\
    struct _vector_data* vec = (struct _vector_data*)self;\
    void* temp = realloc(vec->data, capacity * sizeof(T));\
    if (temp != NULL)\
    {\
      vec->capacity = capacity;\
      vec->data = temp;\
    }\
  }\
  void _push_back_vector_##T(void* self, T data)\
  {\
    struct _vector_data* vec = (struct _vector_data*)self;\
    if (vec->data == NULL)\
    {\
      vec->data = malloc(sizeof(T));\
      if (vec->data != NULL)\
      {\
        vec->capacity = 1;\
      }\
      else return;\
    }\
    \
    if (vec->size == vec->capacity)\
    {\
      void* temp = realloc(vec->data, (vec->capacity << 1) * sizeof(T));\
      if (temp != NULL)\
      {\
        vec->capacity <<= 1;\
        vec->data = temp;\
      }\
      else return;\
    }\
    *((T*)vec->data + vec->size) = data;\
    vec->size++;\
  }\
  void _insert_vector_##T(void* self, unsigned int index, T data)\
  {\
    struct _vector_data* vec = (struct _vector_data*)self;\
    if (index <= vec->size)\
    {\
      if (vec->data == NULL)\
      {\
        vec->data = malloc(sizeof(T));\
        if (vec->data != NULL)\
        {\
          vec->capacity = 1;\
        }\
        else return;\
      }\
      \
      if (vec->size == vec->capacity)\
      {\
        void* temp = realloc(vec->data, (vec->capacity << 1) * sizeof(T));\
        if (temp != NULL)\
        {\
          vec->capacity <<= 1;\
          vec->data = temp;\
        }\
        else return;\
      }\
      T* current_data = (T*)vec->data + index;\
      memmove((void*)(current_data + 1), (void*)current_data, (vec->size - index) * sizeof(T));\
      *current_data = data;\
      vec->size++;\
    }\
  }\
  void _erase_vector_##T(void* self, unsigned int index)\
  {\
    struct _vector_data* vec = (struct _vector_data*)self;\
    if (vec->data != NULL && index < vec->size)\
    {\
      T* current_data = (T*)vec->data + index;\
      memcpy((void*)current_data, (void*)(current_data + 1), (vec->size - index) * sizeof(T));\
      vec->size--;\
    }\
  }\
  void _print_data_vector_##T(void* self)\
  {\
    struct _vector_data* vec = (struct _vector_data*)self;\
    if (vec->data != NULL && vec->size != 0)\
    {\
      printf("Data:\n");\
      unsigned int i = 0;\
      unsigned int size = vec->size * sizeof(T);\
      while (i < size)\
      {\
        printf("%02hhX ", *((unsigned char*)vec->data + i));\
        if (i != size - 1)\
        {\
          if ((i & ((sizeof(T) << 2) - 1)) == ((sizeof(T) << 2) - 1)) printf("\n");\
          else if ((i & (sizeof(T) - 1)) == (sizeof(T) - 1)) printf("| ");\
        }\
        i++;\
      }\
      printf("\n");\
    }\
    else printf("Empty vector\n");\
  }\
  struct _vector_##T\
  {\
    void* const self;\
    void (*const restart)(void*);\
    void (*const clear)(void*);\
    void (*const reserve)(void*, unsigned int);\
    void (*const push)(void*, T);\
    void (*const pop)(void*);\
    void (*const insert)(void*, unsigned int, T);\
    void (*const erase)(void*, unsigned int);\
    unsigned int (*const size)(void*);\
    unsigned int (*const capacity)(void*);\
    void (*const print_data)(void*);\
  }

#ifdef __cplusplus
}
#endif

#endif
