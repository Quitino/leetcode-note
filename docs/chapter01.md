---
title: 第01章 链表
nav_order: 2
---

# 206-链表逆序

给你单链表的头节点 head ，请你反转链表，并返回反转后的链表。
 

示例 1：

![](../assets/images/chapter01/206-pic-1.png)

输入：head = [1,2,3,4,5]
输出：[5,4,3,2,1]
示例 2：

![](../assets/images/chapter01/206-pic-2.png)


输入：head = [1,2]
输出：[2,1]
示例 3：

输入：head = []
输出：[]
 

提示：

链表中节点的数目范围是 [0, 5000]
-5000 <= Node.val <= 5000


- 头插法



![](../assets/images/chapter01/206-链表逆序-头插法-21.png)  


![](../assets/images/chapter01/206-链表逆序-头插法-22.png)  


![](../assets/images/chapter01/206-链表逆序-头插法-23.png)


![](../assets/images/chapter01/206-n-1.jpg)

----------------------------------------

- 直接逆序法


![](../assets/images/chapter01/206-链表逆序-直接逆置法-11.png)


![](../assets/images/chapter01/ 206-链表逆序-直接逆置法-12.png)


![](../assets/images/chapter01/206-链表逆序-直接逆置法-13.png)


![](../assets/images/chapter01/206-链表逆序-直接逆置法-14.png)


![](../assets/images/chapter01/206-n-2.jpg)



```c
/*
 * @Date: 2021-12-22 09:59:14
 * @Author: bFeng
 */
/*
 * @lc app=leetcode.cn id=206 lang=cpp
 *
 * [206] 反转链表
 */

// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

class Solution {
public:
    ListNode* reverseList(ListNode* head) {//直接逆序法
        if(head == nullptr){
            return nullptr;
        }
        ListNode* reverse = nullptr;
        ListNode* next = nullptr;
        while(head != nullptr){
            next = head->next;
            head->next = reverse;
            reverse = head;
            head = next;
        }
        return reverse;
    }
};



class Solution {
public:
    ListNode* reverseList(ListNode* head) {//头插法
        if(head == nullptr){
            return nullptr;
        }
        ListNode tmp = ListNode();
        ListNode* next = nullptr;
        while(head != nullptr){
            next = head->next;
            head->next = tmp.next;
            tmp.next = head;
            head = next;
        }
        return tmp.next;//注意返回的是next
    }
};
// @lc code=end


```

---

相交链表  
Category	Difficulty	Likes	Dislikes  
algorithms	Easy (61.81%)	1472	-  
Tags  
Companies  
给你两个单链表的头节点 headA 和 headB ，请你找出并返回两个单链表相交的起始节点。如果两个链表不存在相交节点，返回 null 。   

图示两个链表在节点 c1 开始相交：  

![](../assets/images/chapter01/160-pic-1.png)  

题目数据 保证 整个链式结构中不存在环。  

注意，函数返回结果后，链表必须 保持其原始结构 。

自定义评测：

评测系统 的输入如下（你设计的程序 不适用 此输入）：  

intersectVal - 相交的起始节点的值。如果不存在相交节点，这一值为 0  
listA - 第一个链表  
listB - 第二个链表  
skipA - 在 listA 中（从头节点开始）跳到交叉节点的节点数  
skipB - 在 listB 中（从头节点开始）跳到交叉节点的节点数  
评测系统将根据这些输入创建链式数据结构，并将两个头节点 headA 和 headB 传递给你的程序。  如果程序能够正确返回相交节点，那么你的解决方案将被 视作正确答案 。  

 

示例 1：

![](../assets/images/chapter01/160-pic-2.png)


输入：intersectVal = 8, listA = [4,1,8,4,5], listB = [5,6,1,8,4,5], skipA = 2, skipB = 3  
输出：Intersected at '8'  
解释：相交节点的值为 8 （注意，如果两个链表相交则不能为 0）。  
从各自的表头开始算起，链表 A 为 [4,1,8,4,5]，链表 B 为 [5,6,1,8,4,5]。  
在 A 中，相交节点前有 2 个节点；在 B 中，相交节点前有 3 个节点。  

