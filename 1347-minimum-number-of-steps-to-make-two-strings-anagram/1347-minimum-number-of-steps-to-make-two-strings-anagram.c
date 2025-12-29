int minSteps(char* s, char* t) {
    int counts[26] = {0};

    char* ps = s;
    for (char* pt = t; *pt != '\0'; ++pt) {
        --counts[*pt - 'a'];
        ++counts[*ps - 'a'];
        ++ps;
    }

    int steps = 0;
    for (int i = 0; i < 26; ++i) {
        int count = counts[i];

        if (count > 0) {
            steps += count;
        }
    }

    return steps;
}