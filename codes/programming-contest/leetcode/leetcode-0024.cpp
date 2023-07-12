/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
	ListNode * swapPairs(ListNode * head) {
		// 特判
		if (head == nullptr || head->next == nullptr) {
			return head;
		}
		// 处理头节点
		ListNode * p = head;
		head = p->next;
		p->next = p->next->next;
		head->next = p;
		// 主循环
		ListNode * prv = p;
		p = p->next;
		while (p != nullptr && p->next != nullptr) {
			// 更新
			prv->next = p->next;
			p->next = p->next->next;
			prv->next->next = p;
			// 递进
			prv = p;
			p = p->next;
		}
		// 返回
		return head;
	}
};
