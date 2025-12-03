class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> wordSet(wordList.begin(), wordList.end());
        size_t n = beginWord.size();
        queue<string> que{};

        que.push(beginWord);
        que.push("");
        int res = 1;

        while (!que.empty()) {
            string curr = std::move(que.front());
            que.pop();

            if (curr == endWord) {
                return res;
            }

            if (curr.empty() && !que.empty()) {
                que.push("");
                ++res;
                continue;
            }

            string cpy{curr};

            for (int i = 0; i < n; ++i) {
                for (char c = 'a'; c <= 'z'; ++c) {
                    if (curr[i] == c) {
                        continue;
                    }

                    cpy[i] = c;
                    auto it = wordSet.find(cpy);

                    if (it != wordSet.end()) {
                        wordSet.erase(it);
                        que.push(cpy);
                    }

                    cpy[i] = curr[i];
                }
            }
        }

        return 0;
    }
};