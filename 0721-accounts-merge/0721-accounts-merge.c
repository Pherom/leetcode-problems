/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
#define HASHMAP_SIZE 10000
#define RET_ARR_SIZE 10000

#define SWAP(first, second, type) {         \
            type temp = *( first );         \
            *( first ) = *( second );       \
            *( second ) = temp;             \
        }

typedef struct Node Node;

struct Node {
    char* key;
    int val;
    Node* next;
};

typedef struct HashMap {
    Node** arr;
    unsigned long size;
    unsigned long count;
    unsigned long (*hashFunc)(char*);
} HashMap;

typedef struct AsssignEmailContext {
    char*** accounts;
    int* emailIdToAccNum;
    char*** result;
    int* returnColumnSizes;
    int* parent;
    int* repToIdx;
    int* currIdx;
} AssignEmailContext;

typedef enum {
    HASHMAP_PUT_SUCCESS,
    HASHMAP_PUT_FAILED
} HashMapPutResult;

typedef enum {
    HASHMAP_GET_FOUND,
    HASHMAP_GET_NOT_FOUND,
    HASHMAP_GET_FAILED
} HashMapGetResult;

Node* nodeCreate(char* key, int val) {
    if (key == NULL) {
        return NULL;
    }

    Node* result = (Node*)malloc(sizeof(Node));

    if (result == NULL) {
        return NULL;
    }

    result->key = key;
    result->val = val;
    result->next = NULL;

    return result;
}

Node* nodeFind(Node* head, char* key) {
    Node* curr = head;

    while (curr != NULL) {
        if (strcmp(curr->key, key) == 0) {
            return curr;
        }

        curr = curr->next;
    }

    return NULL;
}

void nodeDestroy(Node** node) {
    if (node == NULL || *node == NULL) {
        return;
    }

    nodeDestroy(&((*node)->next));
    free(*node);
    *node = NULL;
}

HashMap* hashMapCreate(unsigned long size, unsigned long (*hashFunc)(char*)) {
    if (size < 0 || hashFunc == NULL) {
        return NULL;
    }

    Node** arr = (Node**)malloc(sizeof(Node*) * size);

    if (arr == NULL) {
        return NULL;
    }

    memset(arr, 0, sizeof(Node*) * size);

    HashMap* result = (HashMap*)malloc(sizeof(HashMap));

    if (result == NULL) {
        free(arr);
        return NULL;
    }

    result->arr = arr;
    result->size = size;
    result->count = 0;
    result->hashFunc = hashFunc;

    return result;
}

void hashMapDestroy(HashMap** map) {
    if (map == NULL || *map == NULL) {
        return;
    }

    for (int i = 0; i < (*map)->size; ++i) {
        nodeDestroy((*map)->arr + i);
    }

    free((*map)->arr);
    free(*map);
    *map = NULL;
}

HashMapPutResult hashMapPut(HashMap* map, char* key, int val) {
    if (map == NULL || key == NULL) {
        return HASHMAP_PUT_FAILED;
    }

    unsigned long hashedKey = map->hashFunc(key);

    Node** headPtr = map->arr + (hashedKey % map->size);
    Node* found = nodeFind(*headPtr, key);

    if (found != NULL) {
        found->val = val;
        return HASHMAP_PUT_SUCCESS;
    }

    Node* newNode = nodeCreate(key, val);
    
    if (newNode == NULL) {
        return HASHMAP_PUT_FAILED;
    }

    newNode->next = *headPtr;
    *headPtr = newNode;
    ++map->count;

    return HASHMAP_PUT_SUCCESS;
}

HashMapGetResult hashMapGet(HashMap const* map, char* key, int* val) {
    if (map == NULL || key == NULL || val == NULL) {
        return HASHMAP_GET_FAILED;
    }

    unsigned long hashedKey = map->hashFunc(key);
    Node* head = map->arr[hashedKey % map->size];
    Node* found = nodeFind(head, key);

    if (found == NULL) {
        return HASHMAP_GET_NOT_FOUND;
    }

    *val = found->val;
    return HASHMAP_GET_FOUND;
}

unsigned long hashEmail(char* email) {
    unsigned long hash = 5381;
    int c;

    while (c = *email++)
        hash = ((hash << 5) + hash) + c;

    return hash;
}

void hashMapForEach(HashMap* map, void (*action)(char*, int*, void*), void* context) {
    if (map == NULL || action == NULL) {
        return;
    }

    for (int i = 0; i < map->size; ++i) {
        Node* curr = map->arr[i];

        while (curr != NULL) {
            action(curr->key, &(curr->val), context);
            curr = curr->next;
        }
    }
}

int disjointSetsFind(int* parent, int u) {
    if (u == parent[u]) {
        return u;
    }

    parent[u] = disjointSetsFind(parent, parent[u]);
    return parent[u];
}

