---
title: 第12章 剑指Offer
nav_order: 13
---

JZ3 数组中重复的数字  
 
知识点  ：数组  
描述  ：在一个长度为n的数组里的所有数字都在0到n-1的范围内。 数组中某些数字是重复的，但不知道有几个数字是重复的。也不知道每个数字重复几次。请找出数组中任意一个重复的数字。 例如，如果输入长度为7的数组[2,3,1,0,2,5,3]，那么对应的输出是2或者3。存在不合法的输入的话输出-1  

数据范围：  0<= n <= 100  
进阶：时间复杂度O(n)，空间复杂度O(n)  
示例1  
输入：  
[2,3,1,0,2,5,3]  

返回值：  
2

说明：
2或3都是对的

-----------------

![](../assets/images/chapter12/jz3-1.jpg)

------------------

```c
class Solution { // 排序查重方法
public:
    int duplicate(vector<int>& numbers) {
        // write code here
        if(numbers.empty()) return -1;
        sort(numbers.begin(), numbers.end(), [&](const auto& a,const auto& b){
            return a<b;
        });
        for(int i=1; i<numbers.size(); i++){
            if(numbers[i] == numbers[i-1]) return numbers[i];
        }
        return -1;
    }
};

class Solution { // 其他数据结构辅助set
public:
    int duplicate(vector<int>& numbers) {
        // write code here
        if(numbers.empty()) return -1;
        std::set<int> num_set;
        for(int i=0; i<numbers.size(); i++){
            if(num_set.find(numbers[i]) != num_set.end()){
                return numbers[i];
            }else{
                num_set.insert(numbers[i]);
            }
        }
        return -1;
    }
};

class Solution {// 哈希表方法
public:
    int duplicate(vector<int>& numbers) {
        // write code here
        if(numbers.empty()) return -1;
        int count[10001] = {0};
        for(const auto& num : numbers){
            count[num]++;
        }
        for(int i=0; i<sizeof(count)/sizeof(int); i++){
            if(count[i]>1) {
                return i;
            }
        }
        return -1;
    }
};

class Solution {// 一边排序，一边查重
public:
    int duplicate(vector<int>& numbers) {
        // write code here
        if(numbers.empty()) return -1;
        for(int i=0; i<numbers.size(); i++){
            while(numbers[i] != i){
                if (numbers[i] == numbers[numbers[i]])
                    return numbers[i];
                int tmp = numbers[i];
                numbers[i] = numbers[tmp];
                numbers[tmp] = tmp;
            }
        }
        return -1;
    }
};
```

---

题目:
在一个长度为n+1的数组里的所有数字都在1~n的范围内，所以数组中至少有一个数字是重复的。请找出数组中任意一个重复的数字，但是不能修改输入的数组。例如，如果输入长度为8的数组{2,3,5,4,3,2,6,7}，那么对应的输出是重复的数字2或者3。  

![](../assets/images/chapter12/jz3-2.jpg)


```
class Solution {// 二分法
public:
int duplicate(vector<int>& numbers) {
    // write code here
    if(numbers.empty()) return -1;
    int start=1; int end=numbers.size()-1;
    while(start<=end){
        int mid = start + ((end-start)>>1);
        int cnt = countRange(start, mid, numbers);
        
        if(start == end){
            if(cnt > 1) return start;
            else break;
        }

        if(cnt > (mid-start+1)) end = mid;
        else start = mid + 1;
    }
    return -1;
}
private:
// 以index划分区间，并统计
int countRange(int start, int end, std::vector<int>& numbers){
    if(numbers.empty()) return 0;
    int cnt = 0;
    for(int i=0; i<numbers.size(); i++){
        if(numbers[i]>=start && numbers[i]<=end){
            cnt++;
        }
    }
    return cnt;
}

};
```

---

知识点:数组  
描述  
在一个二维数组array中（每个一维数组的长度相同），每一行都按照从左到右递增的顺序排序，每一列都按照从上到下递增的顺序排序。请完成一个函数，输入这样的一个二维数组和一个整数，判断数组中是否含有该整数。  
```
[
[1,2,8,9],
[2,4,9,12],
[4,7,10,13],
[6,8,11,15]
]
```
给定 target = 7，返回 true。

给定 target = 3，返回 false。

