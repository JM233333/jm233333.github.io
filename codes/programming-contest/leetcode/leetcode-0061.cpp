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
	ListNode * rotateRight(ListNode * head, int k) {
		// 特判
		if (head == nullptr) {
			return head;
		}
		// 初始化
		int n = get_list_length(head);
		k = k % n;
		// 特判
		if (k == 0) {
			return head;
		}
		// 获取左右链表
		ListNode * tail = head;
		for (int i = 1; i <= n - k - 1; i ++) {
			tail = tail->next;
		}
		ListNode * nhead = tail->next;
		ListNode * ntail = nhead;
		while (ntail->next != nullptr) {
			ntail = ntail->next;
		}
		// 旋转
		tail->next = nullptr;
		ntail->next = head;
		// 返回
		return nhead;
	}
	// 获取链表长度
	int get_list_length(ListNode * head) {
		int len = 0;
		ListNode * p = head;
		while (p != nullptr) {
			len ++;
			p = p->next;
		}
		return len;
	}
};
