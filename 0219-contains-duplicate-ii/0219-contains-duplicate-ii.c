#define DICT_ARR_SIZE 100000

typedef struct Node Node;

struct Node {
    int key;
    int value;
    Node* next;
};

typedef struct Dictionary Dictionary;

struct Dictionary {
    int arrSize;
    int (*hashFunc)(int);
    Node** arr;
};

typedef enum DictionaryPutResult {
    DICTIONARY_PUT_SUCCESS,
    DICTIONARY_PUT_FAILED
} DictionaryPutResult;

typedef enum DictionaryGetResult {
    DICTIONARY_GET_FOUND,
    DICTIONARY_GET_NOT_FOUND,
    DICTIONARY_GET_FAILED
} DictionaryGetResult;

Dictionary* dictionaryCreate(int size, int (*hash)(int)) {
    Node** arr = (Node**)malloc(sizeof(Node*) * size);

    if (arr == NULL) {
        return NULL;
    }

    memset(arr, 0, sizeof(Node*) * size);

    Dictionary* dict = (Dictionary*)malloc(sizeof(Dictionary));

    if (dict == NULL) {
        free(arr);
        return NULL;
    }

    dict->arr = arr;
    dict->arrSize = size;
    dict->hashFunc = hash;
    return dict;
}

static Node* nodeFind(Node* head, int key) {
    Node* curr = head;

    while (curr != NULL) {
        if (curr->key == key) {
            return curr;
        }

        curr = curr->next;
    }

    return NULL;
}

static void nodeFree(Node** head) {
    Node* curr = *head;

    while (curr != NULL) {
        Node* temp = curr->next;
        free(curr);
        curr = temp;
    }

    *head = NULL;
}

DictionaryPutResult dictionaryPut(Dictionary* dict, int key, int value) {
    if (dict == NULL) {
        return DICTIONARY_PUT_FAILED;
    }

    Node* head = dict->arr[dict->hashFunc(key)];
    Node* found = nodeFind(head, key);

    if (found != NULL) {
        found->value = value;
        return DICTIONARY_PUT_SUCCESS;
    }

    Node* newHead = (Node*)malloc(sizeof(Node));

    if (newHead == NULL) {
        return DICTIONARY_PUT_FAILED;
    }

    newHead->key = key;
    newHead->value = value;
    newHead->next = head;
    dict->arr[dict->hashFunc(key)] = newHead;

    return DICTIONARY_PUT_SUCCESS;
}

DictionaryGetResult dictionaryGet(Dictionary* dict, int key, int* value) {
    if (dict == NULL || value == NULL) {
        return DICTIONARY_GET_FAILED;
    }

    Node* head = dict->arr[dict->hashFunc(key)];
    Node* found = nodeFind(head, key);

    if (found == NULL) {
        return DICTIONARY_GET_NOT_FOUND;
    }

    *value = found->value;
    return DICTIONARY_GET_FOUND;
}

void dictionaryFree(Dictionary** dict) {
    if (dict == NULL || *dict == NULL) {
        return;
    }

    for (int i = 0; i < (*dict)->arrSize; ++i) {
        Node** head = (*dict)->arr + i;

        if (*head != NULL) {
            nodeFree(head);
        }
    }

    free(*dict);
    *dict = NULL;
}

static int hash(int key) {
    return (int)(((unsigned int)key) % DICT_ARR_SIZE);
}

bool containsNearbyDuplicate(int* nums, int numsSize, int k) {
    Dictionary* dict = dictionaryCreate(DICT_ARR_SIZE, hash);

    for (int i = 0; i < numsSize; ++i) {
        int idxOther = 0;
        DictionaryGetResult getRes = dictionaryGet(dict, nums[i], &idxOther);
        
        if (getRes == DICTIONARY_GET_FOUND && i - idxOther <= k) {
            return true;
        }

        dictionaryPut(dict, nums[i], i);
    }

    return false;
}