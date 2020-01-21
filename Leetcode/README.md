# 리츠코드 문제풀이

## 2020

----------------------------------

### [ 142. Linked List Cycle II ](https://leetcode.com/problems/linked-list-cycle-ii/) - medium

- 문제

Given a linked list, return the node where the cycle begins. If there is no cycle, return null.

To represent a cycle in the given linked list, we use an integer pos which represents the position (0-indexed) in the linked list where tail connects to. If pos is -1, then there is no cycle in the linked list.

Note: Do not modify the linked list.

- 제한사항
	-  Can you solve it without using extra space?

- 입출력 예
  
```
Input: head = [3,2,0,-4], pos = 1
Output: tail connects to node index 1
Explanation: There is a cycle in the linked list, where tail connects to the second node.
```

![example](https://assets.leetcode.com/uploads/2018/12/07/circularlinkedlist.png)

```
Input: head = [1,2], pos = 0
Output: tail connects to node index 0
Explanation: There is a cycle in the linked list, where tail connects to the first node.
```

![example](https://assets.leetcode.com/uploads/2018/12/07/circularlinkedlist_test2.png)

```
Input: head = [1], pos = -1
Output: no cycle
Explanation: There is no cycle in the linked list.
```

![example](https://assets.leetcode.com/uploads/2018/12/07/circularlinkedlist_test3.png)

- 풀이
  - Linked List, two pointer

```C++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        if (head == NULL || head->next == NULL)
            return NULL;
        
        ListNode *slower = head;
        ListNode *faster = head;
        ListNode *temper = head;        
        
        // 항상 faster가 빠르므로, fastet->next, fastet->next->next가 nullptr일때 nullptr을 리턴
        while (faster->next && faster->next->next){
            // slower는 한 노드씩 증가
            // faster는 두 노드씩 증가
            slower = slower->next;
            faster = faster->next->next;
            
            // slower와 faster가 같다면 기본적으로 cycle이 형성된다고 볼수 있음
            if(slower == faster){
                // cycle이 형성된 상태에서 head부터 한 노드씩 증가하는 temper와
                // 현재 slower에서 한 노드씩 증가할때,
                // temper와 slower가 같아지는 노드가 cycle 지점
                 while(slower != temper){
                    slower = slower->next;
                    temper = temper->next;
                 }
                
                return slower;
            }
        };
        return nullptr;
    }
};
```

----------------------------------

### [ 461. Hamming Distance ](https://leetcode.com/problems/hamming-distance/) - easy

- 문제

The Hamming distance between two integers is the number of positions at which the corresponding bits are different.

Given two integers x and y, calculate the Hamming distance.

- 제한사항
	- 0 ≤ x, y < 231.

- 입출력 예
  
```
Input: x = 1, y = 4

Output: 2

Explanation:
1   (0 0 0 1)
4   (0 1 0 0)
       ↑   ↑

The above arrows point to positions where the corresponding bits are different.
```

- 풀이
  - Bit Manipulation

```C++
class Solution {
public:
    int hammingDistance(int x, int y) {
        int count = 0;
        int temp = x ^ y;
        
        while(temp){
            temp = temp & (temp-1);
            ++count;
        }
        
        return count;
    }
};
```

----------------------------------

### [ 292. Nim Game ](https://leetcode.com/problems/nim-game/) - easy

- 문제

You are playing the following Nim Game with your friend: There is a heap of stones on the table, each time one of you take turns to remove 1 to 3 stones. The one who removes the last stone will be the winner. You will take the first turn to remove the stones.

Both of you are very clever and have optimal strategies for the game. Write a function to determine whether you can win the game given the number of stones in the heap.

- 제한사항

- 입출력 예
  
```
Input: 4
Output: false 
Explanation: If there are 4 stones in the heap, then you will never win the game;
             No matter 1, 2, or 3 stones you remove, the last stone will always be 
             removed by your friend.
```

- 풀이
  - 

```C++
class Solution {
public:
    bool canWinNim(int n) {
        if(n % 4 == 0)
            return false;
        
        return true;
    }
};
```

----------------------------------

### [ 1048. Longest String Chain ](https://leetcode.com/problems/longest-string-chain/) - medium

- 문제

Given a list of words, each word consists of English lowercase letters.

Let's say word1 is a predecessor of word2 if and only if we can add exactly one letter anywhere in word1 to make it equal to word2.  For example, "abc" is a predecessor of "abac".

A word chain is a sequence of words [word_1, word_2, ..., word_k] with k >= 1, where word_1 is a predecessor of word_2, word_2 is a predecessor of word_3, and so on.

Return the longest possible length of a word chain with words chosen from the given list of words.

- 제한사항
	- 1 <= words.length <= 1000
    - 1 <= words[i].length <= 16
    - words[i] only consists of English lowercase letters.

- 입출력 예
  
```
Input: ["a","b","ba","bca","bda","bdca"]
Output: 4
Explanation: one of the longest word chain is "a","ba","bda","bdca".
```

- 풀이
  - DP

```C++
bool comp(const string& a, const string& b){
    return a.size() < b.size();
}

class Solution {
public:
    int longestStrChain(vector<string>& words) {
        int len = words.size();
        vector<int> res(len, 1);
        
        // 길이가 작은 단어순으로 정렬
        sort(words.begin() , words.end(), comp);

        for(auto i = 1 ; i < len ; ++i){
            // 단어의 길이가 1 이면 패스
            if(words[i].size() == 1)
                continue;

            int max = 0;
            for(auto j = 0 ; j < i ; ++j){
                // 단어의 길이가 하나 차이가 나야 word chain이 가능
                if(words[j].size() != words[i].size() - 1)
                    continue;
                
                // 첫번째 단어부터 현재단어 전까지 
                // 단어 하나 차이가 나는지 검사
                int checkWordIndex = 0;
                for(auto k = 0 ; k < words[i].size() && checkWordIndex < words[j].size(); ++k){
                    if(words[i][k] == words[j][checkWordIndex]){
                        ++checkWordIndex;
                    }
                }
                
                /// word chain이 가능한 단어중
                // 가장 긴 word chain의 수를 찾음
                if(checkWordIndex == words[j].size()){
                    if(max < res[j])
                        max = res[j];
                }
            }
            
            // 가장 긴 word chain의 수를 저장
            res[i] += max;
        }
        
        return *max_element(res.begin(), res.end());
    }
};
```

----------------------------------

### [ 64. Minimum Path Sum ](https://leetcode.com/problems/minimum-path-sum/) - medium

- 문제

Given a m x n grid filled with non-negative numbers, find a path from top left to bottom right which minimizes the sum of all numbers along its path.

Note: You can only move either down or right at any point in time.

- 제한사항

- 입출력 예
  
```
Input:
[
  [1,3,1],
  [1,5,1],
  [4,2,1]
]
Output: 7
Explanation: Because the path 1→3→1→1→1 minimizes the sum.
```

- 풀이
  - DP

```C++
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        for(auto i = 0 ; i < m ; ++i){
            for(auto j = 0 ; j < n ; ++j){
                if(i == 0 && j == 0)
                    continue;
                // row, colum의 첫줄의 경로는 한가지 밖에 없음
                if(i == 0 && j != 0){
                    grid[i][j] += grid[i][j-1];    
                }
                else if(i !=0 && j == 0){
                    grid[i][j] += grid[i-1][j];                        
                }
		// 경로는 위 또는 왼쪽에서 밖에 올수 없으므로,
		// 둘중 작은 값을 선택
                else{
                    grid[i][j] += min(grid[i][j-1], grid[i-1][j]);
                }
            }
        }
        
        return grid[m-1][n-1];
    }
};
```

----------------------------------

### [ 1277. Count Square Submatrices with All Ones ](https://leetcode.com/problems/count-square-submatrices-with-all-ones/) - medium

- 문제

Given a non negative integer number num. For every numbers i in the range 0 ≤ i ≤ num calculate the number of 1's in their binary representation and return them as an array.

- 제한사항
  - It is very easy to come up with a solution with run time O(n*sizeof(integer)). But can you do it in linear time O(n)/possibly in a single pass?
  - Space complexity should be O(n).
  - Can you do it like a boss? Do it without using any builtin function like __builtin_popcount in c++ or in any other language.


- 입출력 예
  
```
Example 1:

Input: 2
Output: [0,1,1]

Example 2:

Input: 5
Output: [0,1,1,2,1,2]
```

- 풀이
  - DP

```C++
class Solution {
public:
    vector<int> countBits(int num) {
        if(num == 0)
            return {0};
        else if(num == 1)
            return {0,1};

        vector<int> res(num + 1, 0);
        int carry = 0;
        
        res[0] = 0;    
        res[1] = 1;    

        for(int i = 2 ; i <= num ; ++i){
            // Pow of 2 는 비트에서 1의 개수가 무조건 1 
	    if((i & (i - 1)) == 0){
                res[i] = 1;
                carry = i;
            }
            else{
	    	// i = carry + (i - carry)
		// 6 = 4 + 2
		// 7 = 4 + 3
		// 9 = 8 + 1
                res[i] = res[carry] + res[i - carry];   
            }            
        }
        
        return res;
    }
};
```

----------------------------------

### [ 1277. Count Square Submatrices with All Ones ](https://leetcode.com/problems/count-square-submatrices-with-all-ones/) - medium

- 문제

Given a m * n matrix of ones and zeros, return how many square submatrices have all ones.

- 제한사항
  - 1 <= arr.length <= 300
  - 1 <= arr[0].length <= 300
  - 0 <= arr[i][j] <= 1

- 입출력 예
  
```
Example 1:

Input: matrix =
[
  [0,1,1,1],
  [1,1,1,1],
  [0,1,1,1]
]
Output: 15
Explanation: 
There are 10 squares of side 1.
There are 4 squares of side 2.
There is  1 square of side 3.
Total number of squares = 10 + 4 + 1 = 15.

Example 2:

Input: matrix = 
[
  [1,0,1],
  [1,1,0],
  [1,1,0]
]
Output: 7
Explanation: 
There are 6 squares of side 1.  
There is 1 square of side 2. 
Total number of squares = 6 + 1 = 7.

```

- 풀이
  - DP

```C++
class Solution {
public:
    int countSquares(vector<vector<int>>& matrix) {
        int count = 0;
        int m = matrix.size();
        int n = matrix[0].size();
        vector<vector<int>> result = vector<vector<int>>(m, vector<int>(n, 0));
        
        for(auto i = 0 ; i < m ; ++i){
            for(auto j = 0 ; j < n ; ++j){
                // 가로, 세로 첫줄은 그대로 저장
                if(i == 0 || j == 0){
                    result[i][j] = matrix[i][j];
                }
                // 0인 값은 그대로 0을 저장
                else if(matrix[i][j] == 0){
                    result[i][j] = 0;
                }
                // 현재 index의 왼쪽, 위, 왼쪽 위 대각선, 이 세가지 값을 비교후 작은 값에 +1
                // +1 하느 이유는 크기가 1인 사각형을 포함해야 하므로
                else{
                    auto temp = min(matrix[i][j-1], result[i-1][j-1]);
                    result[i][j] = min(result[i-1][j], min(result[i][j-1], result[i-1][j-1])) + 1;
                }
                
                count += result[i][j];
            }
        }
        
        return count;
    }
};
```

----------------------------------

### [ 746. Min Cost Climbing Stairs ](https://leetcode.com/problems/min-cost-climbing-stairs/submissions/) - easy

- 문제

On a staircase, the i-th step has some non-negative cost cost[i] assigned (0 indexed).

Once you pay the cost, you can either climb one or two steps. You need to find minimum cost to reach the top of the floor, and you can either start from the step with index 0, or the step with index 1.

- 제한사항
  - cost will have a length in the range [2, 1000].
  - Every cost[i] will be an integer in the range [0, 999]

- 입출력 예
  
```
Example 1:

Input: cost = [10, 15, 20]
Output: 15
Explanation: Cheapest is start on cost[1], pay that cost and go to the top.

Example 2:

Input: cost = [1, 100, 1, 1, 1, 100, 1, 1, 100, 1]
Output: 6
Explanation: Cheapest is start on cost[0], and only step on 1s, skipping cost[3].

```

- 풀이
  - DP

```C++
class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        vector<int> result(cost.size(), 0);
        int len = cost.size();
        
        result[0] = cost[0];
        result[1] = cost[1];
        
        for(auto i = 2 ; i < len ; ++i){
            result[i] = min(cost[i] + result[i-1], cost[i] + result[i-2]);
        }
        
        return result[len-1] < result[len-2] ? result[len-1] : result[len-2];
    }
};
```

----------------------------------

### [ 303. Range Sum Query - Immutable ](https://leetcode.com/problems/range-sum-query-immutable/) - easy

- 문제

Given an integer array nums, find the sum of the elements between indices i and j (i ≤ j), inclusive.

- 제한사항
  - You may assume that the array does not change.
  - There are many calls to sumRange function.

- 입출력 예
  
```
Example 1:
Given nums = [-2, 0, 3, -5, 2, -1]

sumRange(0, 2) -> 1
sumRange(2, 5) -> -1
sumRange(0, 5) -> -3
```

- 풀이
  - sum

```C++
class NumArray {
private:
    const vector<int>& m_nums;
public:
    NumArray(vector<int>& nums) : m_nums(nums){}
    
    int sumRange(int i, int j) {
        int sum = 0;
        
        for(auto index = i ; index <= j ; ++index){
            sum += m_nums[index];
        }
        
        return sum;
    }
};
```
----------------------------------

### [ 290. Word Pattern ](https://leetcode.com/problems/word-pattern/) - easy

- 문제

Given a pattern and a string str, find if str follows the same pattern.

Here follow means a full match, such that there is a bijection between a letter in pattern and a non-empty word in str.

- 제한사항
  - You may assume pattern contains only lowercase letters, and str contains lowercase letters that may be separated by a single space


- 입출력 예
  
```
Example 1:
Input: pattern = "abba", str = "dog cat cat dog"
Output: true
```
```
Example 2:
Input:pattern = "abba", str = "dog cat cat fish"
Output: false
```
```
Example 3:
Input: pattern = "aaaa", str = "dog cat cat dog"
Output: false
```
```
Example 4:
Input: pattern = "abba", str = "dog dog dog dog"
Output: false
```

- 풀이
  - hash

```C++
class Solution {
public:
    bool wordPattern(string pattern, string str) {
        vector<string> strVec;
        string token;
        stringstream ss(str);
        
        while (getline(ss, token, ' ')) {
		    strVec.push_back(token);
	    }
        
        map<char, string> m;
        set<string> s;
        
        if(pattern.size() != strVec.size())
            return false;
        
        for(auto i = 0 ; i < pattern.size() ; ++i){
            if(m.find(pattern[i]) != m.end()){
                if(m[pattern[i]] != strVec[i])
                    return false;
            }
            else{
                m[pattern[i]] = strVec[i];
                s.insert(m[pattern[i]]);
            }
        }
        
        if(s.size() == m.size())
            return true;
        else
            return false;
    }
};
```

----------------------------------

### [ 283. Move Zeroes ](https://leetcode.com/problems/k-diff-pairs-in-an-array/) - easy

- 문제

Given an array nums, write a function to move all 0's to the end of it while maintaining the relative order of the non-zero elements.

- 제한사항
  - You must do this in-place without making a copy of the array.
  - Minimize the total number of operations.


- 입출력 예
  - Example 1:

```
Input: [0,1,0,3,12]
Output: [1,3,12,0,0]
```

- 풀이
  - array

```C++
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int numsSize = nums.size(), count = 0;
        for(int index = 0 ; index < numsSize - count;){
            if(nums[index] == 0){
                ++count;
                nums.push_back(0);
                nums.erase(nums.begin() + index);
            }
            else
                ++index;
        }
    }
};
```

----------------------------------

### [ K-diff Pairs in an Array ](https://leetcode.com/problems/k-diff-pairs-in-an-array/) - easy

- 문제

Given an array of integers and an integer k, you need to find the number of unique k-diff pairs in the array. Here a k-diff pair is defined as an integer pair (i, j), where i and j are both numbers in the array and their absolute difference is k. 

- 제한사항
  - The pairs (i, j) and (j, i) count as the same pair.
  - The length of the array won't exceed 10,000.
  - All the integers in the given input belong to the range: [-1e7, 1e7].

- 입출력 예
```
Example 1:
Input: [3, 1, 4, 1, 5], k = 2
Output: 2
Explanation: There are two 2-diff pairs in the array, (1, 3) and (3, 5).
Although we have two 1s in the input, we should only return the number of unique pairs.
```
```
Example 2:
Input:[1, 2, 3, 4, 5], k = 1
Output: 4
Explanation: There are four 1-diff pairs in the array, (1, 2), (2, 3), (3, 4) and (4, 5).
```
```
Example 3:
Input: [1, 3, 1, 5, 4], k = 0
Output: 1
Explanation: There is one 0-diff pair in the array, (1, 1).
```

- 풀이
  - map

```C++
class Solution {
public:
    int findPairs(vector<int>& nums, int k) {
        if (k < 0) 
            return 0;
        
        int count = 0;
        unordered_map<int,int> m;
        
        for(const auto& i : nums)
            ++m[i];
        
        for(const auto& i : m){
          if ((!k && i.second > 1) || (k && m.count(i.first + k))) 
              ++count;
        }
            
        return count;
    }
};
```
----------------------------------
