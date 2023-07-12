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
		vector<TreeNode *> vec;
		dfs(root, vec);
		// 恢复
		TreeNode * err1 = nullptr;
		TreeNode * err2 = nullptr;
		for (int i = 1; i < vec.size(); i ++) {
			if (vec[i]->val <= vec[i - 1]->val) {
				if (err1 == nullptr) {
					err1 = vec[i - 1];
				}
				err2 = vec[i];
			}
		}
		swap(err1->val, err2->val);
	}
	// 深度优先搜索：中序遍历
	void dfs(TreeNode * p, vector<TreeNode *> & vec) {
		if (p->left != nullptr) dfs(p->left, vec);
		vec.push_back(p);
		if (p->right != nullptr) dfs(p->right, vec);
	}
};