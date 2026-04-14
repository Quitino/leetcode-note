---
title: 第03章 贪心算法
nav_order: 4
---

分发饼干  
Category	Difficulty	Likes	Dislikes  
algorithms	Easy (57.58%)	421	-  
Tags  
Companies  
假设你是一位很棒的家长，想要给你的孩子们一些小饼干。但是，每个孩子最多只能给一块饼干。  

对每个孩子 i，都有一个胃口值 g[i]，这是能让孩子们满足胃口的饼干的最小尺寸；并且每块饼干 j，都有一个尺寸 s[j] 。如果 s[j] >= g[i]，我们可以将这个饼干 j 分配给孩子 i ，这个孩子会得到满足。你的目标是尽可能满足越多数量的孩子，并输出这个最大数值。  

 
示例 1:

输入: g = [1,2,3], s = [1,1]  
输出: 1  
解释:   
你有三个孩子和两块小饼干，3个孩子的胃口值分别是：1,2,3。  
虽然你有两块小饼干，由于他们的尺寸都是1，你只能让胃口值是1的孩子满足。  
所以你应该输出1。  


示例 2:

输入: g = [1,2], s = [1,2,3]  
输出: 2  
解释:   
你有两个孩子和三块小饼干，2个孩子的胃口值分别是1,2。  
你拥有的饼干数量和尺寸都足以让所有孩子满足。  
所以你应该输出2.  
 

提示：

1 <= g.length <= 3 * 104  
0 <= s.length <= 3 * 104  
1 <= g[i], s[j] <= 231 - 1  
Discussion | Solution  

-----------------------------------------


![](./pic/../../pic/455-1.png)

![](./pic/../../pic/455-2.png)

![](./pic/../../pic/455-3.png)

```c
/*
 * @Date: 2021-12-26 22:39:19
 * @Author: bFeng
 */
/*
 * @lc app=leetcode.cn id=455 lang=cpp
 *
 * [455] 分发饼干
 */

// @lc code=start

//  容器求解
class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        // 首先对两组元素进行排序
        sort(g.begin(), g.end(), [&](const int& a, const int& b){
            return a < b;
        });
        sort(s.begin(), s.end(), [&](const int& a, const int& b){
            return a < b;
        });

        int res = 0;
        std::vector<int>::iterator s_itr = s.begin();
        for(std::vector<int>::iterator g_itr = g.begin(); g_itr != g.end(); ){
            // 注意++ 时要判断是否到尾部
            while(s_itr != s.end() && g_itr != g.end() &&*g_itr <= *s_itr){//如果得到满足
                s_itr ++;
                g_itr ++;
                res ++;
            }
            if(s_itr == s.end()) break;
            s_itr ++;//没得到满足
        }
        
        return res;
    }
};


// 数组求解
class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {

        sort(g.begin(), g.end());
        sort(s.begin(), s.end());

        int child = 0;// child s下标
        int candy = 0;// candy g下标

        while(child < g.size() && candy < s.size()){
            if(s[candy] >= g[child]){// 满足当前孩子
                child ++;
            }
            candy ++;
        }

        return child;//孩子满足的个数
    }
};

// @lc code=end


```

---

用最少数量的箭引爆气球  
Category	Difficulty	Likes	Dislikes  
algorithms	Medium (50.78%)	496	-  
Tags  
Companies  
在二维空间中有许多球形的气球。对于每个气球，提供的输入是水平方向上，气球直径的开始和结束坐标。由于它是水平的，所以纵坐标并不重要，因此只要知道开始和结束的横坐标就足够了。开始坐标总是小于结束坐标。  

一支弓箭可以沿着 x 轴从不同点完全垂直地射出。在坐标 x 处射出一支箭，若有一个气球的直径的开始和结束坐标为 xstart，xend， 且满足  xstart ≤ x ≤ xend，则该气球会被引爆。可以射出的弓箭的数量没有限制。 弓箭一旦被射出之后，可以无限地前进。我们想找到使得所有气球全部被引爆，所需的弓箭的最小数量。  

给你一个数组 points ，其中 points [i] = [xstart,xend] ，返回引爆所有气球所必须射出的最小弓箭数。  

 
示例 1：

输入：points = [[10,16],[2,8],[1,6],[7,12]]  
输出：2  
解释：对于该样例，x = 6 可以射爆 [2,8],[1,6] 两个气球，以及 x = 11 射爆另外两个气球  

示例 2：

输入：points = [[1,2],[3,4],[5,6],[7,8]]  
输出：4  
示例 3：  

输入：points = [[1,2],[2,3],[3,4],[4,5]]  
输出：2  

示例 4：  

输入：points = [[1,2]]  
输出：1  

示例 5：

输入：points = [[2,3],[2,3]]  
输出：1
 

提示：

1 <= points.length <= 104  
points[i].length == 2  
-231 <= xstart < xend <= 231 - 1   
Discussion | Solution  

