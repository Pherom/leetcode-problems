class Solution {
private:
    struct Hash {
        size_t operator()(const array<int, 26>& a) const {
            size_t h = 0;
            for (int x : a) {
                h = (h*31) + x;
            }
            return h;
        }
    };

public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<array<int, 26>, vector<string>, Hash> ordToAnagrams{};

        for (string const& str : strs) {
            array<int, 26> counters{};

            for (char c : str) {
                ++counters[c - 'a'];
            }

            auto it = ordToAnagrams.find(counters);

            if (it == ordToAnagrams.end()) {
                it = ordToAnagrams.insert({std::move(counters), vector<string>{}}).first;
            }

            it->second.push_back(str);
        }

        vector<vector<string>> result{};
        result.reserve(strs.size());

        for (auto const& p : ordToAnagrams) {
            result.emplace_back(std::move(p.second));
        }

        return result;
    }
};