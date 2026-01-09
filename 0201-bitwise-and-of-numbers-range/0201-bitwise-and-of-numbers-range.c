int rangeBitwiseAnd(int left, int right) {
    int result = 0;
    int i = 0;

    while (left != right) {
        left >>= 1;
        right >>= 1;
        ++i;
    }

    return left << i;
}