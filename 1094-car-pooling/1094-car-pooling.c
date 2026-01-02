#define SWAP(first, second, type) {     \
            type temp = *( first );     \
            *( first ) = *( second );   \
            *( second ) = temp;         \
        }

#define PARENT(node) ( ( ( node ) - 1 ) / 2 )
#define LEFT(node) ( ( ( node ) * 2 ) + 1 )
#define RIGHT(node) ( ( ( node ) * 2 ) + 2 )
#define MIN_HEAP_TOP(minHeap) ( ( minHeap )[0] )

typedef struct Passengers {
    int count;
    int headingTo;
} Passengers;

static void bubbleUp(Passengers* minHeap, int size) {
    int curr = size - 1;

    while (curr > 0 && minHeap[PARENT(curr)].headingTo > minHeap[curr].headingTo) {
        SWAP(minHeap + PARENT(curr), minHeap + curr, Passengers);
        curr = PARENT(curr);
    }
}

static void bubbleDown(Passengers* minHeap, int size) {
    int curr = 0;
    
    while (LEFT(curr) < size) {
        int left = LEFT(curr);
        int right = RIGHT(curr);

        int minNode = left;

        if (right < size && minHeap[right].headingTo < minHeap[left].headingTo) {
            minNode = right;
        }

        if (minHeap[curr].headingTo < minHeap[minNode].headingTo) {
            break;
        }

        SWAP(minHeap + curr, minHeap + minNode, Passengers);
        curr = minNode;
    }
}

void minHeapPush(Passengers* minHeap, int* size, Passengers passengers) {
    minHeap[*size] = passengers;
    ++*size;
    bubbleUp(minHeap, *size);
}

void minHeapPop(Passengers* minHeap, int* size) {
    --*size;
    MIN_HEAP_TOP(minHeap) = minHeap[*size];
    bubbleDown(minHeap, *size);
}

static int compareTripsByFrom(void const* first, void const* second) {
    return (*((int**)first))[1] - (*((int**)second))[1];
}

bool carPooling(int** trips, int tripsSize, int* tripsColSize, int capacity) {
    Passengers* minHeap = (Passengers*)malloc(sizeof(Passengers) * capacity);

    if (minHeap == NULL) {
        return false; // Would've preferred returning an error
    }

    int minHeapSize = 0;
    int seatsTaken = 0;

    qsort(trips, tripsSize, sizeof(int*), compareTripsByFrom);
    
    for (int i = 0; i < tripsSize; ++i) {
        int distTraveled = trips[i][1];

        while (minHeapSize > 0 && MIN_HEAP_TOP(minHeap).headingTo <= distTraveled) {
            seatsTaken -= MIN_HEAP_TOP(minHeap).count;
            minHeapPop(minHeap, &minHeapSize);
        }

        Passengers passengers = { trips[i][0], trips[i][2] };

        if (passengers.count > capacity - seatsTaken) {
            // free(minHeap);
            return false;
        }
        
        minHeapPush(minHeap, &minHeapSize, passengers);
        seatsTaken += passengers.count;
    }

    // free(minHeap);
    return true;
}