数据范围：矩阵的长宽满足 $0≤n,m≤500$， 矩阵中的值满足 $0≤val≤10^9$
 
进阶：空间复杂度 O(1) ，时间复杂度O(n+m)  


示例1  
输入：    
7,\[[1,2,8,9],[2,4,9,12],[4,7,10,13],[6,8,11,15]]  

返回值：  
true
 
说明：  
存在7，返回true     


示例2  
输入：    
1,\[[2]]
 
返回值：  
false


示例3    
输入：  
3,\[[1,2,8,9],[2,4,9,12],[4,7,10,13],[6,8,11,15]]
 
返回值：  
false
 
说明：  
不存在3，返回false   


```c
class Solution {
public:
    bool findNumberIn2DArray(vector<vector<int>>& matrix, int target) {
        if(matrix.size() == 0) return false;
        bool res = false;
        int row = 0, col = matrix[0].size() - 1;
        while(row < matrix.size() && col >= 0) {
            if(target == matrix[row][col]) {
                res = true;
                break;
            }
            if(target < matrix[row][col]) {
                col --;
            } else {
                row ++;
            }
        }
        return res;
    }
};
```

---

请实现一个函数，把字符串 s 中的每个空格替换成"%20"。

 

示例 1：

输入：s = "We are happy."  
输出："We%20are%20happy."  
 

限制：

0 <= s 的长度 <= 10000

![](../assets/images/chapter12/jz5-1.jpg)

![](../assets/images/chapter12/jz5-2.jpg)


- [string 的一些函数参考](https://zh.cppreference.com/w/cpp/string/basic_string)

```c
class Solution {
public:
    string replaceSpace(string s) {
        if(s == "") return s;
        int len = 0, count_space = 0;
        while(s[len] != '\0') {
            if(s[len] == ' ') {
                count_space ++;
            }
            len ++;
        }
        // len ++;  注意这里不++ 就没有统计 '/0' 因此后面索引不用 -1
        int new_len = len + 2 * count_space;
        s.resize(new_len);
        int p1 = len, p2 = new_len;//索引不用 -1
        while(p1 >= 0) {
            if(s[p1] == ' ') {
                s[p2--] = '0';
                s[p2--] = '2';
                s[p2--] = '%';
            } else {
                s[p2--] = s[p1];
            }    
            p1 --;
        }
        return s;
    }
};
```

---

输入一个链表的头节点，从尾到头反过来返回每个节点的值（用数组返回）。

 

示例 1：

输入：head = [1,3,2]  
输出：[2,3,1]
 

限制：

0 <= 链表长度 <= 10000


![](../assets/images/chapter12/jz6-1.jpg)

```c
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
    vector<int> reversePrint(ListNode* head) {
        std::vector<int> res;
        if (head == nullptr) return res;

        std::stack<ListNode*> node_ptr_stack;
        ListNode* p = head;
        while( p != nullptr) {
            node_ptr_stack.push(p);
            p = p->next;
        }
        while(!node_ptr_stack.empty()) {
            res.push_back(node_ptr_stack.top()->val);
            node_ptr_stack.pop();
        }
        return res;
    }
};
```

---

输入某二叉树的前序遍历和中序遍历的结果，请构建该二叉树并返回其根节点。

假设输入的前序遍历和中序遍历的结果中都不含重复的数字。

 

示例 1:

![](../assets/images/chapter12/jz7-1.jpg)


Input: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]  
Output: [3,9,20,null,null,15,7]  


示例 2:  

Input: preorder = [-1], inorder = [-1]  
Output: [-1]  
 

限制：  

0 <= 节点个数 <= 5000  

 
![](../assets/images/chapter12/jz7-3.jpg)


