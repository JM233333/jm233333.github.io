class Solution {
private:
	static constexpr int dx[] = {1, -1, 0, 0};
	static constexpr int dy[] = {0, 0, 1, -1};
private:
	// 定义
	static const int MAXC = 26;
	struct Trie {
		Trie * next[MAXC];
		bool symbol;
		Trie() : symbol(false) {
			for (int i = 0; i < MAXC; i ++) {
				next[i] = nullptr;
			}
		}
	};
	Trie * root = new Trie;
	// 插入
	void trie_insert(const string & str) {
		// 主循环
		Trie * p = root;
		for (int i = 0; i < str.length(); i ++) {
			// 获取子节点
			Trie * & np = p->next[str[i] - 'a'];
			// 插入
			if (np == nullptr) {
				np = new Trie;
			}
			if (i == (int)str.length() - 1) {
				np->symbol = true;
			}
			// 递进
			p = np;
		}
	}
public:
	vector<string> findWords(vector<vector<char>> & board, vector<string> & words) {
		// 特判
		if (words.empty()) {
			return vector<string>();
		}
		if (board.empty() || board.front().empty()) {
			return vector<string>();
		}
		// 初始化
		int m = board.size(), n = board.front().size();
		vector<vector<bool>> visited;
		for (int i = 0; i < m; i ++) {
			visited.push_back(vector<bool>(n, false));
		}
		// 建树
		for (int i = 0; i < words.size(); i ++) {
			trie_insert(words[i]);
		}
		// DFS
		vector<string> res;
		string str;
		for (int i = 0; i < m; i ++) for (int j = 0; j < n; j ++) {
			Trie * p = root->next[board[i][j] - 'a'];
			if (p != nullptr) {
				dfs(0, i, j, p, board, words, m, n, visited, res, str);
			}
		}
		// 返回
		return res;
	}
	// 深度优先搜索
	void dfs(int depth, int x, int y, Trie * p, vector<vector<char>> & board, vector<string> & words,
			const int m, const int n, vector<vector<bool>> & visited, vector<string> & res, string & str) {
		// 更新答案
		visited[x][y] = true;
		str += board[x][y];
		if (p->symbol) {
			res.push_back(str);
			p->symbol = false;
		}
		// 递归
		for (int i = 0; i < 4; i ++) {
			int nx = x + dx[i], ny = y + dy[i];
			if (nx >= 0 && nx < m && ny >= 0 && ny < n && !visited[nx][ny]) {
				Trie * np = p->next[board[nx][ny] - 'a'];
				if (np != nullptr) {
					dfs(depth + 1, nx, ny, np, board, words, m, n, visited, res, str);
				}
			}
		}
		visited[x][y] = false;
		str.pop_back();
	}
};
