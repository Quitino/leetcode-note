---
title: 第13章 九日集训
nav_order: 14
---

##  1.两整数之和  
a+b可以转换为 「不带进位的加法运算」+ 「带进位的加法运算」

![](../assets/images/chapter13/04.png)

不带进位：  
![](../assets/images/chapter13/05.png)


带进位：  

![](../assets/images/chapter13/06.png)  
![](../assets/images/chapter13/07.png)  


使用递归运算，递归出口：

![](../assets/images/chapter13/08.png)

```
- a=0,  a^b + (a&b)<<1 = 0^b + 0 = b
- b=0,  a^b + (a&b)<<1 = a^0 + 0 = a
- 所以出口可以直接定义为 
  b == 0; return a; 
  b != 0; return a^b + (a&b)<<1;
```


```c
int getSum(int a, int b) {
  return b == 0 ? a : getSum(a^b, (unsigned int)(a&b)<<1);
}
```
非递归版本
```c
class Solution {
 public:
  int add(int a, int b) {
    //因为不允许用+号，所以求出异或部分和进位部分依然不能用+
    //号，所以只能循环到没有进位为止
    while (b != 0) {
      //保存进位值，下次循环用
      int c = (unsigned int)(a & b) << 1;  // C++中负数不支持左移位，因为结果是不定的
      //保存不进位值，下次循环用，
      a ^= b;
      //如果还有进位，再循环，如果没有，则直接输出没有进位部分即可。
      b = c;
    }
    return a;
  }
};
```

##  2.乘法


a×b看成十进制下的a×二进制下的b，把b按照二进制下的位拆开，用加法代替乘法

```c
class Solution {
public:
    void mul(int&ans,long long a,long long b){
        if(b==0) return; // 终止递归
        if(b&1) ans+=a;  // 选中
        mul(ans,a+a,b>>1);
    }
    int multiply(int A, int B) {
        int ans=0;
        mul(ans,A,B);
        return ans;
    }
};
```

![](../assets/images/chapter13/11.png)


```c
class Solution {
public:
  void multiply(int A, int B) {
    int ret = 0;
    while (b) {
      if (b & 1) {
        ret = ret + a;
      }
      a *= 2;
      b >>= 1;
    }
  }
};
```

- $a \times b=C_{k-1} * a+2^{k-1}+C_{k-2} * a * 2^{k-2}+\cdots+C_{0}*a*2^{0}$
- $3 * 6=1 * 3 * 4+1 * 3 * 2+0 * 3 * 1=18$

**Solution.multiply(3, 6):  6个3相加**
- $(6)_2 = 110$  
- a = 3, b = 6
- ret = 0


人为理解的逻辑顺序:

1. 乘数$2^0$ , b & 1 = 0 (未选中): 计算 $a*2^0 = 3*1 = 1$
2. 乘数$2^1$ , b & 1 = 1 (选中):  计算$a*2^1 = 3*2 = 6$; $ret = ret + 6 = 6$
3. 乘数$2^2$ , b & 1 = 1 (选中):  计算$a*2^2 = 3*4 = 12$; $ret = ret + 12 = 18$
4. 乘数$2^3$ , b & 1 = 0 (未选中): 计算$a*2^3$;

计算 a 时，可以使用迭代：

0. $a = a * 2^0 = a = 3$
1. 乘数$2^0$ , b & 1 = 0 (未选中): --- , 计算 $a*2^1$ --> $a = a*2 = 6$
2. 乘数$2^1$ , b & 1 = 1 (选中): $ret=ret+a=0+6=6$, 计算$a*2^2$--> $a = a*2 = 12$
3. 乘数$2^2$ , b & 1 = 1 (选中): $ret=ret+a=6+12=18$, 计算$a*2^3$--> $a = a*2 = 24$
4. 乘数$2^3$ , b & 1 = 0 (退出循环)


##  3.两数相除  
给定两个整数，被除数 dividend 和除数 divisor。将两数相除，要求不使用乘法、除法和 mod 运算符。

返回被除数 dividend 除以除数 divisor 得到的商。

整数除法的结果应当截去（truncate）其小数部分，例如：truncate(8.345) = 8 以及 truncate(-2.7335) = -2

 

示例 1:  
输入: dividend = 10, divisor = 3  
输出: 3  
解释: 10/3 = truncate(3.33333..) = truncate(3) = 3  


示例 2:  
输入: dividend = 7, divisor = -3  
输出: -2  
解释: 7/-3 = truncate(-2.33333..) = -2  
 