- 自己实现方式 DFS
```c
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
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if(preorder.empty() || inorder.empty()) {
            return nullptr;
        }
        return build_tree_dfs(preorder, inorder);
    }

private:
    TreeNode* build_tree_dfs(vector<int>& preorder, vector<int>& inorder) {
        if(preorder.empty() || inorder.empty()) {
            return nullptr;
        }
        if (preorder.size() == 1 && inorder.size() == 1) {
            return new TreeNode(preorder[0]);
        }

        int root_val = preorder[0];
        std::vector<int> preorder_left, inorder_left, 
                         preorder_right, inorder_right;
        bool boundary_flag = false;
        int boundary_count = 0;
        for(const auto& val : inorder) {
            if(val == root_val) {
                boundary_flag = true;
                continue;
            }
            if(!boundary_flag) {
                inorder_left.push_back(val);
                boundary_count ++;
            }else if(boundary_flag){
                inorder_right.push_back(val);
            }
        }

        for(int i = 1; i < preorder.size(); i++) {
            if (i <= boundary_count) {
                preorder_left.push_back(preorder[i]);
            } else {
                preorder_right.push_back(preorder[i]);
            }
        }

        TreeNode* left = build_tree_dfs(preorder_left, inorder_left);
        TreeNode* right = build_tree_dfs(preorder_right, inorder_right);
        return new TreeNode(root_val, left, right);
    }

};
```
只需一个 new：

```c
class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if(preorder.empty() || inorder.empty()) {
            return nullptr;
        }
        return build_tree_dfs(preorder, inorder);
    }

private:
    TreeNode* build_tree_dfs(vector<int>& preorder, vector<int>& inorder) {
        if(preorder.empty() ) {
            return nullptr;
        }
        // if (preorder.size() == 1 && inorder.size() == 1) {
        //     return new TreeNode(preorder[0]);
        // }
        int root_val = preorder[0];
        TreeNode* root = new TreeNode(root_val);
        std::vector<int> preorder_left, inorder_left, 
                         preorder_right, inorder_right;
        bool boundary_flag = false;
        int boundary_count = 0;
        for(const auto& val : inorder) {
            if(val == root_val) {
                boundary_flag = true;
                continue;
            }
            if(!boundary_flag) {
                inorder_left.push_back(val);
                boundary_count ++;
            }else if(boundary_flag){
                inorder_right.push_back(val);
            }
        }

        for(int i = 1; i < preorder.size(); i++) {
            if (i <= boundary_count) {
                preorder_left.push_back(preorder[i]);
            } else {
                preorder_right.push_back(preorder[i]);
            }
        }

        root->left = build_tree_dfs(preorder_left, inorder_left);
        root->right = build_tree_dfs(preorder_right, inorder_right);
        return root;
    }

};
```


- 改进: 使用下标进行索引，减少内存消耗


![](../assets/images/chapter12/jz7-2.jpg)

```c
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
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if(preorder.empty() || inorder.empty()) {
            return nullptr;
        }
        return build_tree_dfs(preorder, 0, preorder.size()-1, inorder, 0, inorder.size()-1);
    }

private:
    TreeNode* build_tree_dfs(vector<int>& preorder, int preorder_start, int preorder_end,
                             vector<int>& inorder, int inorder_start, int inorder_end) {
        if(preorder_start > preorder_end) {
            return nullptr;
        }
       
        TreeNode* root = new TreeNode(preorder[preorder_start]);// 前序的第一个数是根节点
        int cnt = 0;                                            // 统计左子树元素个数
        for (int i = inorder_start; i <= inorder_end; i++) {    // 在后序遍中找到根节点
            if (inorder[i] == preorder[preorder_start]) {
            cnt = i - inorder_start;
            break;
            }
        }
        
        root->left = build_tree_dfs(preorder, preorder_start+1, preorder_start+cnt,
                                    inorder, inorder_start, inorder_start+cnt-1);
        root->right = build_tree_dfs(preorder, preorder_start+cnt+1, preorder_end,
                                     inorder, inorder_start+cnt+1, inorder_end);
        
        return root;
    }

};
```

---

描述  
给定一个二叉树其中的一个结点，请找出中序遍历顺序的下一个结点并且返回。注意，树中的结点不仅包含左右子结点，同时包含指向父结点的next指针。下图为一棵有9个节点的二叉树。树中从父节点指向子节点的指针用实线表示，从子节点指向父节点的用虚线表示  

![](../assets/images/chapter12/JZ8-1.png)
![](../assets/images/chapter12/jz8-3.jpg)  
示例:  
输入:{8,6,10,5,7,9,11},8  
返回:9  
解析:这个组装传入的子树根节点，其实就是整颗树，中序遍历{5,6,7,8,9,10,11}，根节点8的下一个节点就是9，应该返回{9,10,11}，后台只打印子树的下一个节点，所以只会打印9，如下图，其实都有指向左右孩子的指针，还有指向父节点的指针，下图没有画出来  

