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
	typedef vector<TreeNode *> vectrees;
private:
	static const int MAXN = 8 + 1;
	vectrees dp[MAXN][MAXN];
public:
	vectrees generateTrees(int n) {
		return dfs(1, n);
	}
	// 深度优先搜索
	vectrees dfs(int left, int right) {
		// 递归终止
		if (left > right) {
			return vectrees({nullptr});
		}
		if (!dp[left][right].empty()) {
			return dp[left][right];
		}
		// 递归
		vectrees curtrees;
		for (int i = left; i <= right; i ++) {
			vectrees ltrees = dfs(left, i - 1);
			vectrees rtrees = dfs(i + 1, right);
			for (auto l : ltrees) for (auto r : rtrees) {
				TreeNode * root = new TreeNode(i, l, r);
				curtrees.push_back(root);
			}
		}
		// 返回
		dp[left][right] = curtrees;
		return dp[left][right];
	}
};