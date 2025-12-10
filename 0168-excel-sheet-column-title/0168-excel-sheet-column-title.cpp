class Solution {
public:
    string convertToTitle(int columnNumber) {
        string result{};

        while (columnNumber --> 0) {
            char c = (columnNumber % 26) + 'A';
            columnNumber /= 26;
            result.push_back(c);
        }

        std::reverse(result.begin(), result.end());
        return result;
    }
};