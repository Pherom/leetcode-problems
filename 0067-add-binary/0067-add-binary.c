#define MAX(first, second) (( first ) > ( second ) ? ( first ) : ( second ))

#define SWAP(first, second, type) {     \
            type temp = *( first );     \
            *( first ) = *( second );   \
            *( second ) = temp;         \
        }

void reverse(char* str, size_t size) {
    char* left = str;
    char* right = str + size - 1;

    while (left != right && left != right + 1) {
        SWAP(left, right, char);
        ++left;
        --right;
    }
}

char* addBinary(char* a, char* b) {
    size_t aSize = strlen(a);
    size_t bSize = strlen(b);
    size_t resMaxSize = MAX(aSize, bSize) + 2;

    char* res = (char*)malloc(sizeof(char) * resMaxSize);

    if (res == NULL) {
        return NULL;
    }

    size_t aCurr = aSize;
    size_t bCurr = bSize;
    size_t resCurr = 0;
    unsigned char carry = 0;

    while (aCurr > 0 && bCurr > 0) {
        unsigned char aBit = a[--aCurr] - '0';
        unsigned char bBit = b[--bCurr] - '0';

        res[resCurr++] = aBit ^ bBit ^ carry + '0';
        carry = (aBit & bBit) | (aBit & carry) | (bBit & carry);
    }

    while (aCurr > 0) {
        unsigned char aBit = a[--aCurr] - '0';
        res[resCurr++] = aBit ^ carry + '0';
        carry = aBit & carry;
    }
 
    while (bCurr > 0) {
        unsigned char bBit = b[--bCurr] - '0';
        res[resCurr++] = bBit ^ carry + '0';
        carry = bBit & carry;
    }

    if (carry > 0) {
        res[resCurr++] = '1';
    }

    res[resCurr] = '\0';

    reverse(res, resCurr);
    return res;
}