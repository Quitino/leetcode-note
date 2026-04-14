---
title: 第10章 图与搜索
nav_order: 11
---

课程表   
Category	Difficulty	Likes	Dislikes   
algorithms	Medium (54.08%)	1069	-   
Tags   
depth-first-search | breadth-first-search | graph | topological-sort   

Companies   
apple | uber | yelp | zenefits   

你这个学期必须选修 numCourses 门课程，记为 0 到 numCourses - 1 。   

在选修某些课程之前需要一些先修课程。 先修课程按数组 prerequisites 给出，其中 prerequisites[i] = [ai, bi] ，表示如果要学习课程 ai 则 必须 先学习课程  bi 。   

例如，先修课程对 [0, 1] 表示：想要学习课程 0 ，你需要先完成课程 1 。   
请你判断是否可能完成所有课程的学习？如果可以，返回 true ；否则，返回 false 。    

 

示例 1：  
输入：numCourses = 2, prerequisites = \[[1,0]]  
输出：true   
解释：总共有 2 门课程。学习课程 1 之前，你需要完成课程 0 。这是可能的。   



示例 2：  
输入：numCourses = 2, prerequisites = \[[1,0],[0,1]]  
输出：false   
解释：总共有 2 门课程。学习课程 1 之前，你需要先完成​课程 0 ；并且学习课程 0 之前，你还应先完成课程 1 。这是不可能的。   
 

提示：   

1 <= numCourses <= 105   
0 <= prerequisites.length <= 5000   
prerequisites[i].length == 2   
0 <= ai, bi < numCourses   
prerequisites[i] 中的所有课程对 互不相同   
Discussion | Solution   

----------------------------------------------------

![](../assets/images/chapter10/207-1.png)

![](../assets/images/chapter10/207-2.png)

![](../assets/images/chapter10/207-3.png)

![](../assets/images/chapter10/207-4.png)

![](../assets/images/chapter10/207-5.png)

![](../assets/images/chapter10/207-6.png)

![](../assets/images/chapter10/207-7.png)

![](../assets/images/chapter10/207-8.png)

![](../assets/images/chapter10/207-9.png)

![](../assets/images/chapter10/207-10.png)

![](../assets/images/chapter10/207-11.png)

![](../assets/images/chapter10/207-12.png)

![](../assets/images/chapter10/207-13.png)

![](../assets/images/chapter10/207-14.png)

![](../assets/images/chapter10/207-15.png)

![](../assets/images/chapter10/207-16.png)

![](../assets/images/chapter10/207-17.png)

![](../assets/images/chapter10/207-18.png)

![](../assets/images/chapter10/207-19.png)

![](../assets/images/chapter10/207-20.png)

![](../assets/images/chapter10/207-21.png)

![](../assets/images/chapter10/207-22.png)

![](../assets/images/chapter10/207-23.png)

![](../assets/images/chapter10/207-24.png)

![](../assets/images/chapter10/207-25.png)

![](../assets/images/chapter10/207-26.png)

![](../assets/images/chapter10/207-27.png)

![](../assets/images/chapter10/207-28.png)

![](../assets/images/chapter10/207-29.png)

![](../assets/images/chapter10/207-30.png)

![](../assets/images/chapter10/207-31.png)

![](../assets/images/chapter10/207-32.png)

![](../assets/images/chapter10/207-33.png)

![](../assets/images/chapter10/207-34.png)

![](../assets/images/chapter10/207-35.png)

----------------------------------------------------

