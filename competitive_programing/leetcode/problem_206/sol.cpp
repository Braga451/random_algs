/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode * newHead = nullptr;
        revert(head, newHead);
        return newHead;
    }

    ListNode * revert(ListNode*& n, ListNode*& newHead) {
        if (n == nullptr) return nullptr;

        ListNode * next = revert(n->next, newHead);

        if (next == nullptr) {
            newHead = n;
            return n;
        }

        ListNode * tmp = next->next;
        next->next = n;
        n->next = tmp;

        return n; 
    }
};
