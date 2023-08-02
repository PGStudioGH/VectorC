/* Disable template */
#define VECTOR_WITH_STYLE_C

/* Header VectorC include stdio.h, stdlib.h, string.h */
#include "VectorC.h"

int main(void)
{
  vector(short, v);

  push(v, short, 864);
  push(v, short, 25);
  push(v, short, 93);
  push(v, short, 82);
  push(v, short, 6);
  push(v, short, 9);
  push(v, short, 0xF8F0);
  printf("Show all elements from vector:\n");
  print_data(v);

  printf("\nChanged fourth element to 2022:\n");
  at(v, short)[3] = 2022;
  print_data(v);

  printf("\nSubtract first element by third and second elements:\n");
  short* data = at(v, short);
  data[0] -= data[2] + data[1];
  print_data(v);

  printf("\nAdd new element 9999 on fourth element:\n");
  insert(v, short, 3, 9999);
  print_data(v);

  printf("\nAdd new element 666 on first element:\n");
  insert(v, short, 0, 666);
  print_data(v);

  printf("\nDelete second element:\n");
  erase(v, 1);
  print_data(v);

  printf("\nDelete first element:\n");
  erase(v, 0);
  print_data(v);

  printf("\nUse pop:\n");
  pop(v);
  print_data(v);

  printf("\nClear vector:\n");
  clear(v);
  print_data(v);

  printf("\nAdd 10 element, then add first element:\n");
  int i;
  for (i = 0; i < 10; i++)
    push(v, short, i);
  insert(v, short, 0, 0x1357);
  print_data(v);

  printf("\nSize: %u\nCapacity: %u", size(v), capacity(v));

  free_vector(v);

  return 0;
}
