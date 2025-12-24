#define PARENT(node) ( ( ( node ) - 1 ) / 2 )
#define LEFT(node) ( ( node ) * 2 + 1 )
#define RIGHT(node) ( ( node ) * 2 + 2 )
#define LOWEST_PARENT(heapSize) ( PARENT(( heapSize ) - 1) )

#define SWAP(first, second, type) {               \
            type temp = *( first );               \
            *( first ) = *( second );             \
            *( second ) = temp;                   \
        }

#define HEAP_PUSH(heap, size, item) {             \
            ( heap )[( size )++] = ( item );      \
            bubbleUp(( heap ), ( size ));         \
        }

#define HEAP_TOP(heap) ( ( heap )[0] )

#define HEAP_POP(heap, size) {                            \
            HEAP_TOP(( heap )) = ( heap )[--( size )];    \
            bubbleDown(( heap ), 0, ( size ));            \
        }

#define MAX(first, second) ( ( first ) > ( second ) ? ( first ) : ( second ) )

typedef struct CoordsEffort {
    int i;
    int j;
    int effort;
} CoordsEffort;

void bubbleUp(CoordsEffort* heap, int size) {
    int curr = size - 1;

    while (PARENT(curr) >= 0 && heap[PARENT(curr)].effort > heap[curr].effort) {
        SWAP(heap + PARENT(curr), heap + curr, CoordsEffort);
        curr = PARENT(curr);
    }
}

void bubbleDown(CoordsEffort* heap, int from, int size) {
    int left = LEFT(from);
    int right = RIGHT(from);

    if (left >= size) {
        return;
    }

    if (right >= size && heap[left].effort < heap[from].effort) {
        SWAP(heap + left, heap + from, CoordsEffort);
        return;
    }

    int minNode = heap[left].effort < heap[right].effort ? (heap[left].effort < heap[from].effort ? left : from) : (heap[right].effort < heap[from].effort ? right : from);

    if (minNode != from) {
        SWAP(heap + minNode, heap + from, CoordsEffort);
        bubbleDown(heap, minNode, size);
    }
}

void heapify(CoordsEffort* heap, int size) {
    for (int curr = LOWEST_PARENT(size); curr < size; ++curr) {
        bubbleDown(heap, curr, size);
    }
}

static const int di[4] = { 0,  0, -1, 1 };
static const int dj[4] = { 1, -1,  0, 0 };

int minimumEffortPath(int** heights, int heightsSize, int* heightsColSize) {
    int** effort = (int**)malloc(sizeof(int*) * heightsSize);

    // if (effort == NULL) {
    //     return -1;
    // }    

    for (int i = 0; i < heightsSize; ++i) {
        effort[i] = (int*)malloc(sizeof(int) * *heightsColSize);

        // if (effort[i] == NULL) {
        //     for (int j = 0; j < i; ++j) {
        //         free(effort[j]);
        //     }

        //     free(effort);
        //     return -1;
        // }

        for (int j = 0; j < *heightsColSize; ++j) {
            effort[i][j] = INT32_MAX;
        }
    }

    CoordsEffort* minHeap = (CoordsEffort*)malloc(sizeof(CoordsEffort) * heightsSize * *heightsColSize);

    // if (minHeap == NULL) {
    //     for (int i = 0; i < heightsSize; ++i) {
    //         free(effort[i]);
    //     }

    //     free(effort);
    // }

    int minHeapSize = 0;
    effort[0][0] = 0;
    CoordsEffort ce = {0, 0, 0};
    HEAP_PUSH(minHeap, minHeapSize, ce);

    int result = -1;

    while (minHeapSize > 0) {
        int i = HEAP_TOP(minHeap).i;
        int j = HEAP_TOP(minHeap).j;
        int e = HEAP_TOP(minHeap).effort;
        HEAP_POP(minHeap, minHeapSize);

        if (e > effort[i][j]) {
            continue;
        }

        if (i == heightsSize - 1 && j == *heightsColSize - 1) {
            result = e;
            break;
        }

        for (int k = 0; k < 4; ++k) {
            int ni = i + di[k];
            int nj = j + dj[k];

            if (ni < 0 || ni >= heightsSize || nj < 0 || nj >= *heightsColSize) {
                continue;
            }

            int diff = heights[ni][nj] - heights[i][j];
            if (diff < 0) {
                diff = -1 * diff;
            }
            int potentialEffort = MAX(diff, e);

            if (potentialEffort < effort[ni][nj]) {
                effort[ni][nj] = potentialEffort;
                CoordsEffort ce = {ni, nj, potentialEffort};
                HEAP_PUSH(minHeap, minHeapSize, ce);
            }
        }
    }

    free(minHeap);

    for (int i = 0; i < heightsSize; ++i) {
        free(effort[i]);
    }

    free(effort);

    return result;
}