```c
/*
 * @lc app=leetcode.cn id=207 lang=cpp
 *
 * [207] 课程表
 */

// @lc code=start
class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        std::vector<GraphNode> graph = create_graph(numCourses, prerequisites);
        std::vector<int> visit(numCourses, -1);// 全部初始化为-1， 未访问
        for(int i=0; i<graph.size(); i++){
            // 当前node未访问，则开始访问并判断是否有环
            if(visit[i]==-1 && graph_has_circle(&graph[i],visit)){
                return false;// 有环，无法修完全部课程
            }
        }
        return true; // 无环，可以修完所有课程
    }

private:
    struct GraphNode{
        int label;
        std::vector<GraphNode*> neighbors;
    };
    /**
     * @description: 构建图 邻接表方式
     * @param {prereguisites}  
     *          [1, 0]  课程1 依赖 课程0
     *          [2, 0]  课程2 依赖 课程0
     *          [3, 1]  课程3 依赖 课程1
     *          [3, 2]  课程3 依赖 课程2
     */
    std::vector<GraphNode> create_graph(int numCourses,
                const std::vector<std::vector<int>>& prerequisites){
        std::vector<GraphNode> graph;
        // 初始化长度为课程数的表头
        for(int i=0; i<numCourses; i++){
            graph.push_back(GraphNode());
            graph[i].label = i;
        }
        /*
        * @return std::vector<GraphNode>
        * vector:   GraphNode_0-->GraphNode_1-->GraphNode_2
        * vector:   GraphNode_1-->GraphNode_3
        * vector:   GraphNode_2-->GraphNode_3
        * vector:   GraphNode_3
        */
        for(int i=0; i<prerequisites.size(); i++){
            // prerequisites[i] 只有二维
            // 边起始节点指针begin, 注意是 [i][1]-->[i][0]
            GraphNode* begin = &graph[prerequisites[i][1]];
            // 边结束节点指针end
            GraphNode* end = &graph[prerequisites[i][0]];
            begin->neighbors.push_back(end);
        }
        return graph;
    }

    /**
     * @description: 
     * @param {GraphNode*} node 
     * visit[]  -1 未访问 0 正在访问  1 已完成访问 
     * @return {*}
     */    
    bool graph_has_circle(GraphNode* node, std::vector<int>& visit){
        visit[node->label] = 0;// 正在访问的节点状态标记为0
        // 遍历与 node 相邻的节点
        for(int i=0; i<node->neighbors.size(); i++){
            // 如果相邻的节点还未访问
            if(visit[node->neighbors[i]->label] == -1){
                // 则递归搜索该节点，如果递归结果返回true，说明后面遇到了环
                if(graph_has_circle(node->neighbors[i], visit)){
                    return true;//则当前的函数也返回true
                }
            // 如果相邻的节点状态是正在访问，说明此时遇到了环，返回true
            }else if(visit[node->neighbors[i]->label] == 0){
                return true;
            }
        }
        // 如果node节点全部完成了访问没有遇到环，则将状态置为 1 ，返回false
        visit[node->label] = 1;
        return false;
    }

};
// @lc code=end

```

---

单词接龙
Category	Difficulty	Likes	Dislikes  
algorithms	Hard (47.13%)	926	-  
Tags  
breadth-first-search  

Companies  
amazon | facebook | linkedin | snapchat | yelp  

字典 wordList 中从单词 beginWord 和 endWord 的 转换序列 是一个按下述规格形成的序列：  

序列中第一个单词是 beginWord 。  
序列中最后一个单词是 endWord 。   
每次转换只能改变一个字母。  
转换过程中的中间单词必须是字典 wordList 中的单词。  
给你两个单词 beginWord 和 endWord 和一个字典 wordList ，找到从 beginWord 到 endWord 的 最短转换序列 中的 单词数目 。  如果不存在这样的转换序列，返回 0。  

 
示例 1：  
输入：beginWord = "hit", endWord = "cog", wordList = \["hot","dot","dog","lot","log","cog"]  
输出：5  
解释：一个最短转换序列是 "hit" -> "hot" -> "dot" -> "dog" -> "cog", 返回它的长度 5。  



示例 2：  
输入：beginWord = "hit", endWord = "cog", wordList = \["hot","dot","dog","lot","log"]  
输出：0  
解释：endWord "cog" 不在字典中，所以无法进行转换。  
 

提示：  

1 <= beginWord.length <= 10  
endWord.length == beginWord.length  
1 <= wordList.length <= 5000  
wordList[i].length == beginWord.length  
beginWord、endWord 和 wordList[i] 由小写英文字母组成  
beginWord != endWord  
wordList 中的所有字符串 互不相同  
Discussion | Solution  

--------------------------------------

![](../assets/images/chapter10/127-1.png)

![](../assets/images/chapter10/127-2.png)

![](../assets/images/chapter10/127-3.png)

![](../assets/images/chapter10/127-4.png)

![](../assets/images/chapter10/127-5.png)

![](../assets/images/chapter10/127-6.png)

![](../assets/images/chapter10/127-7.png)

![](../assets/images/chapter10/127-8.png)

![](../assets/images/chapter10/127-9.png)

