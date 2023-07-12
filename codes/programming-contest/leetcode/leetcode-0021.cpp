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
	ListNode * mergeTwoLists(ListNode * l1, ListNode * l2) {
		// 特判
		if (l1 == nullptr && l2 == nullptr) {
			return nullptr;
		} else if (l1 == nullptr) {
			return l2;
		} else if (l2 == nullptr) {
			return l1;
		}
		// 初始化
		ListNode * head;
		if (l1->val < l2->val) {
			head = l1;
			l1 = l1->next;
		} else {
			head = l2;
			l2 = l2->next;
		}
		ListNode * l3 = head;
		// 主循环
		while (l1 != nullptr && l2 != nullptr) {
			if (l1->val < l2->val) {
				l3->next = l1;
				l3 = l1;
				l1 = l1->next;
			} else {
				l3->next = l2;
				l3 = l2;
				l2 = l2->next;
			}
		}
		// 处理剩余部分
		if (l1 != nullptr) {
			l3->next = l1;
		} else if (l2 != nullptr) {
			l3->next = l2;
		}
		// 返回
		return head;
	}
};
