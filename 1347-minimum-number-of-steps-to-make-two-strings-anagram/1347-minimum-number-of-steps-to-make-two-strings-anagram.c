int minSteps(char* s, char* t) {
    int counters[26] = {0};

    for (char* p = t; *p != '\0'; ++p) {
        ++counters[*p - 'a'];
    }

    int count = 0;
    for (char* p = s; *p != '\0'; ++p) {
        if (counters[*p - 'a'] == 0) {
            ++count;
        } else {
            --counters[*p - 'a'];
        }
    }

    return count;
}