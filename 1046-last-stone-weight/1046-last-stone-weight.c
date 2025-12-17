#define RIGHT(x) (( x ) * 2 + 2)
#define LEFT(x) (( x ) * 2 + 1)
#define PARENT(x) ((( x ) - 1) / 2)
#define LOWEST_PARENT(size) PARENT(( size ) - 1)
#define HEAP_TOP(heap) (( heap )[0])

#define SWAP(first, second, type) {         \
            type temp = *( first );         \
            *( first ) = *( second );       \
            *( second ) = temp;             \
        }

#define HEAP_POP(heap, size) {                  \
            ( heap )[0] = ( heap )[--( size )]; \
            bubbleDown(( heap ), 0, ( size ));  \
        }

#define HEAP_PUSH(heap, size, val) {        \
            ( heap )[( size )] = ( val );   \
            bubbleUp(( heap ), ++( size )); \
        }

void bubbleUp(int* heap, int size) {
    int curr = size - 1;
    int parent = PARENT(curr);

    while (parent >= 0 && heap[parent] < heap[curr]) {
        SWAP(heap + parent, heap + curr, int);
        curr = parent;
        parent = PARENT(curr);
    }
}

void bubbleDown(int* heap, int from, int size) {
    int curr = from;
    int left = LEFT(curr);
    int right = RIGHT(curr);

    if (left >= size) {
        return;
    }

    if (right >= size) {
        if (heap[curr] < heap[left]) {
            SWAP(heap + left, heap + curr, int);
        }
        
        return;
    }

    int maxNode = heap[left] > heap[right] ? (heap[left] > heap[curr] ? left : curr) : (heap[right] > heap[curr] ? right : curr);

    if (maxNode == curr) {
        return;
    }

    SWAP(heap + maxNode, heap + curr, int);
    bubbleDown(heap, maxNode, size);
}

void heapify(int* arr, int size) {
    for (int curr = LOWEST_PARENT(size); curr >= 0; --curr) {
        bubbleDown(arr, curr, size);
    }
}

int lastStoneWeight(int* stones, int stonesSize) {
    if (stonesSize == 0) {
        return 0;
    }

    heapify(stones, stonesSize);

    while (stonesSize > 1) {
        int y = HEAP_TOP(stones);
        HEAP_POP(stones, stonesSize);
        int x = HEAP_TOP(stones);
        HEAP_POP(stones, stonesSize);

        if (x < y) {
            HEAP_PUSH(stones, stonesSize, y - x);
        }
    }

    if (stonesSize == 0) {
        return 0;
    }

    return HEAP_TOP(stones);
}