提示：

被除数和除数均为 32 位有符号整数。   
除数不为 0。  
假设我们的环境只能存储 32 位有符号整数，其数值范围是 [−2^31,  2^31 − 1]。本题中，如果除法结果溢出，则返回 2^31 − 1。


思路：  
![](../assets/images/chapter13/2.jpg)

```c
class Solution {
public:
    int divide(int dividend, int divisor) {
        // 最高位 0代表正数，1代表负数
        int sign = ((dividend ^ divisor) >> 31 & 0x1 == 1) ? -1 : 1;
        // 转换为 long 防止越界
        long dividend_long = abs((long)dividend);
        long divisor_long = abs((long)divisor);
        long cnt = 0;
        while(dividend_long >= divisor_long) {
            long i = 1;
            long tmp = divisor_long;
            while(dividend_long >= tmp) {
                dividend_long -= tmp;
                cnt += i; //统计作差的次数
                i <<= 1;      //步长加倍
                tmp <<= 1;
            }
        }

        cnt *= sign; // 加上符号位
        if(cnt > INT_MAX || cnt < INT_MIN) { // 检查是否越界
            return INT_MAX;
        }
        return (int)cnt;
    }
};
```



##  4.Pow(x, n)

- [参考](https://www.bilibili.com/video/BV1i44y1q7ck?from=search&seid=3443053821312317981&spm_id_from=333.337.0.0)

实现 pow(x, n) ，即计算 x 的 n 次幂函数（即，xn ）。


内存爆炸

```c
class Solution {
public:
    double myPow(double x, int n) {
        // 最高位 0代表正数，1代表负数
        int sign = (n >> 31 & 0x1 == 1) ? 1 : 0;
        if(sign == 1) {
            n = abs(n);
            x = 1.0/x;
        }
        return myPow_internal(x, n);
    }
private:
    double myPow_internal(double x, int n) {
        if(n==1) return x;
        return x * myPow(x, n-1);
    }
};
```


暴力法，超时

```c
class Solution {
public:
    double myPow(double x, int n) {
        // 最高位 0代表正数，1代表负数
        int sign = (n >> 31 & 0x1 == 1) ? 1 : 0;
        if(sign == 1) {
            n = abs(n);
            x = 1.0/x;
        }
        double res = 1;
        while(n--){
            res *= x;
        }
        return res;
    }
};
```


快速幂-1

![](../assets/images/chapter13/3.jpg)

```c
class Solution {
public:
    double myPow(double x, int n) {
        if(n==0 || x==1) {
            return 1;
        }
        if(n < 0) {
            n = abs(n);
            x = 1.0/x;
        }
        return myPow_internal(x,n);
    }
private:
    double myPow_internal(double x, int n) {
        if(n==1) return x;
        if(n & 1) { // 奇数
            double half_val = myPow_internal(x, n/2);
            return half_val * half_val * x;
        } else {
            double half_val = myPow_internal(x, n/2);
            return half_val * half_val;
        }
    }
};
```



快速幂-2

![](../assets/images/chapter13/09.png)
![](../assets/images/chapter13/10.png)

```c
class Solution {
 public:
  double myPow(double x, int n) {
    if (n >= 0)
      return myPow_internal(x, (long long)n);
    else
      return 1.0 / myPow_internal(x, -(long long)n);
  }

 private:
  double myPow_internal(double a, long long n) {
    double res = 1.0;
    while (n) {
      // 判断 n 二进制最右一位是否为 1
      if (n & 1) {
        res *= a;
      }
      a *= a;
      // n 右移一位
      n >>= 1;
    }
    return res;
  }
};
```

- 指数：$\mathrm{b}=C_{k-1} * 2^{k-1}+C_{k-2} * 2^{k-2}+\cdots+C_{0} * 2^{0}$
- $6=1 * 2^{2}+1 * 2^{1}+0 * 2^{0}$
- $a^{b}=a^{C_{k-1} * 2^{k-1}}+C_{k-2} * 2^{k-2}+\cdots+C_{0} * 2^{0}=a^{C_{k-1} * 2^{k-1}} * a^{C_{k-2} * 2^{k-2}} * \ldots * a^{C_{0} * 2^{0}}$
- $3^{6}=3^{4} * 3^{2}=729$

**Solution.myPow(3, 6):  6个3相乘**
- $(6)_2 = 110$  
- a = 3, b = 6
- ret = 1


人为理解的逻辑顺序:

1. 指数$2^0$ , b & 1 = 0 (未选中): 计算 $a^{2^0} = 3^1 = 3$
2. 指数$2^1$ , b & 1 = 1 (选中):  计算$a^{2^1} = 3^2 = 9$; $ret = ret * 9 = 9$
3. 指数$2^2$ , b & 1 = 1 (选中):  计算$a^{2^2} = 3^4 = 81$; $ret = ret * 81 = 729$
4. 指数$2^3$ , b & 1 = 0 (未选中): 计算$a^{2^3}$;

计算 a 时，可以使用迭代：

0. $a = a ^ {2^0} = a^1 = 3$
1. 指数$2^0$ , b & 1 = 0 (未选中): --- , 计算 $a^{2^1}$ --> $a = a^2 = 9$
2. 指数$2^1$ , b & 1 = 1 (选中): $ret=ret*a=1*9=9$, 计算$a^{2^2}$--> $a = a^2 = 81$
3. 指数$2^2$ , b & 1 = 1 (选中): $ret=ret*a=81*9=729$, 计算$a^{2^3}$--> $a = a^2 = 6561$
4. 指数$2^3$ , b & 1 = 0 (退出循环)


- [阅读](https://blog.csdn.net/qq_43827595/article/details/106157681)


##  7.mySqrt



- 二分法


```c
class Solution {
public:
  int mySqrt(int x) {
      if(x==0) return 0;
      if(x==1) return 1;
      int left = 0, right = x, res = -1;
      while(left <= right) {
          int mid = left + 0.5 * (right - left);
          if((long long)mid*mid <= x) {
            res = mid;
            left = mid + 1;  
          } else {
            right = mid - 1;
          }
      }
      return (int)res;
  }
};
```

##  8.maximum

找出两个数字a和b中最大的那一个。不得使用if-else或其他比较运算符。

max = (a + b + abs(a - b)) / 2

```c
class Solution {
public:
  int maximum(int a, int b) {
    long diff = abs((long)a - (long)b);
    return (long)((long)a + (long)b + diff) / 2;
  }
};
```

##  9.反转两次的数字

反转 一个整数意味着倒置它的所有位。

例如，反转 2021 得到 1202 。反转 12300 得到 321 ，不保留前导零 。给你一个整数 num ，反转 num 得到 reversed1 ，接着反转 reversed1 得到 reversed2 。如果 reversed2 等于 num ，返回 true ；否则，返回 false 。


```c
class Solution {
public:
    bool isSameAfterReversals(int num) {
        if(num == 0) return true;
        if(num % 10 == 0) return false;
        return true;
    }
};
```

```c
class Solution {
public:
    bool isSameAfterReversals(int num) {
        return num == 0 || num % 10 != 0;
    }
};
```

---

## 1.1+2+...+n
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

##  2. isPowerOfTwo

![](../assets/images/chapter13/4.jpg)

位运算相关性质。

```c
class Solution {
public:
    bool isPowerOfTwo(int n) {
         return (n > 0 && (n & (n - 1)) == 0);
    }
};
```

##  3.isPowetrOfThree


hash表实现

```c
class Solution {
public:
    Solution(){
        int power_of_three = 1;
        hash_set_.insert(power_of_three);
        while(power_of_three <= std::numeric_limits<int>::max() / 3) {
            power_of_three *= 3;
            hash_set_.insert(power_of_three);
        }
    }
    bool isPowerOfThree(int n) {
        return n > 0 && hash_set_.find(n) != hash_set_.end();
    }
private:
    unordered_set<int> hash_set_;
};
```

##  4.isPowerOfFour

如果 n 是 4 的幂，那么它可以表示成 $4^x$的形式，我们可以发现它除以 3 的余数一定为 1，即：

$$4^x \equiv (3+1)^x \equiv 1^x \equiv 1 \quad (\bmod ~3)$$

如果 n 是 2 的幂却不是 4 的幂，那么它可以表示成 $4^x \times 2$的形式，此时它除以 3 的余数一定为 2。

因此我们可以通过 n 除以 3 的余数是否为 1 来判断 n 是否是 4 的幂。


```c
class Solution {
public:
    bool isPowerOfFour(int n) {
        return n > 0 && (n & (n - 1)) == 0 && n % 3 == 1;
    }
};
```


##  5.kthFactor

- n 的第k个因子

给你两个正整数 n 和 k 。

如果正整数 i 满足 n % i == 0 ，那么我们就说正整数 i 是整数 n 的因子。

考虑整数 n 的所有因子，将它们 升序排列 。请你返回第 k 个因子。如果 n 的因子数少于 k ，请你返回 -1 。

 

示例 1：  
输入：n = 12, k = 3  
输出：3  
解释：因子列表包括 [1, 2, 3, 4, 6, 12]，第 3 个因子是 3 。  


示例 2：  
输入：n = 7, k = 2  
输出：7  
解释：因子列表包括 [1, 7] ，第 2 个因子是 7 。  


示例 3：  
输入：n = 4, k = 4  
输出：-1  
解释：因子列表包括 [1, 2, 4] ，只有 3 个因子，所以我们应该返回 -1 。  


```c
class Solution {
public:
    int kthFactor(int n, int k) {
        int cnt = 0;
        for(int i = 1; i <= n; ++i) {
            if(n % i == 0) {
                cnt ++;
                if(cnt == k) {
                    return i;
                }
            }
        }
        return -1;
    }
};
```

##  6.isPerfectSquare


给定一个 正整数 num ，编写一个函数，如果 num 是一个完全平方数，则返回 true ，否则返回 false 。

进阶：不要 使用任何内置的库函数，如  sqrt 。

 

示例 1：  
输入：num = 16  
输出：true  


示例 2：  
输入：num = 14  
输出：false  


我们知道对于一个完全平方数而言，可以写成如下形式：

$$num = n^2 = 1 + 3 + 5 + ... + (2 * n - 1)$$

因此另外一种做法是对 num 进行不断的奇数试减，如果最终能够减到 000，说明 num 可展开成如 $1+3+5+...+(2∗n−1)$ 的形式， num 为完全平方数。


```c
class Solution {
public:
    bool isPerfectSquare(int num) {
        int x = 1;
        while (num > 0) {
            num -= x;
            x += 2;
        }
        return num == 0;
    }
};
```

---

##  1.搜索旋转排序数组

递归，实现复杂了

```c
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
};
```

##  2.搜索旋转排序数组II


同样使用二分法

```c
class Solution {
public:
    bool search(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size() - 1;

        while(left <= right){
            int mid = left + (right-left)/2;
            if(nums[mid] == target) return true;
            if(nums[left] == nums[right] && 
               nums[left] == nums[mid]) {
              left ++, right --;
              continue;
            }
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
        return false;
    }
};
```

##  3.寻找旋转排序数组中的最小值



```c
class Solution {
public:
    int findMin(vector<int>& nums) {
      int left = 0, right = nums.size()-1;
      int min = nums[0]; // 记录最小值
      while(left <= right) {
        int mid = left + (right - left) / 2;
        if(nums[left] <= nums[mid]) { // 左边有序
          min = nums[left] < min ? nums[left] : min;
          left = mid + 1;
        } else { // 右边有序
          min = nums[mid] < min ? nums[mid] : min;
          right = mid - 1;
        }
      }
      return min;
    }
};
```

 - [阅读](https://leetcode-cn.com/problems/find-minimum-in-rotated-sorted-array/solution/xun-zhao-xuan-zhuan-pai-xu-shu-zu-zhong-5irwp/)

## 4.爬楼梯

![](../assets/images/chapter13/5.jpg)

```c
class Solution {
public:
    int climbStairs(int n) {
        int p = 0, q = 0, r = 1;
        for (int i = 1; i <= n; ++i) {
            p = q; 
            q = r; 
            r = p + q;
        }
        return r;
    }
};
```


##  5.斐波那契数

先简单递归实现吧

```c
class Solution {
public:
    int fib(int n) {
      if (n == 0) return 0;
      if (n == 1) return 1;
      return fib(n-1) + fib(n-2);
    }
};
```

##  6.第 N 个泰波那契数


同样使用递归简单实现
```c
class Solution {
public:
    int tribonacci(int n) {
      if(n == 0) return 0;
      if (n == 1 || n == 2) return 1;
      return tribonacci(n-1) + tribonacci(n-2) + tribonacci(n-3);
    }
};
```
递归实现超时，改为自上而下的计算避免重复计算

```c
class Solution {
public:
int tribonacci(int n) {
  if (n == 0) return 0;
  if (n == 1 || n == 2) return 1;
  int a = 0, b = 1, c = 1;
  for (int i = 3; i <= n; i++) {
      int d = a + b + c;
      a = b;
      b = c;
      c = d;
  }
  return c;
}
};
```

##  7.差的绝对值为 K 的数对数目


##  8.猜数字

##  9.拿硬币

##  10.山峰数组的顶部

---

##  1.重新排列数组

- [1470-重新排列数组](https://leetcode-cn.com/problems/shuffle-the-array/)

![](../assets/images/chapter13/6.jpg)

和教练博客中的函数头不同：

```c
class Solution {
public:
    vector<int> shuffle(vector<int>& nums, int n) {
      std::vector<int> res(nums.size());
      for(int i = 0; i < nums.size(); ++i) {
        if(i & 1) { // 新索引为奇数
          res[i] = nums[n + i/2];
        } else {    // 新索引为偶数
          res[i] = nums[i/2];
        }
      }
      return res;
    }
};
```

教练：

```c
/**
Note: The returned array must be malloced, assume caller calls free().  // (1)
 */
int* shuffle(int* nums, int numsSize, int n, int* returnSize)           // (2)
    int i;
    int *ret = (int *)malloc( sizeof(int) * numsSize );                 // (3)
    for(i = 0; i < numsSize; ++i) {                                     // (4)
        if(i & 1) {
            ret[i] = nums[n + i/2];
        }else {
            ret[i] = nums[(i+1)/2];
        }
    }
    *returnSize = numsSize;                                             // (5)
    return ret;                                                         // (6)
}
```


##  2.数组串联

- [1929-数组串联](https://leetcode-cn.com/problems/concatenation-of-array/)

同样和教练的函数头不一样。

```c
class Solution {
public:
    vector<int> getConcatenation(vector<int>& nums) {
      std::vector<int> res;
      
      for (int i = 0; i < nums.size(); ++i) 
        res.push_back(nums[i]);
      for (int i = 0; i < nums.size(); ++i) 
        res.push_back(nums[i]);

      return res;      
    }
};
```

```c
class Solution {
public:
    vector<int> getConcatenation(vector<int>& nums) {
      int n = nums.size();
      std::vector<int> res(2*n);

      for (int i = 0; i < n; ++i) {
        res[i] = nums[i];
        res[i + n] = nums[i];
      }

      return res;      
    }
};
```

英雄：

```/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* getConcatenation(int* nums, int numsSize, int* returnSize){
    int i;
    int *ret = (int *)malloc(2*numsSize*sizeof(int)); // (1)
    for(i = 0; i < numsSize; ++i) {
        ret[i+numsSize] = ret[i] = nums[i];           // (2)
    }
    *returnSize = 2 * numsSize;                       // (3) 
    return ret;
}
```


##  3.基于排列构建数组

- [1920. 基于排列构建数组](https://leetcode-cn.com/problems/build-array-from-permutation/)

同样和教练的函数头不一样。


```c
class Solution {
public:
    vector<int> buildArray(vector<int>& nums) {
      std::vector<int> res(nums.size());
      for(int i = 0; i < nums.size(); ++i) {
        res[i] = nums[nums[i]];
      }
      return res;
    }
};
```

英雄：

```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* buildArray(int* nums, int numsSize, int* returnSize){
    int i;
    int *ret = (int *)malloc( sizeof(int) * numsSize );
    for(i = 0; i < numsSize; ++i) {
        ret[i] =  nums[  nums[i] ];           // (1)
    }
    *returnSize = numsSize;
    return ret;
}

```

##  4.一维数组的动态和

- [1480. 一维数组的动态和](https://leetcode-cn.com/problems/running-sum-of-1d-array/)

同样和教练的函数头不一样。


```c
class Solution {
public:
    vector<int> runningSum(vector<int>& nums) {
      std::vector<int> res(nums.size());
      for(int i = 0; i < nums.size(); ++i) {
        int tmp = 0;
        for(int j = 0; j <= i; ++j) {
          tmp += nums[j];
        }
        res[i] = tmp;
      }
      return res;
    }
};
```

迭代思维：

```c
class Solution {
public:
    vector<int> runningSum(vector<int>& nums) {
      std::vector<int> res(nums.size());
      res[0] = nums[0];
      for(int i = 1; i < nums.size(); ++i) {
        res[i] = res[i-1] + nums[i];
      }
      return res;
    }
};
```

如果允许改变传入参数的话：

```c
class Solution {
public:
    vector<int> runningSum(vector<int>& nums) {
        int n = nums.size();
        for (int i = 1; i < n; i++) {
            nums[i] += nums[i - 1];
        }
        return nums;
    }
};
```

英雄：

```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* runningSum(int* nums, int numsSize, int* returnSize){
    int i;
    int *ret = (int *)malloc( numsSize * sizeof(int) );
    for(i = 0; i < numsSize; ++i) {    // (1)
        ret[i] = nums[i];
        if(i) {
            ret[i] += ret[i-1];                      
        }
    }
    *returnSize = numsSize;
    return ret;
}

```

##  5.剑指 Offer 58 - II. 左旋转字符串

- [剑指 Offer 58 - II. 左旋转字符串](https://leetcode-cn.com/problems/zuo-xuan-zhuan-zi-fu-chuan-lcof/)

同样和教练的函数头不一样。


```c
class Solution {
public:
    string reverseLeftWords(string s, int n) {
      std::string res;
      res = s.substr(n, s.size()-1);
      res += s.substr(0, n);
      return res+'\0';
    }
};
```


英雄：

```c
char* reverseLeftWords(char* s, int k){
    int i;
    int n = strlen(s);
    char *ret = (char *)malloc( (n + 1) * sizeof(char) );    // (1)
    for(i = 0; i < n; ++i) {
        ret[i] = s[(i + k) % n];                             // (2)
    }
    ret[n] = '\0';                                           // (3)
    return ret;
}
```

##  6.IP 地址无效化


- [1108. IP 地址无效化](https://leetcode-cn.com/problems/defanging-an-ip-address/)


同样和教练的函数头不一样。


原地替换

```c
class Solution {
public:
    string defangIPaddr(string address) {
      int cnt_dot = 0;
      for(const auto& bit : address) {
        if (bit == '.') {
          cnt_dot ++;
        }
      }
      int p1 = address.size();
      int p2 = p1 + 2*cnt_dot;
      address.resize(p2);
      while (p1 < p2) {
        if(address[p1] == '.') {
          address[p2--] = ']';
          address[p2--] = '.';
          address[p2--] = '[';
          p1--;
        } else {
          address[p2--] = address[p1--];
        }
      }
      return address;
    }
};
```


##  7.替换空格


- [剑指 Offer 05. 替换空格](https://leetcode-cn.com/problems/ti-huan-kong-ge-lcof/)

和上一题一模一样

```c
class Solution {
public:
    string replaceSpace(string s) {
      int cnt_space = 0;
      for(const auto& bit : s) {
        if (bit == ' ') {
          cnt_space ++;
        }
      }
      int p1 = s.size();
      int p2 = p1 + 2*cnt_space;
      s.resize(p2);
      while (p1 < p2) {
        if(s[p1] == ' ') {
          s[p2--] = '0';
          s[p2--] = '2';
          s[p2--] = '%';
          p1--;
        } else {
          s[p2--] = s[p1--];
        }
      }
      return s;
    }
};
```


##  8.有多少小于当前数字的数字

-[1365. 有多少小于当前数字的数字](https://leetcode-cn.com/problems/how-many-numbers-are-smaller-than-the-current-number/)

```c
class Solution {
public:
    vector<int> smallerNumbersThanCurrent(vector<int>& nums) {
      std::vector<int> res(nums.size(), 0);
      for(int i = 0; i < nums.size(); ++i) {
        for (int j = 0; j < nums.size(); ++j) {
          if (j == i) continue;
          if (nums[j] < nums[i]) {
            res[i] ++;
          }
        }
      }
      return res;
    }
};
```


##  9.打印从1到最大的n位数


- [剑指 Offer 17. 打印从1到最大的n位数](https://leetcode-cn.com/problems/da-yin-cong-1dao-zui-da-de-nwei-shu-lcof/)

```c
class Solution {
public:
    vector<int> printNumbers(int n) {
      std::vector<int> res(pow(10,n)-1);
      for(int i = 0; i < res.size(); i++) {
        res[i] = i + 1;
      }
      return res;
    }
};
```

##  10.按既定顺序创建目标数组

- [1389. 按既定顺序创建目标数组](https://leetcode-cn.com/problems/create-target-array-in-the-given-order/)

```c
class Solution {
public:
    vector<int> createTargetArray(vector<int>& nums, vector<int>& index) {
        std::vector<int> res;
        if(nums.size() != index.size()) return res;
        // res.resize(nums.size());
        //  auto it = res.begin();
        for (int i = 0; i < nums.size(); ++i) {
          res.insert(res.begin() + index[i], nums[i]);
        }

        return res;
    }
};
```


##  11.总结

直到做完，才发现，英雄选择的语言是 `c`, 我选择的语言是 `c++`, 难怪函数头不一样，淦。