#ifndef VECTORC89_H
#define VECTORC89_H

/** How install VectorC.h? **
 * 1. Just download VectorC.h and put on own project C
 * 2. Include VectorC.h using code: "#include "VectorC.h""
 * 3. Done
 *
 * Attention! This header can be work only in compiler for C (C89 and latest), not C++.
 **/

/** How use vector? **
 * 1. Use macro "template_vector(type);" before using vector
 * 2. Create vector using macro "vector(type, name_vector);". Even you can create vector without virtual methods using macro "vector_directly(type, name_vector);". See difference:
 // Vector with virtual methods //
 vector(int, v1);
 v1.methods->push(v1.self, 500);
 // Vector without virtual methods //
 vector_directly(int, v2);
 v2.push(v2.self, 500);
 * 3. You can use methods: "name_vector.methods->name_method(...);"
 * 4. You can use operator [], just use macro "DATA(name_vector, type)[index]" or create temporary variable "type* name_variable = DATA(name_vector, type); name_variable[index] = ...;"
 * 5. With enjoy :)
 * 6. But dont forget to free vector using macro "free_vector(name_vector);"
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

/* Includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Struct classic vector */
struct _vector_data
{
  unsigned int size;
  unsigned int capacity;
  void* data;
};

/* Struct virtual table for vector */
struct _vector_vtable
{
  void (*restart)();
  void (*clear)();
  void (*reserve)();
  void (*push)();
  void (*pop)();
  void (*insert)();
  void (*erase)();
  unsigned int (*size)();
  unsigned int (*capacity)();
  void (*print_data)();
};

/* Interface vector */
struct _vector
{
  struct _vector_data* self;
  const struct _vector_vtable* methods;
};
struct _vector_directly
{
    struct _vector_data* self;
    void (*restart)();
    void (*clear)();
    void (*reserve)();
    void (*push)();
    void (*pop)();
    void (*insert)();
    void (*erase)();
    unsigned int (*size)();
    unsigned int (*capacity)();
    void (*print_data)();
};

/* Functions without template */
void _init_vector_data(struct _vector_data** vec)
{
  *vec = (struct _vector_data*)malloc(sizeof(struct _vector_data));
  if (*vec != NULL)
  {
    (*vec)->size = 0;
    (*vec)->capacity = 0;
    (*vec)->data = NULL;
  } 
}
void _free_vector_data(struct _vector_data** vec)
{
  if (*vec != NULL)
  {
    free((*vec)->data);
    free(*vec);
    *vec = NULL;
  }
}
void _restart_vector(struct _vector_data* vec)
{
  if (vec != NULL)
  {
    vec->size = 0;
    vec->capacity = 0;
    free(vec->data);
    vec->data = NULL;
  }
}
void _clear_vector(struct _vector_data* vec)
{
  if (vec != NULL)
  {
    vec->size = 0;
  }
}
void _pop_back_vector(struct _vector_data* vec)
{
  if (vec != NULL && vec->size > 0)
  {
    vec->size--;
  }
}
unsigned int _size_vector(struct _vector_data* vec)
{
  if (vec != NULL && vec->data != NULL)
  {
    return vec->size;
  }
  return 0;
}
unsigned int _capacity_vector(struct _vector_data* vec)
{
  if (vec != NULL && vec->data != NULL)
  {
    return vec->capacity;
  }
  return 0;
}

/* Functions with template */
#define vector(T, V)\
  struct _vector V;\
  _init_vector_data(&V.self);\
  V.methods = &_vector_vtable_##T;

#define vector_directly(T, V)\
    struct _vector_directly V;\
    _init_vector_data(&V.self);\
    *(struct _vector_vtable*)((void*)&V.self + sizeof(V.self)) = _vector_vtable_##T;

#define free_vector(V)\
  _free_vector_data(&V.self);\
  memset(&V, 0, sizeof(V));

#define DATA(V, T) ((T*)V.self->data)

#define template_vector(T)\
  void _reserve_vector_##T(struct _vector_data* vec, unsigned int capacity)\
  {\
    if (vec != NULL)\
    {\
      void* temp = realloc(vec->data, capacity * sizeof(T));\
      if (temp != NULL)\
      {\
        vec->capacity = capacity;\
        vec->data = temp;\
      }\
    }\
  }\
  void _push_back_vector_##T(struct _vector_data* vec, T data)\
  {\
    if (vec != NULL)\
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
      *((T*)vec->data + vec->size) = data;\
      vec->size++;\
    }\
  }\
  void _insert_vector_##T(struct _vector_data* vec, unsigned int index, T data)\
  {\
    if (vec != NULL && index <= vec->size)\
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
  void _erase_vector_##T(struct _vector_data* vec, unsigned int index)\
  {\
    if (vec != NULL && vec->data != NULL && index < vec->size)\
    {\
      T* current_data = (T*)vec->data + index;\
      memcpy((void*)current_data, (void*)(current_data + 1), (vec->size - index) * sizeof(T));\
      vec->size--;\
    }\
  }\
  void _print_data_vector_##T(struct _vector_data* vec)\
  {\
    if (vec != NULL && vec->data != NULL && vec->size != 0)\
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
  const static struct _vector_vtable _vector_vtable_##T = \
  {\
    (void (*)())_restart_vector, (void (*)())_clear_vector,\
    (void (*)())_reserve_vector_##T, (void (*)())_push_back_vector_##T,\
    (void (*)())_pop_back_vector,\
    (void (*)())_insert_vector_##T, (void (*)())_erase_vector_##T,\
    (unsigned int (*)())_size_vector, (unsigned int (*)())_capacity_vector,\
    (void (*)())_print_data_vector_##T\
  };

#endif
