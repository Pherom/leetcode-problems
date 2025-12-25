/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
typedef struct ListNode ListNode;

ListNode* merge2Lists(ListNode* first, ListNode* second) {
    ListNode* dummy = (ListNode*)malloc(sizeof(ListNode));

    if (dummy == NULL) {
        return NULL;
    }

    ListNode* currF = first;
    ListNode* currS = second;
    ListNode* currR = dummy;

    while (currF != NULL && currS != NULL) {
        ListNode* nextF = currF->next;
        ListNode* nextS = currS->next;

        if (currF->val < currS->val) {
            currR->next = currF;
            currF = nextF;
        } else {
            currR->next = currS;
            currS = nextS;
        }

        currR = currR->next;
    }

    while (currF != NULL) {
        currR->next = currF;
        currF = currF->next;
        currR = currR->next;
    }

    while (currS != NULL) {
        currR->next = currS;
        currS = currS->next;
        currR = currR->next;
    }

    currR->next = NULL;

    ListNode* res = dummy->next;
    free(dummy);
    return res;
}

ListNode* mergeRange(ListNode** lists, int rangeSize) {
    if (rangeSize == 0) {
        return NULL;
    }

    if (rangeSize == 1) {
        return *lists;
    }

    int firstSize = rangeSize / 2;
    int secondSize = rangeSize - firstSize;
    ListNode* first = mergeRange(lists, firstSize);
    ListNode* second = mergeRange(lists + firstSize, secondSize);
    return merge2Lists(first, second);
}

ListNode* mergeKLists(ListNode** lists, int listsSize) {
    return mergeRange(lists, listsSize);
}