---
title: 第09章 动态规划
nav_order: 10
---

打家劫舍  
Category	Difficulty	Likes	Dislikes  
algorithms	Medium (52.04%)	1813	-  
Tags  
dynamic-programming  

Companies  
airbnb | linkedin  

你是一个专业的小偷，计划偷窃沿街的房屋。每间房内都藏有一定的现金，影响你偷窃的唯一制约因素就是相邻的房屋装有相互连通的防盗系统，如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警。  

给定一个代表每个房屋存放金额的非负整数数组，计算你 不触动警报装置的情况下 ，一夜之内能够偷窃到的最高金额。  

 

示例 1：  
输入：[1,2,3,1]  
输出：4  
解释：偷窃 1 号房屋 (金额 = 1) ，然后偷窃 3 号房屋 (金额 = 3)。  
     偷窃到的最高金额 = 1 + 3 = 4 。  


示例 2：  
输入：[2,7,9,3,1]  
输出：12  
解释：偷窃 1 号房屋 (金额 = 2), 偷窃 3 号房屋 (金额 = 9)，接着偷窃 5 号房屋 (金额 = 1)。  
     偷窃到的最高金额 = 2 + 9 + 1 = 12 。  
 

提示：  

1 <= nums.length <= 100  
0 <= nums[i] <= 400  
Discussion | Solution  

------------------------------------

![](../assets/images/chapter09/198-1.png)

![](../assets/images/chapter09/198-2.png)

![](../assets/images/chapter09/198-3.png)

![](../assets/images/chapter09/198-4.png)

![](../assets/images/chapter09/198-5.png)

![](../assets/images/chapter09/198-6.png)

![](../assets/images/chapter09/198-7.png)

![](../assets/images/chapter09/198-8.png)

![](../assets/images/chapter09/198-9.png)

![](../assets/images/chapter09/198-10.png)

![](../assets/images/chapter09/198-11.png)

![](../assets/images/chapter09/198-12.png)

![](../assets/images/chapter09/198-13.png)

![](../assets/images/chapter09/198-14.png)

![](../assets/images/chapter09/198-15.png)

![](../assets/images/chapter09/198-16.png)

![](../assets/images/chapter09/198-17.png)

![](../assets/images/chapter09/198-18.png)

![](../assets/images/chapter09/198-19.png)

![](../assets/images/chapter09/198-20.png)

![](../assets/images/chapter09/198-21.png)

![](../assets/images/chapter09/198-22.png)

![](../assets/images/chapter09/198-23.png)

![](../assets/images/chapter09/198-24.png)

![](../assets/images/chapter09/198-25.png)

![](../assets/images/chapter09/198-26.png)

![](../assets/images/chapter09/198-27.png)


------------------------------------

```c
- 动态转移方程：  value[i] = max{value[i-1] /*不打劫i*/, value[i-2] + nums[i] /*打劫i*/}

打劫第 i 家的最大收益分为，打劫第 i 家 与 不打劫第 i 家。

```
```c
/*
 * @lc app=leetcode.cn id=198 lang=cpp
 *
 * [198] 打家劫舍
 */
//------------递归实现--------------------
// @lc code=start
class Solution {
public:
    int rob(vector<int>& nums) {
        if(nums.empty()) return 0;
        if(nums.size() == 1) return nums[0];
        std::vector<int> max_cnt(nums.size(), 0);
        DFS(nums, max_cnt, nums.size()-1);
        return max_cnt[max_cnt.size()-1];
    }

private:
    void DFS(const std::vector<int>& nums, std::vector<int>& max_cnt,
             int i){
        if(i==1){
            max_cnt[0] = nums[0];
            if(nums[i] > nums[0]){
                max_cnt[i] = nums[i];
            }else{
                max_cnt[i] = nums[0];
            }
            return;
        }
        DFS(nums, max_cnt, i-1);
        if(max_cnt[i-2] + nums[i] > max_cnt[i-1]){
            max_cnt[i] = max_cnt[i-2] + nums[i];
        }else{
            max_cnt[i] = max_cnt[i-1];
        }
    }
};
// @lc code=end
//------------------------递推实现------------------
class Solution {
public:
    int rob(vector<int>& nums) {
        if(nums.empty()) return 0;
        if(nums.size() == 1) return nums[0];
        std::vector<int> max_cnt(nums.size(), 0);
        
        max_cnt[0] = nums[0];
        if(nums[1] > nums[0]){
            max_cnt[1] = nums[1];
        }else{
            max_cnt[1] = nums[0];
        }

        for(int i=2; i<nums.size(); i++){
            if(max_cnt[i-2] + nums[i] > max_cnt[i-1]){
                max_cnt[i] = max_cnt[i-2] + nums[i];
            }else{
                max_cnt[i] = max_cnt[i-1];
            }
        }
        // DFS(nums, max_cnt, nums.size()-1);
        return max_cnt[max_cnt.size()-1];
    }
}；
```

