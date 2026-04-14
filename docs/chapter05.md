---
title: 第05章 二叉树
nav_order: 6
---

- <font color = red>二叉树的相关题目，通常和 '递归与回溯' , '栈' 等相结合。</font>

-  **心得：DFS需要终止遍历时，函数就定义为 bool 型**


#  二叉树


树的大部分操作的平均运行时间为O(logN).


- root, parent, child, edge, leaf,  ancestor祖先， descendant后裔， proper ancestor真祖先， proper descendant真后裔
- path:n1->nkd的路径上边的条数，k-1.


对任意节点：

-  深度：该节点到root的路径长 （root的深为0）
-  高度：该节点到最远leaf的路径长（leaf 的高为0）
-  树的深度：最深leaf的深度
-  度Degree：节点拥有子树数，度为0 的节点称为叶节点leaf




每个节点不能多于两个儿子。$T_L$ 和 $T_R$ 均可能为空。

**二叉树性质：**

-  1.二叉树平均深度要比N小得多.平均深度为O(sqrt(N))
-  2.在二叉树的第 $i$ 层至多有 $2^{(i-1)}$ 个节点.（某层的节点数）
-  3.深度为 $k$ 的二叉树至多有 $(2^k)-1$ 个节点.（整个树的节点数）
-  4.对任何一颗二叉树 $T$ ，如果其终端节点数为 $n_0$ ,度为 2 的节点数为 $n_2$ ,则 $n_0 = n_2+1$.



**表达式树**

用于记录运算式子的二叉树.


- 表达式树的树叶leaf是操作数（0123456789），比如常量或变量，而其他节点称之为操作符（+-*/）.
- 中序遍历inorder traversal：左+节点+右. 的顺序遍历.-->中缀表达式
- 后序遍历postorder traversal: 左+右+节点. 的遍历顺序.-->后缀表达式
- 先序遍历preorder traversal：节点+右+左. 的遍历顺序.-->前缀表达式（不常用）
- 层序遍历：顾名思义，从根节点开始，每层从左到右依次遍历.

记忆：先中后表节点的位置，这样就好记多了！


注：  
数据结构与算法描述中，先序遍历为：节点+右+左  
大话数据结构中，先序遍历为：节点+左+右

---

路径总和 II  
Category	Difficulty	Likes	Dislikes  
algorithms	Medium (62.79%)	641	-  
Tags  
tree | depth-first-search  

Companies 
bloomberg  

给你二叉树的根节点 root 和一个整数目标和 targetSum ，找出所有 从根节点到叶子节点 路径总和等于给定目标和的路径。  

叶子节点 是指没有子节点的节点。  

 

示例 1：  
![](../assets/images/chapter05/113-1.png)

输入：root = [5,4,8,11,null,13,4,7,2,null,null,5,1], targetSum = 22  
输出：\[[5,4,11,2],[5,8,4,5]]  


示例 2：  
![](../assets/images/chapter05/113-2.png)

输入：root = [1,2,3], targetSum = 5  
输出：[]  


示例 3：  

输入：root = [1,2], targetSum = 0  
输出：[]
 

提示：

树中节点总数在范围 [0, 5000] 内  
-1000 <= Node.val <= 1000  
-1000 <= targetSum <= 1000  
Discussion | Solution  

-----------------------------------

- 虽然是二叉树的题目，用到的也是递归的思想


![](./../pic/113-3.png)

![](./../pic/113-4.png) 

![](./../pic/113-5.png)

![](./../pic/113-6.png)

![](./../pic/113-7.png)

![](./../pic/113-8.png)

![](./../pic/113-9.png)



---------------------------------

```c

/*
 * @lc app=leetcode.cn id=113 lang=cpp
 *
 * [113] 路径总和 II
 */

// @lc code=start
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
 //-----------------自己尝试：未通过-----------------------------
class Solution {
public:
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        std::vector<std::vector<int>> path;
        if(root == nullptr) return path;
        std::stack<int> path_stack;//用栈好像在复制的时候是浅拷贝
        int path_cost = 0;
        DFS(root, path_cost, path_stack, path, targetSum);
        return path;
    }


private:
    void DFS(TreeNode* root,// 节点
             int& path_cost,// 顾名思义
             std::stack<int>& path_stack,// 记录一条path
             std::vector<std::vector<int>>& path,// 总的path
             int& tar){

        path_cost += root->val;
        path_stack.push(root->val);
        if(root->left){
            DFS(root->left, path_cost, path_stack, path, tar);
        }
        if(root->right){
            DFS(root->right, path_cost, path_stack, path, tar);
        }

        if(root->left == nullptr && root->right == nullptr && path_cost == tar){
            std::vector<int> tmp;
            std::stack<int> backup_stack = path_stack;
            while(path_stack.empty()){
                tmp.insert(tmp.begin(), path_stack.top());
                path_stack.pop();
            }
            path.push_back(tmp);
            path_stack = backup_stack;
            return;
        }
        path_cost -= root->val;
        path_stack.pop();
    }
};
// @lc code=end

//-------------参考实现-------------------------

class Solution {
public:
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        std::vector<std::vector<int>> path;
        if(root == nullptr) return path;
        std::vector<int> path_stack;// 模拟栈的操作
        int path_cost = 0;
        DFS(root, path_cost, path_stack, path, targetSum);
        return path;
    }

private:
    void DFS(TreeNode* root,// 当前节点
             int& path_cost,// 顾名思义
             std::vector<int>& path_stack,// 记录一条path
             std::vector<std::vector<int>>& path,// 总的path
             int& tar){// 目标和
        if(!root) return;// 传入的是空指针，说明到底了！
        path_cost += root->val;
        path_stack.push_back(root->val);//--------前序------------
        if(root->left == nullptr && root->right == nullptr && path_cost == tar){
            path.push_back(path_stack);
        }

        if(root->left){
            DFS(root->left, path_cost, path_stack, path, tar);
        }
        if(root->right){
            DFS(root->right, path_cost, path_stack, path, tar);
        }

        path_cost -= root->val;// 回溯，恢复
        path_stack.pop_back();
    }
};


```

