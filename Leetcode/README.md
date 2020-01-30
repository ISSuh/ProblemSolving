# 리츠코드 문제풀이

## 2020

----------------------------------

### [ 589. N-ary Tree Preorder Traversal ](https://leetcode.com/problems/n-ary-tree-preorder-traversal/) - easy

#### 문제

Given an n-ary tree, return the preorder traversal of its nodes' values.

Nary-Tree input serialization is represented in their level order traversal, each group of children is separated by the null value (See examples).

#### 제한사항
  - The height of the n-ary tree is less than or equal to 1000
  - The total number of nodes is between [0, 10^4]

#### 입출력 예

![example](https://assets.leetcode.com/uploads/2018/10/12/narytreeexample.png)

```
Input: root = [1,null,3,2,4,null,5,6]
Output: [1,3,5,6,2,4]
```

![example](https://assets.leetcode.com/uploads/2019/11/08/sample_4_964.png)

```
Input: root = [1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14]
Output: [1,2,3,6,7,11,14,4,8,12,5,9,13,10]
```

#### 풀이
  - Tree

```C++
/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/
class Solution {
public:
    vector<int> preorder(Node* root) {
        if(root == nullptr)
            return {};
        
        vector<int> item;
        
	// 현재 val 추가
	// 재귀로 Tree PreOrder 구현
        item.push_back(root->val);
        for(auto i = 0 ; i < root->children.size() ; ++i){
            auto temp = preorder(root->children[i]);
	    
	    // 재귀적으로 PreOrder로 조회한 자식노드들을 현재 vector에 뒤에 붙임
            item.insert(item.end(), temp.begin(), temp.end());
        }
        
        return item;
    }
};
```

----------------------------------

### [ 1207. Unique Number of Occurrences ](https://leetcode.com/problems/unique-number-of-occurrences/) - easy

#### 문제

Given an array of integers arr, write a function that returns true if and only if the number of occurrences of each value in the array is unique.

#### 제한사항
  - 1 <= arr.length <= 1000
  - -1000 <= arr[i] <= 1000


#### 입출력 예

```
Example 1:
Input: arr = [1,2,2,1,1,3]
Output: true
Explanation: The value 1 has 3 occurrences, 2 has 2 and 3 has 1. No two values have the same number of occurrences.

Example 2:
Input: arr = [1,2]
Output: false

Example 3:
Input: arr = [-3,0,1,-3,1,1,1,-3,10,0]
Output: true

```

#### 풀이
  - Hash

```C++
class Solution {
public:
    bool uniqueOccurrences(vector<int>& arr) {
        map<int, int> m;
        set<int> s;
        
        for(auto& i : arr){
            ++m[i];
        }
        
        for(auto i = m.begin() ; i != m.end() ; ++i){
            s.insert(i->second);
        }
                
        return s.size() == m.size();
    }
};
```

----------------------------------

### [ 289. Game of Life ](https://leetcode.com/problems/game-of-life/) - medium

#### 문제

According to the Wikipedia's article: "The Game of Life, also known simply as Life, is a cellular automaton devised by the British mathematician John Horton Conway in 1970."

Given a board with m by n cells, each cell has an initial state live (1) or dead (0). Each cell interacts with its eight neighbors (horizontal, vertical, diagonal) using the following four rules (taken from the above Wikipedia article):

    1. Any live cell with fewer than two live neighbors dies, as if caused by under-population.
    2. Any live cell with two or three live neighbors lives on to the next generation.
    3. Any live cell with more than three live neighbors dies, as if by over-population..
    4. Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.

Write a function to compute the next state (after one update) of the board given its current state. The next state is created by applying the above rules simultaneously to every cell in the current state, where births and deaths occur simultaneously.

#### 제한사항

#### 입출력 예

```
Input: 
[
  [0,1,0],
  [0,0,1],
  [1,1,1],
  [0,0,0]
]
Output: 
[
  [0,0,0],
  [1,0,1],
  [0,1,1],
  [0,1,0]
]
```

#### 풀이
  - Array, Brute Force

```C++
class Solution {
public:
    void gameOfLife(vector<vector<int>>& board) {
        auto newBoard = board;
        int row = board.size();
        int col = board[0].size();
        
        for(auto i = 0 ; i < row ; ++i){
            for(auto j = 0 ; j < col ; ++j){
                
                // 현재 cell의 주변 이웃의 생존 및 죽은 cell 수 검사
                int liveCount = 0, deadCount = 0;
                for(auto m = -1 ; m < 2 ; ++m){
                    for(auto n = -1 ; n < 2 ; ++n){
                        if(m == 0 && n == 0)
                            continue;
                        if(i + m < 0 || i + m >= row)
                            continue;
                        if(j + n < 0 || j + n >= col)
                            continue;
                        
                        if(board[i + m][j + n])
                            ++liveCount;
                        else
                            ++deadCount;
                    }
                }
                
                // 현재 cell이 생존했을때,
                if(board[i][j]){
                    // 1번 조건
                    if(liveCount < 2)
                        newBoard[i][j] = 0;
                    // 2번 조건
                    else if(2 <= liveCount && liveCount <= 3)
                        newBoard[i][j] = 1;
                    // 3번 조건
                    else
                        newBoard[i][j] = 0;                        
                }
                // 현재 cell이 죽은상태일때,
                else{
                    // 4번 조건
                    if(liveCount == 3)
                        newBoard[i][j] = 1;
                }
            }
        }
        
        swap(newBoard, board);
    }
};
```

----------------------------------

### [ 230. Kth Smallest Element in a BST ](https://leetcode.com/problems/kth-smallest-element-in-a-bst/) - medium

#### 문제

Given a binary search tree, write a function kthSmallest to find the kth smallest element in it.

#### 제한사항
  - You may assume k is always valid, 1 ≤ k ≤ BST's total elements.

#### 입출력 예

```
Example 1:
Input: root = [3,1,4,null,2], k = 1
   3
  / \
 1   4
  \
   2
Output: 1

Example 2:
Input: root = [5,3,6,2,4,null,null,1], k = 3
       5
      / \
     3   6
    / \
   2   4
  /
 1
Output: 3

```

#### 풀이
  - BFS

```C++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
        set<int> s;
        queue<TreeNode*> q;
        q.push(root);
        
        // BFS로 전체 노드의 val 값을 저장
        while(!q.empty()){
            auto node = q.front();
            q.pop();
            
            s.insert(node->val);
            
            if(node->left)
                q.push(node->left);
            
            if(node->right)
                q.push(node->right);
        }
        
        // k번째 작은수 검색
        auto answer = s.begin();
        for(auto i = 0 ; i < k - 1 ; ++i){
            ++answer;
        }
        
        return *answer;
    }
};
```

----------------------------------

### [ 215. Kth Largest Element in an Array ](https://leetcode.com/problems/kth-largest-element-in-an-array/) - medium

#### 문제

Find the kth largest element in an unsorted array. Note that it is the kth largest element in the sorted order, not the kth distinct element.

#### 제한사항
  - You may assume k is always valid, 1 ≤ k ≤ array's length.

#### 입출력 예

```
Example 1:
Input: [3,2,1,5,6,4] and k = 2
Output: 5

Example 2:
Input: [3,2,3,1,2,4,5,5,6] and k = 4
Output: 4
```

#### 풀이
  - Divide and Conquer, Heap, Sort

```C++
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
       
        sort(nums.begin(), nums.end(), greater<int>());
        
        return nums[k - 1];
    }
};
```

----------------------------------

### [ 169. Majority Element ](https://leetcode.com/problems/majority-element/) - easy

#### 문제

Given an array of size n, find the majority element. The majority element is the element that appears more than ⌊ n/2 ⌋ times.

You may assume that the array is non-empty and the majority element always exist in the array.

#### 제한사항

#### 입출력 예

```
Example 1:
Input: [3,2,3]
Output: 3

Example 2:
Input: [2,2,1,1,1,2,2]
Output: 2
```

#### 풀이
  - Divide and Conquer

```C++
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int majorityCount = nums.size() / 2;
        map<int, int> m;
        
        for(auto& i : nums)
            ++m[i];
        
        for(auto& i : m){
            if(i.second > majorityCount)
                return i.first;
        }

        return 0;
    }
};
```

----------------------------------

### [ 3. Longest Substring Without Repeating Characters ](https://leetcode.com/problems/longest-substring-without-repeating-characters/) - medium

- 문제

Given a string, find the length of the longest substring without repeating characters.

- 제한사항

- 입출력 예

```
Example 1:
Input: "abcabcbb"
Output: 3 
Explanation: The answer is "abc", with the length of 3. 

Example 2:
Input: "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.

Example 3:
Input: "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3. 
             Note that the answer must be a substring, "pwke" is a subsequence and not a substring.
```

- 풀이
  - String, Brute Force, Hash

```C++
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        if(s.size() == 1)
            return 1;
        
        set<char> sub;
        string subStr;
        
        // 문자열의 모든 경우를 검사하여 최대 길이를 검색
        for(auto i = 0 ; i < s.size(); ++i){
            for(auto j = i ; j < s.size() ; ++j){
                // Set에 현재 문자가 없으면 추가
                if(sub.find(s[j]) == sub.end()){
                    sub.insert(s[j]);
                }
                // Set에 현재 문자가 있으면
                // 현재까지의 문자열과 이전의 문자열과 길이를 비교하여 문자열 저장
                else{
                    string temp;
                    
                    for(auto& i : sub)
                        temp.push_back(i);
                    
                    if(subStr.size() < temp.size())
                        subStr = temp;
                    
                    sub.clear();

                    break;
                }
            }
        }
             
        return subStr.size();
    }
};
```

----------------------------------

### [ 279. Perfect Squares ](https://leetcode.com/problems/perfect-squares/) - medium

- 문제

Given a positive integer n, find the least number of perfect square numbers (for example, 1, 4, 9, 16, ...) which sum to n.

- 제한사항

- 입출력 예

```
Example 1:
Input: n = 12
Output: 3 
Explanation: 12 = 4 + 4 + 4.

Example 2:
Input: n = 13
Output: 2
Explanation: 13 = 4 + 9.
```

- 풀이
  - DP

```C++
class Solution {
public:
    int numSquares(int n) {
        int digit = 1;
        vector<int> item(n+1, 1);
        
        item[0] = 0;
        
        // 1...n 까지 제곱수 끼리의 합을 만드는 방법은
        // item[n] = item[n - sqrt(i)] + 1 이며,
        // 가장 수가 적게 만들어야 하므로 i를 1부터 최대 제곱근까지 검사
        for(auto i = 1 ; i <= n ; ++i){
            
            // 현재 i까지의 최대 제곱근 검사
            int sr = sqrt(i);
            if((sr - floor(sr)) == 0){
                digit = sr * sr;
            }
            
            // 1부터 현재 i까지의 최대 제곱근까지,
            // 제곱끼리의 합이 i를 만족하며 갯수가 최소인 갯수를 검사
            int minVal = INT_MAX;
            for(auto j = 1 ; (j*j) <= digit ; ++j){
                int val = item[i] + item[i - (j*j)]; 
                minVal = min(minVal, val);
            }
            
            // 찾은 최소값을 현재 item[i] 에 저장
            item[i] = minVal;
        }
        
        return item[n];
    }
};
```

----------------------------------

### [ 62. Unique Paths ](https://leetcode.com/problems/unique-paths/) - medium

- 문제

A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).

The robot can only move either down or right at any point in time. The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).