---

三角形最小路径和  
Category	Difficulty	Likes	Dislikes  
algorithms	Medium (68.30%)	925	-  
Tags  
array | dynamic-programming  

Companies  
给定一个三角形 triangle ，找出自顶向下的最小路径和。  

每一步只能移动到下一行中相邻的结点上。相邻的结点 在这里指的是 下标 与 上一层结点下标 相同或者等于 上一层结点下标 + 1 的两个结点。也就是说，如果正位于当前行的下标 i ，那么下一步可以移动到下一行的下标 i 或 i + 1 。  



示例 1：  
输入：triangle = \[[2],[3,4],[6,5,7],[4,1,8,3]]  
输出：11  
解释：如下面简图所示：  
```
   2  
  3 4  
 6 5 7  
4 1 8 3  
```
自顶向下的最小路径和为 11（即，2 + 3 + 5 + 1 = 11）。  

示例 2：  
输入：triangle = \[[-10]]  
输出：-10  
 

提示：  

1 <= triangle.length <= 200  
triangle[0].length == 1  
triangle[i].length == triangle[i - 1].length + 1  
-104 <= triangle[i][j] <= 104  
 

进阶：  

你可以只使用 O(n) 的额外空间（n 为三角形的总行数）来解决这个问题吗？  
Discussion | Solution  

----------------------------------

![](../assets/images/chapter09/120-1.png)

![](../assets/images/chapter09/120-2.png)

![](../assets/images/chapter09/120-3.png)

![](../assets/images/chapter09/120-4.png)

![](../assets/images/chapter09/120-5.png)

![](../assets/images/chapter09/120-6.png)

![](../assets/images/chapter09/120-7.png)

![](../assets/images/chapter09/120-8.png)

![](../assets/images/chapter09/120-9.png)

![](../assets/images/chapter09/120-10.png)

![](../assets/images/chapter09/120-11.png)

![](../assets/images/chapter09/120-12.png)

![](../assets/images/chapter09/120-13.png)

![](../assets/images/chapter09/120-14.png)

![](../assets/images/chapter09/120-15.png)

![](../assets/images/chapter09/120-16.png)

![](../assets/images/chapter09/120-17.png)

-----------------------------------

```c
/*
 * @lc app=leetcode.cn id=120 lang=cpp
 *
 * [120] 三角形最小路径和
 * 重点思想在：倒着看！
 */
/*
*/
// @lc code=start
class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        if(triangle.empty()) return 0;
        if(triangle.size() == 1) return triangle[0][0];

        std::vector<std::vector<int>> tri = triangle;
        for(int i=tri.size()-2; i>=0; i--){
            for(int j=0; j<tri[i].size(); j++){
                // 转移方程
                tri[i][j] += tri[i+1][j]<tri[i+1][j+1] ? tri[i+1][j] : tri[i+1][j+1];
            }
        }
        return tri[0][0];
    }
};

//-------参考实现：倒着计算时，实际上只和上一状态的值有关，所有只申请一个一维数组就行----

// @lc code=start
class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        if(triangle.empty()) return 0;
        if(triangle.size() == 1) return triangle[0][0];

        std::vector<int> tri = triangle[triangle.size()-1];
        for(int i=triangle.size()-2; i>=0; i--){
            for(int j=0; j<triangle[i].size(); j++){
                tri[j] = triangle[i][j] + (tri[j]<tri[j+1] ? tri[j] : tri[j+1]);
            }
        }
        return tri[0];
    }

};


```

