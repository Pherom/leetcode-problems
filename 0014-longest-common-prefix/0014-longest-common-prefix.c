char* createCopyOf(char* str, size_t len) {
    char* res = (char*)malloc(sizeof(char) * (len + 1));

    if (res == NULL) {
        return NULL;
    }

    res[len] = '\0';
    strcpy(res, str);
    return res;
}

char* longestCommonPrefix(char** strs, int strsSize) {
    if (strs == NULL || strsSize == 0) {
        return "";
    }

    char const* first = strs[0];

    int i = 0;

    while (first[i] != '\0') {
        char fc = first[i];

        for (int j = 1; j < strsSize; ++j) {
            char const* curr = strs[j];
            char cc = curr[i];

            if (cc == '\0' || cc != fc) {
                char* res = (char*)malloc(sizeof(char) * (i + 1));

                if (res == NULL) {
                    return "";
                }

                res[i] = '\0';
                strncpy(res, first, i);
                return res;
            }
        }

        ++i;
    }

    return createCopyOf(first, i);
}