How many possible unique paths are there?

![example](https://assets.leetcode.com/uploads/2018/10/22/robot_maze.png)

Above is a 7 x 3 grid. How many possible unique paths are there?

- 제한사항
	- m and n will be at most 100.

- 입출력 예

```
Example 1:
Input: m = 3, n = 2
Output: 3
Explanation:
From the top-left corner, there are a total of 3 ways to reach the bottom-right corner:
1. Right -> Right -> Down
2. Right -> Down -> Right
3. Down -> Right -> Right

Example 2:
Input: m = 7, n = 3
Output: 28
```

- 풀이
  - DP

```C++
class Solution {
public:
    int uniquePaths(int m, int n) {
        if(m == 1 || n == 1)
            return 1;
        
        vector<vector<int>> item(m, vector<int>(n, 1));
        
        for(auto i = 1 ; i < m ; ++i){
            for(auto j = 1 ; j < n ; ++j){
                item[i][j] = item[i-1][j] + item[i][j-1]; 
            }
        }
        
        return item[m-1][n-1];
    }
};
```

----------------------------------

### [ 1079. Letter Tile Possibilities ](https://leetcode.com/problems/letter-tile-possibilities/) - medium

- 문제

You have a set of tiles, where each tile has one letter tiles[i] printed on it.  Return the number of possible non-empty sequences of letters you can make.

- 제한사항
	- 1 <= tiles.length <= 7
	- tiles consists of uppercase English letters.

- 입출력 예

```
Example 1:

Input: "AAB"
Output: 8
Explanation: The possible sequences are "A", "B", "AA", "AB", "BA", "AAB", "ABA", "BAA".

Example 2:

Input: "AAABBC"
Output: 188
```

- 풀이
  - Recursive, BackTracking

```C++
class Solution {
public:
    void backTracking(set<string>& item, string& tiles, string& subStr, vector<bool>& check){
        if(subStr.size() == tiles.size()){
            return;
        }
        
        // 문자를 하나씩 추가하며 전체 경우를 찾아봄
        for(auto i = 0 ; i < tiles.size() ; ++i){
            // 현재 문자를 이미 추가했는지 체크
            if(check[i]){
                subStr.push_back(tiles[i]);
                
                // 추가한 문자가 이미 set에 있다면,
                // 이후 모든 조합은 이미 있게 되는 것이므로 탐색 중지
                if(item.find(subStr) != item.end()){
                    subStr.pop_back();
                    continue;
                }
                
                check[i] = false;
                
                item.insert(subStr);
                backTracking(item, tiles, subStr, check);
                
                subStr.pop_back();
                check[i] = true;
            }
        }
    }
    
    int numTilePossibilities(string tiles) {
        set<string> item;
        vector<bool> check(tiles.size(), true);
        string temp;
        
        backTracking(item, tiles, temp, check);
        
        return item.size();
    }
};
```

----------------------------------

### [ 60. Permutation Sequence ](https://leetcode.com/problems/permutation-sequence/) - medium

- 문제

The set [1,2,3,...,n] contains a total of n! unique permutations.

By listing and labeling all of the permutations in order, we get the following sequence for n = 3:

	1. "123"
	2. "132"
	3. "213"
	4. "231"
	5. "312"
	7. "321"
Given n and k, return the kth permutation sequence.

- 제한사항
	- Given n will be between 1 and 9 inclusive.
	- Given k will be between 1 and n! inclusive.

- 입출력 예

```
Example 1:

Input: n = 3, k = 3
Output: "213"

Example 2:

Input: n = 4, k = 9
Output: "2314"
```

- 풀이
  - Recursive, BackTracking

```C++
class Solution {
public:
    int count = 0;
    bool backTracking(string& cur, int n, int k, vector<bool>& check){
        // 현재 문자열 크기가 n이면 리턴이며,
        // count가 k가 되도록 순번을 증가시킴
        // true로 리턴하여 답을 찾음을 알림
        if(cur.size() == n){
            ++count;

            if(count == k)
                return true;
        
            return false;
        }
        
        // 현재 check가 true인 것만 다음 탐색 시작
        // 중간에 재귀로 true를 리턴받으면 답을 찾았다는 것이니
        // 이후 계속해서 탐색할 필요가 없음
        for(auto i = 1 ; i <= n ; ++i){
            if(check[i]){
                check[i] = false;
                cur.push_back(i + '0');

                if(backTracking(cur, n, k, check))
                    return true;
                
                check[i] = true;
                cur.pop_back();
            }
        }
        
        return false;
    }
    
    string getPermutation(int n, int k) {
        string answer;
        vector<bool> check(n+1, true);

        backTracking(answer, n, k, check);
        
        return answer;
    }
};
```

----------------------------------

### [ 784. Letter Case Permutation ](https://leetcode.com/problems/letter-case-permutation/) - easy

- 문제

Given a string S, we can transform every letter individually to be lowercase or uppercase to create another string.  Return a list of all possible strings we could create.

- 제한사항
	- S will be a string with length between 1 and 12.
	- S will consist only of letters or digits.

- 입출력 예

```
Examples:
Input: S = "a1b2"
Output: ["a1b2", "a1B2", "A1b2", "A1B2"]

Input: S = "3z4"
Output: ["3z4", "3Z4"]

Input: S = "12345"
Output: ["12345"]
```

- 풀이
  - Recursive, BackTracking

```C++
class Solution {
public:
    void backTracking(vector<string>& ans, string& s, string& curS, int curIndex){
        // index가 문자열만큼 커지면 리턴
        if(curIndex == s.size()){
            ans.push_back(curS);
            return;
        }
        
        // 다음 인덱스
        int nextIndex = curIndex + 1;
                
        // 문자열의 문자중 숫자면 현재까지 문자열에 그대로 저장
        if('0' <= s[curIndex] && s[curIndex] <= '9'){            
            curS.push_back(s[curIndex]);
            backTracking(ans, s, curS, nextIndex);
        }
        else{
            // 현재까지의 문자열에 현재 문자 그대로인 문자조합을 위해
            // 문자 그대로 저장
            string str = curS;
            str.push_back(s[curIndex]);
            backTracking(ans, s, str, nextIndex);
            
            // 현재 문자가 소문자일때 대문자로 바꿔 현재까지의 문자열에 저장
            if('a' <= s[curIndex] && s[curIndex] <= 'z'){
                char upper = toupper(s[curIndex]);
                curS.push_back(upper);
                backTracking(ans, s, curS, nextIndex);
            }
            // 현재 문자가 대문자일때 소문자로 바꿔 현재까지의 문자열에 저장
            else{
                char lower = tolower(s[curIndex]);
                curS.push_back(lower);
                backTracking(ans, s, curS, nextIndex);
            }
            
        }
    }
    
    vector<string> letterCasePermutation(string S) {
        vector<string> answer;
        string temp = "";
        backTracking(answer, S, temp, 0);
        return answer;
    }
};
```

----------------------------------

### [ 39. Combination Sum ](https://leetcode.com/problems/combination-sum/) - medium

- 문제

Given a set of candidate numbers (candidates) (without duplicates) and a target number (target), find all unique combinations in candidates where the candidate numbers sums to target.

The same repeated number may be chosen from candidates unlimited number of times.

- 제한사항
	- All numbers (including target) will be positive integers.
    - The solution set must not contain duplicate combinations.

- 입출력 예

```
Input: candidates = [2,3,6,7], target = 7,
A solution set is:
[
  [7],
  [2,2,3]
]
```

```
Input: candidates = [2,3,5], target = 8,
A solution set is:
[
  [2,2,2,2],
  [2,3,3],
  [3,5]
]
```

- 풀이
  - Recursive, BackTracking

```C++
class Solution {
public:
    void backTracking(vector<vector<int>>& ans, vector<int>& candidates, vector<int>& curItem, int target, int cur, int begin){
        // 현재 값이 target과 같으면 리턴 
        if(cur == target){
            ans.push_back(curItem);
            return;
        }
        
        // 같은 내용이 반복되지 않도록 candidates의 index를 0 부터 candidates.size() 까지 
        // candidates의 index를 매개변수로 하여 중복 방지
        for(auto i = begin ; i < candidates.size() ; ++i){
            // 현재 값 + candidates[i] 이 target보다 작거나 같아야 해당 candidates[i]를 추가
            // 재귀로 BackTracking 수행후, pop을 하여 중복되는 원소 제거
            if(candidates[i] + cur <= target){
                curItem.push_back(candidates[i]);
                backTracking(ans, candidates, curItem, target, cur + candidates[i], i);
                curItem.pop_back();
            }
        }
    }
    
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> answer;
        vector<int> item;
        
        backTracking(answer, candidates, item, target, 0, 0);
        
        return answer;
    }
};
```

----------------------------------

### [ 78. Subsets ](https://leetcode.com/problems/subsets/) - medium

- 문제

Given a set of distinct integers, nums, return all possible subsets (the power set).

Note: The solution set must not contain duplicate subsets.

- 제한사항

- 입출력 예

```
Input: nums = [1,2,3]
Output:
[
  [3],
  [1],
  [2],
  [1,2,3],
  [1,3],
  [2,3],
  [1,2],
  []
]
```

- 풀이
  - Recursive

```C++
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> answer;
        int max = 1 << (nums.size());
        
        for(auto i = 0 ; i < max ; ++i){
            vector<int> sub;
            for(auto j = 0 ; j < nums.size() ; ++j){
                if(i & (1 << j)) 
                    sub.push_back(nums[j]);
            }
            answer.push_back(sub);
        }
        
        return answer;
    }
};
```

----------------------------------

### [ 94. Binary Tree Inorder Traversal ](https://leetcode.com/problems/binary-tree-inorder-traversal/) - medium

- 문제

Given a binary tree, return the inorder traversal of its nodes' values.
Example:

```
Input: [1,null,2,3]
   1
    \
     2
    /
   3

Output: [1,3,2]
```

- 제한사항

- 입출력 예

- 풀이
  - Recursive

```C++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    // PreOrder : root -> left -> right
    void preOrder(vector<int>& answer, TreeNode* node){
        if(node == nullptr)
            return;
        
        answer.push_back(node->val);
        preOrder(answer, node->left);
        preOrder(answer, node->right);
    }
    
    // InOrder : left -> root -> right
    void inOrder(vector<int>& answer, TreeNode* node){
        if(node == nullptr)
            return;
        
        inOrder(answer, node->left);
        answer.push_back(node->val);
        inOrder(answer, node->right);
    }
    
    // PostOrder : left -> right -> root
    void postOrder(vector<int>& answer, TreeNode* node){
        if(node == nullptr)
            return;
        
        postOrder(answer, node->left);
        postOrder(answer, node->right);
        answer.push_back(node->val);
    }
    
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> answer;
        inOrder(answer, root);
        return answer;
    }
};
```

----------------------------------

### [ 22. Generate Parentheses ](https://leetcode.com/problems/generate-parentheses/submissions/) - medium

- 문제

 Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.

For example, given n = 3, a solution set is: 
```
[
  "((()))",
  "(()())",
  "(())()",
  "()(())",
  "()()()"
]
```

- 제한사항

- 입출력 예

- 풀이
  - Back Tracking

```C++
class Solution {
public:
    // Back Tracking
    void OpenClose(vector<string>& ans, int n, string str, int open, int close){
        // '(', ')' 괄호가 2개가 한세트 이므로 2*n이 정답의 총 길이
        if(str.size() == 2 * n){
            ans.push_back(str);
            return;
        }
        
        // '(' 가 n개수보다 작으면 '(' 추가
        if(open < n)
            OpenClose(ans, n, str+'(', open+1, close);
        
        // ')' 가 현재 문자의 '(' 개수 보다 작으면 ')' 추가
        if(close < open)
            OpenClose(ans, n, str+')', open, close+1);
            
    }

    vector<string> generateParenthesis(int n) {
        vector<string> answer;
        OpenClose(answer, n, "",0 ,0);
        return answer;
    }    
};
```

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
