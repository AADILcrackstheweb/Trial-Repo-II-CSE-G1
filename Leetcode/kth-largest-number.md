## Kth Largest Element in an Array (#215, M)
### **Problem Description**
Given an integer array `nums` and an integer `k`, return the `kth` largest element in the array.

Note that it is the `kth` largest element in the sorted order, not the `kth` distinct element.

### **Algorithm**
1. Initialize an integer array `frequency` of size 20001 with all elements set to 0. This array will be used to store the frequency of each integer in the input array.

2. Iterate over the `nums` array from index 0 to `numsSize - 1`.

3. For each element in the `nums` array, calculate its index in the `frequency` array by adding 10000 to the element's value. Increment the value at that index in the `frequency` array by 1.

4. Iterate through the frequency array from back, i.e., from index 20000 to 0

5. For each element in the `frequency` array, subtract its value from `k`. If `k` is less than or equal to 0, return the integer value corresponding to the current index in the `frequency` array minus 10000.

### **Source Code**
```c
int findKthLargest(int* nums, int numsSize, int k) {
    int frequency[20001] = {0};

    for (int i = 0; i < numsSize; i++)
        frequency[nums[i] + 10000]++;

    for (int i = 20000; i >= 0; i--) {
        k -= frequency[i];
        if (k <= 0) return i - 10000;
    }

    return 0;
}
```

### **Submission Metrics**
Runtime: 69 ms

Memory Usage: 11.8 MB