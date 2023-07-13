#include <stdio.h>

#include "vector.h"

int main(void)
{
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

    printf("\nSize: %u\nCapacity: %u", size_vector(v), capacity_vector(v));

    free_vector(v);

    return 0;
}
