#define CAPACITY 100000
#define NOT_FOUND -1

typedef struct MyListNode MyListNode;

struct MyListNode {
    int key;
    int value;
    MyListNode* next;
};

typedef struct {
    MyListNode* vec[CAPACITY];
} MyHashMap;

MyHashMap* myHashMapCreate() {
    MyHashMap* res = (MyHashMap*)malloc(sizeof(MyHashMap));

    if (res == NULL) {
        return NULL;
    }

    memset(res->vec, 0, CAPACITY * sizeof(MyListNode*));

    return res;
}

MyListNode* find(MyListNode* head, int key) {
    MyListNode* curr = head;

    while (curr != NULL) {
        printf("%d\n", curr->key);
        if (curr->key == key) {
            return curr;
        }

        curr = curr->next;
    }

    return NULL;
}

void myHashMapPut(MyHashMap* obj, int key, int value) {
    if (obj == NULL || key < 0) {
        return;
    }

    MyListNode* head = obj->vec[key % CAPACITY];
    MyListNode* found = find(head, key);

    if(found != NULL) {
        found->value = value;
        return;
    }

    MyListNode* newHead = (MyListNode*)malloc(sizeof(MyListNode));
    
    if(newHead == NULL) {
        return;
    }

    newHead->key = key;
    newHead->value = value;
    newHead->next = head;

    obj->vec[key % CAPACITY] = newHead;
}

int myHashMapGet(MyHashMap* obj, int key) {
    if (obj == NULL || key < 0) {
        return NOT_FOUND;
    }

    MyListNode* head = obj->vec[key % CAPACITY];
    MyListNode* found = find(head, key);

    if (found == NULL) {
        return NOT_FOUND;
    }

    return found->value;
}

void myHashMapRemove(MyHashMap* obj, int key) {
    if (obj == NULL || key < 0) {
        return;
    }

    MyListNode* head = obj->vec[key % CAPACITY];

    MyListNode* prev = NULL;
    MyListNode* curr = head;

    while (curr != NULL) {
        if (curr->key == key) {
            if (prev == NULL) {
                obj->vec[key % CAPACITY] = curr->next;
            } else {
                prev->next = curr->next;
            }

            free(curr);
            return;
        }

        prev = curr;
        curr = curr->next;
    }
}

void myHashMapFree(MyHashMap* obj) {
    if (obj == NULL) {
        return;
    }

    for (int i = 0; i < CAPACITY; ++i) {
        MyListNode* head = obj->vec[i];

        if (head == NULL) {
            continue;
        }

        MyListNode* curr = head;

        while (curr != NULL) {
            MyListNode* temp = curr->next;
            free(curr);
            curr = temp;
        }
    }

    free(obj);
}

/**
 * Your MyHashMap struct will be instantiated and called as such:
 * MyHashMap* obj = myHashMapCreate();
 * myHashMapPut(obj, key, value);
 
 * int param_2 = myHashMapGet(obj, key);
 
 * myHashMapRemove(obj, key);
 
 * myHashMapFree(obj);
*/