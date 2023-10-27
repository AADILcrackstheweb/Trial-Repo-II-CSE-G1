## Recursion
- Every recursion algorithm must have a _base-case_ (condition for terminating recursion) and a _recursion-case_ (condition on what to do after recursion)
- Absence of a _base-case_ would lead to an infinte loop

- Write a program to compute the factorial of a number recursively
  ```c
  #include <stdio.h>

  int factorial(int n){
      if (n == 1){
          return 1;
      }
      else{
          return n * factorial(n-1);
      }
  }

  int main()
  {
      int n;
      printf("Enter a number: ");
      scanf("%d", &n);
      printf("The factorial of %d is %d", n, factorial(n));
      return 0;
  }
  ```

- A typical tracing for a recursion program (here factorial) should look like 
  ```
  main() {
    factorial(5) {
      line 4
      call factorial(4)
      factorial(4) {
        line 4
        call factorial(3)
        factorial(3) {
          line 4
          call factorial(2)
          factorial(2) {
            line 4
            call factorial(1)
            factorial(1) {
              line 1
              line 2
              return 1
            }
            2 * factorial(1)
            2 * 1
            return 2
          }
          3 * factorial(2)
          3 * 2
          return 6
        }
        4 * factorial(3)
        4 * 6
        return 24
      }
      5 * factorial(4)
      5 * 24
      return 120
    }
    main function ends
    return 0
  }
  ```

Homework:
- Write a program to compute fibonacci series recursively
  ```c
  
  #include <stdio.h>

  int fib(int n)
  {
      if (n == 0 || n == 1)
          return n;
      else
          return fib(n - 1) + fib(n - 2);
  }

  int main()
  {
      int n;
      printf("Enter the number of terms: ");
      scanf("%d", &n);
      printf("The fibonacci series is: ");
      for (int loopvariable1 = 0; loopvariable1 < n; loopvariable1++)
      {
          printf("%d ", fib(loopvariable1));
      }
      printf("\n");
      return 0;
  }
  ```
