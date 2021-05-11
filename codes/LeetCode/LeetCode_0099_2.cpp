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
	void recoverTree(TreeNode * root) {
		// DFS
		TreeNode * prv = nullptr;
		TreeNode * err1 = nullptr;
		TreeNode * err2 = nullptr;
		dfs(root, prv, err1, err2);
		// 恢复
		swap(err1->val, err2->val);
	}
	// 深度优先搜索：中序遍历
	void dfs(TreeNode * p, TreeNode * & prv, TreeNode * & err1, TreeNode * & err2) {
		// 递归左子树
		if (p->left != nullptr) dfs(p->left, prv, err1, err2);
		// 更新答案
		if (prv != nullptr && p->val <= prv->val) {
			if (err1 == nullptr) {
				err1 = prv;
			}
			err2 = p;
		}
		prv = p;
		// 递归右子树
		if (p->right != nullptr) dfs(p->right, prv, err1, err2);
	}
};