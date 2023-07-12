class Solution {
public:
	bool canJump(vector<int> & nums) {
		// 求解
		int farest = 0;
		for (int i = 0; i < nums.size(); i ++) {
			// 失败的情况
			if (i > farest) {
				return false;
			}
			// 更新
			farest = max(farest, i + nums[i]);
		}
		// 返回
		return true;
	}
};
