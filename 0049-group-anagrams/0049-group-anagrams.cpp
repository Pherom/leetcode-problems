class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> ordToAnagrams{};
        array<int, 26> counters{};

        for (string const& str : strs) {
            for (char c : str) {
                ++counters[c - 'a'];
            }

            string sortedStr{};
            sortedStr.reserve(str.size());

            for (int i = 0; i < 26; ++i) {
                while (counters[i] > 0) {
                    sortedStr.push_back('a' + i);
                    --counters[i];
                }
            }

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