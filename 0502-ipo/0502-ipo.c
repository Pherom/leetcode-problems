#define PARENT(node) ( ( node ) - 1 ) / 2
#define LEFT(node) ( ( node ) * 2 + 1 )
#define RIGHT(node) ( ( node ) * 2 + 2 )

#define SWAP(first, second, type) {     \
            type temp = *( first );     \
            *( first ) = *( second );   \
            *( second ) = temp;         \
        }

#define MAX_HEAP_CAP 100001
#define MAX_HEAP_TOP(maxHeap) ( ( maxHeap )[0] )
#define MAX_HEAP_PUSH(maxHeap, size, item) {        \
            maxHeap[(*( size ))++] = item;          \
            bubbleUp(maxHeap, *( size ));           \
        }
#define MAX_HEAP_POP(maxHeap, size) {                             \
            MAX_HEAP_TOP(( maxHeap )) = maxHeap[--(*( size ))];   \
            bubbleDown(maxHeap, *( size ));                       \
        }

typedef struct ProfitCapitalPair {
    int profit;
    int capital;
} ProfitCapitalPair;

int profitCapitalPairCmp(void const* first, void const* second) {
    ProfitCapitalPair const* firstPair = first;
    ProfitCapitalPair const* secondPair = second;

    return firstPair->capital - secondPair->capital;
}

void bubbleUp(int* maxHeap, int size) {
    int curr = size - 1;

    while (curr > 0 && maxHeap[curr] > maxHeap[PARENT(curr)]) {
        SWAP(maxHeap + curr, maxHeap + PARENT(curr), int);
        curr = PARENT(curr);
    }
}

void bubbleDown(int* maxHeap, int size) {
    int curr = 0;

    while (true) {
        int left = LEFT(curr);

        if (left >= size) {
            break;
        }

        int maxNode = left;
        int right = RIGHT(curr);

        if (right < size && maxHeap[right] > maxHeap[maxNode]) {
            maxNode = right;
        }

        if (maxHeap[curr] > maxHeap[maxNode]) {
            break;
        }

        SWAP(maxHeap + curr, maxHeap + maxNode, int);
        curr = maxNode;
    }
}

int maxHeap[MAX_HEAP_CAP];

int findMaximizedCapital(int k, int w, int* profits, int profitsSize, int* capital, int capitalSize) {
    ProfitCapitalPair* zipped = (ProfitCapitalPair*)malloc(sizeof(ProfitCapitalPair) * profitsSize);

    // if (zipped == NULL) {
    //     return -1;
    // }

    for (int i = 0; i < profitsSize; ++i) {
        ProfitCapitalPair* curr = zipped + i;

        curr->profit = profits[i];
        curr->capital = capital[i];
    }

    qsort((void*)zipped, profitsSize, sizeof(ProfitCapitalPair), profitCapitalPairCmp);

    int heapSize = 0;
    int i = 0;

    while (k --> 0) {
        while (i < profitsSize && zipped[i].capital <= w) {
            MAX_HEAP_PUSH(maxHeap, &heapSize, zipped[i++].profit);
        }

        if (heapSize == 0) {
            break;
        }

        int top = MAX_HEAP_TOP(maxHeap);
        w += top;
        MAX_HEAP_POP(maxHeap, &heapSize);
    }

    // free(zipped);
    return w;
}