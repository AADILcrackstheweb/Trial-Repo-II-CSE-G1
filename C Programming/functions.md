### **Functions**

- The value passed in into a function call is called **argument** and variable in function declaration is called **parameter**

- Write a program with a function `isFactor()` which takes in two parameters and returns a boolean which is then used in a `main()` to print some final statements

  ```c
  #include <stdio.h>

  int isFactor(int a, int b)
  {
      if (a % b == 0)
      {
          return 1;
      }
      else
      {
          return 0;
      }
  }

  int main()
  {
      int a, b;
      printf("Enter two numbers: ");
      scanf("%d %d", &a, &b);
      if (isFactor(a, b))
      {
          printf("%d is a factor of %d\n", b, a);
      }
      else
      {
          printf("%d is not a factor of %d\n", b, a);
      }
      return 0;
  }

  ```

- Use the above function `isFactor()` for checking wheter a given number is a prime number or not

  ```c
  int isPrime(int a)
  {
      int loopvariable1;
      for (loopvariable1 = 2; loopvariable1 < a; loopvariable1++)
      {
          if (isFactor(a, loopvariable1) == 1)
          {
              return 0;
          }
      }
      return 1;
  }

  ```

- Use the above two functions `isFactor` and `isPrime` to create a new function `primerange` which prints prime numbers between two ranges

  ```c
  void primerange(int a, int b)
  {
      int loopvariable1;
      for (loopvariable1 = a; loopvariable1 <= b; loopvariable1++)
      {
          if (isPrime(loopvariable1) == 1)
          {
              printf("%d\n", loopvariable1);
          }
      }
  }

  int main()
  {
      int a, b;
      printf("Enter two numbers: ");
      scanf("%d %d", &a, &b);
      primerange(a, b);
      return 0;
  }
  ```
