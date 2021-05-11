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
private:
	int MAX = INT_MAX;
	int MIN = INT_MIN;
public:
	bool isValidBST(TreeNode * root) {
		// DFS
		return dfs(root, MIN, MAX, false, false);
	}
	// 深度优先搜索
	bool dfs(TreeNode * p, int vmin, int vmax, bool flagmin, bool flagmax) {
		// 递归终止
		if ((flagmin && p->val <= vmin) || (flagmax && p->val >= vmax)) {
			return false;
		}
		// 递归
		if (p->left != nullptr && !dfs(p->left, vmin, p->val, flagmin, true)) {
			return false;
		}
		if (p->right != nullptr && !dfs(p->right, p->val, vmax, true, flagmax)) {
			return false;
		}
		// 返回
		return true;
	}
};