---

最大子数组和  
Category	Difficulty	Likes	Dislikes  
algorithms	Easy (55.28%)	4160	-  
Tags  
array | divide-and-conquer | dynamic-programming  

Companies  
bloomberg | linkedin | microsoft  

给你一个整数数组 nums ，请你找出一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。  

子数组 是数组中的一个连续部分。  

 

示例 1：  
输入：nums = \[-2,1,-3,4,-1,2,1,-5,4]  
输出：6  
解释：连续子数组 [4,-1,2,1] 的和最大，为 6 。


示例 2：  
输入：nums = [1]  
输出：1  

示例 3：  
输入：nums = [5,4,-1,7,8]  
输出：23  
 

提示：  
1 <= nums.length <= 105  
-104 <= nums[i] <= 104   
 

进阶：如果你已经实现复杂度为 O(n) 的解法，尝试使用更为精妙的 分治法 求解。  

Discussion | Solution  

--------------------------------
![](../assets/images/chapter09/53-1.png)

![](../assets/images/chapter09/53-2.png)

![](../assets/images/chapter09/53-3.png)

![](../assets/images/chapter09/53-4.png)

![](../assets/images/chapter09/53-5.png)

![](../assets/images/chapter09/53-6.png)

![](../assets/images/chapter09/53-7.png)

![](../assets/images/chapter09/53-8.png)

![](../assets/images/chapter09/53-9.png)

![](../assets/images/chapter09/53-10.png)

![](../assets/images/chapter09/53-11.png)

--------------------------------


采用分治的方法实现，先把数组用中点分为左右两个子数组，这样最大和子数组存在三种情况：

（1）在左边的子数组；  
（2）在右边的子数组；  
（3）跨过中点，左边子数组的右半部分（也可能是全部）和右边数组的左半部分（也可能是全部）。


对于前两种情况，无论哪一种，直接递归下去，而第三种情况，可以根据中点继续分成左半部分和右半部分，左边从中点向左求出最大和，右边从中点向右求出最大和，然后相加。这样三种情况就都可以处理了，每次取处理后的最大值就可以了。


---------------------------------

```c
/*
 * @lc app=leetcode.cn id=53 lang=cpp
 *
 * [53] 最大子数组和
 */
// ------------------暴力法：O(n^2)  超时-------------------
// @lc code=start
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        std::vector<int> sub_sum;
        subArray(nums, sub_sum);
        sort(sub_sum.begin(), sub_sum.end(), [&](const auto& a, const auto& b){
            return a > b;
        });    
        return sub_sum[0];    
    }

private:
    void subArray(const std::vector<int>& nums, 
                  std::vector<int>& sub_sum){
        std::vector<std::vector<int>> sub_array;
        for(int win_len=1; win_len<=nums.size(); win_len++){
            for(int j=0; j<=nums.size(); j++){
                if(j+win_len>nums.size()) break;
                std::vector<int> tmp(nums.begin()+j, nums.begin()+j+win_len);
                sub_array.push_back(tmp);
                tmp.clear();
            }
        }

        for(int i=0; i<sub_array.size(); i++){
            sub_sum.push_back(accumulate(sub_array[i].begin(), sub_array[i].end(), 0));
        }
    }

};
// @lc code=end

//------------------动态规划思想：时间复杂度： O(n)--------------------
// @lc code=start
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        std::vector<int> sub_sum;
        // 注意没定义数组大小时，不要 index 访问
        sub_sum.push_back(nums[0]);
        for(int i=1; i<nums.size(); i++){
            if(sub_sum[i-1]>0){
                sub_sum.push_back(sub_sum[i-1] + nums[i]);
            }else{
            // 如果前面的都小于 0 了，没必要考虑它了，没利用价值了，嗐，没了价值，数组都会被抛弃
                sub_sum.push_back(nums[i]);
            }
        }
        sort(sub_sum.begin(), sub_sum.end(), [&](const auto& a, const auto& b){
            return a > b;
        });    
        return sub_sum[0];    
    }
};
// @lc code=end

```

