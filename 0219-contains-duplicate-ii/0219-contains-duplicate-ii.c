#define HASH_SET_SIZE 1000
#define ABS(num) (( num ) < 0 ? -( num ) : ( num ))

typedef struct Node Node;

struct Node {
    int val;
    Node* next;
};

bool contains(Node** hashSet, int val) {
    Node* curr = hashSet[ABS(val) % HASH_SET_SIZE];

    while (curr != NULL) {
        if (curr->val == val) {
            return true;
        }

        curr = curr->next;
    }

    return false;
}

bool insert(Node** hashSet, int val) {
    if (contains(hashSet, val)) {
        return false;
    }

    Node* new = (Node*)malloc(sizeof(Node));

    if (new == NULL) {
        return false;
    }

    new->val = val;
    Node** headPtr = hashSet + (ABS(val) % HASH_SET_SIZE);
    new->next = (*headPtr);
    *headPtr = new;

    return true;
}

bool rem(Node** hashSet, int val) {
    Node** headPtr = hashSet + (ABS(val) % HASH_SET_SIZE);
    Node* prev = NULL;
    Node* curr = *headPtr;

    while (curr != NULL) {
        if (curr->val == val) {
            if (prev == NULL) {
                *headPtr = curr->next;
            } else {
                prev->next = curr->next;
            }

            free(curr);
            return true;
        }

        curr = curr->next;
    }

    return false;
}

void freeList(Node** head) {
    Node* curr = *head;

    while (curr != NULL) {
        Node* next = curr->next;
        curr->next = NULL;
        free(curr);
        curr = next;
    }

    *head = NULL;
}

void freeHashSet(Node** hashSet) {
    for (int i = 0; i < HASH_SET_SIZE; ++i) {
        freeList(hashSet + i);
    }
}

bool containsNearbyDuplicate(int* nums, int numsSize, int k) {
    Node** hashSet = (Node**)calloc(HASH_SET_SIZE, sizeof(Node*));

    if (hashSet == NULL) {
        return false; // Would rather an error code but whatever...
    }

    if (k > numsSize) {
        k = numsSize;
    }

    int left = 0;
    int right = 0;

    for (; right < k; ++right) {
        if (!insert(hashSet, nums[right])) {
            // freeHashSet(hashSet);
            return true;
        }
    }

    for (; right < numsSize; ++right) {
        if (contains(hashSet, nums[right])) {
            return true;
        }

        insert(hashSet, nums[right]);
        rem(hashSet, nums[left++]);
    }

    // freeHashSet(hashSet);
    return false;
}