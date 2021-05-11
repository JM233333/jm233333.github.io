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
	bool isValidBST(TreeNode * root) {
		// DFS
		TreeNode * prv = nullptr;
		return dfs(root, prv);
	}
	// 深度优先搜索：中序遍历
	bool dfs(TreeNode * p, TreeNode * & prv) {
		// 递归左子树
		if (p->left != nullptr && !dfs(p->left, prv)) {
			return false;
		}
		// 更新答案
		if (prv != nullptr && p->val <= prv->val) {
			return false;
		}
		prv = p;
		// 递归右子树
		if (p->right != nullptr && !dfs(p->right, prv)) {
			return false;
		}
		// 返回
		return true;
	}
};