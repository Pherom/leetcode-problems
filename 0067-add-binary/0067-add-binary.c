#define MAX(first, second) (( first ) > ( second ) ? ( first ) : ( second ))

#define SWAP(first, second, type) {     \
            type temp = *( first );     \
            *( first ) = *( second );   \
            *( second ) = temp;         \
        }

void reverse(char* str, char* end) {
    char* left = str;
    char* right = end - 1;

    while (right - left > 0) {
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

    char* aCurr = a + aSize - 1;
    char* bCurr = b + bSize - 1;
    char* resCurr = res;
    unsigned char carry = 0;

    while (aCurr - a >= 0 && bCurr - b >= 0) {
        unsigned char aBit = *(aCurr--) - '0';
        unsigned char bBit = *(bCurr--) - '0';

        *(resCurr++) = aBit ^ bBit ^ carry + '0';
        carry = (aBit & bBit) | (aBit & carry) | (bBit & carry);
    }

    while (aCurr - a >= 0) {
        unsigned char aBit = *(aCurr--) - '0';
        *(resCurr++) = aBit ^ carry + '0';
        carry = aBit & carry;
    }
 
    while (bCurr - b >= 0) {
        unsigned char bBit = *(bCurr--) - '0';
        *(resCurr++) = bBit ^ carry + '0';
        carry = bBit & carry;
    }

    if (carry > 0) {
        *(resCurr++) = '1';
    }

    *resCurr = '\0';

    reverse(res, resCurr);
    return res;
}