示例 2：

![](../assets/images/chapter01/160-pic-3.png)


输入：intersectVal = 2, listA = [1,9,1,2,4], listB = [3,2,4], skipA = 3, skipB = 1  
输出：Intersected at '2'  
解释：相交节点的值为 2 （注意，如果两个链表相交则不能为 0）。  
从各自的表头开始算起，链表 A 为 [1,9,1,2,4]，链表 B 为 [3,2,4]。  
在 A 中，相交节点前有 3 个节点；在 B 中，相交节点前有 1 个节点。  

示例 3：

![](../assets/images/chapter01/160-pic-4.png)


输入：intersectVal = 0, listA = [2,6,4], listB = [1,5], skipA = 3, skipB = 2
输出：null  
解释：从各自的表头开始算起，链表 A 为 [2,6,4]，链表 B 为 [1,5]。  
由于这两个链表不相交，所以 intersectVal 必须为 0，而 skipA 和 skipB 可以是任意值。  
这两个链表不相交，因此返回 null 。  
 

提示：

listA 中节点数目为 m  
listB 中节点数目为 n  
1 <= m, n <= 3 * 104  
1 <= Node.val <= 105  
0 <= skipA <= m  
0 <= skipB <= n  
如果 listA 和 listB 没有交点，intersectVal 为 0  
如果 listA 和 listB 有交点，intersectVal == listA[skipA] == listB[skipB]  
 

进阶：你能否设计一个时间复杂度 O(m + n) 、仅用 O(1) 内存的解决方案？

Discussion | Solution

-----------------------------------------------
- 两层循环遍历


![](../assets/images/chapter01/160-链表交点-两层循环-1.png)

![](../assets/images/chapter01/160-链表交点-两层循环-2.png)

---------------------------------------------

- set优化

![](../assets/images/chapter01/160-链表交点-set优化-1.png)


--------------------------------------------

- 双指针法


![](../assets/images/chapter01/160-链表交点-双指针-1.png)


![](../assets/images/chapter01/160-链表交点-双指针-2.png)

![](../assets/images/chapter01/160-链表交点-双指针-3.png)

![](../assets/images/chapter01/160-链表交点-双指针-4.png)

![](../assets/images/chapter01/160-链表交点-双指针-5.png)


1.统计链表长度

2.删除长链表

3.同时遍历


```c
/*
 * @Date: 2021-12-22 11:45:07
 * @Author: bFeng
 */
/*
 * @lc app=leetcode.cn id=160 lang=cpp
 *
 * [160] 相交链表
 */

// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {// 使用set优化  O(nlogn)
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if(headA == nullptr|| headB == nullptr){
            return nullptr;
        }
        std::set<ListNode*> check_set;
        ListNode* tmp = headA;
        while(tmp){
            check_set.insert(tmp);
            tmp = tmp->next;
        }
        tmp = headB;
        while(tmp){
            if(check_set.find(tmp) != check_set.end())
            return tmp;
            tmp = tmp->next;
        }
        return nullptr;
    }
};


class Solution {// 双指针  O(n)
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if(headA == nullptr|| headB == nullptr){
            return nullptr;
        }
        int countA = 0; int countB = 0;
        ListNode* traverse_ptrA = headA;
        ListNode* traverse_ptrB = headB;
        while(traverse_ptrA){
            countA ++;
            traverse_ptrA = traverse_ptrA->next;
        }
        while(traverse_ptrB){
            countB ++;
            traverse_ptrB = traverse_ptrB->next;
        }

        traverse_ptrA = headA;
        traverse_ptrB = headB;
        if(countA > countB){
            int sub = countA - countB;
            while(sub--){
                traverse_ptrA = traverse_ptrA->next;
            }
        }else if(countA < countB){
            int sub = countB - countA;
            while(sub--){
                traverse_ptrB = traverse_ptrB->next;
            }
        }

        while(traverse_ptrA&&traverse_ptrB){
            if(traverse_ptrA == traverse_ptrB)
                return traverse_ptrA;
            traverse_ptrA = traverse_ptrA->next;
            traverse_ptrB = traverse_ptrB->next;
        }

        return nullptr;
    }
};
// @lc code=end


```

