#define TOTAL_CHARS (1 << (sizeof(char)) * CHAR_BIT)
#define MAX(first, second) ( ( first ) > ( second ) ? ( first ) : ( second ) )

int lengthOfLongestSubstring(char* s) {
    int lastSeen[TOTAL_CHARS];
    int result  = 0;

    for (int c = 0; c < TOTAL_CHARS; ++c) {
        lastSeen[c] = -1;
    }

    char* start = s;
    char* p = s;
    for (; *p != '\0'; ++p) {
        unsigned char lsIdx = *p;
        if (lastSeen[lsIdx] != -1 && s + lastSeen[lsIdx] >= start) {
            result = MAX(result, p - start);
            start = s + lastSeen[lsIdx] + 1;
        }

        lastSeen[lsIdx] = p - s;
    }

    result = MAX(result, p - start);
    return result;
}