---

零钱兑换  
Category	Difficulty	Likes	Dislikes  
algorithms	Medium (44.78%)	1630	-  
Tags  
dynamic-programming 

Companies   
给你一个整数数组 coins ，表示不同面额的硬币；以及一个整数 amount ，表示总金额。  

计算并返回可以凑成总金额所需的 最少的硬币个数 。如果没有任何一种硬币组合能组成总金额，返回 -1 。  

你可以认为每种硬币的数量是无限的。  

 

示例 1：  
输入：coins = [1, 2, 5], amount = 11  
输出：3   
解释：11 = 5 + 5 + 1  

示例 2：  
输入：coins = [2], amount = 3  
输出：-1  


示例 3：  
输入：coins = [1], amount = 0  
输出：0  

示例 4：  
输入：coins = [1], amount = 1  
输出：1  

示例 5：  
输入：coins = [1], amount = 2  
输出：2  
 

提示：  

1 <= coins.length <= 12  
1 <= coins[i] <= 231 - 1  
0 <= amount <= 104  
Discussion | Solution  

--------------------------------------------------

![](../assets/images/chapter09/322-1.png)

![](../assets/images/chapter09/322-2.png)

![](../assets/images/chapter09/322-3.png)

![](../assets/images/chapter09/322-4.png)

![](../assets/images/chapter09/322-5.png)

![](../assets/images/chapter09/322-6.png)

![](../assets/images/chapter09/322-7.png)

![](../assets/images/chapter09/322-8.png)

![](../assets/images/chapter09/322-9.png)

![](../assets/images/chapter09/322-10.png)

![](../assets/images/chapter09/322-11.png)

![](../assets/images/chapter09/322-12.png)

![](../assets/images/chapter09/322-13.png)

![](../assets/images/chapter09/322-14.png)

![](../assets/images/chapter09/322-15.png)

![](../assets/images/chapter09/322-16.png)

![](../assets/images/chapter09/322-17.png)

![](../assets/images/chapter09/322-18.png)

![](../assets/images/chapter09/322-19.png)

![](../assets/images/chapter09/322-20.png)

![](../assets/images/chapter09/322-21.png)

![](../assets/images/chapter09/322-22.png)

![](../assets/images/chapter09/322-23.png)

![](../assets/images/chapter09/322-24.png)

![](../assets/images/chapter09/322-25.png)


--------------------------------------------------

```c
/*
 * @lc app=leetcode.cn id=322 lang=cpp
 *
 * [322] 零钱兑换
 */

// @lc code=start
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        // 索引为amount  值为最优解
        std::vector<int> opt_nums(amount+1, -1);
        opt_nums[0] = 0;

        // 索引 i 为 amount 金额
        for(int i=1; i<= amount; i++){
            // 对于每个金额 i ，使用变量 j 遍历面值 coins 数组
            for(int j=0; j<coins.size(); j++){
                // 所有小于等于 i 的面值 coins[j]
                // 如果金额 i-coins[j] 有最优解
                if(coins[j]<=i && opt_nums[i-coins[j]] !=-1){
                    // 如果，当前金额还未计算
                    // 或者 opt_nums[i] 比正在计算的最优解大
                    if(opt_nums[i]==-1 || opt_nums[i] > opt_nums[i-coins[j]]+1){
                        opt_nums[i] = opt_nums[i-coins[j]] + 1;// 更新opt_nums[i]
                    }
                }
            }
        }

        return opt_nums[amount];
    }

};
// @lc code=end
```