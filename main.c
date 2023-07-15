#include <stdio.h>

#include "vector.h"

void hard_way()
{
  printf("\nHard way without macros:\n");
  //First way to create
  struct vector_t* v;
  v = create_vector_t(sizeof(int));
  //Second way to create
  init_vector_t(&v, sizeof(int));

  int temp = 864;
  push_vector_t(v, &temp);
  temp = 25;
  push_vector_t(v, &temp);
  temp = 93;
  push_vector_t(v, &temp);
  temp = 82;
  push_vector_t(v, &temp);
  temp = 6;
  push_vector_t(v, &temp);
  temp = 9;
  push_vector_t(v, &temp);
  temp = 0xFF88FF00;
  push_vector_t(v, &temp);
  printf("Show all elements from vector:\n");
  print_vector_t(v);
  
  printf("\nChanged fourth element to 2022:\n");
  *(int*)element_vector_t(v, 3) = 2022;
  print_vector_t(v);

  printf("\nSubtract first element by third and second elements:\n");
  *(int*)element_vector_t(v, 0) -= *(int*)element_vector_t(v, 2) + *(int*)element_vector_t(v, 1);
  print_vector_t(v);

  printf("\nAdd new element 9999 on fourth element:\n");
  temp = 9999;
  insert_vector_t(v, &temp, 3);
  print_vector_t(v);

  printf("\nAdd new element 666 on first element:\n");
  temp = 666;
  insert_vector_t(v, &temp, 0);
  print_vector_t(v);

  printf("\nDelete second element:\n");
  erase_vector_t(v, 1);
  print_vector_t(v);

  printf("\nUse pop_front:\n");
  erase_vector_t(v, 0);
  print_vector_t(v);

  printf("\nUse pop_back:\n");
  pop_vector_t(v);
  print_vector_t(v);

  printf("\nClear vector:\n");
  clear_vector_t(v);
  print_vector_t(v);

  printf("\nAdd 10 element, then use push_front:\n");
  for (int i = 0; i < 10; i++)
  {
    temp = i;
    push_vector_t(v, &temp);
  }
  temp = 0x12345678;
  insert_vector_t(v, &temp, 0);
  print_vector_t(v);

  printf("\nSize: %u\nCapacity: %u\n", size_vector_t(v), capacity_vector_t(v));

  free_vector_t(&v);
}

void easy_way()
{
  printf("\nEasy way with macros:\n");
  //First way to create
  vector v = create_vector(int);
  //Second way to create
  init_vector(v, int);

  push_back_vector(v, int, 864);
  push_back_vector(v, int, 25);
  push_back_vector(v, int, 93);
  push_back_vector(v, int, 82);
  push_back_vector(v, int, 6);
  push_back_vector(v, int, 9);
  push_back_vector(v, int, 0xFF88FF00);
  printf("Show all elements from vector:\n");
  print_vector(v);
  
  printf("\nChanged fourth element to 2022:\n");
  element_vector(v, int, 3) = 2022;
  print_vector(v);

  printf("\nSubtract first element by third and second elements:\n");
  element_vector(v, int, 0) -= element_vector(v, int, 2) + element_vector(v, int, 1);
  print_vector(v);

  printf("\nAdd new element 9999 on fourth element:\n");
  insert_vector(v, int, 9999, 3);
  print_vector(v);

  printf("\nAdd new element 666 on first element:\n");
  insert_vector(v, int, 666, 0);
  print_vector(v);

  printf("\nDelete second element:\n");
  erase_vector(v, 1);
  print_vector(v);

  printf("\nUse pop_front:\n");
  pop_front_vector(v);
  print_vector(v);

  printf("\nUse pop_back:\n");
  pop_back_vector(v);
  print_vector(v);

  printf("\nClear vector:\n");
  clear_vector(v);
  print_vector(v);

  printf("\nAdd 10 element, then use push_front:\n");
  for (int i = 0; i < 10; i++)
    push_back_vector(v, int, i);
  push_front_vector(v, int, 0x12345678);
  print_vector(v);

  printf("\nSize: %u\nCapacity: %u\n\n", size_vector(v), capacity_vector(v));

  free_vector(v);
}

int main(void)
{
  hard_way();
  easy_way();

  return 0;
}