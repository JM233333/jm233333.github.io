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
	ListNode * removeNthFromEnd(ListNode * head, int n) {
		// 预处理
		ListNode * p = head;
		ListNode * q = head;
		while (n --) {
			q = q->next;
		}
		// 特判
		if (q == nullptr) {
			// 删除
			q = head;
			head = head->next;
			delete q;
			// 返回
			return head;
		}
		// 处理
		while (q->next != nullptr) {
			p = p->next;
			q = q->next;
		}
		// 删除
		q = p->next;
		p->next = p->next->next;
		delete q;
		// 返回
		return head;
	}
};
