#define LEFT_CHILD(node) ( ( node ) * 2 + 1 )
#define RIGHT_CHILD(node) ( ( node ) * 2 + 2 )
#define PARENT(node) ( (( node ) - 1) / 2 )

#define SWAP(first, second, type) {             \
            type temp = *( first );             \
            *( first ) = *( second );           \
            *( second ) = temp;                 \
        }

#define MIN(first, second) ( ( first ) < ( second ) ? ( first ) : ( second ) )

static void bubbleUp(int* minHeap, int size) {
    int curr = size - 1;

    while (curr > 0 && minHeap[curr] < minHeap[PARENT(curr)]) {
        SWAP(minHeap + curr, minHeap + PARENT(curr), int);
        curr = PARENT(curr);
    }
}

static void bubbleDown(int* minHeap, int start, int size) {
    int curr = start;

    while (curr <= size / 2 - 1) {
        int left = minHeap[LEFT_CHILD(curr)];
        int val = minHeap[curr];

        if (RIGHT_CHILD(curr) >= size) {
            if (val <= left) {
                return;
            }

            SWAP(minHeap + curr, minHeap + LEFT_CHILD(curr), int);
            break;
        }
        
        int right = minHeap[RIGHT_CHILD(curr)];
        
        if (val <= left && val <= right) {
            return;
        }

        int minNode = left >= right ? RIGHT_CHILD(curr) : LEFT_CHILD(curr);

        SWAP(minHeap + curr, minHeap + minNode, int);
        curr = minNode;
    }
}

void heapify(int* nums, int size) {
    for (int curr = size / 2 - 1; curr >= 0; --curr) {
        bubbleDown(nums, curr, size);
    }
}

typedef struct {
    int* minHeap;
    int size;
    int capacity;
} KthLargest;

KthLargest* kthLargestCreate(int k, int* nums, int numsSize);
int kthLargestAdd(KthLargest* obj, int val);
void kthLargestFree(KthLargest* obj);

KthLargest* kthLargestCreate(int k, int* nums, int numsSize) {
    int m = MIN(k, numsSize);
    int* minHeap = (int*)malloc(sizeof(int) * k);

    if (minHeap == NULL) {
        return NULL;
    }

    KthLargest* res = (KthLargest*)malloc(sizeof(KthLargest));

    if (res == NULL) {
        free(minHeap);
        return NULL;
    }

    memcpy(minHeap, nums, sizeof(int) * m);
    heapify(minHeap, m);

    res->minHeap = minHeap;
    res->size = m;
    res->capacity = k;

    for (int i = m; i < numsSize; ++i) {
        kthLargestAdd(res, nums[i]);
    }

    return res;
}

int kthLargestAdd(KthLargest* obj, int val) {
    if (obj->size == obj->capacity && val > obj->minHeap[0]) {
        obj->minHeap[0] = val;
        bubbleDown(obj->minHeap, 0, obj->size);
    }

    if (obj->size < obj->capacity) {
        obj->minHeap[obj->size] = val;
        bubbleUp(obj->minHeap, ++obj->size);
    }

    return obj->minHeap[0];
}

void kthLargestFree(KthLargest* obj) {
    if (obj != NULL) {
        free(obj->minHeap);
        free(obj);
    }
}

/**
 * Your KthLargest struct will be instantiated and called as such:
 * KthLargest* obj = kthLargestCreate(k, nums, numsSize);
 * int param_1 = kthLargestAdd(obj, val);
 
 * kthLargestFree(obj);
*/