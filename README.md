# VectorC
Safe vector in C for any type, but because of safety little slow ~0-20% than std::vector from C++. Support C89 and latest.
Welcome to Vector in C. To use it, please see the commands in the macros section in the header vector.h, as well as the sample code in the main.c section.
Anyone knows how to optimize, please write in a comment.
You can compare with vector in C++. It might be interesting to see the difference.
***
However, I recommend you use VectorC.h for own project in C. Because there is a template and convenient use here. A bit like OOP. Look at an example from file example.c.
***
How install VectorC.h?
* Just download VectorC.h and put on own project C
* Include VectorC.h using code: `#include "VectorC.h"`
* Done
Attention! This header can be work only in compiler for C (C89 and latest), not C++.

How use vector?
* Use macro `template_vector(type);` before using vector
* Create vector using macro `vector(type, name_vector);`. Even you can create vector without virtual methods using macro `vector_directly(type, name_vector);`. See difference:
```
 // Vector with virtual methods //
 vector(int, v1);
 v1.methods->push(v1.self, 500);
 // Vector without virtual methods //
 vector_directly(int, v2);
 v2.push(v2.self, 500);
```
* You can use methods: `name_vector.methods->name_method(...);`
* You can use operator [], just use macro `DATA(name_vector, type)[index] = ...;` or create temporary variable:
```
type* name_variable = DATA(name_vector, type);
name_variable[index] = ...;
```
* With enjoy :)
* But dont forget to free vector using macro `free_vector(name_vector);`
 
Methods:
```
restart(self); //Reset vector, free array
clear(self); //Clear vector without free
reserve(self, capacity); //Resize capacity of array
push(self, value); //Push
pop(self); //Pop
insert(self, index, value); //Add element in array
erase(self, index); //Delete element from array
size(self); //Get length of vector
capacity(self); //Get capacity of vector
print_data(self); //Print data
```
 
How use self?
* Just write `name_vector.self`
 
How use type struct?
* You need use `typedef struct name_struct;`
 
P.S. Please look file example.c
***
Well, thanks for visiting my code :)
