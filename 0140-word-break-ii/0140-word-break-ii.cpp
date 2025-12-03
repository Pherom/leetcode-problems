class Solution {
private:
    struct TrieNode {
        array<unique_ptr<TrieNode>, 26> children;
        bool is_word;

        TrieNode()
        : children{nullptr}
        , is_word{false}
        {}
    };

private:
    void initTrie(TrieNode* root, vector<string> const& wordDict) {
        for (string const& word : wordDict) {
            TrieNode* curr = root;

            for (char c : word) {
                if (curr->children[c - 'a'] == nullptr) {
                    curr->children[c - 'a'] = std::make_unique<TrieNode>();
                }

                curr = curr->children[c - 'a'].get();
            }

            curr->is_word = true;
        }
    }

    void backtrack(vector<string>& res, string& curr, string const& s, size_t sLen, int i, TrieNode* root) {
        if (i == sLen) {
            curr.pop_back();
            res.push_back(curr);
            curr.push_back(' ');
            return;
        }

        TrieNode* trieCurr = root;

        for (int j = i; j < sLen; ++j) {
            char c = s[j];

            if (trieCurr->children[c - 'a'] == nullptr) {
                break;
            }

            if (trieCurr->children[c - 'a']->is_word) {
                size_t wordLen = j - i + 1;
                curr += s.substr(i, wordLen) + " ";
                backtrack(res, curr, s, sLen, j + 1, root);
                curr.resize(curr.size() - wordLen - 1);
            }

            trieCurr = trieCurr->children[c - 'a'].get();
        }
    }

public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        unique_ptr<TrieNode> root{std::make_unique<TrieNode>()};
        initTrie(root.get(), wordDict);
        vector<string> res{};
        string curr{};

        backtrack(res, curr, s, s.size(), 0, root.get());

        return res;
    }
};