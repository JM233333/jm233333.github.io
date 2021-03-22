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
	ListNode * deleteDuplicates(ListNode * head) {
		// 特判
		if (head == nullptr) {
			return head;
		}
		// 初始化
		ListNode * phead = new ListNode(0, head);
		// 求解
		ListNode * prv = phead;
		while (prv != nullptr && prv->next != nullptr) {
			ListNode * p = prv->next;
			if (p->next != nullptr && p->val == p->next->val) {
				// 去重
				do {
					ListNode * q = p;
					p = p->next;
					delete q;
				} while (p->next != nullptr && p->val == p->next->val);
				prv->next = p->next;
			} else {
				// 递进
				prv = prv->next;
			}
			// 递进
		}
		// 返回
		return phead->next;
	}
};
