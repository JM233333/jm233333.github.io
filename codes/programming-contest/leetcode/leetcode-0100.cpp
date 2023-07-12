/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode * left;
 *     TreeNode * right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode * left, TreeNode * right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
	bool isSameTree(TreeNode * p, TreeNode * q) {
		// 特判
		if (p == nullptr || q == nullptr) {
			return (p == nullptr && q == nullptr);
		}
		// DFS
		return dfs(p, q);
	}
	// 深度优先搜索
	bool dfs(TreeNode * p, TreeNode * q) {
		// 检查
		if (p->val != q->val ||
			(p->left == nullptr) != (q->left == nullptr) ||
			(p->right == nullptr) != (q->right == nullptr)) {
			return false;
		}
		// 递归
		bool flag = true;
		if (p->left != nullptr) flag &= dfs(p->left, q->left);
		if (p->right != nullptr) flag &= dfs(p->right, q->right);
		return flag;
	}
};