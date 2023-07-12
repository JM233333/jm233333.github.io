/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode * next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode * next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
	ListNode * mergeKLists(vector<ListNode *> & lists) {
		// 初始化
		typedef ListNode * pNode;
		auto cmp = [](const pNode & p, const pNode & q) {
			return (p->val > q->val);
		};
		priority_queue<pNode, vector<pNode>, decltype(cmp)> pq(cmp);
		for (auto l : lists) {
			if (l != nullptr) {
				pq.push(l);
			}
		}
		pNode head = nullptr;
		// 主循环
		pNode p = nullptr;
		while (!pq.empty()) {
			// 出队
			pNode l = pq.top();
			pq.pop();
			// 插入
			if (head == nullptr) {
				head = l;
			} else {
				p->next = l;
			}
			p = l;
			// 入队
			l = l->next;
			if (l != nullptr) {
				pq.push(l);
			}
		}
		// 返回
		return head;
	}
};
