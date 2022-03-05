/*
 * @Date: 2021-12-27 10:53:04
 * @Author: bFeng
 */

#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>

using namespace std;

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

TreeNode* build_tree_dfs(vector<int>& preorder, int preorder_start,
                         int preorder_end, vector<int>& inorder,
                         int inorder_start, int inorder_end) {
  if (preorder_start > preorder_end) {
    return nullptr;
  }

  TreeNode* root =
      new TreeNode(preorder[preorder_start]);  // 前序的第一个数是根节点
  int cnt = 0;                                 // 统计左子树元素个数
  for (int i = inorder_start; i <= inorder_end; i++) {  // 在后序遍中找到根节点
    if (inorder[i] == preorder[preorder_start]) {
      cnt = i - inorder_start;
      break;
    }
  }

  root->left =
      build_tree_dfs(preorder, preorder_start + 1, preorder_start + cnt,
                     inorder, inorder_start, inorder_start + cnt - 1);
  root->right = build_tree_dfs(preorder, preorder_start + cnt + 1, preorder_end,
                               inorder, inorder_start + cnt + 1, inorder_end);

  return root;
}

TreeNode* build_tree(vector<int>& preorder, vector<int>& inorder) {
  if (preorder.empty() || inorder.empty()) {
    return nullptr;
  }
  return build_tree_dfs(preorder, 0, preorder.size() - 1, inorder, 0,
                        inorder.size() - 1);
}

void print_tree(TreeNode* root) {
  std::cout << root->val << ", ";
  print_tree(root->left);
  print_tree(root->right);
}

int main() {
  std::vector<int> in1{3, 9, 20, 15, 7};
  std::vector<int> in2{9, 3, 15, 20, 7};
  // TreeNode* root = build_tree(in1, in2);
  print_tree(build_tree(in1, in2));
  return 0;
}

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
    while (n > 0) {
      if (n & 1 == 1) res *= a;
      a *= a;
      n /= 2;
    }
    return res;
  }
};
