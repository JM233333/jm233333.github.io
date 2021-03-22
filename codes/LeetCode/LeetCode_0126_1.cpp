class Solution {
public:
	typedef vector<vector<int>> adjList;
	const int INF = 1e9;
public:
	vector<vector<string>> findLadders(const string & beginWord, const string & endWord, vector<string> & wordList) {
		// 预处理
		int st = -1, ed = -1;
		for (int i = 0; i < wordList.size(); i ++) {
			if (wordList[i] == beginWord) st = i;
			if (wordList[i] == endWord) ed = i;
		}
		if (st == -1) {
			wordList.push_back(beginWord);
			st = wordList.size() - 1;
		}
		if (ed == -1) {
			return vector<vector<string>>();
		}
		// 建图
		int n = wordList.size();
		adjList graph(n, vector<int>());
		for (int i = 0; i < n; i ++) for (int j = i + 1; j < n; j ++) {
			if (has_edge(wordList[i], wordList[j])) {
				add_edge(graph, i, j);
			}
		}
		// BFS
		vector<int> dist(n, INF);
		bfs(graph, st, ed, dist);
		// 无解的情况
		if (dist[ed] == INF) {
			return vector<vector<string>>();
		}
		// DFS
		vector<int> seq;
		vector<vector<int>> vecseq;
		dfs(st, seq, vecseq, graph, ed, dist);
		// 返回
		vector<vector<string>> res;
		for (auto & seq : vecseq) {
			vector<string> tmp;
			for (auto & u : seq) {
				tmp.push_back(wordList[u]);
			}
			res.push_back(tmp);
		}
		return res;
	}
	// 判断是否仅差一个字母
	bool has_edge(const string & a, const string & b) {
		// 特判
		if (a.length() != b.length()) {
			return false;
		}
		// 遍历
		int cnt = 0;
		for (int i = 0; i < a.length(); i ++) {
			if (a[i] != b[i]) {
				cnt ++;
				if (cnt > 1) return false;
			}
		}
		// 返回
		return (cnt == 1);
	}
	// 加入新边
	inline void add_edge(adjList & graph, int u, int v) {
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	// 广度优先搜索
	void bfs(adjList & graph, int st, int ed, vector<int> & dist) {
		// 初始化
		int n = graph.size();
		vector<bool> visited(n, false);
		// 主循环
		queue<int> q;
		q.push(st);
		visited[st] = true;
		dist[st] = 0;
		while (!q.empty()) {
			// 出队
			int u = q.front();
			q.pop();
			// 遍历邻接节点
			for (int i = 0; i < graph[u].size(); i ++) {
				int v = graph[u][i];
				if (!visited[v]) {
					q.push(v);
					visited[v] = true;
					dist[v] = dist[u] + 1;
				}
			}
		}
	}
	// 深度优先搜索
	void dfs(int u, vector<int> & seq, vector<vector<int>> & vecseq,
			 const adjList & graph, const int ed, const vector<int> & dist) {
		// 递归终止
		if (u == ed) {
			seq.push_back(u);
			vecseq.push_back(seq);
			seq.pop_back();
			return;
		}
		// 递归
		seq.push_back(u);
		for (int i = 0; i < graph[u].size(); i ++) {
			int v = graph[u][i];
			if (dist[v] == dist[u] + 1) {
				dfs(v, seq, vecseq, graph, ed, dist);
			}
		}
		// 回溯
		seq.pop_back();
	}
};
