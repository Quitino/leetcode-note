---
title: 第07章 二分查找
nav_order: 8
---

搜索插入位置  
Category	Difficulty	Likes	Dislikes  
algorithms	Easy (45.94%)	1248	-  
Tags  
array | binary-search  

Companies  
给定一个排序数组和一个目标值，在数组中找到目标值，并返回其索引。如果目标值不存在于数组中，返回它将会被按顺序插入的位置。  

请必须使用时间复杂度为 O(log n) 的算法。  

 

示例 1:
输入: nums = [1,3,5,6], target = 5    
输出: 2    


  
示例 2:   
输入: nums = [1,3,5,6], target = 2  
输出: 1  


示例 3:  
输入: nums = [1,3,5,6], target = 7  
输出: 4  


示例 4:  
输入: nums = [1,3,5,6], target = 0  
输出: 0  


示例 5:  
输入: nums = [1], target = 0  
输出: 0  
 

提示:

1 <= nums.length <= 104  
-104 <= nums[i] <= 104  
nums 为无重复元素的升序排列数组  
-104 <= target <= 104  
Discussion | Solution  

------------------------------

![](../assets/images/chapter07/35-1.png)

![](../assets/images/chapter07/35-2.png)

![](../assets/images/chapter07/35-3.png)

![](../assets/images/chapter07/35-4.png)

![](../assets/images/chapter07/35-5.png)

----------------------------------
```c
/*
 * @lc app=leetcode.cn id=35 lang=cpp
 *
 * [35] 搜索插入位置
 */

// @lc code=start
//  ------------时间复杂度 O(n)----------------
class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        if(nums.empty()) return 0;
        int res;
        for(int i=0; i<nums.size(); i++){
            if(nums[i] == target || nums[i]>target){
                res = i;
                break;
            }
        }
        return res;
    }

    // ------------------时间复杂度 O(logn)------------
    int searchInsert(vector<int>& nums, int target) {
        if(nums.empty()) return 0;
        int left = 0;
        int right = nums.size();
        while(left != right){
            int mid = left + (right - left)/2;
            if(nums[mid] >= target){// >=
                right = mid;
            }else{
                left = mid + 1;
            }
        }
        return left;
    }
};
// @lc code=end


```

---

在排序数组中查找元素的第一个和最后一个位置  
Category	Difficulty	Likes	Dislikes  
algorithms	Medium (42.27%)	1363	-  
Tags  
array | binary-search  

Companies  
给定一个按照升序排列的整数数组 nums，和一个目标值 target。找出给定目标值在数组中的开始位置和结束位置。  

如果数组中不存在目标值 target，返回 [-1, -1]。  

进阶：  

你可以设计并实现时间复杂度为 O(log n) 的算法解决此问题吗？  
 

示例 1：  
输入：nums = [5,7,7,8,8,10], target = 8  
输出：[3,4] 


示例 2：  
输入：nums = [5,7,7,8,8,10], target = 6  
输出：[-1,-1]  


示例 3：  
输入：nums = [], target = 0  
输出：[-1,-1]  
 

提示：  

0 <= nums.length <= 105  
-109 <= nums[i] <= 109  
nums 是一个非递减数组  
-109 <= target <= 109  
Discussion | Solution   

-------------------------------

- 两次二分查找，分别查找 起始 和 终止 位置

- 观察起始 和 终止 位置的性质。  

 ![](../assets/images/chapter07/34-3.png)

![](../assets/images/chapter07/34-4.png)

![](../assets/images/chapter07/34-5.png)

![](../assets/images/chapter07/34-6.png)

![](../assets/images/chapter07/34-7.png)

![](../assets/images/chapter07/34-8.png)

![](../assets/images/chapter07/34-9.png)



 ----------------------------

 ```c
/*
 * @lc app=leetcode.cn id=34 lang=cpp
 *
 * [34] 在排序数组中查找元素的第一个和最后一个位置
 */

// @lc code=start
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        std::vector<int> res{-1,-1};
        int left = 0;
        int right = nums.size() - 1;
        int mid;
        // 左端点
        while(left <= right){
            mid = left + (right - left)/2;
            if(target == nums[mid]){//中间元素等于目标元素
                // 左端点性质， 注意左端点可能为第一位
                // 结束条件： target == nums[mid] && nums[mid-1] < target
                // mid==0 要写在前面， 利用 ||  短路逻辑， 当只有一个元素的时候 mid-1 不会报错
                if(mid==0 || nums[mid-1]<target){
                    res[0] = mid;
                    break;
                }
                right = mid - 1;//重复（多个元素等于target）等于target 左移找左端点
            }else if(target < nums[mid]){
                right = mid - 1;
            }else if(target > nums[mid]){
                left = mid + 1;
            }
        }

        // 重置数组指针
        left = 0;
        right = nums.size() - 1;

        // 右端点
        while(left <= right){
            mid = left + (right - left)/2;
            if(target == nums[mid]){//中间元素等于目标元素
                // 右端点性质， 注意右端点可能为最后一位
                // 结束条件： target == nums[mid] && nums[mid+1] > target
                // mid == nums.size()-1 要写在前面， 利用 ||  短路逻辑， 当只有一个元素的时候 mid-1 不会报错
                if(mid == nums.size()-1 || nums[mid+1]>target ){
                    res[1] = mid;
                    break;
                }
                left = mid + 1;// 重复（多个元素等于target）等于target 右移 找右端点
            }else if(target < nums[mid]){
                right = mid - 1;
            }else if(target > nums[mid]){
                left = mid + 1;
            }
        }

        return res;
    }
};
// @lc code=end


 ```

