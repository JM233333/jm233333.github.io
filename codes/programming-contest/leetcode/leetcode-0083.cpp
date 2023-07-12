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
		// 求解
		ListNode * p = head;
		while (p != nullptr && p->next != nullptr) {
			// 去重
			while (p != nullptr && p->next != nullptr && p->val == p->next->val) {
				//ListNode * q = p->next;
				p->next = p->next->next;
				//delete q;
			}
			// 递进
			p = p->next;
		}
		// 返回
		return head;
	}
};
