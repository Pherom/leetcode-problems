#define TOTAL_CHARS (1 << (sizeof(char)) * CHAR_BIT)
#define MAX(first, second) ( ( first ) > ( second ) ? ( first ) : ( second ) )

int lengthOfLongestSubstring(char* s) {
    char* lastSeen[TOTAL_CHARS];
    int result  = 0;

    memset(lastSeen, 0, sizeof(char*) * TOTAL_CHARS);

    char* start = s;
    char* p = s;
    for (; *p != '\0'; ++p) {
        unsigned char lsIdx = *p;

        if (lastSeen[lsIdx] != NULL && lastSeen[lsIdx] - start >= 0) {
            result = MAX(result, p - start);
            start = lastSeen[lsIdx] + 1;
        }

        lastSeen[lsIdx] = p;
    }

    result = MAX(result, p - start);
    return result;
}