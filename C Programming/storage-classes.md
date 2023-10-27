### **Storage Classes**
- There are totally four types of variables, 
  
  1. `auto`(global)
  2. `static`
  3. `register`
  4. `local`

- Variables that are more frequently used are explcitly declared to be stored in registry than RAM for faster access
- The keyword `register` is used
- Static Variables:
  - **Scope**: Static variables have either file scope (if defined outside of any function) or block scope (if defined inside a function). File scope means the variable is accessible from any function within the same source file. Block scope restricts the variable's visibility to the block where it is defined.
  - **Lifetime**: Static variables have a lifetime that extends throughout the execution of the program. They are created when the program starts and retain their values between function calls. If declared inside a function, they are initialized only once.

- Global Variables:

  - **Scope**: Global variables have file scope, meaning they can be accessed from any function within the same source file. Additionally, global variables can be accessed by other source files if they are declared with the "extern" keyword.
  - **Lifetime**: Global variables have a lifetime that extends throughout the execution of the program. They are created when the program starts and retain their values until the program terminates.

- Local Variables:

  - **Scope**: Local variables are declared within a block or function and have block scope. They are accessible only within the block where they are defined.
  - **Lifetime**: Local variables have a lifetime that depends on their storage class. Automatic (non-static) local variables are created when the block is entered and destroyed when it is exited.Static local variables have a lifetime that extends throughout the execution of the program, similar to static variables.

- Register Variables:

  - **Scope**: Register variables have block scope and are accessible only within the block where they are defined.
  - **Lifetime**: Register variables have a lifetime that is similar to automatic (non-static) local variables. They are created when the block is entered and destroyed when it is exited. However, the "register" keyword is often ignored by modern compilers, and the variables may be stored in memory instead of registers.
