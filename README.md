# VectorC
Safe vector in C for any type, but because of safety little slow ~0-20% than std::vector from C++. Support C89 and latest.
Welcome to Vector in C. To use it, please see the commands in the macros section in the header vector.h, as well as the sample code in the main.c section.
Anyone knows how to optimize, please write in a comment.
You can compare with vector in C++. It might be interesting to see the difference.
***
However, I recommend you use VectorC.h for own project in C. Because there is a template and convenient use here. A bit like OOP. Look at an example from file example.c.
***
  How install VectorC.h?
* 1. Just download VectorC.h and put on own project C
* 2. Include VectorC.h using code: "#include "VectorC.h""
* 3. Done
*
* Attention! This header can be work only in compiler for C (C89 and latest), not C++.

   How use vector?
 * 1. Use macro "template_vector(type);" before using vector
 * 2. Create vector using macro "vector(type, name_vector);"
 * 3. You can use methods: "name_vector.methods->name_method(...);"
 * 4. You can use operator [], just use macro "DATA(name_vector, type)[index]" or create temporary variable "type* name_variable = DATA(name_vector, type); name_variable[index] = ...;"
 * 5. With enjoy :)
 * 6. But dont forget to free vector using macro "free_vector(name_vector);"
 
   Methods:
restart(self);
clear(self);
reserve(self, capacity);
push(self, value);
pop(self);
insert(self, index, value);
erase(self, index);
size(self);
capacity(self);
print_data(self);
 
   How use self?
 * - Just write "name_vector.self"
 
   How use type struct?
 * - You need use typedef struct
 
P.S. Please look file example.c
***
Well, thanks for visiting my code :)
