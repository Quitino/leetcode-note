---
title: 第08章 哈希表
nav_order: 9
---

最长回文串  
Category	Difficulty	Likes	Dislikes  
algorithms	Easy (55.58%)	367	-  
Tags  
hash-table  

Companies  
google  

给定一个包含大写字母和小写字母的字符串，找到通过这些字母构造成的最长的回文串。  

在构造过程中，请注意区分大小写。比如 "Aa" 不能当做一个回文字符串。  

注意:  
假设字符串的长度不会超过 1010。  

示例 1:  

输入:  
"abccccdd"  

输出:  
7  

解释:    
我们可以构造的最长的回文串是"dccaccd", 它的长度是 7。  
Discussion | Solution  

-----------------------------------

![](../assets/images/chapter08/409-1.png)

![](../assets/images/chapter08/409-2.png)

![](../assets/images/chapter08/409-3.png)

![](../assets/images/chapter08/409-4.png)

![](../assets/images/chapter08/409-5.png)

![](../assets/images/chapter08/409-6.png)

![](../assets/images/chapter08/409-7.png)



```c
/*
 * @lc app=leetcode.cn id=409 lang=cpp
 *
 * [409] 最长回文串
 */

// @lc code=start
//-------------自己实现--------
class Solution {
public:
    int longestPalindrome(std::string s) {
        int cnt_map[128] = {0};
        for (const auto& i : s){
            cnt_map[i] ++;
        }
        bool hasOdd = false;
        int res = 0;
        for(int i=0; i<128; i++){
            if(cnt_map[i]%2){//奇数
                hasOdd = true;
                res += (cnt_map[i]-1);
            }else{
                res += cnt_map[i];
            }
        }
        if(hasOdd) return res+1;
        return res;
    }
};
// @lc code=end


```

---

单词规律  
Category	Difficulty	Likes	Dislikes  
algorithms	Easy (45.56%)	415	-  
Tags  
Companies  
给定一种规律 pattern 和一个字符串 str ，判断 str 是否遵循相同的规律。  

这里的 遵循 指完全匹配，例如， pattern 里的每个字母和字符串 str 中的每个非空单词之间存在着双向连接的对应规律。

示例1:  
输入: pattern = "abba", str = "dog cat cat dog"  
输出: true  


示例 2:  
输入:pattern = "abba", str = "dog cat cat fish"  
输出: false  

示例 3:  
输入: pattern = "aaaa", str = "dog cat cat dog"  
输出: false

示例 4:  
输入: pattern = "abba", str = "dog dog dog dog"  
输出: false  


说明:  
你可以假设 pattern 只包含小写字母， str 包含了由单个空格分隔的小写字母。      

Discussion | Solution  

-------------------------

![](../assets/images/chapter08/290-1.png)

![](../assets/images/chapter08/290-2.png)

![](../assets/images/chapter08/290-3.png)

![](../assets/images/chapter08/290-4.png)

![](../assets/images/chapter08/290-5.png)

![](../assets/images/chapter08/290-6.png)

![](../assets/images/chapter08/290-7.png)

![](../assets/images/chapter08/290-8.png)

![](../assets/images/chapter08/290-9.png)





-------------------------


```c
/*
 * @lc app=leetcode.cn id=290 lang=cpp
 *
 * [290] 单词规律
 */

// @lc code=start
class Solution {
public:
    bool wordPattern(string pattern, string s) {
        std::vector<std::string> words;
        str2word(s, words);
        if(pattern.size() != words.size()) return false;
        // 双向检查，一个字母不能对应多个单词，一个单词也不能对应多个字母
        std::map<char, std::string> map_pw;
        std::map<std::string, char> map_wp;

        for(int i=0; i<pattern.size(); i++){
            if(map_pw.find(pattern[i]) != map_pw.end() 
                    && map_pw[pattern[i]] != words[i]){
                return false;
            }
            if(map_wp.find(words[i]) != map_wp.end() 
                    && map_wp[words[i]] != pattern[i]){
                return false;
            }

            map_pw[pattern[i]] = words[i];
            map_wp[words[i]] = pattern[i];
        }

    return true;
    }

private:
    void str2word(const std::string& str, std::vector<std::string>& words){
        if(str==""){
            words.push_back(str);
            return;
        }
        std::string word = "";
        for(const auto& ch : str){
            if(ch == ' ' && word != ""){
                words.push_back(word);
                word = "";
                continue;
            }
            word += ch;
        }
        words.push_back(word);// 注意保存最后一个单词
        // for debug
        for(const auto& str : words){
            std::cout<<str<<std::endl;
        }
        std::cout<<words.size()<<std::endl;
    }
};
// @lc code=end

```

---

重复的DNA序列  
Category	Difficulty	Likes	Dislikes  
algorithms	Medium (52.20%)	318	-  
Tags  
Companies  
所有 DNA 都由一系列缩写为 'A'，'C'，'G' 和 'T' 的核苷酸组成，例如："ACGAATTCCG"。在研究 DNA 时，识别 DNA 中的重复序列有时会对研究非常有帮助。  

编写一个函数来找出所有目标子串，目标子串的长度为 10，且在 DNA 字符串 s 中出现次数超过一次。  

 

示例 1：  
输入：s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT"  
输出：["AAAAACCCCC","CCCCCAAAAA"]  

示例 2：  
输入：s = "AAAAAAAAAAAAA"  
输出：["AAAAAAAAAA"]  
 

提示：  

0 <= s.length <= 105  
s[i] 为 'A'、'C'、'G' 或 'T'  
Discussion | Solution  

Code Now


------------------------------

![](../assets/images/chapter08/187-1.png)

![](../assets/images/chapter08/187-2.png)

![](../assets/images/chapter08/187-3.png)

![](../assets/images/chapter08/187-4.png)

![](../assets/images/chapter08/187-5.png)

![](../assets/images/chapter08/187-6.png)

![](../assets/images/chapter08/187-7.png)

![](../assets/images/chapter08/187-8.png)







---------------------------------


```c
/*
 * @lc app=leetcode.cn id=187 lang=cpp
 *
 * [187] 重复的DNA序列
 */

// @lc code=start
// ------------主要思想在于滑动窗口----------
class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        const int WIN_LEN = 10;
        std::vector<std::string> all_str;
        std::vector<std::string> res_str;

        for(int i=0; i<s.size(); i++){
            if( i+WIN_LEN > s.size()) break;
            all_str.push_back(s.substr(i, WIN_LEN));
        }

        std::map<std::string, int> map_cnt;
        std::set<std::string> res_set;//利用set去重
        for(int i=0; i<all_str.size(); i++){
            if(map_cnt.find(all_str[i]) != map_cnt.end()){
                res_set.insert(all_str[i]);
            }
            map_cnt[all_str[i]] ++;
        }

        for(const auto& str : res_set){
            res_str.push_back(str);
        }
        return res_str;
    }
};
// @lc code=end


// -------------参考： 不需使用set去重，考察map的值就行, all_str也可以简化---------------
class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        const int WIN_LEN = 10;
        std::vector<std::string> res_str;
        std::map<std::string, int> map_cnt;

        for(int i=0; i<s.size(); i++){
            if( i+WIN_LEN > s.size()) break;
            map_cnt[s.substr(i, WIN_LEN)] ++;
        }

        for(const auto& str : map_cnt){
            if(str.second > 1){
                res_str.push_back(str.first);
            }
        }
        return res_str;
    }
};

```