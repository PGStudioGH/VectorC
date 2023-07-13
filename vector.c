#include "vector.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct vector_t
{
    uint64_t size;
    uint64_t capacity;
    uint64_t size_of_type;
    void* data;
};

void init_vector_t(vector vec, uint64_t size_of_type)
{
    if (vec != NULL)
    {
        free(vec->data);
        free(vec);
    }
    vec = create_vector_t(size_of_type);
}
vector create_vector_t(uint64_t size_of_type)
{
    vector new_vector = (vector)malloc(sizeof(struct vector_t));
    new_vector->size = 0;
    new_vector->capacity = 1;
    new_vector->size_of_type = size_of_type;
    new_vector->data = malloc(size_of_type);
    return new_vector;
}
void free_vector_t(vector vec)
{
    if (vec != NULL && vec->data != NULL)
    {
        free(vec->data);
        free(vec);
        vec = NULL;
    }
}
void restart_vector_t(vector vec)
{
    if (vec != NULL && vec->data != NULL)
    {
        free(vec->data);
        vec->size = 0;
        vec->capacity = 1;
        vec->data = malloc(vec->size_of_type);
    }
}
void reserve_vector_t(vector vec, uint64_t capacity)
{
    if (vec != NULL)
    {
        void* new_data = malloc(capacity * vec->size_of_type);
        memcpy(new_data, vec->data, vec->size * vec->size_of_type);
        free(vec->data);
        vec->data = new_data;
        vec->capacity = capacity;
    }
}
void push_vector_t(vector vec, void* data)
{
    if (vec != NULL)
    {
        if (vec->size == vec->capacity) 
        {
            void* new_data = malloc((vec->capacity * 2) * vec->size_of_type);
            memcpy(new_data, vec->data, vec->size * vec->size_of_type);
            free(vec->data);
            vec->data = new_data;
            vec->capacity *= 2;
        }
        memcpy((void*)((uint8_t*)vec->data + vec->size * vec->size_of_type), data, vec->size_of_type);
        vec->size++;
    }
}
void pop_vector_t(vector vec)
{
    if (vec != NULL)
    {
        vec->size--;
    }
}
void* element_vector_t(vector vec, uint64_t index)
{
    if (vec != NULL)
    {
        return (void*)((uint8_t*)vec->data + index * vec->size_of_type);
    }
    return NULL;
}
void insert_vector_t(vector vec, void* data, uint64_t index)
{
    if (vec != NULL && index <= vec->size)
    {
        if (vec->size == vec->capacity) 
        {
            vec->capacity *= 2;
            void* new_data = malloc(vec->capacity * vec->size_of_type);
            memcpy(new_data, vec->data, index * vec->size_of_type);
            memcpy((void*)((uint8_t*)new_data + index * vec->size_of_type), data, vec->size_of_type);
            memcpy((void*)((uint8_t*)new_data + (index + 1) * vec->size_of_type), (void*)((uint8_t*)vec->data + index * vec->size_of_type), (vec->size - index) * vec->size_of_type);
            free(vec->data);
            vec->data = new_data;
        }
        else
        {
            uint8_t* current_data = (uint8_t*)vec->data + index * vec->size_of_type;
            memmove((void*)(current_data + vec->size_of_type), (void*)(current_data), (vec->size - index) * vec->size_of_type);
            memcpy((void*)(current_data), data, vec->size_of_type);
        }
        vec->size++;
    }
}
void erase_vector_t(vector vec, uint64_t index)
{
    if (vec != NULL && index < vec->size)
    {
        uint8_t* current_data = (uint8_t*)vec->data + index * vec->size_of_type;
        memcpy((void*)(current_data), (void*)(current_data + vec->size_of_type), (vec->size - index) * vec->size_of_type);
        vec->size--;
    }
}
void clear_vector_t(vector vec)
{
    if (vec != NULL)
    {
        vec->size = 0;
    }
}
uint64_t size_vector_t(vector vec)
{
    if (vec != NULL)
    {
        return vec->size;
    }
    return 0;
}
uint64_t capacity_vector_t(vector vec)
{
    if (vec != NULL)
    {
        return vec->capacity;
    }
    return 0;
}
void print_vector_t(vector vec)
{
    if (vec != NULL && vec->size != 0)
    {
        printf("Data:\n");
        int i = 0;
        int size = vec->size * vec->size_of_type;
        while (i < size)
        {
            printf("%02hhX ", *((uint8_t*)vec->data + i));
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
