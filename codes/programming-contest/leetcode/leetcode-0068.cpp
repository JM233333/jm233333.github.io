class Solution {
public:
	vector<string> fullJustify(vector<string> & words, int maxWidth) {
		// 分配单词到各行
		vector<vector<string>> rows;
		vector<string> row;
		vector<int> len_of_rows;
		int len_of_row = 0;
		for (int i = 0; i < words.size(); i ++) {
			// 进入下一行
			if (row.size() + len_of_row + (words[i].length() + 1) > maxWidth + 1) {
				assert(!row.empty());
				rows.push_back(row);
				len_of_rows.push_back(len_of_row);
				row.clear();
				len_of_row = 0;
			}
			// 加入当前行
			row.push_back(words[i]);
			len_of_row += words[i].length();
		}
		// 生成字符串
		vector<string> res;
		for (int i = 0; i < rows.size(); i ++) {
			// 获取当前行
			vector<string> & row = rows[i];
			int len_of_row = len_of_rows[i];
			// 单个单词的情况
			if (row.size() == 1) {
				string str = row[0] + string(maxWidth - row[0].length(), ' ');
				res.push_back(str);
				continue;
			}
			// 计算空格数
			int cnt = (row.size() - 1);
			int space_of_row = (maxWidth - len_of_row) / cnt;
			int rem = (maxWidth - len_of_row) % cnt;
			// 生成
			string str;
			for (int j = 0; j < row.size() - 1; j ++) {
				str += row[j] + string(space_of_row + (rem > 0), ' ');
				rem --;
			}
			str += row.back();
			res.push_back(str);
		}
		// 生成字符串（最后一行）
		string str;
		for (int j = 0; j < row.size() - 1; j ++) {
			str += row[j] + ' ';
		}
		str += row.back();
		str += string(maxWidth - str.length(), ' ');
		res.push_back(str);
		// 返回
		return res;
	}
};
