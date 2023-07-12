/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode * next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
	// 解决
	ListNode * addTwoNumbers(ListNode * l1, ListNode * l2) {
		// 初始化
		ListNode * head = nullptr;
		// 主循环
		ListNode * p = nullptr;
		int rem = 0;
		while (l1 != nullptr || l2 != nullptr) {
			// 计算
			int val1 = get_value(l1);
			int val2 = get_value(l2);
			int sum = val1 + val2 + rem;
			int val = sum % 10;
			rem = sum / 10;
			// 插入
			if (head == nullptr) {
				head = new ListNode(val);
				p = head;
			} else {
				p->next = new ListNode(val);
				p = p->next;
			}
			// 递进
			if (l1 != nullptr) l1 = l1->next;
			if (l2 != nullptr) l2 = l2->next;
		}
		// 处理余数
		if (rem > 0) {
			p->next = new ListNode(rem);
			p = p->next;
			rem = 0;
		}
		// 返回
		return head;
	}
	// 获取节点的值
	inline int get_value(ListNode * p) {
		return (p == nullptr ? 0 : p->val);
	}
};
