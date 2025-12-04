class WordDictionary {
private:
    struct TrieNode {
        array<unique_ptr<TrieNode>, 26> children{};
        bool is_word;

        TrieNode()
        : children{nullptr}
        , is_word{false}
        {}
    };

private:
    unique_ptr<TrieNode> root;

private:
    bool searchFrom(string_view word, size_t n, size_t i, TrieNode* root) const {
        TrieNode* curr = root;

        for (size_t j = i; j < n; ++j) {
            char c = word[j];

            if (c != '.') {
                if (curr->children[c - 'a'] == nullptr) {
                    return false;
                }

                curr = curr->children[c - 'a'].get();
            } else {
                bool res = false;

                for (int k = 0; k < 26; ++k) {
                    if (curr->children[k] != nullptr && searchFrom(word, n, j + 1, curr->children[k].get())) {
                        res = true;
                        break;
                    }
                }

                return res;
            }
        }

        return curr->is_word;
    }

public:
    WordDictionary()
    : root{make_unique<TrieNode>()}
    {}
    
    void addWord(string_view word) {
        TrieNode* curr = root.get();

        for (char c : word) {
            if (curr->children[c - 'a'] == nullptr) {
                curr->children[c - 'a'] = make_unique<TrieNode>();
            }

            curr = curr->children[c - 'a'].get();
        }

        curr->is_word = true;
    }
    
    bool search(string_view word) const {
        return searchFrom(word, word.size(), 0, root.get());
    }
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */