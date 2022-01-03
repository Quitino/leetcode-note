<!--
 * @Date: 2021-12-22 13:58:43
 * @Author: bFeng
-->
# leetcode

- 笔记，供自己回顾。

##  1.参考链接

- [基础概念参考](https://www.runoob.com/data-structures/data-structures-tutorial.html)

##  2.心得

- 在二分查找，排序数组查找，二叉搜索树查找等已经排好序的查找问题中，经常会遇到 `if(target < nums[mid])`  这类的比较，这种情形就把 `target`放左边，思维上可以很快的定位到 `target` 是在左边还是右边，可以提高思维速度。

* DFS需要终止遍历时，函数就定义为 bool 型。