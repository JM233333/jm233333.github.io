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
	ListNode * reverseKGroup(ListNode * head, int k) {
		// 特判
		if (head == nullptr) {
			return head;
		}
		if (k == 1) {
			return head;
		}
		// 处理头节点
		ListNode ss = ListNode(0);
		ListNode * head0 = &ss;
		head0->next = head;
		// 主循环
		ListNode * prv = head0;
		ListNode * lst = prv;
		while (prv != nullptr) {
			// 获取一组的尾部
			for (int i = 0; i < k; i ++) {
				lst = lst->next;
				if (lst == nullptr) {
					return head0->next;
				}
			}
			// 处理一组
			ListNode * p = prv->next;
			ListNode * q = prv->next->next;
			ListNode * nprv = p;
			// 处理一组的首尾部分
			p->next = lst->next;
			prv->next = lst;
			// 处理一组的中间部分
			while (p != lst) {
				// 更新
				ListNode * t = q->next;
				q->next = p;
				// 递进
				p = q;
				q = t;
			}
			// 递进
			prv = nprv;
			lst = prv;
		}
		// 返回
		return head0->next;
	}
};
