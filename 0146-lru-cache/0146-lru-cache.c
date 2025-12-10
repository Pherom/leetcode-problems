#define UNWIRE_DLN(dln) {                                           \
            ( dln )->prev->next = ( dln )->next;                    \
            ( dln )->next->prev = ( dln )->prev;                    \
}

#define TOUCH(cache, entry) {                                       \
            ( entry )->dln->prev = cache->head;                     \
            ( entry )->dln->next = ( cache )->head->next;           \
            ( cache )->head->next->prev = ( entry )->dln;           \
            ( cache )->head->next = ( entry )->dln;                 \
        }

typedef struct DListNode DListNode;

struct DListNode {
    int key;
    int value;
    DListNode *prev;
    DListNode *next;
};

typedef struct {
    int key;
    DListNode *dln;
    UT_hash_handle hh;
} Entry;

typedef struct {
    Entry *map;
    DListNode *head;
    DListNode *tail;
    int size;
    int capacity;
} LRUCache;


LRUCache* lRUCacheCreate(int capacity) {
    if (capacity <= 0) {
        return NULL;
    }

    LRUCache *cache = (LRUCache*)malloc(sizeof(LRUCache));

    if (cache == NULL) {
        return NULL;
    }

    cache->map = NULL;
    cache->head = (DListNode*)malloc(sizeof(DListNode)); //dummy

    if (cache->head == NULL) {
        free(cache);
        return NULL;
    }

    cache->head->prev = cache->head;

    cache->tail = (DListNode*)malloc(sizeof(DListNode));

    if (cache->tail == NULL) {
        free(cache->head);
        free(cache);
        return NULL;
    }

    cache->tail->next = cache->tail;

    cache->head->next = cache->tail;
    cache->tail->prev = cache->head;

    cache->size = 0;
    cache->capacity = capacity;

    return cache;
}

int lRUCacheGet(LRUCache* obj, int key) {
    if (obj == NULL) {
        return -1;
    }

    Entry *entry;
    HASH_FIND_INT(obj->map, &key, entry);

    if (entry == NULL) {
        return -1;
    }

    UNWIRE_DLN(entry->dln);
    TOUCH(obj, entry);

    return entry->dln->value;
}

void lRUCachePut(LRUCache* obj, int key, int value) {
    if (obj == NULL) {
        return;
    }

    Entry* entry;
    HASH_FIND_INT(obj->map, &key, entry);

    if (entry != NULL) {
        entry->dln->value = value;
        UNWIRE_DLN(entry->dln);
        TOUCH(obj, entry);
        return;
    }

    DListNode* dln = (DListNode*)malloc(sizeof(DListNode));

    if (dln == NULL) {
        return;
    }

    entry = (Entry*)malloc(sizeof(Entry));

    if (entry == NULL) {
        free(dln);
        return;
    }

    if (obj->size == obj->capacity) {
        DListNode* deleteDln = obj->tail->prev;
        Entry* deleteEntry;
        HASH_FIND_INT(obj->map, &(deleteDln->key), deleteEntry);
        HASH_DEL(obj->map, deleteEntry);
        free(deleteEntry);
        UNWIRE_DLN(deleteDln);
        free(deleteDln);
        --obj->size;
    }

    dln->key = key;
    dln->value = value;
    entry->key = key;
    entry->dln = dln;
    HASH_ADD_INT(obj->map, key, entry);
    TOUCH(obj, entry);
    ++obj->size;
}

void lRUCacheFree(LRUCache* obj) {
    DListNode* currDln = obj->head;

    while (currDln->next != currDln) {
        DListNode* temp = currDln->next;
        free(currDln);
        currDln = temp;
    }

    free(obj->tail);

    Entry *currEntry;
    Entry *temp;

    HASH_ITER(hh, obj->map, currEntry, temp) {
        HASH_DEL(obj->map, currEntry);
        free(currEntry);
    }

    free(obj);
}

/**
 * Your LRUCache struct will be instantiated and called as such:
 * LRUCache* obj = lRUCacheCreate(capacity);
 * int param_1 = lRUCacheGet(obj, key);
 
 * lRUCachePut(obj, key, value);
 
 * lRUCacheFree(obj);
*/