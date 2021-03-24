/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* deleteDuplicates(struct ListNode* head){
    struct ListNode *q = head, *p;
    if (head == NULL)
        return head;
    while (q->next != NULL)
    {
        if (q->next->val == q->val)
        {
            p = q->next;
            q->next = q->next->next;
            free(p);
        }
        else
        {
            q = q->next;
        }
    }
    return head;
}