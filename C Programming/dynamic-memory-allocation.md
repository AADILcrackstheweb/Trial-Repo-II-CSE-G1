### **Dynamic Memory Allocation**
- Dynamic memory allocation in C allows the program to request memory from the system at runtime. 
- The standard library functions `malloc`, `calloc`, and `realloc` are used to allocate memory dynamically. 
- The `free` function is used to release the allocated memory when it is no longer needed.

- `malloc`:
   - Allocates a block of memory of the specified size in bytes.
   - The allocated memory block contains garbage values. You need to manually initialize the memory before using it.
   - Example:
     ```c
     int* ptr = (int*)malloc(5 * sizeof(int));
     ```

- `calloc`:
   - Allocates a block of memory for an array of elements, initializing all bytes to zero.
   - The allocated memory block is initialized to zero.
   - Example:
     ```c
     int* ptr = (int*)calloc(5, sizeof(int));
     ```

- `realloc`:
   - Resizes the memory block pointed to by `ptr` to the specified size.
   - If the new size is larger than the old size, the additional bytes are uninitialized. If the new size is smaller, the data may be truncated.
   - Example:
     ```c
     int* ptr = (int*)malloc(5 * sizeof(int));
     // Reallocate to a larger size
     ptr = (int*)realloc(ptr, 10 * sizeof(int));
     ```

In summary, `malloc` allocates memory without initializing it, `calloc` allocates memory and initializes all bytes to zero, `realloc` resizes an existing memory block, preserving the old data (if possible) and potentially extending or truncating the block.

- Write a program to allocate memory for int array of size 10 and write and read using pointer arithmetic.
  ```c
  #include <stdio.h>
  #include <stdlib.h>

  int main()
  {
      int *pointer = malloc(sizeof(int) * 10);

      for (int loopvariable1 = 0; loopvariable1 < 10; loopvariable1++)
      {
          *(pointer + loopvariable1) = loopvariable1 + 1;
      }

      for (int loopvariable1 = 0; loopvariable1 < 10; loopvariable1++)
      {
          printf("%d\n", *(pointer + loopvariable1));
      }

      free(pointer);
  }
  ```
- Rewrite the above function to use the `calloc()` function 
  ```c
  #include <stdio.h>
  #include <stdlib.h>

  int main(void)
  {
      int *pointer = calloc(10, sizeof(int));

      for (int loopvariable1 = 0; loopvariable1 < 10; loopvariable1++)
      {
          *(pointer + loopvariable1) = loopvariable1 + 1;
      }

      for (int loopvariable1 = 0; loopvariable1 < 10; loopvariable1++)
      {
          printf("%d\n", *(pointer + loopvariable1));
      }

      free(pointer);    
  }```

- Using `realloc()` to increase the size returns a pointer to a new larger chunk of memory. Existing values are being copied to a new memory address whislt the old memory address is discarded.
- Similarly, using `realloc()` for decrease the size returns original pointer with reduced size and values outside are discarded.
- Write a program that takes a sentence as input, dynamically allocates memory for that sentence and counts number of words in that sentence.
  ```c
  #include <stdio.h>
  #include <stdlib.h>
  #include <conio.h>

  int main(void)
  {
      printf("Enter a sentence:\n");

      int size = 1, words = 0;
      char *memoryPointer = malloc(sizeof(char));
      do
      {
          *(memoryPointer + size - 1) = getch();
          if (*(memoryPointer + size - 1) == ' ')
          {
              words += 1;
          }
          size += 1;
          memoryPointer = realloc(memoryPointer, sizeof(char) * size);
      }
      while (*(memoryPointer + size - 2) != '.');

      *(memoryPointer + size - 1) = '\0';

      printf("\nEnterned sentence is:\n%s\nIt has %i words", memoryPointer, words + 1);

      free(memoryPointer);
  }
  ```
