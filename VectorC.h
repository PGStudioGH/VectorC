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
 * 2. If you want use vector with style C and without method (universal vector), you can write "#define VECTOR_WITH_STYLE_C" before including header. Please look file example_with_style_c.c. But slower than vector with template. 
 * 3. Create vector using macro "vector(type, name_vector);"
 * 4. You can use methods: "name_vector.name_method(...);"
 * 5. You can use operator [], just use macro "at(name_vector, type)[index]" or create temporary variable "type* name_variable = at(name_vector, type); name_variable[index] = ...;"
 * 6. With enjoy :)
 * 7. But dont forget to free vector using macro "free_vector(name_vector);", because C don't have auto-deconstructor
 *
 * Methods:
 * restart(self);
 * clear(self);
 * reserve(self, capacity);
 * push(self, value);
 * push(self, type, value); --> for vector without template
 * pop(self);
 * insert(self, index, value);
 * insert(self, type, index, value); --> for vector without template
 * erase(self, index);
 * size(self);
 * capacity(self);
 * print_data(self);
 *
 * How I can use self?
 * - Just write "name_vector.self"
 *
 * How I can use type struct?
 * - Need use typedef struct
 *
 * How I can use pointer type? Pointer to function?
 * - Just write "typedef type* type_ptr;", then "vector(type_ptr, v);". Even write "typedef type (*type_fun)(...arguments...);", then "vector(type_fun, v);"
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
void _erase_vector(void* self, unsigned int index);
unsigned int _size_vector(void* self);
unsigned int _capacity_vector(void* self);
void _reserve_vector(void* self, unsigned int capacity);
void _print_data_vector(void* self);

#ifdef VECTOR_WITH_STYLE_C
  void _push_back_vector(void* self, void* data);
  void _insert_vector(void* self, unsigned int index, void* data);
  struct _vector;
#else
  #define _TEMPLATE_FUNCTION(T)\
    void _push_back_vector_##T(void* self, T data);\
    void _insert_vector_##T(void* self, unsigned int index, T data);\
    struct _vector_##T;
#endif

/* Struct classic vector */
struct _vector_data
{
  unsigned int size;
  unsigned int capacity;
  unsigned int size_of_type;
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
    vec->size--;
}
void _erase_vector(void* self, unsigned int index)
{
  struct _vector_data* vec = (struct _vector_data*)self;
  if (vec->data != NULL && index < vec->size) {
    unsigned char* current_data = (unsigned char*)vec->data + index * vec->size_of_type;
    memcpy((void*)current_data, (void*)(current_data + vec->size_of_type), (vec->size - index) * vec->size_of_type);
    vec->size--;
  }
}
unsigned int _size_vector(void* self)
{
  struct _vector_data* vec = (struct _vector_data*)self;
  if (vec->data != NULL)
    return vec->size;
  return 0;
}
unsigned int _capacity_vector(void* self)
{
  struct _vector_data* vec = (struct _vector_data*)self;
  if (vec->data != NULL)
    return vec->capacity;
  return 0;
}
void _reserve_vector(void* self, unsigned int capacity)
{
  struct _vector_data* vec = (struct _vector_data*)self;
  void* temp = realloc(vec->data, capacity * vec->size_of_type);
  if (temp != NULL) {
    vec->capacity = capacity;
    vec->data = temp;
  }
}
void _print_data_vector(void* self)
{
  struct _vector_data* vec = (struct _vector_data*)self;
  if (vec->data != NULL && vec->size != 0) {
    printf("Data:\n");
    unsigned int i = 0;\
    unsigned int size = vec->size * vec->size_of_type;
    while (i < size) {
      printf("%02hhX ", *((unsigned char*)vec->data + i));
      if (i != size - 1) {
        if ((i & ((vec->size_of_type << 2) - 1)) == ((vec->size_of_type << 2) - 1)) printf("\n");
        else if ((i & (vec->size_of_type - 1)) == (vec->size_of_type - 1)) printf("| ");
      }
      i++;
    }
    printf("\n");
  }
  else printf("Empty vector\n");
}

