---
title: 第04章 递归与回溯
nav_order: 5
---

-  **心得：DFS需要终止遍历时，函数就定义为 bool 型**

---

子集  
Category	Difficulty	Likes	Dislikes  
algorithms	Medium (80.22%)	1428	-  
Tags  
Companies  
给你一个整数数组 nums ，数组中的元素 互不相同 。返回该数组所有可能的子集（幂集）。  

解集 不能 包含重复的子集。你可以按 任意顺序 返回解集。  

 

示例 1：  

输入：nums = [1,2,3]  
输出：\[[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]  

示例 2：

输入：nums = [0]  
输出：\[[],[0]]  
 

提示：  

1 <= nums.length <= 10  
-10 <= nums[i] <= 10  
nums 中的所有元素 互不相同  
Discussion | Solution  

------------------------------

![](../assets/images/chapter04/78-20.png)

- 循环算法： 例如集合 [1,2,3]，他的子集可以通过是否选 [1] ，是否选 [2]， 是否选 [3] 进行产生。三个不同元素组成的集合有 $2^3 = 8$  种可能。 $n$ 各元素则有 $2^n$ 个子集。


![](../assets/images/chapter04/78-15.png)

- 递归算法：和循环算法一样，只能生成 [1], [1,2], [1,2,3]


![](../assets/images/chapter04/78-17.png)

![](../assets/images/chapter04/78-18.png)

![](../assets/images/chapter04/78-19.png)

- 回溯算法：生成全部子集

---------------------------------------------

![](../assets/images/chapter04/78-1.png)

![](../assets/images/chapter04/78-2.png)

![](../assets/images/chapter04/78-3.png)

![](../assets/images/chapter04/78-4.png)

![](../assets/images/chapter04/78-5.png)

![](../assets/images/chapter04/78-6.png)

![](../assets/images/chapter04/78-7.png)

![](../assets/images/chapter04/78-8.png)

![](../assets/images/chapter04/78-9.png)

![](../assets/images/chapter04/78-10.png)

![](../assets/images/chapter04/78-11.png)

![](../assets/images/chapter04/78-12.png)

![](../assets/images/chapter04/78-13.png)

![](../assets/images/chapter04/78-14.png)

![](../assets/images/chapter04/78-15.png)

![](../assets/images/chapter04/78-16.png)

![](../assets/images/chapter04/78-17.png)

![](../assets/images/chapter04/78-18.png)

![](../assets/images/chapter04/78-19.png)

![](../assets/images/chapter04/78-20.png)

![](../assets/images/chapter04/78-21.png)

![](../assets/images/chapter04/78-22.png)

![](../assets/images/chapter04/78-23.png)

![](../assets/images/chapter04/78-24.png)

![](../assets/images/chapter04/78-25.png)

![](../assets/images/chapter04/78-26.png)

![](../assets/images/chapter04/78-27.png)

------------------------------------

```c
/*
 * @Date: 2021-12-28 11:50:53
 * @Author: bFeng
 */
/*
 * @lc app=leetcode.cn id=78 lang=cpp
 *
 * [78] 子集
 */
//  
// @lc code=start
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        std::vector<int> subset;
        std::vector<std::vector<int>> set;
        set.push_back(subset);// 空集情况
        backtrack(0, nums, subset, set);//回溯算法
        return set;
    }
private:
    void backtrack(int i,
                   std::vector<int>& nums,
                   std::vector<int>& subset,
                   std::vector<std::vector<int>>& set){
        if(i >= nums.size()) return;// 递归结束
        // 选择第 i 个元素的情况下，进行后面元素的递归选择
        subset.push_back(nums[i]);// 理解：这里是推入的一个数
        set.push_back(subset);
        backtrack(i+1, nums, subset, set);//递归
        // 第一次递归回溯到这里后，再次进行操作
        // 取消选择第 i 个元素，再次进行递归
        subset.pop_back(); // 从subset中剔除第 i 个元素的选择
        backtrack(i+1, nums, subset, set);
    }
};
// @lc code=end



```

---

括号生成  
括号生成  
Category	Difficulty	Likes	Dislikes  
algorithms	Medium (77.30%)	2241	-  
Tags  
string | backtracking  

Companies  
google | uber | zenefits  

数字 n 代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且 有效的 括号组合。

 

示例 1：

输入：n = 3  
输出：["((()))","(()())","(())()","()(())","()()()"]  


示例 2：  

输入：n = 1  
输出：["()"]  
 

提示：

1 <= n <= 8  
Discussion | Solution


---------------------------

![](../assets/images/chapter04/22-1.png)

![](../assets/images/chapter04/22-2.png)

![](../assets/images/chapter04/22-3.png)

![](../assets/images/chapter04/22-4.png)

![](../assets/images/chapter04/22-5.png)

![](../assets/images/chapter04/22-6.png)

![](../assets/images/chapter04/22-7.png)

---------------------------

```c
/*
 * @Date: 2021-12-28 16:15:31
 * @Author: bFeng
 */
/*
 * @lc app=leetcode.cn id=22 lang=cpp
 *
 * [22] 括号生成
 */

// @lc code=start
class Solution {
public:
    std::vector<std::string> generateParenthesis(int n) {
        std::vector<std::string> brackets;
        std::string sub_brackets;
        // Step 1 递归生成所有的括号组合
        backtrack(n, sub_brackets, brackets);
        std::vector<std::string> res;
        // Step 2 判断合法的括号组合
        for(int i=0; i<brackets.size(); i++){
            if(bracketsLegalJudge(brackets[i])){
                res.push_back(brackets[i]);
            }
        }
        return res;
    }

private:
    void backtrack(int n, 
                   std::string sub_brackets, 
                   std::vector<std::string>& brackets){
        if(sub_brackets.size() == 2*n){// 生成四个括号后就返回，相当于只取树的叶子节点
            brackets.push_back(sub_brackets);
            return;
        }
        backtrack(n, sub_brackets + "(", brackets);
        backtrack(n, sub_brackets + ")", brackets);
    }

    bool bracketsLegalJudge(std::string& bracket){
        std::stack<char> data;
        for(int i=0; i<bracket.size(); i++){
            if(bracket[i] == '('){
                data.push('(');
            }else if(bracket[i] == ')' && !data.empty()){
                data.pop();
            }else{
                return false;
            }
        }
        if(data.empty()) return true;
        return false;
    }
};
// @lc code=end
//----------------------------
// @lc code=start
// 直接在递归的时候进行筛选合法的组合
class Solution {
public:
    std::vector<std::string> generateParenthesis(int n) {
        std::vector<std::string> brackets;
        std::string sub_brackets;
        int left = 0; int right = 0;
        backtrack(n, left, right, sub_brackets, brackets);
        std::vector<std::string> res;
        return brackets;
    }

private:
    void backtrack(int n, int left, int right, 
                   std::string sub_brackets, 
                   std::vector<std::string>& brackets){
        if(sub_brackets.size() == 2*n){// 生成四个括号后就返回，相当于只取树的叶子节点
            brackets.push_back(sub_brackets);
            return;
        }
        if(left < n){// 保证左括号数量不大于2
            backtrack(n, left+1, right, sub_brackets + "(", brackets);
        }
        if(right < left){// 保证左括号 先于 右括号放置
            backtrack(n, left, right+1, sub_brackets + ")", brackets);
        }
    }
};

```

---

N 皇后  
Category	Difficulty	Likes	Dislikes  
algorithms	Hard (73.80%)	1134	-  
Tags
Companies  
n 皇后问题 研究的是如何将 n 个皇后放置在 n×n 的棋盘上，并且使皇后彼此之间不能相互攻击。

给你一个整数 n ，返回所有不同的 n 皇后问题 的解决方案。

每一种解法包含一个不同的 n 皇后问题 的棋子放置方案，该方案中 'Q' 和 '.' 分别代表了皇后和空位。

 

示例 1：


输入：n = 4  
输出：\[[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]]  
解释：如上图所示，4 皇后问题存在两个不同的解法。    


示例 2：

输入：n = 1  
输出：\[["Q"]]  
 

提示：  

1 <= n <= 9  
Discussion | Solution  

----------------------------------


![](../assets/images/chapter04/51-1.png)

![](../assets/images/chapter04/51-2.png)

![](../assets/images/chapter04/51-3.png)

![](../assets/images/chapter04/51-4.png)

![](../assets/images/chapter04/51-5.png)

![](../assets/images/chapter04/51-6.png)

![](../assets/images/chapter04/51-7.png)

![](../assets/images/chapter04/51-8.png)

![](../assets/images/chapter04/51-9.png)

![](../assets/images/chapter04/51-10.png)

![](../assets/images/chapter04/55-11.jpg)



----------------------------------

```c
/*
 * @Date: 2021-12-28 20:00:06
 * @Author: bFeng
 */
/*
 * @lc app=leetcode.cn id=51 lang=cpp
 *
 * [51] N 皇后
 */

// @lc code=start
class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        std::vector<string> queen; // 存储皇后的位置
        std::vector<std::vector<int>> attack; // attack标记皇后攻击的位置
        std::vector<std::vector<string>> res;// 最后的结果

        for(int i=0; i<n; i++){
            attack.push_back(std::vector<int>());//少定义一个变量
            for(int j=0; j<n; j++){
                attack[i].push_back(0);
            }
            queen.push_back("");
            queen[i].append(n,'.');
        }

        backtrack(0, n, queen, attack, res);
        return res;
    }

private:

    void put_queen(int x, int y, std::vector<std::vector<int>>& attack){
        static const int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};//八个方向
        static const int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};
        attack[x][y] = 1;
        int n = attack[0].size();
        for(int i=0; i<n; i++){
            for(int j=0; j<8; j++){
                int tmp_x = x + i*dx[j];
                int tmp_y = y + i*dy[j];
                if( 0<=tmp_x && tmp_x< n && 0<=tmp_y && tmp_y<n){//坐标在棋盘内
                    attack[tmp_x][tmp_y] = 1;
                } 
            }
        }
    }

    // 大的递归是按行进行
    void backtrack(int k, // 当前处理的行
                   int n, // N皇后中的N
                   std::vector<string>& queen, // 存储皇后的位置
                   std::vector<std::vector<int>>& attack, // attack标记皇后攻击的位置
                   std::vector<std::vector<string>>& res){ // 存储N皇后的全部解法
        if(k==n){// 找到一组解
            res.push_back(queen);
            return;
        }
        // 遍历 0 至 n-1 列，在循环中，回溯试探皇后可以放置的位置
        for(int i=0; i<n; i++){
            if(attack[k][i]==0){// 判断是否可以放皇后， 如果k行所有列都满了，backtrack执行完由栈递归返回
                std::vector<std::vector<int>> tmp = attack;// 备份attack数组
                queen[k][i] = 'Q'; // 标记皇后位置
                put_queen(k, i, attack);// 更新attack
                
                backtrack(k+1, n, queen, attack, res);// 递归试探 k+1 行的皇后放置位置
                // 回溯回来， 恢复状态
                attack = tmp;// 恢复attack数组
                queen[k][i] = '.';// 恢复queen数组
            }
        }
    }


};
// @lc code=end


```

---

火柴拼正方形  
Category	Difficulty	Likes	Dislikes  
algorithms	Medium (42.12%)	232	-  
Tags  
Companies  
还记得童话《卖火柴的小女孩》吗？现在，你知道小女孩有多少根火柴，请找出一种能使用所有火柴拼成一个正方形的方法。不能折断火柴，可以把火柴连接起来，并且每根火柴都要用到。  
  
输入为小女孩拥有火柴的数目，每根火柴用其长度表示。输出即为是否能用所有的火柴拼成正方形。  

示例 1:

输入: [1,1,2,2,2]  
输出: true

解释: 能拼成一个边长为2的正方形，每边两根火柴。  


示例 2:

输入: [3,3,3,3,4]  
输出: false



解释: 不能用所有火柴拼成一个正方形。  
注意:

给定的火柴长度和在 0 到 10^9之间。
火柴数组的长度不超过15。
Discussion | Solution

--------------------------------

![](../assets/images/chapter04/473-1.png)

![](../assets/images/chapter04/473-2.png)

![](../assets/images/chapter04/473-3.png)

![](../assets/images/chapter04/473-4.png)

![](../assets/images/chapter04/473-5.png)

![](../assets/images/chapter04/473-6.png)

![](../assets/images/chapter04/473-7.png)

![](../assets/images/chapter04/473-8.png)

![](../assets/images/chapter04/473-9.png)

![](../assets/images/chapter04/473-10.png)

![](../assets/images/chapter04/473-11.png)



-----------------------------

```c
/*
 * @Date: 2021-12-28 22:07:39
 * @Author: bFeng
 */
/*
 * @lc app=leetcode.cn id=473 lang=cpp
 *
 * [473] 火柴拼正方形
 */
//--------------自己尝试：未能通过所有测试，主要是回溯部分有问题-----------------
// @lc code=start
class Solution {
public:
    bool makesquare(std::vector<int>& matchsticks) {
        if(matchsticks.size() < 4) return false;
        int perimeter = 0;// 周长
        for(const auto& i : matchsticks){
            perimeter += i;
        }
        if( perimeter%4 != 0) return false;
        int side_len = perimeter/4;

        // 排序  大到小
        sort(matchsticks.begin(), matchsticks.end(), [&](const auto& a, const auto& b){
            return a > b;
        });
        bool res = true;
        std::vector<int> bucket = {side_len, side_len, side_len, side_len};

        backtrack(res, 0, matchsticks, bucket);

        return res;
    }

private:
    void backtrack(bool& res,
                   int i,// 第 i 根火柴
                   std::vector<int>& matchsticks,
                   std::vector<int>& bucket){
        if(i >= matchsticks.size()){
            for(const auto& i : bucket){
                res &= (~(bool)i);
            }
            return;
        }

        // std::vector<int> backup_mat = matchsticks;//备份
        std::vector<int> backup_buc = bucket;

        for(int j=0; j<bucket.size(); j++){// 遍历四个桶
            if(matchsticks[i] <= bucket[j]){//如果可以放进去
                // std::vector<int>::iterator to_del = matchsticks.begin() + i;
                // matchsticks.erase(to_del);
                bucket[j] -= matchsticks[i]; // 更新容量
                break;
            }
        }

        // 放下一根火柴
        backtrack(res, i+1, matchsticks, bucket);

        // matchsticks = backup_mat;
        bucket = backup_buc;
    }
};
// @lc code=end


//-------------参考实现：超时，应该是 bucket 复制耗时过多---------------------
/*
 * @Date: 2021-12-28 22:07:39
 * @Author: bFeng
 */
/*
 * @lc app=leetcode.cn id=473 lang=cpp
 *
 * [473] 火柴拼正方形
 */

// @lc code=start
class Solution {
public:
    bool makesquare(std::vector<int>& matchsticks) {
        if(matchsticks.size() < 4) return false;
        int perimeter = 0;// 周长
        for(const auto& i : matchsticks){
            perimeter += i;
        }
        if( perimeter%4 != 0) return false;
        int side_len = perimeter/4;

        // 排序  大到小
        sort(matchsticks.begin(), matchsticks.end(), [&](const auto& a, const auto& b){
            return a > b;
        });

        std::vector<int> bucket = {side_len, side_len, side_len, side_len};
        return backtrack(0, matchsticks, bucket);
    }


private:
    bool backtrack(int i,// 第 i 根火柴
                   std::vector<int>& matchsticks,
                   std::vector<int>& bucket){
        if(i >= matchsticks.size()){
            return true;
        }

        for(int j=0; j<bucket.size(); j++){// 遍历四个桶
            std::vector<int> backup_buc = bucket;
            if(matchsticks[i] > bucket[j]){//如果放不进去
                continue;
            }
            bucket[j] -= matchsticks[i]; // 如果可以放进去，更新容量
            if(backtrack(i+1, matchsticks, bucket)){//放下一根火柴
                return true;
            }
            bucket = backup_buc;//回溯，恢复
        }
        return false;
    }
};
// @lc code=end


//-------------------参考实现： 通过---------------------------
/*
 * @Date: 2021-12-28 22:07:39
 * @Author: bFeng
 */
/*
 * @lc app=leetcode.cn id=473 lang=cpp
 *
 * [473] 火柴拼正方形
 */

// @lc code=start
class Solution {
public:
    bool makesquare(std::vector<int>& matchsticks) {
        if(matchsticks.size() < 4) return false;
        int perimeter = 0;// 周长
        for(const auto& i : matchsticks){
            perimeter += i;
        }
        if( perimeter%4 != 0) return false;
        int side_len = perimeter/4;

        // 排序  大到小
        sort(matchsticks.begin(), matchsticks.end(), [&](const auto& a, const auto& b){
            return a > b;
        });

        int bucket[] = {side_len, side_len, side_len, side_len};
        return backtrack(0, matchsticks, bucket);
    }



private:
    bool backtrack(int i,// 第 i 根火柴
                   std::vector<int>& matchsticks,
                   int bucket[]){// 会被退化为指针，深拷贝
        if(i >= matchsticks.size()){
            return true;
        }

        for(int j=0; j<4; j++){// 遍历四个桶
            if(matchsticks[i] > bucket[j]){//如果放不进去
                continue;
            }
            bucket[j] -= matchsticks[i]; // 如果可以放进去，更新容量
            if(backtrack(i+1, matchsticks, bucket)){//放下一根火柴
                return true;
            }
            bucket[j] += matchsticks[i]; // 回溯，恢复
        }
        return false;
    }
};
// @lc code=end

```