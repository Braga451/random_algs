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
    ListNode* rotateRight(ListNode* head, int k) {
        if (k == 0 || head == nullptr) return head;

        std::stack<ListNode *> s;
        ListNode * tmp = head;
        int listSize = 0;

        while (tmp != nullptr) {
            listSize++;
            s.push(tmp);
            tmp = tmp->next;
        }

        k %= listSize;
        ListNode * finalHead = head;
        while (k > 0) {
            ListNode * popped = s.top();
            s.pop();
            popped->next = finalHead;
            finalHead = popped;
            k--;
            if (k == 0) {
                ListNode * final = s.top();
                s.pop();
                final->next = nullptr;
            }
        }

        return finalHead;
    }
};
