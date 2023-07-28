# VectorC
Welcome to safe vector in C for any type, but because of safety little slow ~0-10% than std::vector from C++. Support C89 and latest, even C++98 and latest.
Anyone knows how to optimize, please write in a comment.
You can compare with vector in C++. It might be interesting to see the difference.
***
I recommend you use VectorC.h for own project in C. Because there is a template and convenient use here. A bit like OOP. Look at an example from file example.c.
***
How install VectorC.h?
* Just download VectorC.h and put on own project C
* Include VectorC.h using code: `#include "VectorC.h"`
* Done

How use vector?
* Use macro `template_vector(type);` before using vector in global visibility
* Create vector using macro `vector(type, name_vector);`
* You can use methods: `name_vector.name_method(...);`
* You can use operator [], just use macro `DATA(name_vector, type)[index] = ...;` or create temporary variable:
```
type* name_variable = DATA(name_vector, type);
name_variable[index] = ...;
```
* With enjoy :)
* But dont forget to free vector using macro `free_vector(name_vector);`, because C don't have auto-deconstructor
 
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
* You need use `typedef struct _name_struct { ... } name_struct;`
 
P.S. Please look file example.c
***
Well, thanks for visiting my code :)
