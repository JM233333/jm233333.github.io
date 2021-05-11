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
		int vmax = MIN, vmin = MAX;
		return dfs(root, vmax, vmin);
	}
	// 深度优先搜索
	bool dfs(TreeNode * p, int & f_vmax, int & f_vmin) {
		// 递归左子树
		if (p->left != nullptr) {
			int vmax = MIN, vmin = MAX;
			if (!dfs(p->left, vmax, vmin) || p->val <= vmax) {
				return false;
			}
			f_vmax = max(f_vmax, vmax);
			f_vmin = min(f_vmin, vmin);
		}
		// 递归右子树
		if (p->right != nullptr) {
			int vmax = MIN, vmin = MAX;
			if (!dfs(p->right, vmax, vmin) || p->val >= vmin) {
				return false;
			}
			f_vmax = max(f_vmax, vmax);
			f_vmin = min(f_vmin, vmin);
		}
		// 返回
		f_vmax = max(f_vmax, p->val);
		f_vmin = min(f_vmin, p->val);
		return true;
	}
};