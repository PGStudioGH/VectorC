#ifndef VECTOR_H
#define VECTOR_H

//Include
#include <stdint.h>

//Typedef
typedef struct vector_t*                            vector;

//Functions
vector create_vector_t(uint64_t size_of_type);
void free_vector_t(vector vec);
void restart_vector_t(vector vec);
void push_vector_t(vector vec, void* data);
void pop_vector_t(vector vec);
void* element_vector_t(vector vec, uint64_t index);
void insert_vector_t(vector vec, void* data, uint64_t index);
void erase_vector_t(vector vec, uint64_t index);
void clear_vector_t(vector vec);
uint64_t size_vector_t(vector vec);
void print_vector_t(vector vec);

//Macros
#define create_vector(type)                         create_vector_t(sizeof(type))
#define free_vector(vector)                         free_vector_t(vector)
#define restart_vector(vector)                      restart_vector_t(vector)
#define push_vector(vector, type, data)             { type temp = data; push_vector_t(vector, &temp); }
#define pop_vector(vector)                          pop_vector_t(vector)
#define element_vector(vector, type, index)         *(type*)element_vector_t(vector, index)
#define insert_vector(vector, type, data, index)    { type temp = data; insert_vector_t(vector, &temp, index); }
#define erase_vector(vector, index)                 erase_vector_t(vector, index)
#define clear_vector(vector)                        clear_vector_t(vector)
#define size_vector(vector)                         size_vector_t(vector)
#define print_vector(vector)                        print_vector_t(vector)

#endif