/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
typedef struct ListNode ListNode;

static void listNodeDestroy(ListNode* head) {
    ListNode* curr = head;

    while (curr != NULL) {
        ListNode* temp = curr->next;
        free(curr);
        curr = temp;
    }
}

static bool handleSingleList(ListNode** currRes, ListNode* curr, int* carry) {
    while (curr != NULL) {
        (*currRes)->next = (ListNode*)malloc(sizeof(ListNode));

        if ((*currRes)->next == NULL) {
            return false;
        }

        *currRes =  (*currRes)->next;
        int sum = *carry + curr->val;
        (*currRes)->val = sum % 10;
        *carry = sum / 10;
        curr = curr->next;
    }

    return true;
}

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    ListNode* dummy = (ListNode*)malloc(sizeof(ListNode));

    if (dummy == NULL) {
        return NULL;
    }

    int carry = 0;
    ListNode* curr1 = l1;
    ListNode* curr2 = l2;
    ListNode* currRes = dummy;

    while (curr1 != NULL && curr2 != NULL) {
        currRes->next = (ListNode*)malloc(sizeof(ListNode));

        if (currRes->next == NULL) {
            listNodeDestroy(dummy);
            return NULL;
        }

        currRes =  currRes->next;
        int sum = carry + curr1->val + curr2->val;
        currRes->val = sum % 10;
        carry = sum / 10;
        curr1 = curr1->next;
        curr2 = curr2->next;
    }

    if (!handleSingleList(&currRes, curr1, &carry)) {
        listNodeDestroy(dummy);
    }

    if (!handleSingleList(&currRes, curr2, &carry)) {
        listNodeDestroy(dummy);
    }

    if (carry > 0) {
        currRes->next = (ListNode*)malloc(sizeof(ListNode));

        if (currRes->next == NULL) {
            listNodeDestroy(dummy);
            return NULL;
        }

        currRes = currRes->next;
        currRes->val = carry;
    }

    currRes->next = NULL;
    currRes = dummy->next;
    free(dummy);
    return currRes;
}