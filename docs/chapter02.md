---
title: 第02章 栈与队列
nav_order: 3
---

用栈实现队列  
Category	Difficulty	Likes	Dislikes  
algorithms	Easy (68.97%)	523	-  
Tags  
Companies  
请你仅使用两个栈实现先入先出队列。队列应当支持一般队列支持的所有操作（push、pop、peek、empty）：  

实现 MyQueue 类：  

void push(int x) 将元素 x 推到队列的末尾  
int pop() 从队列的开头移除并返回元素  
int peek() 返回队列开头的元素  
boolean empty() 如果队列为空，返回 true ；否则，返回 false  
 

说明：  

你只能使用标准的栈操作 —— 也就是只有 push to top, peek/pop from top, size, 和 is empty 操作是合法的。  
你所使用的语言也许不支持栈。你可以使用 list 或者 deque（双端队列）来模拟一个栈，只要是标准的栈操作即可。  
 

进阶：  

你能否实现每个操作均摊时间复杂度为 O(1) 的队列？换句话说，执行 n 个操作的总时间复杂度为 O(n) ，即使其中一个操作可能花费较长时间。  
 

示例：  

输入：  
\["MyQueue", "push", "push", "peek", "pop", "empty"]  
\[[], [1], [2], [], [], []]  
输出：  
\[null, null, null, 1, 1, false] 

解释：  
MyQueue myQueue = new MyQueue();  
myQueue.push(1); // queue is: [1]  
myQueue.push(2); // queue is: [1, 2] (leftmost is front of the queue)  
myQueue.peek(); // return 1  
myQueue.pop(); // return 1, queue is [2]  
myQueue.empty(); // return false  
 

提示：  

1 <= x <= 9  
最多调用 100 次 push、pop、peek 和 empty  
假设所有操作都是有效的 （例如，一个空的队列不会调用 pop 或者 peek 操作）  
Discussion | Solution  

Code Now


- 临时栈法

![](../assets/images/chapter02/232-1.png)

![](../assets/images/chapter02/232-2.png)

![](../assets/images/chapter02/232-3.png)

![](../assets/images/chapter02/232-4.png)

![](../assets/images/chapter02/232-5.png)

![](../assets/images/chapter02/232-6.png)

![](../assets/images/chapter02/232-7.png)

------------------------------------

- 双栈法



![](../assets/images/chapter02/232-9.png)

![](../assets/images/chapter02/232-10.png)

![](../assets/images/chapter02/232-11.png)

![](../assets/images/chapter02/232-12.png)










```c
/*
 * @Date: 2021-12-24 11:17:48
 * @Author: bFeng
 */
/*
 * @lc app=leetcode.cn id=232 lang=cpp
 *
 * [232] 用栈实现队列
 */

// @lc code=start
//  method 1: 临时栈法
class MyQueue {
public:
    MyQueue() {
        // data_stack_.clear();
        // tmp_stack_.clear();
    }
    
    void push(int x) {
        data_stack_.push(x);
    }
    
    int pop() {
        // 照理来说应该判断一下
        // if(data_stack_.empty()){
        //     return ;
        // }

        int res;
        while(!data_stack_.empty()){
            tmp_stack_.push( data_stack_.top() );//top只读
            data_stack_.pop();//pop只出
        }

        res = tmp_stack_.top();
        tmp_stack_.pop();

        while(!tmp_stack_.empty()){
            data_stack_.push( tmp_stack_.top() );
            tmp_stack_.pop();
        }
        return res;
    }
    
    int peek() {
        // if(data_stack_.empty()){
        //     return ;
        // }

        int res;
        while(!data_stack_.empty()){
            tmp_stack_.push( data_stack_.top() );
            data_stack_.pop();
        }

        res = tmp_stack_.top();

        while(!tmp_stack_.empty()){
            data_stack_.push( tmp_stack_.top() );
            tmp_stack_.pop();
        }
        return res;
    }
    
    bool empty() {
        return data_stack_.empty();
    }
private:
    std::stack<int> data_stack_;
    std::stack<int> tmp_stack_;
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */
// @lc code=end



```

---

最小栈  
Category	Difficulty	Likes	Dislikes  
algorithms	Easy (57.52%)	1120	-  
Tags  
Companies  
设计一个支持 push ，pop ，top 操作，并能在常数时间内检索到最小元素的栈。  

push(x) —— 将元素 x 推入栈中。   
pop() —— 删除栈顶的元素。 
top() —— 获取栈顶元素。  
getMin() —— 检索栈中的最小元素。  
 

示例:  

输入：  
\["MinStack","push","push","push","getMin","pop","top","getMin"]  
\[[],[-2],[0],[-3],[],[],[],[]]  

输出：  
\[null,null,null,null,-3,null,0,-2]  

