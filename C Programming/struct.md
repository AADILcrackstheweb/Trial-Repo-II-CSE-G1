### `struct`
- A `struct` is a user-defined data type that allows to group  multiple variables of different types into a single unit

- It provides a way to represent a collection of data elements as a single entity

- General Syntax of a `struct` is as follows:
  ```c
  struct structureName {
   dataType member1;
   dataType member2;
   // ... additional members
  };
  ```
- Structs can be initiallized in two ways. 
  ```c
  struct Person person1;
  strcpy(person1.name, "John Doe");
  person1.age = 25;
  person1.height = 175.5;
  ```
  or
  ```c
  struct Person person2 = {"Jane Smith", 30, 162.3};

  ```

- String Assignment cannot happen like `str1 = str2`. Every index of the string(s) must be iterated and assigned

- `int number` is a _definition_ and `extern int i` is a _declaration_. 

- A declaration **does not** take up memory space.

- One can quickly assign properties of a struct by using below syntax:
  ```c
  struct employee e = {name="<employee-name>",id= 1001}
  ```
- One way of accessing a _structure member_ is via a period (**.**)
- Q: Write a program to copy a string from one variable to another variable
  ```c
  #include <stdio.h>
  #include <stdlib.h>

  int main()
  {
      char str1[20] = "Hello World";
      char str2[20];

      int loopvariable1 = 0;
      while(str1[loopvariable1] != '\0')
      {
          str2[loopvariable1] = str1[loopvariable1];
          loopvariable1++;
      }
      str2[loopvariable1] = '\0';
      printf("%s", str2);
      return 0;
  }
  ```
- Q: Write a program to define an `employee` struct, assign its properties and print it in main function
  ```c
  #include <stdio.h>
  #include <stdlib.h>

  struct employee
  {
      char name[20];
      int id;
  };

  int main()
  {
      struct employee e;
      printf("Enter the name of the employee: ");
      scanf("%s", e.name);
      printf("Enter the id of the employee: ");
      scanf("%d", &e.id);
      printf("The name of the employee is %s and his id is %d\n", e.name, e.id);
      return 0;
  }
  ```
Some alternatives of above program is
  ```c
  #include <stdio.h>

  struct employees
  {
      char name[100];
      int id;
  };

  int main(void)
  {
  struct employees e[3] = {{.name = "joerogan", 
  id = 1}, {.name = "morgan", .id = 2}, {.name = 
  "freeman", .id = 3}};

  }
  ```
- Create a structure `person` with `name`, `height`, `marks(6)` and `age`. Get input for 3 persons and average marks for each person.
  ```c
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>

  struct person
  {
      char name[20];
      int height;
      int marks[6];
      int age;
      float average;
  };

  int main(void) {
      struct person personstructure[3];
      int loopvariable1;
      float highestAverage = 0;
      struct person highestAveragePerson;

      for (loopvariable1 = 0; loopvariable1 < 3; loopvariable1++) {
          printf("Enter name: ");
          scanf("%s", personstructure[loopvariable1].name);
          printf("Enter height: ");
          scanf("%d", &personstructure[loopvariable1].height);
          printf("Enter age: ");
          scanf("%d", &personstructure[loopvariable1].age);
          printf("Enter marks: ");
          scanf("%d %d %d %d %d %d", &personstructure[loopvariable1].marks[0], &personstructure[loopvariable1].marks[1], &personstructure[loopvariable1].marks[2], &personstructure[loopvariable1].marks[3], &personstructure[loopvariable1].marks[4], &personstructure[loopvariable1].marks[5]);
          personstructure[loopvariable1].average = (personstructure[loopvariable1].marks[0] + personstructure[loopvariable1].marks[1] + personstructure[loopvariable1].marks[2] + personstructure[loopvariable1].marks[3] + personstructure[loopvariable1].marks[4] + personstructure[loopvariable1].marks[5]) / 6.0;
          printf("Average: %.2f\n", personstructure[loopvariable1].average);
          if (personstructure[loopvariable1].average > highestAverage) {
              highestAverage = personstructure[loopvariable1].average;
              highestAveragePerson = personstructure[loopvariable1];
          }
      }
  }
  ```
- Q:Create a similar program like above, which computes the person with maximum average by passing the array of structures to a function.

  ```c
    #include <stdio.h>

  struct person
  {
      char name[100];
      float height;
      int age;
      float marks[6];
      float avg;
  };

  float avg(struct person avgstruct);
  struct person maxAvg(struct person avgstruct[], int length);

  int main(void)
  {
      struct person personstructure[3];

      for (int loopvariable1 = 0; loopvariable1 < 3; loopvariable1++)
      {
          printf("Person %d\nEnter the name: ", loopvariable1 + 1);
          fgets(personstructure[loopvariable1].name, 100, stdin);

          printf("Enter Height: ");
          scanf("%f", &personstructure[loopvariable1].height);

          printf("Enter Age: ");
          scanf("%d", &personstructure[loopvariable1].age);

          for (int loopvariable2 = 0; loopvariable2 < 6; loopvariable2++)
          {
              printf("Enter mark %d: ", loopvariable2 + 1);
              scanf("%f", &personstructure[loopvariable1].marks[loopvariable2]);
          }
          
          personstructure[loopvariable1].avg = avg(personstructure[loopvariable1]);
      }

      printf("\n");
      struct person maxRecord = maxAvg(personstructure, 3);
      printf("Person with maximum average is %s", maxRecord.name);   
  }

  float avg(struct person avgstruct)
  {
      float avg = 0;
      for (int loopvariable1 = 1; loopvariable1 < 6; loopvariable1++)
      {
          avg += avgstruct.marks[loopvariable1];
      }
      avg /= (float) 6;
      return avg;
  }

  struct person maxAvg(struct person avgstruct[], int length)
  {
      struct person maximum = avgstruct[0];
      for (int loopvariable1 = 0; loopvariable1 < length; loopvariable1 ++)
      {
          if (maximum.avg < avgstruct[loopvariable1].avg)
          {
              maximum = avgstruct[loopvariable1];
          }
      }

      return maximum;
  }
  ```