----------------------------------


![](../assets/images/chapter03/452-1.png)

![](../assets/images/chapter03/452-2.png)

![](../assets/images/chapter03/452-3.png)

![](../assets/images/chapter03/452-4.png)

![](../assets/images/chapter03/452-5.png)

![](../assets/images/chapter03/452-6.png)

![](../assets/images/chapter03/452-7.png)

![](../assets/images/chapter03/452-8.jpg)

![](../assets/images/chapter03/452-9.png)

```c
/*
 * @Date: 2021-12-27 00:04:33
 * @Author: bFeng
 */
/*
 * @lc app=leetcode.cn id=452 lang=cpp
 *
 * [452] 用最少数量的箭引爆气球
 */

// @lc code=start

// 按左端点进行排序
class Solution {
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        if(points.empty()) return 0;
        // 排序时需要注意，右坐标相等的情况
        sort(points.begin(), points.end(), [&](const auto& a, const auto& b){
            if(a[0] == b[0]){
                return a[1] < b[1];
            }
            return a[0] < b[0];
        });

        std::vector<int> left;
        std::vector<int> right;
        for(const auto& itr : points){
            left.push_back(itr[0]);
            right.push_back(itr[1]);
        }

        int left_idx = 0;
        int right_idx = 0;
        int res = 1;//由于最后跳出while循环的那个区间统计不到，所以从1开始
        int min_right = right[right_idx];
        while(left_idx<points.size() && right_idx<points.size()){
            if(min_right > right[right_idx]){//注意是和右边最小的那个值比较，想象一下，公有部分
                min_right = right[right_idx];
            }
            // if(left[left_idx] <= right[right_idx]){
            if(left[left_idx] <= min_right){//小于这个区间段的最小值
                left_idx ++;
                right_idx ++;
                continue;
            }
            res ++;
            min_right = right[right_idx];//新的一个区间段，注意更新min_right
        }
        return res;
    }
};
// @lc code=end


// 通过维护射击区间进行计算
class Solution {
public:
    int findMinArrowShots(std::vector<std::vector<int>>& points) {
        if(points.empty()) return 0;
        // 排序时需要注意，右坐标相等的情况
        sort(points.begin(), points.end(), [&](const auto& a, const auto& b){
            if(a[0] == b[0]){
                return a[1] < b[1];
            }
            return a[0] < b[0];
        });

        // 维护射击的范围，夹在中间
        int shoot_range[2] = {points[0][0], points[0][1]};

        int res = 1;
        for(const auto& pt : points ){
            if(pt[0] > shoot_range[0]){//更新射击范围左边界
                shoot_range[0] = pt[0];
            }
            if(pt[1] < shoot_range[1]){//更新射击范围右边界
                shoot_range[1] = pt[1];
            }
            if(shoot_range[0] <= shoot_range[1]){//判断射击范围是否合法
                continue;
            }
            res ++;
            shoot_range[0] = pt[0];//重启射击范围
            shoot_range[1] = pt[1];
        }
        return res;
    }

};




```

---

移掉 K 位数字  
Category	Difficulty	Likes	Dislikes  
algorithms	Medium (32.66%)	705	-  
Tags  
Companies  
给你一个以字符串表示的非负整数 num 和一个整数 k ，移除这个数中的 k 位数字，使得剩下的数字最小。请你以字符串形式返回这个最小的数字。  

 
示例 1 ：

输入：num = "1432219", k = 3  
输出："1219"  
解释：移除掉三个数字 4, 3, 和 2 形成一个新的最小的数字 1219 。  

示例 2 ：

输入：num = "10200", k = 1    
输出："200"  
解释：移掉首位的 1 剩下的数字为 200. 注意输出不能有任何前导零。  

示例 3 ：

输入：num = "10", k = 2  
输出："0"  
解释：从原数字移除所有的数字，剩余为空就是 0 。  
 

提示：

1 <= k <= num.length <= 105  
num 仅由若干位数字（0 - 9）组成  
除了 0 本身之外，num 不含任何前导零  
Discussion | Solution  

-------------------------------

![](../assets/images/chapter03/402-1.png)

![](../assets/images/chapter03/402-2.png)

![](../assets/images/chapter03/402-3.png)

![](../assets/images/chapter03/402-4.png)

![](../assets/images/chapter03/402-5.png)

![](../assets/images/chapter03/402-6.png)

![](../assets/images/chapter03/402-7.png)

![](../assets/images/chapter03/402-8.png)

![](../assets/images/chapter03/402-9.png)

![](../assets/images/chapter03/402-10.png)

![](../assets/images/chapter03/402-11.png)

![](../assets/images/chapter03/402-12.png)

![](../assets/images/chapter03/402-13.png)

![](../assets/images/chapter03/402-14.png)

![](../assets/images/chapter03/402-15.png)

-----------------------


