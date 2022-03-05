<!--
 * @Date: 2022-03-04 10:26:17
 * @Author: bFeng
-->


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

![](../pic/4.jpg)

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