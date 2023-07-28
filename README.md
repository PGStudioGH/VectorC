# VectorC
Welcome to safe vector in C for any type, but because of safety little slower ~0-10% (sometime little faster ~0-10%) than std::vector from C++. Support C89 and latest, even C++98 and latest.
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
* If you want use vector without template (universal vector), you can write `#define VECTOR_WITHOUT_TEMPLATE` before including header. Please look file example_without_template.c. But slower than vector with template.
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
push(self, type, value); //Push for vector without template
pop(self); //Pop
insert(self, index, value); //Add element in array
insert(self, type, index, value); //Insert for vector without template
erase(self, index); //Delete element from array
size(self); //Get length of vector
capacity(self); //Get capacity of vector
print_data(self); //Print data
```
 
How I can use self?
* Just write `name_vector.self`
 
How I can use type struct?
* Need use `typedef struct _name_struct { ... } name_struct;`

How I can use type pointer? Pointer to function?
* Just write `typedef type* type_ptr;`, then `vector(type_ptr, v);`. Even write `typedef type (*type_fun)();`, then `vector(type_fun, v);`
 
P.S. Please look file example.c
***
Well, thanks for visiting my code :)
