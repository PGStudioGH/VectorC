#include "VectorC.h"

/* Initialization template */
template_vector(short);

int main(void)
{
  /* Create vector */
  vector(short, v);

  v.methods->push(v.self, 864);
  v.methods->push(v.self, 25);
  v.methods->push(v.self, 93);
  v.methods->push(v.self, 82);
  v.methods->push(v.self, 6);
  v.methods->push(v.self, 9);
  v.methods->push(v.self, 0xF8F0);
  printf("Show all elements from vector:\n");
  v.methods->print_data(v.self);

  printf("\nChanged fourth element to 2022:\n");
  DATA(v, short)[3] = 2022;
  v.methods->print_data(v.self);

  printf("\nSubtract first element by third and second elements:\n");
  short* data = DATA(v, short);
  data[0] -= data[2] + data[1];
  v.methods->print_data(v.self);

  printf("\nAdd new element 9999 on fourth element:\n");
  v.methods->insert(v.self, 3, 9999);
  v.methods->print_data(v.self);

  printf("\nAdd new element 666 on first element:\n");
  v.methods->insert(v.self, 0, 666);
  v.methods->print_data(v.self);

  printf("\nDelete second element:\n");
  v.methods->erase(v.self, 1);
  v.methods->print_data(v.self);

  printf("\nDelete first element:\n");
  v.methods->erase(v.self, 0);
  v.methods->print_data(v.self);

  printf("\nUse pop:\n");
  v.methods->pop(v.self);
  v.methods->print_data(v.self);

  printf("\nClear vector:\n");
  v.methods->clear(v.self);
  v.methods->print_data(v.self);

  printf("\nAdd 10 element, then add first element:\n");
  int i;
  for (i = 0; i < 10; i++)
    v.methods->push(v.self, i);
  v.methods->insert(v.self, 0, 0x1357);
  v.methods->print_data(v.self);

  printf("\nSize: %u\nCapacity: %u", v.methods->size(v.self), v.methods->capacity(v.self));

  free_vector(v);

  return 0;
}