解释：  
MinStack minStack = new MinStack();  
minStack.push(-2);  
minStack.push(0);  
minStack.push(-3);  
minStack.getMin();   --> 返回 -3.  
minStack.pop();  
minStack.top();      --> 返回 0.  
minStack.getMin();   --> 返回 -2.  
 

提示：  

pop、top 和 getMin 操作总是在 非空栈 上调用。  
Discussion | Solution  

-----------------------

- 栈 + 变量 min 进行实现

![](../assets/images/chapter02/155-1.png)

![](../assets/images/chapter02/155-2.png)

![](../assets/images/chapter02/155-3.png)



--------------------

![](../assets/images/chapter02/155-4.png)

![](../assets/images/chapter02/155-5.png)

![](../assets/images/chapter02/155-6.png)


```c
/*
 * @Date: 2021-12-24 15:38:47
 * @Author: bFeng
 */
/*
 * @lc app=leetcode.cn id=155 lang=cpp
 *
 * [155] 最小栈
 */

// @lc code=start
// 栈 + 变量 min_
class MinStack {
public:
    MinStack() {

    }
    
    void push(int val) {
        if(data_.empty()){
            min_ = val;
        }
        if(min_ > val){
            min_ = val;
        }
        data_.push(val);
    }
    
    void pop() {
        if(data_.top() == min_){
            data_.pop();
            std::stack<int> tmp_stack;

            while( !data_.empty() ){ //把剩下的倒出来
                tmp_stack.push( data_.top());
                data_.pop();
            }

            while ( !tmp_stack.empty() ){ //再调用自己的函数，装回去
                this->push(tmp_stack.top());
                tmp_stack.pop();
            }
        }else{
            data_.pop();
        }
    }
    
    int top() {
        return data_.top();
    }
    
    int getMin() {
        return min_;
    }
private:
    std::stack<int> data_;
    int min_ ;
};



// 栈 + 栈 min_
class MinStack {
public:
    MinStack() {

    }
    
    void push(int val) {
        data_.push(val);
        if(!min_.empty() && val > min_.top()){
            val = min_.top();
        }
        min_.push(val);//如果min_为空就直接添加进去
    }
    
    void pop() {
        data_.pop();
        min_.pop();
    }
    
    int top() {
        return data_.top();
    }
    
    int getMin() {
        return min_.top();
    }
private:
    std::stack<int> data_;
    std::stack<int> min_;
};


/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */
// @lc code=end


```

---

验证栈序列  
Category	Difficulty	Likes	Dislikes  
algorithms	Medium (62.78%)	213	-  
Tags  
Companies  
给定 pushed 和 popped 两个序列，每个序列中的 值都不重复，只有当它们可能是在最初空栈上进行的推入 push 和弹出 pop 操作序列的结果时，返回 true；否则，返回 false 。  

 
  
示例 1：  

输入：pushed = [1,2,3,4,5], popped = [4,5,3,2,1]  
输出：true  
解释：我们可以按以下顺序执行：  
push(1), push(2), push(3), push(4), pop() -> 4,  
push(5), pop() -> 5, pop() -> 3, pop() -> 2, pop() -> 1  
示例 2：  

输入：pushed = [1,2,3,4,5], popped = [4,3,5,1,2]  
输出：false  
解释：1 不能在 2 之前弹出。  
 

提示：  

1 <= pushed.length <= 1000  
0 <= pushed[i] <= 1000  
pushed 的所有元素 互不相同  
popped.length == pushed.length  
popped 是 pushed 的一个排列  
Discussion | Solution  

--------------------------------


- 栈 +  队列  进行解题


![](../assets/images/chapter02/946-1.png)


![](../assets/images/chapter02/946-2.png)


![](../assets/images/chapter02/946-3.png)


![](../assets/images/chapter02/946-4.png)


![](../assets/images/chapter02/946-5.png)


![](../assets/images/chapter02/946-6.png)


![](../assets/images/chapter02/946-7.png)


![](../assets/images/chapter02/946-8.png)


![](../assets/images/chapter02/946-9.png)

![](../assets/images/chapter02/946-10.png)

-----------------------
```c
/*
 * @Date: 2021-12-24 23:55:17
 * @Author: bFeng
 */
/*
 * @lc app=leetcode.cn id=946 lang=cpp
 *
 * [946] 验证栈序列
 */

// @lc code=start
class Solution {
public:
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        std::stack<int> data_stack;
        std::queue<int> data_queue;

        for(const auto& itr : popped){
            data_queue.push(itr);
        }

        for(auto& itr : pushed){
            data_stack.push(itr);
            // 特别注意 pop之前一定要判断是否为空 不然会段错误
            while(!data_stack.empty()&&!data_queue.empty() &&data_queue.front() == data_stack.top()){
                data_stack.pop();
                data_queue.pop();
            }
        }

        if( data_queue.empty() && data_stack.empty() ){
            return true;
        }
        return false;

    }
};
// @lc code=end


```