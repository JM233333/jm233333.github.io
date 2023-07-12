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
	ListNode * reverseList(ListNode * head) {
		// 遍历
		ListNode * prv = nullptr;
		ListNode * cur = head;
		while (cur != nullptr) {
			ListNode * nxt = cur->next;
			cur->next = prv;
			prv = cur;
			cur = nxt;
		}
		// 返回
		return prv;
	}
};