#ifdef VECTOR_WITH_STYLE_C
  void _push_back_vector(void* self, void* data)
  {
    struct _vector_data* vec = (struct _vector_data*)self;
    if (vec->data == NULL) {
      vec->data = malloc(vec->size_of_type);
      if (vec->data != NULL)
        vec->capacity = 1;
      else return;
    }
    
    if (vec->size == vec->capacity) {
      void* temp = realloc(vec->data, (vec->capacity << 1) * vec->size_of_type);
      if (temp != NULL) {
        vec->capacity <<= 1;
        vec->data = temp;
      }
      else return;
    }
    unsigned char* current_data = (unsigned char*)vec->data + vec->size * vec->size_of_type;
    memcpy((void*)current_data, data, vec->size_of_type);
    vec->size++;
  }
  void _insert_vector(void* self, unsigned int index, void* data)
  {
    struct _vector_data* vec = (struct _vector_data*)self;
    if (index <= vec->size) {
      if (vec->data == NULL) {
        vec->data = malloc(vec->size_of_type);
        if (vec->data != NULL)
          vec->capacity = 1;
        else return;
      }
      
      if (vec->size == vec->capacity) {
        void* temp = realloc(vec->data, (vec->capacity << 1) * vec->size_of_type);
        if (temp != NULL) {
          vec->capacity <<= 1;
          vec->data = temp;
        }
        else return;
      }
      unsigned char* current_data = (unsigned char*)vec->data + index * vec->size_of_type;
      memmove((void*)(current_data + vec->size_of_type), (void*)current_data, (vec->size - index) * vec->size_of_type);
      memcpy((void*)current_data, data, vec->size_of_type);
      vec->size++;
    }
  }
  struct _vector
  {
    void* const self;
  };
#else
  /* Functions with template */
  #define template_vector(T)\
    _TEMPLATE_FUNCTION(T)\
    void _push_back_vector_##T(void* self, T data)\
    {\
      struct _vector_data* vec = (struct _vector_data*)self;\
      if (vec->data == NULL) {\
        vec->data = malloc(sizeof(T));\
        if (vec->data != NULL)\
          vec->capacity = 1;\
        else return;\
      }\
      \
      if (vec->size == vec->capacity) {\
        void* temp = realloc(vec->data, (vec->capacity << 1) * sizeof(T));\
        if (temp != NULL) {\
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
      if (index <= vec->size) {\
        if (vec->data == NULL) {\
          vec->data = malloc(sizeof(T));\
          if (vec->data != NULL)\
            vec->capacity = 1;\
          else return;\
        }\
        \
        if (vec->size == vec->capacity) {\
          void* temp = realloc(vec->data, (vec->capacity << 1) * sizeof(T));\
          if (temp != NULL) {\
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
    };
#endif

/* Macros */
#ifdef VECTOR_WITH_STYLE_C
  #define vector(T, V)\
    const struct _vector V =\
    {\
      calloc(1, sizeof(struct _vector_data))\
    };\
    ((struct _vector_data*)V.self)->size_of_type = sizeof(T);
  #define restart(vec)                      _restart_vector(vec.self)
  #define reserve(vec, capacity)            _reserve_vector(vec.self, capacity)
  #define push(vec, type, data)             _push_back_vector(vec.self, &((type){data}))
  #define pop(vec)                          _pop_back_vector(vec.self)
  #define insert(vec, type, index, data)    _insert_vector(vec.self, index, &((type){data}))
  #define erase(vec, index)                 _erase_vector(vec.self, index)
  #define clear(vec)                        _clear_vector(vec.self)
  #define size(vec)                         _size_vector(vec.self)
  #define capacity(vec)                     _capacity_vector(vec.self)
  #define print_data(vec)                   _print_data_vector(vec.self)
#else
  #define vector(T, V)\
    const struct _vector_##T V =\
    {\
      calloc(1, sizeof(struct _vector_data)),\
      _restart_vector, _clear_vector,\
      _reserve_vector, _push_back_vector_##T,\
      _pop_back_vector, _insert_vector_##T,\
      _erase_vector, _size_vector,\
      _capacity_vector, _print_data_vector\
    };\
    ((struct _vector_data*)V.self)->size_of_type = sizeof(T);
#endif

#define free_vector(V)\
  free(((struct _vector_data*)V.self)->data);\
  free(V.self);

#define at(V, T)\
  ((T*)((struct _vector_data*)V.self)->data)

#ifdef __cplusplus
}
#endif

#endif
