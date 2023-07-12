class Solution {
public:
vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
	unordered_set<string> dict(wordList.begin(), wordList.end());
	if (dict.find(endWord) == dict.end()) return {};

	path = { beginWord };
	unordered_set<string> src{ beginWord };
	unordered_set<string> tgt{ endWord };
	bool src2tgt = true;
	bool found = false;

	while (!src.empty() && !tgt.empty()) {
		if(src.size() > tgt.size()){
			swap(src, tgt);
			src2tgt = !src2tgt;
		}

		for (const auto& s : src) dict.erase(s);

		unordered_set<string> adj;
		for (const auto& s : src) {
			for (int i = 0; i < s.length(); ++i) {
				string w = s;

				for (char c = 'a'; c <= 'z'; ++c) {
					w[i] = c;

					if (dict.find(w) == dict.end()) continue;
					if (tgt.find(w) != tgt.end()) found = true;
					adj.insert(w);
					src2tgt ? child[s].push_back(w) : child[w].push_back(s);
				}
			}
		}

		if (found) {
			genLadders(beginWord, endWord);
			return res;
		}
		src = adj;
	}

	return res;
}

private:
    void genLadders(string beginWord, string endWord) {
        if (beginWord == endWord)
            res.push_back(path);
        else {
            for (const auto& w : child[beginWord]) {
                path.push_back(w);
                genLadders(w, endWord);
                path.pop_back();
            }
        }
    }

	vector<vector<string>> res;
	unordered_map<string, vector<string>> child;
	vector<string> path;
};
