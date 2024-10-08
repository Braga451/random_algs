class Solution {
public:
    int getDecimalValue(ListNode* head) {
        ListNode * tmp = head;
        int i = 0;
        int num = 0;
        while (tmp != nullptr) {
            tmp = tmp->next;
            i++;
        }
        tmp = head;
        for (i; i > 0; tmp = tmp->next, i--) {
            num += tmp->val * std::pow(2, i - 1);
        }
        return num;
    }
};
