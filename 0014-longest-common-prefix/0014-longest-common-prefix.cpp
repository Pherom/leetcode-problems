class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        vector<string>::size_type n = strs.size();
        string& model = strs[0];

        if (n == 1) {
            return model;
        }
        
        size_t modelSize = model.size();
        int i = 0;
        bool found = false;

        for (; i < modelSize; ++i) {
            for (int j = 1; j < n; ++j) {
                string& currStr = strs[j];

                if (i >= currStr.size() || currStr[i] != model[i]) {
                    found = true;
                    break;
                }
            }

            if (found) {
                break;
            }
        }

        return model.substr(0, i);
    }
};