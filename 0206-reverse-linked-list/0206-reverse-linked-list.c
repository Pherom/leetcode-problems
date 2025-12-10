/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* reverseList(struct ListNode* head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }

    struct ListNode* dummy = (struct ListNode*)malloc(sizeof(struct ListNode));

    if (dummy == NULL) {
        // Not ideal but can't change function signature
        return NULL;
    }

    dummy->next = head;
    struct ListNode* curr = head;

    while (curr->next != NULL) {
        struct ListNode* temp = dummy->next;
        dummy->next = curr->next;
        curr->next = curr->next->next;
        dummy->next->next = temp;
    }

    head = dummy->next;
    free(dummy);
    return head;
}