---

合并两个有序链表  
Category	Difficulty	Likes	Dislikes  
algorithms	Easy (66.70%)	2106	-  
Tags  
Companies  
将两个升序链表合并为一个新的 升序 链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。   

 

示例 1：  

![](../assets/images/chapter01/21-pic-1.png)  




输入：l1 = [1,2,4], l2 = [1,3,4]  
输出：[1,1,2,3,4,4]  
示例 2：  

输入：l1 = [], l2 = []  
输出：[]  
示例 3：  

输入：l1 = [], l2 = [0]  
输出：[0]  
 

提示：

两个链表的节点数目范围是 [0, 50]  
-100 <= Node.val <= 100  
l1 和 l2 均按 非递减顺序 排列  
Discussion | Solution  

------------------------------------

![](../assets/images/chapter01/21-1.png)


- 归并排序

![](../assets/images/chapter01/21-2.png)

![](../assets/images/chapter01/21-3.png)

![](../assets/images/chapter01/21-4.png)

![](../assets/images/chapter01/21-5.png)

![](../assets/images/chapter01/21-6.png)

![](../assets/images/chapter01/21-7.png)



```c
/*
 * @Date: 2021-12-22 14:45:03
 * @Author: bFeng
 */
/*
 * @lc app=leetcode.cn id=21 lang=cpp
 *
 * [21] 合并两个有序链表
 */

// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        if(list1 == nullptr) return list2;
        if(list2 == nullptr) return list1;

        ListNode res; // 使用临时节点
        ListNode* res_ptr = &res;

        while(list1 || list2){
            // 遍历完其中一个，另一个直接交管
            if(list1 == nullptr){
                res_ptr->next = list2;
                return res.next;
            }
            if(list2 == nullptr){
                res_ptr->next = list1;
                return res.next;
            }
            // 对每一个比较大小， 进行赋值
            if(list1->val < list2->val){
                res_ptr->next = list1;
                list1 = list1->next;
                res_ptr = res_ptr->next;
            }else{
                res_ptr->next = list2;
                list2 = list2->next;
                res_ptr = res_ptr->next;
            }
        }
    return res.next;
    }
};
// @lc code=end



```

---

分隔链表  
Category	Difficulty	Likes	Dislikes  
algorithms	Medium (63.25%)	498	-  
Tags  
Companies  
给你一个链表的头节点 head 和一个特定值 x ，请你对链表进行分隔，使得所有 小于 x 的节点都出现在 大于或等于 x 的节点之前。  

你应当 保留 两个分区中每个节点的初始相对位置。  

 

示例 1：


![](../assets/images/chapter01/86-1.png)

输入：head = [1,4,3,2,5,2], x = 3  
输出：[1,2,2,4,3,5]  



示例 2：

输入：head = [2,1], x = 2  
输出：[1,2]  
 

提示：

链表中节点的数目在范围 [0, 200] 内  
-100 <= Node.val <= 100  
-200 <= x <= 200  
Discussion | Solution  

---------------------------------



![](../assets/images/chapter01/86-2.png)


![](../assets/images/chapter01/86-3.png)



![](../assets/images/chapter01/86-4.png)



![](../assets/images/chapter01/86-5.png)



![](../assets/images/chapter01/86-6.png)



![](../assets/images/chapter01/86-7.png)



![](../assets/images/chapter01/86-8.png)



![](../assets/images/chapter01/86-9.png)


![](../assets/images/chapter01/86-10.png)



![](../assets/images/chapter01/86-11.png)