---

搜索旋转排序数组  
Category	Difficulty	Likes	Dislikes  
algorithms	Medium (43.01%)	1749	-  
Tags  
array | binary-search  

Companies  
整数数组 nums 按升序排列，数组中的值 互不相同 。  

在传递给函数之前，nums 在预先未知的某个下标 k（0 <= k < nums.length）上进行了 旋转，使数组变为 [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]]（下标 从 0 开始 计数）。例如， [0,1,2,4,5,6,7] 在下标 3 处经旋转后可能变为 [4,5,6,7,0,1,2] 。  

给你 旋转后 的数组 nums 和一个整数 target ，如果 nums 中存在这个目标值 target ，则返回它的下标，否则返回 -1 。  

 

示例 1：  
输入：nums = [4,5,6,7,0,1,2], target = 0  
输出：4 


示例 2：
输入：nums = [4,5,6,7,0,1,2], target = 3  
输出：-1  


示例 3：  
输入：nums = [1], target = 0  
输出：-1  
 

提示：  

1 <= nums.length <= 5000  
-10^4 <= nums[i] <= 10^4  
nums 中的每个值都 独一无二  
题目数据保证 nums 在预先未知的某个下标上进行了旋转  
-10^4 <= target <= 10^4  
 

进阶：你可以设计一个时间复杂度为 O(log n) 的解决方案吗？  

Discussion | Solution

--------------------------------------------

![](../assets/images/chapter07/33-1.png)

![](../assets/images/chapter07/33-2.png)

![](../assets/images/chapter07/33-3.png)

![](../assets/images/chapter07/33-4.png)

![](../assets/images/chapter07/33-5.png)

![](../assets/images/chapter07/33-6.png)

![](../assets/images/chapter07/33-7.png)

![](../assets/images/chapter07/33-8.png)

![](../assets/images/chapter07/33-9.png)

![](../assets/images/chapter07/33-10.png)


-------------------------------------------
```c
/*
 * @lc app=leetcode.cn id=33 lang=cpp
 *
 * [33] 搜索旋转排序数组
 */
 //------------------自己实现：无序部分递归调用自己-------------------------
// 对旋转数组， 二分法分为两个部分以后， 其中有一部分是有序的，另一部分的是无序的
// @lc code=start
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int res;
        recursion(nums, target, 0, nums.size()-1, res);
        return res;
    }

private:

    bool recursion(std::vector<int>& nums,
                   int& target,
                   int left, int right, int& mid){// mid 为引用只是保存结果的作用
        if(left == right){
            if(nums[left] == target){
                mid = left;
                return true;
            }else{
                mid = -1;
                return false;
            }
        }

        mid = left + (right-left)/2;
        if(target == nums[mid]) return true;

        if(nums[left] <= nums[mid] ){// 左部分有序 
            if(target<nums[mid] && target>=nums[left]){//且 目标值在区间里面
                // 在有序区间里使用二分查找
                return binSearch(nums, target, left, mid - 1, mid);
            }else{// 目标值在右边无序里面
                return recursion(nums, target, mid+1, right, mid);
            }
        }else{// 右部分有序
            if(target>nums[mid] && target<=nums[right]){//且 目标值在区间里面
                // 在有序区间里使用二分查找
                return binSearch(nums, target, mid + 1, right, mid);
            }else{// 目标值在左边无序里面
                return recursion(nums, target, left, mid-1, mid);
            }
        }
        mid = -1;
        return false;
    } 

    bool binSearch(std::vector<int>& nums, int& target, int left, 
                   int right, int& mid){// mid只是传结果出去
        while(left <= right){
            mid = left + (right-left)/2;
            if(target == nums[mid]) return true;
            if(target < nums[mid]){
                right = mid - 1;
            }else if(target > nums[mid]){
                left = mid + 1;
            }
        }
        // while 没找到 mid = -1
        mid = -1;
        return false;
    }


//---------------参考实现----------------------
//--------啊啊啊啊是我把事情想复杂了------------------
    int search(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size() - 1;

        while(left <= right){
            int mid = left + (right-left)/2;
            if(nums[mid] == target) return mid;
            
            if(nums[left] <= nums[mid]){// 左边有序 右边无序
                // target 在有序序列中
                if(target>=nums[left] && target<nums[mid]){
                    right = mid - 1;
                }else{// target 在右边无序列中
                    left = mid + 1;
                }
            }else{// 左边无序 右边有序
                // target 在有序序列中
                if(target<=nums[right] && target>nums[mid]){
                    left = mid + 1;
                }else{// target 在右边无序列中
                    right = mid - 1;
                }
            }
        }
        return -1;
    }

};
// @lc code=end


```