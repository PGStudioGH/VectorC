#include <stdio.h>

#include "vector.h"

int main(void)
{
    vector v = create_vector(int);

    push_vector(v, int, 864);
    push_vector(v, int, 25);
    push_vector(v, int, 93);
    push_vector(v, int, 82);
    push_vector(v, int, 6);
    push_vector(v, int, 9);
    push_vector(v, int, 0xFF88FF00);
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

    printf("\nSize: %llu", size_vector(v));

    free_vector(v);

    return 0;
}