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
	ListNode * partition(ListNode * head, int x) {
		// 初始化
		ListNode * head1 = new ListNode();
		ListNode * head2 = new ListNode();
		// 遍历
		ListNode * p = head;
		ListNode * l1 = head1;
		ListNode * l2 = head2;
		while (p != nullptr) {
			ListNode * q = p->next;
			insert_back((p->val < x ? l1 : l2), p);
			p = q;
		}
		// 返回
		l1->next = head2->next;
		ListNode * res = head1->next;
		//delete head1;
		//delete head2;
		return res;
	}
	// 插入尾部
	void insert_back(ListNode * & l, ListNode * p) {
		l->next = p;
		l = l->next;
		p->next = nullptr;
	}
};
