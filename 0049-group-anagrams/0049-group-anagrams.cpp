class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> ordToAnagrams{};

        for (string const& str : strs) {
            string sortedStr{str};
            std::sort(sortedStr.begin(), sortedStr.end());

            auto it = ordToAnagrams.find(sortedStr);

            if (it == ordToAnagrams.end()) {
                ordToAnagrams.insert({sortedStr, vector<string>{}});
            }

            ordToAnagrams[sortedStr].push_back(str);
        }

        vector<vector<string>> result{};
        result.reserve(strs.size());

        for (auto const& p : ordToAnagrams) {
            result.emplace_back(std::move(p.second));
        }

        return result;
    }
};