![](../assets/images/chapter10/127-10.png)

![](../assets/images/chapter10/127-11.png)

![](../assets/images/chapter10/127-12.png)

![](../assets/images/chapter10/127-13.png)

![](../assets/images/chapter10/127-14.png)

![](../assets/images/chapter10/127-15.png)

![](../assets/images/chapter10/127-16.png)

![](../assets/images/chapter10/127-17.png)

![](../assets/images/chapter10/127-18.png)

![](../assets/images/chapter10/127-19.png)

![](../assets/images/chapter10/127-20.png)

![](../assets/images/chapter10/127-21.png)

![](../assets/images/chapter10/127-22.png)

![](../assets/images/chapter10/127-23.png)

![](../assets/images/chapter10/127-24.png)

![](../assets/images/chapter10/127-25.png)

![](../assets/images/chapter10/127-26.png)

![](../assets/images/chapter10/127-27.png)

![](../assets/images/chapter10/127-28.png)

![](../assets/images/chapter10/127-29.png)

![](../assets/images/chapter10/127-30.png)

![](../assets/images/chapter10/127-31.png)

![](../assets/images/chapter10/127-32.png)

![](../assets/images/chapter10/127-33.png)

--------------------------------------

```c
/*
 * @lc app=leetcode.cn id=127 lang=cpp
 *
 * [127] 单词接龙
 */

// @lc code=start
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        map<string, vector<string>> graph;
        build_graph(beginWord, wordList, graph);
        return BFS_graph(beginWord, endWord, graph);
    }

private:
    bool connect(const string& w1, const string& w2){
        int count = 0;// 单词相差的字母个数
        for(int i=0; i<w1.length(); i++){
            if(w1[i] != w2[i]){
                count ++;
            }
        }
        return count == 1;
    }
    /**
     * @description:  建图
     * @param {begin} 其实单词
     * @param {wordList} 存储字典单词列表
     * @return {graph} 图邻接表
     */    
    void build_graph(std::string& begin,
                std::vector<std::string>& wordList,
                std::map<string, std::vector<string>>& graph){
        wordList.push_back(begin);// 将起始节点添加到wordList中
        // 通过循环，将每个顶点单词对应一个空的vector，构建一个空的图
        for(int i=0; i<wordList.size(); i++){
            graph[wordList[i]] = std::vector<string>();
        }
        // 遍历图中每一个顶点单词
        for(int i=0; i<wordList.size(); i++){
            // 对于每个单词都和其他单词计算相差的字符数
            for(int j=0; j<wordList.size(); j++){
                if(connect(wordList[i], wordList[j])){
                    // 建立边
                    graph[wordList[i]].push_back(wordList[j]);
                    graph[wordList[j]].push_back(wordList[i]);
                }
            }
        }
    }
    /**
     * @description: BFS
     * @param {begin, end} 起始节点与终止节点
     * @param {graph} 图的邻接表
     * @return {*}
     */
    int BFS_graph(string& begin, string &end,
        map<string,vector<string>>& graph){
            // 存储顶点单词与到达不熟的pair对
            queue<pair<string,int>> Q;
            set<string> visit;// 标记已进入队列的顶点单词
            Q.push(make_pair(begin,1));
            visit.insert(begin);
            while(!Q.empty()){//只要队列不空，就循环搜索
                // 取出待搜索单词word与到达待搜索单词的不熟step
                string word = Q.front().first;
                int step = Q.front().second;
                Q.pop();

                // 如果word与结束单词end相同
                if(word == end){
                    return step;
                }
                // 获取与word对应的邻接表
                const vector<string>& neighbors = graph[word];
                // 遍历邻接表中的单词
                for(int i=0; i<neighbors.size(); i++){
                    // 如果单词没有在visit中
                    if(visit.find(neighbors[i]) == visit.end() ){
                        Q.push(make_pair(neighbors[i], step+1));
                        visit.insert(neighbors[i]);                   
                    }
                }
            }
            return 0;
        }
};
// @lc code=end


```

---

岛屿数量   
Category	Difficulty	Likes	Dislikes   
algorithms	Medium (56.35%)	1480	-   
Tags   
depth-first-search | breadth-first-search | union-find   

Companies   
amazon | facebook | google | microsoft | zenefits   

