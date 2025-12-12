#define SNAP_VAL_ARRAY_INITIAL_CAPACITY 5
#define SNAPSHOT_ARRAY_GET_FAILED -1

typedef struct {
    int snap;
    int val;
} SnapValPair;

typedef struct {
    SnapValPair* arr;
    int size;
    int capacity;
    int growBy;
} SnapValArray;

typedef struct {
    SnapValArray** arr;
    int size;
    int snapsTaken;
} SnapshotArray;

SnapValArray* snapValArrayCreate(int initialCapacity) {
    if (initialCapacity < 0) {
        return NULL;
    }

    SnapValPair* arr = (SnapValPair*)malloc(sizeof(SnapValPair) * initialCapacity);

    if (arr == NULL) {
        return NULL;
    }

    SnapValArray* res = (SnapValArray*)malloc(sizeof(SnapValArray));

    if (res == NULL) {
        free(arr);
        return NULL;
    }

    res->arr = arr;
    res->capacity = initialCapacity;
    res->size = 0;
    res->growBy = 1;

    return res;
}

bool snapValArrayAdd(SnapValArray* obj, SnapValPair pair) {
    if (pair.snap < 0) {
        return false;
    }

    if (obj->size > 0) {
        SnapValPair* latest = obj->arr + obj->size - 1;

        if (pair.snap < latest->snap) {
            return false;
        }

        if (pair.snap == latest->snap) {
            latest->val = pair.val;
            return true;
        }
    }

    if (obj->size == obj->capacity) {
        int newCapacity = obj->capacity + obj->growBy;
        SnapValPair* temp = (SnapValPair*)realloc(obj->arr, sizeof(SnapValPair) * newCapacity);

        if (temp == NULL) {
            return false;
        }

        obj->arr = temp;
        obj->capacity = newCapacity;
        obj->growBy *= 2;
    }

    obj->arr[obj->size++] = pair;
    return true;
}

void snapValArrayDestroy(SnapValArray** obj) {
    if (obj == NULL || *obj == NULL) {
        return;
    }

    free((*obj)->arr);
    free(*obj);
    *obj = NULL;
}

SnapshotArray* snapshotArrayCreate(int length) {
    if (length < 0) {
        return NULL;
    }

    SnapValArray** arr = (SnapValArray**)malloc(sizeof(SnapValArray*) * length);

    if (arr == NULL) {
        return NULL;
    }

    for (int i = 0; i < length; ++i) {
        arr[i] = snapValArrayCreate(SNAP_VAL_ARRAY_INITIAL_CAPACITY);

        if (arr + i == NULL) {
            for (int j = 0; j < i; ++j) {
                snapValArrayDestroy(arr + j);
            }

            free(arr);
            return NULL;
        }
    }

    SnapshotArray* res = (SnapshotArray*)malloc(sizeof(SnapshotArray));

    if (res == NULL) {
        for (int i = 0; i < length; ++i) {
            snapValArrayDestroy(arr + i);
            free(arr);
            return NULL;
        }
    }

    res->arr = arr;
    res->size = length;
    res->snapsTaken = 0;
    return res;
}

void snapshotArraySet(SnapshotArray* obj, int index, int val) {
    if (obj == NULL || index >= obj->size || index < 0) {
        return;
    }

    SnapValArray* targetArr = obj->arr[index];

    SnapValPair pair = { obj->snapsTaken, val };
    snapValArrayAdd(targetArr, pair);
}

int snapshotArraySnap(SnapshotArray* obj) {
    return obj->snapsTaken++;
}

int snapshotArrayGet(SnapshotArray* obj, int index, int snap_id) {
    if (obj == NULL || index < 0 || index >= obj->size) {
        return SNAPSHOT_ARRAY_GET_FAILED;
    }

    SnapValArray* target = obj->arr[index];

    int left = 0;
    int right = target->size - 1;
    int res = -1;

    while (left <= right) {
        int mid = (left + right) / 2;

        if (target->arr[mid].snap <= snap_id) {
            left = mid + 1;
            res = mid;
        } else {
            right = mid - 1;
        }
    }

    if (res == -1) {
        return 0;
    }

    return target->arr[res].val;
}

void snapshotArrayFree(SnapshotArray* obj) {
    if (obj == NULL) {
        return;
    }

    for (int i = 0; i < obj->size; ++i) {
        snapValArrayDestroy(obj->arr + i);
    }

    free(obj->arr);
    free(obj);
}

/**
 * Your SnapshotArray struct will be instantiated and called as such:
 * SnapshotArray* obj = snapshotArrayCreate(length);
 * snapshotArraySet(obj, index, val);
 
 * int param_2 = snapshotArraySnap(obj);
 
 * int param_3 = snapshotArrayGet(obj, index, snap_id);
 
 * snapshotArrayFree(obj);
*/