#include "vector.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct vector_t
{
  unsigned int size;
  unsigned int capacity;
  unsigned int size_of_type;
  void* data;
};

void init_vector_t(vector* vec, unsigned int size_of_type)
{
  if (*vec != NULL)
  {
    free((*vec)->data);
    free(*vec);
  }
  *vec = create_vector_t(size_of_type);
}
vector create_vector_t(unsigned int size_of_type)
{
  vector new_vector = (vector)malloc(sizeof(struct vector_t));
  if (new_vector != NULL)
  {
    new_vector->size = 0;
    new_vector->capacity = 0;
    new_vector->size_of_type = size_of_type;
    new_vector->data = NULL;
  }
  return new_vector;
}
void free_vector_t(vector* vec)
{
  if (*vec != NULL)
  {
    free((*vec)->data);
    free(*vec);
    *vec = NULL;
  }
}
void restart_vector_t(vector vec)
{
  if (vec != NULL)
  {
    vec->size = 0;
    vec->capacity = 0;
    free(vec->data);
    vec->data = NULL;
  }
}
void reserve_vector_t(vector vec, unsigned int capacity)
{
  if (vec != NULL)
  {
    void* temp = realloc(vec->data, capacity * vec->size_of_type);
    if (temp != NULL) 
    {
      if (vec->size > capacity) vec->size = capacity;
      vec->capacity = capacity;
      vec->data = temp;
    }
  }
}
void push_vector_t(vector vec, void* data)
{
  if (vec != NULL && data != NULL)
  {
    if (vec->data == NULL)
    {
      vec->data = malloc(vec->size_of_type);
      if (vec->data != NULL)
      {
        vec->capacity = 1;
      }
      else return;
    }

    if (vec->size == vec->capacity)
    {
      unsigned int capacity = vec->capacity << 1;
      void* temp = realloc(vec->data, capacity * vec->size_of_type);
      if (temp != NULL) 
      {
        vec->capacity = capacity;
        vec->data = temp;
        unsigned char* current_data = (unsigned char*)vec->data + vec->size * vec->size_of_type;
        memcpy((void*)current_data, data, vec->size_of_type);
        vec->size++;
      }
    }
    else
    {
      unsigned char* current_data = (unsigned char*)vec->data + vec->size * vec->size_of_type;
      memcpy((void*)current_data, data, vec->size_of_type);
      vec->size++;
    }
  }
}
void pop_vector_t(vector vec)
{
  if (vec != NULL && vec->data != NULL && vec->size > 0)
  {
    vec->size--;
  }
}
void* element_vector_t(vector vec, unsigned int index)
{
  if (vec != NULL && vec->data != NULL && index < vec->size)
  {
    unsigned char* element = (unsigned char*)vec->data + index * vec->size_of_type;
    return (void*)element;
  }
  return NULL;
}
void* get_data(vector vec)
{
  if (vec != NULL)
  {
    return vec->data;
  }
  return NULL;
}
void insert_vector_t(vector vec, void* data, unsigned int index)
{
  if (vec != NULL && data != NULL && index <= vec->size)
  {
    if (vec->data == NULL)
    {
      vec->data = malloc(vec->size_of_type);
      if (vec->data != NULL)
      {
        vec->capacity = 1;
      }
      else return;
    }

    if (vec->size == vec->capacity)
    {
      unsigned int capacity = vec->capacity << 1;
      void* temp = realloc(vec->data, capacity * vec->size_of_type);
      if (temp != NULL)
      {
        vec->capacity = capacity;
        vec->data = temp;
        unsigned char* current_data = (unsigned char*)vec->data + index * vec->size_of_type;
        memmove((void*)(current_data + vec->size_of_type), (void*)current_data, (vec->size - index) * vec->size_of_type);
        memcpy((void*)current_data, data, vec->size_of_type);
        vec->size++;
      }
    }
    else
    {
      unsigned char* current_data = (unsigned char*)vec->data + index * vec->size_of_type;
      memmove((void*)(current_data + vec->size_of_type), (void*)current_data, (vec->size - index) * vec->size_of_type);
      memcpy((void*)current_data, data, vec->size_of_type);
      vec->size++;
    }
  }
}
void erase_vector_t(vector vec, unsigned int index)
{
  if (vec != NULL && vec->data != NULL && index < vec->size)
  {
    unsigned char* current_data = (unsigned char*)vec->data + index * vec->size_of_type;
    memcpy((void*)current_data, (void*)(current_data + vec->size_of_type), (vec->size - index) * vec->size_of_type);
    vec->size--;
  }
}
void clear_vector_t(vector vec)
{
  if (vec != NULL && vec->data != NULL)
  {
    vec->size = 0;
  }
}
unsigned int size_vector_t(vector vec)
{
  if (vec != NULL && vec->data != NULL)
  {
    return vec->size;
  }
  return 0;
}
unsigned int capacity_vector_t(vector vec)
{
  if (vec != NULL && vec->data != NULL)
  {
    return vec->capacity;
  }
  return 0;
}
void print_vector_t(vector vec)
{
  if (vec != NULL && vec->data != NULL && vec->size != 0)
  {
    printf("Data:\n");
    unsigned int i = 0;
    unsigned int size = vec->size * vec->size_of_type;
    while (i < size)
    {
      printf("%02hhX ", *((unsigned char*)vec->data + i));
      if (i != size - 1)
      {
        if ((i & 0xF) == 0xF) printf("\n");
        else if ((i & 0x3) == 0x3) printf("| ");
      }
      i++;
    }
    printf("\n");
  }
  else printf("Empty vector\n");
}
