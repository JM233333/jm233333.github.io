class Solution {
public:
	int jump(vector<int> & nums) {
		// 初始化
		int n = nums.size();
		int res = 0;
		// 主循环
		int pos = 0;
		while (pos < n - 1) {
			// 贪心
			int nxt = pos;
			for (int i = pos + 1; i <= min(pos + nums[pos], n - 1); i ++) {
				if (min(nxt + nums[nxt], n - 1) <= min(i + nums[i], n - 1)) {
					nxt = i;
				}
			}
			// 更新答案
			res ++;
			// 递进
			pos = nxt;
		}
		// 返回
		return res;
	}
};
