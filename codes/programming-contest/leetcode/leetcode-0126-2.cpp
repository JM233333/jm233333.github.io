class Solution {
public:
	typedef vector<vector<int>> adjList;
	const int INF = 1e9;
public:
	vector<vector<string>> findLadders(const string & beginWord, const string & endWord, vector<string> & wordList) {
		// 预处理
		unordered_set<string> wordSet(wordList.begin(), wordList.end());
		if (wordSet.find(endWord) == wordSet.end()) {
			return vector<vector<string>>();
		}
		// 双向BFS
		unordered_set<string>
		int n = wordList.size();
		adjList graph(n, vector<int>());
		for (int i = 0; i < n; i ++) {
			string word = wordList[i];
			for (int j = 0; j < word.length(); j ++) {
				char tmp = word[j];
				for (char ch = 'a'; ch <= 'z'; ch ++) {
					if (ch == tmp) continue;
					word[j] = ch;
					if (ump.find(word) != ump.end()) {
						add_edge(graph, i, ump[word]); printf("addedge %d -> %d\n",i,ump[word]);
					}
				}
				word[j] = tmp;
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
