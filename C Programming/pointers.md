### Pointers
reference: [dhakkshin's *Sem2_C* repository](https://github.com/Dhakkshin/sem2_C/blob/main/notes/pointers.md#200523)

- A Pointer basically stores the memory address of one variable in it

- It refers back to the memory address incase of a call and performs the requested operations

- Example Code:
  ```c
  #include <stdio.h>

  int main(void)
  {
      int number = 4;
      int *pointer = &number;
      printf("%i, %p\n", *pointer, pointer);
      //same as
      // printf("%i, %p\n", number, pointer);
  }
  ```
  
- Dereferencing is the process of accessing a memory address of the variable a pointer points to by adding an asterisk(*) infront of it, like the above example

- Pointer Arithmetic allows the pointer to access values in different memory address by performing arithmetic operations from its intial value

  ```c
  #include <stdio.h>

  int main(void)
  {
      int numberarray[] = {1,2,3,4};
      int *pointer = numberarray;

      printf("%i, %i\n",*pointer, *(pointer + 1));
  }
  ```
- Consider the following code:
  ```c
  #include <stdio.h>

  int main(void)
  {
      int number1[] = {1,2,3,4}, number2;
      int *pointer1 = number1;
      int *pointer2 = number2;

      printf("")

      // number1, number2, pointer1, pointer2
      // &number1, &number2, &pointer1, &pointer2
      // *pointer1, *pointer2
  }
  ```
  in the above code,
  |Memory Address|Value|
  | - | - |
  |number1, pointer1, pointer2, &number1, &number2, &pointer1, &pointer2|number2, *pointer1, *pointer2|
