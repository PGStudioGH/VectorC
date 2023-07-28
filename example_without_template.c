/* Disable template */
#define VECTOR_WITHOUT_TEMPLATE

/* Header VectorC include stdio.h, stdlib.h, string.h */
#include "VectorC.h"

int main(void)
{
  vector(short, v);

  v.push(v.self, short, 864);
  v.push(v.self, short, 25);
  v.push(v.self, short, 93);
  v.push(v.self, short, 82);
  v.push(v.self, short, 6);
  v.push(v.self, short, 9);
  v.push(v.self, short, 0xF8F0);
  printf("Show all elements from vector:\n");
  v.print_data(v.self);

  printf("\nChanged fourth element to 2022:\n");
  DATA(v, short)[3] = 2022;
  v.print_data(v.self);

  printf("\nSubtract first element by third and second elements:\n");
  short* data = DATA(v, short);
  data[0] -= data[2] + data[1];
  v.print_data(v.self);

  printf("\nAdd new element 9999 on fourth element:\n");
  v.insert(v.self, short, 3, 9999);
  v.print_data(v.self);

  printf("\nAdd new element 666 on first element:\n");
  v.insert(v.self, short, 0, 666);
  v.print_data(v.self);

  printf("\nDelete second element:\n");
  v.erase(v.self, 1);
  v.print_data(v.self);

  printf("\nDelete first element:\n");
  v.erase(v.self, 0);
  v.print_data(v.self);

  printf("\nUse pop:\n");
  v.pop(v.self);
  v.print_data(v.self);

  printf("\nClear vector:\n");
  v.clear(v.self);
  v.print_data(v.self);

  printf("\nAdd 10 element, then add first element:\n");
  int i;
  for (i = 0; i < 10; i++)
    v.push(v.self, short, i);
  v.insert(v.self, short, 0, 0x1357);
  v.print_data(v.self);

  printf("\nSize: %u\nCapacity: %u", v.size(v.self), v.capacity(v.self));

  free_vector(v);

  return 0;
}
