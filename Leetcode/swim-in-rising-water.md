## Swim in Rising Water (#778,H)
### **Problem Statement**
You are given an `n x n` integer matrix `grid` where each value `grid[i][j]` represents the elevation at that point `(i, j)`.

The rain starts to fall. At time `t`, the depth of the water everywhere is `t`. You can swim from a square to another 4-directionally adjacent square if and only if the elevation of both squares individually are at most `t`. 

You can swim infinite distances in zero time. Of course, you must stay within the boundaries of the grid during your swim.

Return the least time until you can reach the bottom right square `(n - 1, n - 1)` if you start at the top left square `(0, 0)`

![](https://assets.leetcode.com/uploads/2021/06/29/swim2-grid-1.jpg)

### **Algorithm**
1. Have a `start` and `end` variable with values from `numberarray[0][0]` and `numberarray[numsize-1][numsize-1]` respectively
2. Access values of current values in all possible directions (up, down, left, right). 
3. Call the same function on the indicies of the minimumvalue of adjacent matrix
4. Maintain a array `path` containing the elements which contains all the elements already crossed
5. Have a integer variable `max`, initialized to the first element and periodically updates its value _if it crosses an element with value greater than itself_
6. After reaching bottom right element, terminate the loop / recursion and return `max`

### **Source Code**
```python
class Solution:
    def move(self, gridmatrix, xpos, ypos, pathlist):
        # find up down left and right elements and call the function on the smallest element
        up = gridmatrix[xpos-1][ypos] if xpos > 0 else 10000
        down = gridmatrix[xpos+1][ypos] if xpos < len(gridmatrix)-1 else 10000
        left = gridmatrix[xpos][ypos-1] if ypos > 0 else 10000
        right = gridmatrix[xpos][ypos+1] if ypos < len(gridmatrix[0])-1 else 10000

        # find the smallest element that hasn't been visited
        smallest = min(val for val in [up, down, left, right] if val not in pathlist)

        # find the position of the smallest element
        if smallest == up:
            xpos -= 1
        elif smallest == down:
            xpos += 1
        elif smallest == left:
            ypos -= 1
        elif smallest == right:
            ypos += 1

        # check if the smallest element is the last element
        if gridmatrix[-1][-1] in [up, down, left, right]:
            pathlist.append(gridmatrix[-1][-1])
            return pathlist
        else:
            pathlist.append(smallest)
            return self.move(gridmatrix, xpos, ypos, pathlist)

    def swimInWater(self, grid):
        path = [grid[0][0]]
        return max(self.move(grid, 0, 0, path))
```

### **Submission Metrics**
Runtime: 90 ms

Memory Usage: 16.9 MB