---

二叉树的最近公共祖先  
Category	Difficulty	Likes	Dislikes  
algorithms	Medium (68.32%)	1455	-  
Tags  
Companies  
给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。  

百度百科中最近公共祖先的定义为：“对于有根树 T 的两个节点 p、q，最近公共祖先表示为一个节点 x，满足 x 是 p、q 的祖先且 x 的深度尽可能大（一个节点也可以是它自己的祖先）。”  

 

示例 1：  
![](../assets/images/chapter05/236-1.png)

输入：root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1  
输出：3  
解释：节点 5 和节点 1 的最近公共祖先是节点 3 。 



示例 2：  
![](../assets/images/chapter05/236-2.png)

输入：root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4  
输出：5  
解释：节点 5 和节点 4 的最近公共祖先是节点 5 。因为根据定义最近公共祖先节点可以为节点本身。  



示例 3：

输入：root = [1,2], p = 1, q = 2  
输出：1  
 

提示：  

树中节点数目在范围 [2, 105] 内。  
-109 <= Node.val <= 109  
所有 Node.val 互不相同 。  
p != q  
p 和 q 均存在于给定的二叉树中。  
Discussion | Solution  

----------------------------------------------------------

![](../assets/images/chapter05/236-3.png)

![](../assets/images/chapter05/236-4.png)

![](../assets/images/chapter05/236-5.png)

![](../assets/images/chapter05/236-6.png)

![](../assets/images/chapter05/236-7.png)

![](../assets/images/chapter05/236-8.png)

![](../assets/images/chapter05/236-9.png)

![](../assets/images/chapter05/236-10.png)

![](../assets/images/chapter05/236-11.png)

![](../assets/images/chapter05/236-12.png)

![](../assets/images/chapter05/236-13.png)

![](../assets/images/chapter05/236-14.png)

![](../assets/images/chapter05/236-15.png)

![](../assets/images/chapter05/236-16.png)

![](../assets/images/chapter05/236-17.png)



- 1.找路径
- 2.找共同路径
- 3.找离根节点最远的共同节点
-----------------------------------------------------------

```c

/*
 * @lc app=leetcode.cn id=236 lang=cpp
 *
 * [236] 二叉树的最近公共祖先
 */

// @lc code=start
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
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(!root) return root;
        std::vector<TreeNode*> path_p;//存储节点路径，模拟栈
        std::vector<TreeNode*> path_q;
        DFS(root, p, path_p);
        DFS(root, q, path_q);

        std::stack<TreeNode*> res;
        int sz = path_p.size()<path_q.size() ? path_p.size() : path_q.size();
        for(int i=0; i<sz; i++){
            if(path_p[i] == path_q[i]){
                res.push(path_p[i]);
            }
        }
        
        return res.top();// 离根节点最远的那个节点
    }

private:
    bool DFS(TreeNode* root,
             TreeNode* target_node,
             std::vector<TreeNode*>& path){
        if(!root) return false;
        path.push_back(root);//前序
        if(target_node == root) return true;
        if(DFS(root->left, target_node, path)) return true;
        if(DFS(root->right, target_node, path)) return true;
        path.pop_back();// 回溯，恢复
        return false;
    }
};
// @lc code=end


```

---

二叉树展开为链表  
Category	Difficulty	Likes	Dislikes  
algorithms	Medium (72.69%)	1016	-  
Tags  
tree | depth-first-search  

Companies  
microsoft  

给你二叉树的根结点 root ，请你将它展开为一个单链表：  

展开后的单链表应该同样使用 TreeNode ，其中 right 子指针指向链表中下一个结点，而左子指针始终为 null 。  
展开后的单链表应该与二叉树 先序遍历 顺序相同。  
 

示例 1：  

![](../assets/images/chapter05/114-1.png)

输入：root = [1,2,5,3,4,null,6]  
输出：[1,null,2,null,3,null,4,null,5,null,6]  


示例 2：

输入：root = []  
输出：[]  
示例 3：  

输入：root = [0]  
输出：[0]  
 

提示：

树中结点数在范围 [0, 2000] 内  
-100 <= Node.val <= 100  
 