```c
/*
 * @Date: 2021-12-27 15:35:52
 * @Author: bFeng
 */
/*
 * @lc app=leetcode.cn id=402 lang=cpp
 *
 * [402] 移掉 K 位数字
 */

// @lc code=start
// 使用栈保存处理结果
class Solution {
public:
     std::string removeKdigits(std::string num, int k) {
        if(num == "" || k==0) return num;
        std::stack<char> res_inv;//高位在下
        // res_inv.push(num[0]);
        for(int i=0; i<num.size(); i++){
            // 删除数字的条件
            while(!res_inv.empty() && k>0 && res_inv.top()>num[i]){
                res_inv.pop();
                k--;
            }
            // 处理数字开头为 0 的情况， 0 不入栈
            if(res_inv.empty() && num[i]=='0'){
                continue;
            }
            res_inv.push(num[i]);
        }

        // 若遍历完还没删完，就从栈顶开始删除
        while(k-- && !res_inv.empty()){
            res_inv.pop();
        }

        // 处理空的情况
        if(res_inv.empty()) return "0";

        // 构造字符串，进行输出
        std::string res;

        while(!res_inv.empty()){
            res += res_inv.top();
            res_inv.pop();
        }
        // 反转字符串
        reverse(res.begin(), res.end());
        return res;
    }


};
// @lc code=end


```

---

跳跃游戏  
Category	Difficulty	Likes	Dislikes  
algorithms	Medium (43.39%)	1551	-  
Tags  
Companies  
给定一个非负整数数组 nums ，你最初位于数组的 第一个下标 。  

数组中的每个元素代表你在该位置可以跳跃的最大长度。  

判断你是否能够到达最后一个下标。  

 

示例 1：  

输入：nums = [2,3,1,1,4]  
输出：true  
解释：可以先跳 1 步，从下标 0 到达下标 1, 然后再从下标 1 跳 3 步到达最后一个下标。  


示例 2：

输入：nums = [3,2,1,0,4]  
输出：false  
解释：无论怎样，总会到达下标为 3 的位置。但该下标的最大跳跃长度是 0 ， 所以永远不可能到达最后一个下标。  
 

提示：  

1 <= nums.length <= 3 * 104  
0 <= nums[i] <= 105  
Discussion | Solution  

Code Now

-------------------------------------


![](../assets/images/chapter03/55-1.png)

![](../assets/images/chapter03/55-2.png)

![](../assets/images/chapter03/55-3.png)

![](../assets/images/chapter03/55-4.png)

![](../assets/images/chapter03/55-5.png)

![](../assets/images/chapter03/55-6.png)

![](../assets/images/chapter03/55-7.png)

![](../assets/images/chapter03/55-8.png)

![](../assets/images/chapter03/55-9.png)

![](../assets/images/chapter03/55-10.png)

![](../assets/images/chapter03/55-11.png)

![](../assets/images/chapter03/55-12.png)

![](../assets/images/chapter03/55-13.png)

![](../assets/images/chapter03/55-14.jpg)

--------------------------------------


```c

/*
 * @Date: 2021-12-27 21:09:52
 * @Author: bFeng
 */
/*
 * @lc app=leetcode.cn id=55 lang=cpp
 *
 * [55] 跳跃游戏
 */

// @lc code=start
// 参考解法 
class Solution {
public:
    bool canJump(std::vector<int>& nums) {
        std::vector<int> jump;
        for(int i=0; i<nums.size(); i++){
            jump.push_back(i + nums[i]);
        }

        int curr = 0;// 当前所在index
        int max_jump = jump[0];// 存储当前可以到达的最远位置
        while(curr < nums.size() && curr <= max_jump){
            if(max_jump < jump[curr]){
                max_jump = jump[curr];
            }
            curr ++;//这样才会在jump[]相同的时候，往前走
        }

        if(curr == nums.size()) return true;
        else return false;
    }
};
// @lc code=end

------------------------------
    // 自己的解法： 未通过全部案例测试：
    // index 0 1 2 3 4
    // nums  3 2 1 0 4
    // jump  3 3 3 3 4
    // 这种情况，当jump都为 3 3 3 3，相同时，无法通过测试
    bool canJump(std::vector<int>& nums) {
        std::vector<int> jump;
        for(int i=0; i<nums.size(); i++){
            jump.push_back(i + nums[i]);
        }

        int curr = 0;
        while(curr < nums.size()-1){
            // 使用 map 来记录 index
            std::map<int,int> curr_jump;
            for(int i=curr; i<=jump[curr]; i++){
                curr_jump[i] = jump[i];
            }

            int max_jump = 0;
            int record_idx = -1;
            for(const auto& itr : curr_jump){
                if(max_jump < itr.second){
                    max_jump = itr.second;
                    record_idx = itr.first;
                }
            }

            curr = record_idx;
            if(0 == nums[curr]) break;
        }

        if(jump[curr] >= nums.size()-1) return true;
        else return false;
    }
```