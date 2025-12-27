#define HASHMAP_INIT_CAP 1000
#define ARR_INIT_CAP 5
#define MAX_STR_SIZE 101

#define SWAP(first, second, type) {     \
            type temp = *( first );     \
            *( first ) = *( second );   \
            *( second ) = temp;         \
        }

typedef struct NodeData {
    char** arr;
    size_t capacity;
    size_t size;
} NodeData;

typedef struct Node Node;

struct Node {
    char* key;
    NodeData* val;
    Node* next;
};

typedef struct InsertIntoContext {
    size_t* idx;
    char*** result;
    int* arrSizes;
} InsertIntoContext;

Node* nodeCreate(char* key) {
    if (key == NULL) {
        return NULL;
    }

    size_t keyLen = strlen(key);

    char* copy = (char*)malloc(sizeof(char) * (keyLen + 1));

    if (copy == NULL) {
        return NULL;
    }

    char** arr = (char**)malloc(sizeof(char*) * ARR_INIT_CAP);

    if (arr == NULL) {
        free(copy);
        return NULL;
    }

    NodeData* data = (NodeData*)malloc(sizeof(NodeData));

    if (data == NULL) {
        free(arr);
        free(copy);
        return NULL;
    }

    data->arr = arr;
    data->size = 0;
    data->capacity = ARR_INIT_CAP;

    Node* result = (Node*)malloc(sizeof(Node));

    if (result == NULL) {
        free(data);
        free(arr);
        free(copy);
        return NULL;
    }

    strcpy(copy, key);
    result->key = copy;
    result->val = data;
    result->next = NULL;
    return result;
}

void nodeDestroy(Node** node) {
    if (node == NULL || *node == NULL) {
        return;
    }

    Node* curr = *node;

    while (curr != NULL) {
        Node* next = curr->next;
        free(curr->val->arr);
        free(curr->val);
        free(curr->key);
        free(curr);
        curr = next;
    }
}

void nodeForEach(Node* node, void (*action)(char*, NodeData*, void*), void* context) {
    Node* curr = node;

    while (curr != NULL) {
        action(curr->key, curr->val, context);
        curr = curr->next;
    }
}

typedef struct HashMap {
    Node** arr;
    size_t size;
    size_t capacity;
    size_t (*hashFunc)(char*);
} HashMap;

typedef enum HashMapPutResult {
    HASHMAP_PUT_SUCCESS,
    HASHMAP_PUT_FAILED
} HashMapPutResult;

typedef enum HashMapGetResult {
    HASHMAP_GET_FOUND,
    HASHMAP_GET_NOT_FOUND,
    HASHMAP_GET_FAILED
} HashMapGetResult;

typedef enum HashMapForEachResult {
    HASHMAP_FOR_EACH_SUCCESS,
    HASHMAP_FOR_EACH_FAILED
} HashMapForEachResult;

size_t hash(char* str) {
    if (str == NULL) {
        return 0;
    }

    unsigned char* ustr = str;
    size_t hash = 5381;
    int c;

    while (c = *ustr++)
        hash = ((hash << 5) + hash) + c;

    return hash;
}

HashMap* hashMapCreate(size_t capacity, size_t (*hashFunc)(char*)) {
    if (hashFunc == NULL || capacity == 0) {
        return NULL;
    }

    Node** arr = (Node**)malloc(sizeof(Node*) * capacity);

    if (arr == NULL) {
        return NULL;
    }

    memset(arr, 0, sizeof(Node*) * capacity);

    HashMap* result = (HashMap*)malloc(sizeof(HashMap));

    if (result == NULL) {
        free(arr);
        return NULL;
    }

    result->arr = arr;
    result->size = 0;
    result->capacity = capacity;
    result->hashFunc = hashFunc;
    return result;
}