进阶：你可以使用原地算法（O(1) 额外空间）展开这棵树吗？  

Discussion | Solution  

-----------------------------


![](./../pic/114-2.png)

![](./../pic/114-3.png)

![](./../pic/114-4.png)

![](./../pic/114-5.png)

![](./../pic/114-6.png)

![](./../pic/114-7.png)

![](./../pic/114-8.png)

![](./../pic/114-9.png)

![](./../pic/114-10.png)

![](./../pic/114-11.png)

![](./../pic/114-12.png)

![](./../pic/114-13.png)

![](./../pic/114-14.png)

![](./../pic/114-15.png)

![](./../pic/114-16.png)



-------------------------------

```c
/*
 * @Date: 2021-12-29 21:46:30
 * @Author: bFeng
 */
/*
 * @lc app=leetcode.cn id=114 lang=cpp
 *
 * [114] 二叉树展开为链表
 */

// @lc code=start
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    void flatten(TreeNode* root) {
        if(!root) return;
        std::vector<TreeNode*> res;
        DFS(root, res);
        TreeNode* curr = root;
        for(int i=1; i<res.size(); i++){
            curr->right = res[i];//可以直接使用res[i-1]代替curr
            curr->left = nullptr;
            curr = curr->right;
        }
        curr->left = nullptr;
        curr->right = nullptr;
        return;
    }

private:
    // 前序遍历即可
    void DFS(TreeNode* root,
        std::vector<TreeNode*>& res){
        if(!root) return;
        res.push_back(root);
        DFS(root->left, res);
        DFS(root->right,res);
    }
};


//------------------原地实现是真的绕啊------------------
class Solution {
public:
    void flatten(TreeNode* root) {
        backtrack(root);
    }

private:
    TreeNode* backtrack(TreeNode* root){
        if(!root) return nullptr;
        if(!root->left && !root->right){// root 为叶子节点
            return root;// 返回 root
        }
        TreeNode* left = root->left;// 指向 root 的左子树
        TreeNode* right = root->right;// 指向 root 的右子树
        TreeNode* left_tail = nullptr;//
        TreeNode* right_tail = nullptr;//
        TreeNode* tail = nullptr;// 将指向root二叉树的最后一个节点
        root->left = nullptr;// 将 root 的做指针置空

        if(left){// 当 left 不为空时
            // 递归的将左子树转为链表， left_tail 指向左子树最后一个节点
            left_tail = backtrack(left);
            root->right = left;
            tail = left_tail;
        }

        if(right){
            right_tail = backtrack(right);
            if(left){
                left_tail->right = right;
            }
            tail = right_tail;
        }
        return tail;
    }
};
// @lc code=end


```

---

二叉树的右视图  
Category	Difficulty	Likes	Dislikes  
algorithms	Medium (65.27%)	592	-  
Tags  
tree | depth-first-search | breadth-first-search  

Companies  
给定一个二叉树的 根节点 root，想象自己站在它的右侧，按照从顶部到底部的顺序，返回从右侧所能看到的节点值。  

 

示例 1:  

![](../assets/images/chapter05/199-1.png)

输入: [1,2,3,null,5,null,4]  
输出: [1,3,4]  


示例 2:

输入: [1,null,3]  
输出: [1,3]  



示例 3:

输入: []  
输出: []  
 

提示:  

二叉树的节点个数的范围是 [0,100]  
-100 <= Node.val <= 100   
Discussion | Solution  


----------------------------------------------



![](../assets/images/chapter05/199-2.png)

![](../assets/images/chapter05/199-3.png)

![](../assets/images/chapter05/199-4.png)

![](../assets/images/chapter05/199-5.png)








---------------------------------------------

```c
/*
 * @Date: 2021-12-30 10:19:47
 * @Author: bFeng
 */
/*
 * @lc app=leetcode.cn id=199 lang=cpp
 *
 * [199] 二叉树的右视图
 */

// @lc code=start
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
// -----------------自己尝试： 使用队列实现BFS--------------
class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        std::vector<int> res;
        if(!root) return res;
        std::queue<TreeNode*> que;que.push(root);
        int num = 1;
        res.push_back(root->val);
        BFS(root, que, num, res);
        return res;
    }

private:
    void BFS(TreeNode* curr,// 除了外部调用，其余时刻当做tmp_ptr在使用
             std::queue<TreeNode*>& que,// 传入下一层的queue
             int& num,// 统计该层的节点数传入下一层
             std::vector<int>& res){
        if(!curr) return;
        // if(!curr->left && !curr->right) return;
        // if(que.empty() && num == 0){//根节点处理
        //     que.push(curr);
        //     num += 1;
        //     res.push_back(curr->val);
        // }
        if(que.empty() && num == 0) return;
        while(num--){
            curr = que.front();
            if(curr->left){
                que.push(curr->left);
            }
            if(curr->right){
                que.push(curr->right);
            }
            que.pop();
        }
        num = que.size();
        if(!que.empty()){
            curr = que.back();// 最后入队列的节点，就是最右边的节点
            res.push_back(curr->val);
        }
        BFS(curr, que, num, res);
    }

};
// @lc code=end


```