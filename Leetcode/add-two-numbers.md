## Add Two Numbers (#2, M)
### **Problem Statement**
You are given two **non-empty** linked lists representing two non-negative integers. The digits are stored in **reverse order**, and each of their nodes contains a single digit. Add the two numbers and return the sum as a linked list.

You may assume the two numbers do not contain any leading zero, except the number 0 itself.

![](https://assets.leetcode.com/uploads/2020/10/02/addtwonumber1.jpg)

### **Algorithm**
1. Firstly normalize the Linked List (if two lists are of unequal size) by adding elements with `0` to the end of required list
2. Iterate through both lists simultaneously add two numbers in that element and carry forward the `carry` if necessary. 
3. Insert the sum without the carry to a new linked list
4. After iterating completely, return the third linked list containing all sum  

### **Source Code**
```c
void normalizelists(struct ListNode * listhead1, struct ListNode * listhead2){
    struct ListNode * iterableelement1 = listhead1, * iterableelement2 = listhead2;
    int lengthoflist1 = 0, lengthoflist2 = 0;

    while(iterableelement1->next != NULL || iterableelement2->next != NULL){
        if(iterableelement1->next != NULL){
            lengthoflist1++;
            iterableelement1 = iterableelement1->next;
        }
        if(iterableelement2->next != NULL){
            lengthoflist2++;
            iterableelement2 = iterableelement2->next;
        }
    }
    
    int difference = lengthoflist1 - lengthoflist2;
    struct ListNode * iterableelement = difference < 0 ? iterableelement1 : iterableelement2;

    for (int iterable = 0; iterable < abs(difference); iterable++){
        struct ListNode * newListNode = getListNode(0);
        iterableelement->next = newListNode;
        iterableelement = iterableelement->next;
    }
}

struct ListNode * addition(struct ListNode * headelement1, struct ListNode * headelement2){

    int carry = 0, arithmeticsum = 0, sum = 0;
    struct ListNode * finalAssignment  =  NULL, * assignvar = finalAssignment;
    struct ListNode * temp1 = headelement1, * temp2 = headelement2;

    while (temp1 != NULL && temp2 != NULL){
        arithmeticsum = temp1->val + temp2->val + carry;
        carry = arithmeticsum / 10;
        sum = arithmeticsum % 10;

        temp1 = temp1->next;
        temp2 = temp2->next;
        
        struct ListNode * newListNode = getListNode(sum);
        if (finalAssignment == NULL){
            finalAssignment = newListNode;
            assignvar = finalAssignment;
        } else {
            assignvar->next = newListNode;
            assignvar = assignvar->next;
        }
    }

    if(carry == 1){
        struct ListNode * newListNode = getListNode(carry);
        assignvar->next = newListNode;
        assignvar = assignvar->next;
    }

    return finalAssignment;
}

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2){
    normalizelists(l1, l2);
    return addition(l1, l2);
}

```

### **Submission Metrics**
Runtime: 16ms

Memory Usage: 7.7 MB