![](../assets/images/chapter12/JZ8-2.png)

数据范围：节点数满足 1≤n≤50 1≤n≤50  ，节点上的值满足 1≤val≤100 1≤val≤100 



要求：空间复杂度 O(1) O(1)  ，时间复杂度 O(n) O(n)   
输入描述：  输入分为2段，第一段是整体的二叉树，第二段是给定二叉树节点的值，后台会将这2个参数组装为一个二叉树局部的子树传入到函数GetNext里面，用户得到的输入只有一个子树根节点

返回值描述： 返回传入的子树根节点的下一个节点，后台会打印输出这个节点  


示例1  
输入：  {8,6,10,5,7,9,11},8  
返回值： 
9  


示例2  
输入：  {8,6,10,5,7,9,11},6  
返回值：  7  


示例3  
输入：  {1,2,#,#,3,#,4},4  
返回值： 1



示例4  
输入：  {5},5  
返回值： "null"



```c
/*
struct TreeLinkNode {
    int val;
    struct TreeLinkNode *left;
    struct TreeLinkNode *right;
    struct TreeLinkNode *next;
    TreeLinkNode(int x) :val(x), left(NULL), right(NULL), next(NULL) {
        
    }
};
*/
class Solution {
public:
    TreeLinkNode* GetNext(TreeLinkNode* pNode) {
        if(pNode == nullptr) return nullptr;
        
        // 1.有右子树
        if(pNode->right) {
            // right_child
            TreeLinkNode* next_node = pNode->right;
            while(next_node->left != nullptr) {
                next_node = next_node->left;
            }
            return next_node;
        }
        // 2.没有父节点
        if(!pNode->next) {
            return nullptr;
        }
        // 3.无右子树
        // 3.1.该节点为父节点的左子
        if(pNode->next->left == pNode) {
            return pNode->next;
        }
        
        // 3.2.该节点为父节点的右子
        if(pNode->next->right == pNode) {
            TreeLinkNode* next_node = pNode->next;
            while(next_node->next) {
                if(next_node == next_node->next->left) {
                    return next_node->next;
                }
                next_node = next_node->next;
            }
        }
        
        return nullptr;
    }
};
```

---

用两个栈实现一个队列。队列的声明如下，请实现它的两个函数 appendTail 和 deleteHead ，分别完成在队列尾部插入整数和在队列头部删除整数的功能。(若队列中没有元素，deleteHead 操作返回 -1 )  

 

示例 1：  
输入：  
["CQueue","appendTail","deleteHead","deleteHead"]  
[[],[3],[],[]]  
输出：[null,null,3,-1]  


示例 2：  
输入：  
["CQueue","deleteHead","appendTail","appendTail","deleteHead","deleteHead"]  
[[],[],[5],[2],[],[]]  
输出：[null,-1,null,null,5,2]  


![](../assets/images/chapter12/jz9-1.jpg)


```c
class CQueue {
public:
    CQueue() {

    }
    
    void appendTail(int value) {
        data_.push(value);
    }
    
    int deleteHead() {
        if (data_.empty()) {
            return -1;
        }
        while(!data_.empty()) {
            tmp_.push(data_.top());
            data_.pop();
        }
        int res = tmp_.top();
        tmp_.pop();

        while(!tmp_.empty()) {
            data_.push(tmp_.top());
            tmp_.pop();
        }
        return res;
    }
private:
    std::stack<int> data_;
    std::stack<int> tmp_;
};
```

---

求 1+2+...+n ，要求不能使用乘除法、for、while、if、else、switch、case等关键字及条件判断语句（A?B:C）。

 

示例 1：  
输入: n = 3  
输出: 6  


示例 2：  
输入: n = 9  
输出: 45  
 


```c
class Solution {
public:
    int sumNums(int n) {
        // return 0.5 * n * (n+1);

        // bool a[n][n+1];       // 数组size实现乘法
        // return sizeof(a)>>1;

        n > 1 && sumNums(n - 1); // 短路实现终止
        res_ += n;
        return res_;
    }

private:
 int res_ = 0;
};
```