HashMapPutResult hashMapPut(HashMap* map, char* key, char* value) {
    if(map == NULL || key == NULL || value == NULL) {
        return HASHMAP_PUT_FAILED;
    }

    size_t hashedKey = map->hashFunc(key);

    Node* head = map->arr[hashedKey % map->capacity];
    Node* curr = head;

    while (curr != NULL) {
        if (strcmp(curr->key, key) == 0) {
            if (curr->val->capacity == curr->val->size) {
                size_t newCapacity = curr->val->capacity * 2;
                char** temp = (char**)realloc(curr->val->arr, sizeof(char*) * newCapacity);
                if (temp == NULL) {
                    return HASHMAP_PUT_FAILED;
                }

                curr->val->arr = temp;
                curr->val->capacity = newCapacity;
            }

            curr->val->arr[curr->val->size++] = value;
            return HASHMAP_PUT_SUCCESS;
        }

        curr = curr->next;
    }

    curr = nodeCreate(key);

    if (curr == NULL) {
        return HASHMAP_PUT_FAILED;
    }

    curr->next = head;
    map->arr[hashedKey % map->capacity] = curr;
    curr->val->arr[curr->val->size++] = value;
    ++map->size;
    return HASHMAP_PUT_SUCCESS;
}

HashMapGetResult hashMapGet(HashMap* map, char* key, NodeData** data) {
    if (map == NULL || key == NULL || data == NULL) {
        return HASHMAP_GET_FAILED;
    }

    size_t hashedKey = map->hashFunc(key);

    Node* curr = map->arr[hashedKey];

    while (curr != NULL) {
        if (strcmp(curr->key, key) == 0) {
            *data = curr->val;
            return HASHMAP_GET_FOUND;
        }

        curr = curr->next;
    }

    return HASHMAP_GET_NOT_FOUND;
}

HashMapForEachResult hashMapForEach(HashMap* map, void (*action)(char*, NodeData*, void*), void* context) {
    if (map == NULL || action == NULL) {
        return HASHMAP_FOR_EACH_FAILED;
    }

    for (int i = 0; i < map->capacity; ++i) {
        Node* head = map->arr[i];
        nodeForEach(head, action, context);
    }

    return HASHMAP_FOR_EACH_SUCCESS;
}

void hashMapDestroy(HashMap** map) {
    if (map == NULL || *map == NULL) {
        return;
    }

    free(*map);
    *map = NULL;
}

void sort(char* str) {
    size_t buckets[26] = {0};

    for (char* p = str; *p != '\0'; ++p) {
        ++buckets[*p - 'a'];
    }

    char* curr = str;
    for (int i = 0; i < 26; ++i) {
        size_t count = buckets[i];

        for (int j = 0; j < count; ++j) {
            *curr = i + 'a';
            ++curr;
        }
    }
}

void insertInto(char* key, NodeData* data, void* _context) {
    InsertIntoContext* context = _context;

    size_t idx = *(context->idx);
    context->result[idx] = data->arr;
    context->arrSizes[idx] = data->size;

    ++(*(context->idx));
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char*** groupAnagrams(char** strs, int strsSize, int* returnSize, int** returnColumnSizes) {
    if (strs == NULL || strsSize < 0 || returnSize == NULL || returnColumnSizes == NULL) {
        return NULL;
    }

    HashMap* map = hashMapCreate(HASHMAP_INIT_CAP, hash);

    if (map == NULL) {
        return NULL;
    }

    char temp[MAX_STR_SIZE];

    for (int i = 0; i < strsSize; ++i) {
        char* str = strs[i];

        strcpy(temp, str);
        sort(temp);

        hashMapPut(map, temp, str);
    }

    char*** result = (char***)malloc(sizeof(char**) * map->size);

    if (result == NULL) {
        hashMapDestroy(&map);
        return NULL;
    }

    *returnSize = map->size;

    *returnColumnSizes = (int*)malloc(sizeof(int) * map->size);

    if (*returnColumnSizes == NULL) {
        free(result);
        hashMapDestroy(&map);
        return NULL;
    }

    size_t currIdx = 0;

    InsertIntoContext context = {
        .idx = &currIdx,
        .result = result,
        .arrSizes = *returnColumnSizes
    };

    hashMapForEach(map, insertInto, &context);

    hashMapDestroy(&map);

    return result;
}