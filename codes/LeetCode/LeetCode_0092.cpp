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
	ListNode * reverseBetween(ListNode * head, int left, int right) {
		// 特判
		if (head == nullptr) {
			return head;
		}
		// 初始化
		ListNode * prv = nullptr;
		ListNode * cur = head;
		int idx = 0;
		// 获取边界
		while (cur != nullptr && idx < left - 1) {
			prv = cur;
			cur = cur->next;
			idx ++;
		}
		ListNode * xprv = prv;
		ListNode * xcur = cur;
		// 遍历
		while (cur != nullptr && idx < right) {
			ListNode * nxt = cur->next;
			cur->next = prv;
			prv = cur;
			cur = nxt;
			idx ++;
		}
		// 处理边界
		if (xprv != nullptr) {
			xprv->next = prv;
		} else {
			head = prv;
		}
		xcur->next = cur;
		// 返回
		return head;
	}
};
