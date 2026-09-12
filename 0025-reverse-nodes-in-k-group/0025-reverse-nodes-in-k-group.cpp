class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        
        ListNode* node = head;
        int count = 0;
        while (node != nullptr && count < k) {
            node = node->next;
            count++;
        }

        
        if (count < k) {
            return head;
        }

        
        ListNode* newHead = reverseKGroup(node, k);

       
        ListNode* prev = newHead;
        ListNode* curr = head;
        for (int i = 0; i < k; i++) {
            ListNode* nextTemp = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nextTemp;
        }

        return prev; 
    }
};