给你一个由 '1'（陆地）和 '0'（水）组成的的二维网格，请你计算网格中岛屿的数量。   

岛屿总是被水包围，并且每座岛屿只能由水平方向和/或竖直方向上相邻的陆地连接形成。   

此外，你可以假设该网格的四条边均被水包围。   

 
```
示例 1：

输入：grid = [
  ["1","1","1","1","0"],
  ["1","1","0","1","0"],
  ["1","1","0","0","0"],
  ["0","0","0","0","0"]
]
输出：1
示例 2：

输入：grid = [
  ["1","1","0","0","0"],
  ["1","1","0","0","0"],
  ["0","0","1","0","0"],
  ["0","0","0","1","1"]
]
输出：3
 

提示：

m == grid.length
n == grid[i].length
1 <= m, n <= 300
grid[i][j] 的值为 '0' 或 '1'
Discussion | Solution

Code Now
```

----------------------------


![](../assets/images/chapter10/200-1.png)

![](../assets/images/chapter10/200-2.png)

![](../assets/images/chapter10/200-3.png)

![](../assets/images/chapter10/200-4.png)

![](../assets/images/chapter10/200-5.png)

![](../assets/images/chapter10/200-6.png)

![](../assets/images/chapter10/200-7.png)

![](../assets/images/chapter10/200-8.png)

![](../assets/images/chapter10/200-9.png)

![](../assets/images/chapter10/200-10.png)

![](../assets/images/chapter10/200-11.png)

![](../assets/images/chapter10/200-12.png)

![](../assets/images/chapter10/200-13.png)

![](../assets/images/chapter10/200-14.png)

![](../assets/images/chapter10/200-15.png)

![](../assets/images/chapter10/200-16.png)

![](../assets/images/chapter10/200-17.png)

![](../assets/images/chapter10/200-18.png)

![](../assets/images/chapter10/200-19.png)

![](../assets/images/chapter10/200-20.png)

----------------------------


```c
/*
 * @lc app=leetcode.cn id=200 lang=cpp
 *
 * [200] 岛屿数量
 */

// @lc code=start
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        std::vector<int> visit_col(grid[0].size(), 0);
        std::vector<std::vector<int>> visit(grid.size(), visit_col);

        int res;

        for(int i=0; i<grid.size(); i++){
            for(int j=0; j<grid[i].size(); j++){
                if(visit[i][j]) continue;// 如果已访问
                if(grid[i][j]=='1' && visit[i][j]==0){
                    // DFS(grid, i, j, visit);
                    BFS(grid, i, j, visit);
                    res ++;
                }
            }
        }

        return res;
    }
private:
    void DFS(vector<vector<char>>& grid, // 在grid中与x,y相连的位置进行标记
             int x, int y,// 遍历的当前位置
             vector<vector<int>>& visit){
        visit[x][y] = 1;
        static const int dx[] = {-1, 1, 0, 0};
        static const int dy[] = {0, 0, -1, 1};
        for(int i=0; i<4; i++){
            int newx = dx[i] + x;
            int newy = dy[i] + y;
            // 越界判断
            if(newx<0 || newx>=visit.size() ||
               newy<0 || newy>=visit[newx].size()){
                continue;
            }
            // 未访问 且 为陆地
            if(visit[newx][newy]==0 && grid[newx][newy]=='1'){
                DFS(grid, newx, newy, visit);
            }
        }
    }

    void BFS(vector<vector<char>>& grid,
             int x, int y,
             vector<vector<int>>& visit){

        static const int dx[] = {-1, 1, 0, 0};
        static const int dy[] = {0, 0, -1, 1};
        
        std::queue<pair<int,int>> Q;
        Q.push(make_pair(x,y));
        visit[x][y] = 1;

        while(!Q.empty()){
            x = Q.front().first;
            y = Q.front().second;
            Q.pop();

            for(int i=0; i<4; i++){
                int newx = dx[i] + x;
                int newy = dy[i] + y;
                // 越界判断
                if(newx<0 || newx>=visit.size() ||
                newy<0 || newy>=visit[newx].size()){
                    continue;
                }
                // 未访问 且 为陆地
                if(visit[newx][newy]==0 && grid[newx][newy]=='1'){
                    Q.push(make_pair(newx, newy));
                    visit[newx][newy] = 1;
                }
            }
        }

    }
};
// @lc code=end


```