```c

/*
 * @lc app=leetcode.cn id=86 lang=cpp
 *
 * [86] 分隔链表
 */

// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public: //[1,4,3,2,5,2]
    ListNode* partition(ListNode* head, int x) {
        ListNode smaller = ListNode();
        ListNode greater = ListNode();
        ListNode* st = &smaller;
        ListNode* gt = &greater;

        while(head){
            // 为什么非得备份？
            ListNode* backup = head->next;
            if(head->val < x){
                st->next = head;
                st = st->next;
                // head = head->next;
            }else{
                gt->next = head;
                gt = gt->next;
                // head = head->next;
            }
            head->next = nullptr;
            head = backup;
        }
        st->next = greater.next;
        return smaller.next;
    }
};



class Solution {
public: //[1,4,3,2,5,2]
    ListNode* partition(ListNode* head, int x) {
        ListNode smaller = ListNode();
        ListNode greater = ListNode();
        ListNode* st = &smaller;
        ListNode* gt = &greater;

        while(head){
            // 为什么非得备份？
            // ListNode* backup = head->next;
            if(head->val < x){
                st->next = head;
                st = st->next;
                head = head->next;
            }else{
                gt->next = head;
                gt = gt->next;
                head = head->next;
            }
            // head->next = nullptr;
            // head = backup;
        }
        gt->next = nullptr;//如果不考虑备份的方式，则需要注意最后一个节点的next要置空
        st->next = greater.next;
        return smaller.next;
    }
};

```

---

环形链表 II  
Category	Difficulty	Likes	Dislikes  
algorithms	Medium (55.44%)	1291	-  
Tags  
Companies  
给定一个链表，返回链表开始入环的第一个节点。 如果链表无环，则返回 null。  

如果链表中有某个节点，可以通过连续跟踪 next 指针再次到达，则链表中存在环。 为了表示给定链表中的环，评测系统内部使用整数 pos 来表示链表尾连接到链表中的位置（索引从 0 开始）。如果 pos 是 -1，则在该链表中没有环。注意：pos 不作为参数进行传递，仅仅是为了标识链表的实际情况。  

不允许修改 链表。  

 

示例 1：

![](../assets/images/chapter01/142-1.png)


输入：head = [3,2,0,-4], pos = 1  
输出：返回索引为 1 的链表节点  
解释：链表中有一个环，其尾部连接到第二个节点。  


示例 2：

![](../assets/images/chapter01/142-2.png)

输入：head = [1,2], pos = 0  
输出：返回索引为 0 的链表节点  
解释：链表中有一个环，其尾部连接到第一个节点。  


示例 3：

![](../assets/images/chapter01/142-3.png)  

输入：head = [1], pos = -1  
输出：返回 null  
解释：链表中没有环。  
 

提示：

链表中节点的数目范围在范围 [0, 104] 内  
-105 <= Node.val <= 105  
pos 的值为 -1 或者链表中的一个有效索引  
 

进阶：你是否可以使用 O(1) 空间解决此题？  

Discussion | Solution

-----------------------------------

- set优化法

![](../assets/images/chapter01/142-4.png)

![](../assets/images/chapter01/142-5.png)





![](../assets/images/chapter01/142-6.png)


----------------------------------------

- 快慢指针法

![](../assets/images/chapter01/142-7.png)

![](../assets/images/chapter01/142-8.png)

![](../assets/images/chapter01/142-9.png)

![](../assets/images/chapter01/142-10.png)

----------------------------

```c
/*
 * @lc app=leetcode.cn id=142 lang=cpp
 *
 * [142] 环形链表 II
 */

// @lc code=start
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
        // 使用 set 解题
        std::set<ListNode*> check_node;
        while(head){
            check_node.insert(head);
            head = head->next;
            if(check_node.find(head) != check_node.end()){
                return head;
            }
        }
        return nullptr;
    }
};


// 快慢指针法
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode* slow = head;
        ListNode* fast = head;
        while(fast){
            if(fast->next == nullptr) return nullptr;//只有一个node的情况
            if(fast->next->next == nullptr) return nullptr;
            slow = slow->next;
            fast = fast->next->next;//两倍速度
            if(slow == fast){//meet
                break;
            }
        }
        while(head){
            if(head == fast){
                return head;
            }
            head = head->next;
            fast = fast->next;
        }
        return nullptr;
    }
};


```