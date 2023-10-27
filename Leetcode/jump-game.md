## Jump Game(#55, M)
### **Problem Statement**
You are given an integer array `nums`. You are initially positioned at the array's first index, and each element in the array represents your maximum jump length at that position.

Return `true` if you can reach the last index, or `false` otherwise.

### **Algorithm**
1. We have the function header `bool canJump(int* nums, int numsSize)`
2. Use a integer `target` variable which is set to the last index number, `numsSize - 1`
3. Iterate through the given integer array from back. If the *sum of the current element* and its *index* is **greater than or equal** to the target, update the target to the current index.
4. Once the `target` value has reached 0, which means if it had reached the first index, then we can conclude that it is possible to jump from first element to the last element

### **Source Code**
```c
bool canJump(int* nums, int numsSize){
    int target = numsSize - 1;
    for (int iterable = numsSize - 2; iterable >= 0; iterable--){
        if (nums[iterable] + iterable >= target){
            target = iterable;
        }
    }
    return target == 0;
}
```

### **Submission Metrics**
Runtime: 48 milliseconds

Memory Usage: 8.6 MB