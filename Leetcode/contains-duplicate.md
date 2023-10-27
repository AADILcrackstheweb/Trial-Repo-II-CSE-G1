## Contains Duplicate (#216, E)
### **Problem Statement**
Given an integer array `nums`, return `true` if any value appears **at least twice** in the array, and return `false` if every element is distinct.

### **Algorithm**
1. Create a Hash Map and add every element as the program encounters it
2. Record it's presence by incrementing the respective hash, i.e., its occurence
3. While checking element, if any element's respective hash value is non-zero, (was already found) then break the loop and return `True`

### **Source Code**
```java
class Solution {
    public boolean containsDuplicate(int[] nums) {
        
        if(nums==null || nums.length==0)
            return false;
        
        HashSet<Integer> hset = new HashSet<Integer>();
        
        for(int idx: nums){
            if(!hset.add(idx)){
                return true;
            }
        }
        return false;
    }
}
```

### **Submission Metrics**
Runtime: 6 ms

Memory Usage: 55.72 MB