void assignEmail(char* email, int* id, void* _context) {
    AssignEmailContext* context = (AssignEmailContext*)_context;

    int rep = disjointSetsFind(context->parent, *id);

    int idx = context->repToIdx[rep];

    if (idx == -1) {
        idx = (*(context->currIdx))++;
        context->repToIdx[rep] = idx;
        context->result[idx][0] = context->accounts[context->emailIdToAccNum[*id]][0];
    }

    context->result[idx][context->returnColumnSizes[idx]++] = email;
}

int partition(char** strArr, int size) {
    int result = 0;
    char* pivot = strArr[size - 1];

    for (int i = 0; i < size - 1; ++i) {
        if (strcmp(strArr[i], pivot) < 0) {
            SWAP(strArr + i, strArr + result, char*);
            ++result;
        }
    }

    SWAP(strArr + size - 1, strArr + result, char*);
    return result;
}

void quickSort(char** strArr, int size) {
    if (size <= 1) {
        return;
    }

    int part = partition(strArr, size);
    quickSort(strArr, part);
    quickSort(strArr + part + 1, size - part - 1);
}

char*** accountsMerge(char*** accounts, int accountsSize, int* accountsColSize, int* returnSize, int** returnColumnSizes) {
    if (accounts == NULL || accountsSize < 0 || accountsColSize == NULL || returnSize == NULL || returnColumnSizes == NULL) {
        return NULL;
    }

    HashMap* emailToId = hashMapCreate(HASHMAP_SIZE, hashEmail);

    if (emailToId == NULL) {
        return NULL;
    }

    int currId = 0;
    for (int i = 0; i < accountsSize; ++i) {
        for (int j = 1; j < accountsColSize[i]; ++j) {
            int found = -1;
            HashMapGetResult getRes = hashMapGet(emailToId, accounts[i][j], &found);

            if (getRes != HASHMAP_GET_FOUND) {
                hashMapPut(emailToId, accounts[i][j], currId++);
            }
        }
    }

    int* parent = (int*)malloc(sizeof(int) * emailToId->count);

    if (parent == NULL) {
        hashMapDestroy(&emailToId);
        return NULL;
    }

    int* emailIdToAccNum = (int*)malloc(sizeof(int) * emailToId->count);

    if (emailIdToAccNum == NULL) {
        free(parent);
        hashMapDestroy(&emailToId);
        return NULL;
    }

    for (int i = 0; i < emailToId->count; ++i) {
        parent[i] = i;
    }

    int groupCount = emailToId->count;
    for (int i = 0; i < accountsSize; ++i) {
        int firstId = -1;
        hashMapGet(emailToId, accounts[i][1], &firstId);
        emailIdToAccNum[firstId] = i;
        int firstRep = disjointSetsFind(parent, firstId);

        for (int j = 2; j < accountsColSize[i]; ++j) {
            int id = -1;
            hashMapGet(emailToId, accounts[i][j], &id);
            emailIdToAccNum[id] = i;
            int rep = disjointSetsFind(parent, id);
            if (rep != firstRep) {
                parent[rep] = firstRep;
                --groupCount;
            }
        }
    }

    char*** result = (char***)malloc(sizeof(char**) * groupCount);

    if (result == NULL) {
        free(parent);
        free(emailIdToAccNum);
        hashMapDestroy(&emailToId);
        return NULL;
    }

    *returnColumnSizes = (int*)malloc(sizeof(int) * groupCount);

    if (*returnColumnSizes == NULL) {
        free(result);
        free(parent);
        free(emailIdToAccNum);
        hashMapDestroy(&emailToId);
        return NULL;
    }

    for (int i = 0; i < groupCount; ++i) {
        (*returnColumnSizes)[i] = 1;
    }

    for (int i = 0; i < groupCount; ++i) {
        result[i] = (char**)malloc(sizeof(char*) * RET_ARR_SIZE);

        if (result[i] == NULL) {
            for (int j = 0; j < i; ++j) {
                free(result[j]);
            }

            free(result);
            free(parent);
            free(emailIdToAccNum);
            hashMapDestroy(&emailToId);
            return NULL;
        }
    }

    int* repToIdx = (int*)malloc(sizeof(int) * emailToId->count);

    if (repToIdx == NULL) {
        for (int i = 0; i < groupCount; ++i) {
            free(result[i]);
        }

        free(result);
        free(parent);
        free(emailIdToAccNum);
        hashMapDestroy(&emailToId);
        return NULL;
    }

    for (int i = 0; i < emailToId->count; ++i) {
        repToIdx[i] = -1;
    }

    int currIdx = 0;
    AssignEmailContext context = {
        accounts,
        emailIdToAccNum,
        result,
        *returnColumnSizes,
        parent,
        repToIdx,
        &currIdx
    };

    hashMapForEach(emailToId, assignEmail, (void*)(&context));

    for (int i = 0; i < groupCount; ++i) {
        quickSort(result[i] + 1, (*returnColumnSizes)[i] - 1);
    }

    *returnSize = groupCount;

    free(repToIdx);
    free(parent);
    free(emailIdToAccNum);
    hashMapDestroy(&emailToId);
    return result;
}