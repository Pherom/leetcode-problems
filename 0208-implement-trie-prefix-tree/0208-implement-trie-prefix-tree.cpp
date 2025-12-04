class Trie {
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
    unique_ptr<TrieNode> root;

public:
    Trie()
    : root{make_unique<TrieNode>()}
    {}
    
    void insert(string_view word) {
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
        TrieNode* curr = root.get();

        for (char c : word) {
            if (curr->children[c - 'a'] == nullptr) {
                return false;
            }

            curr = curr->children[c - 'a'].get();
        }

        return curr->is_word;
    }
    
    bool startsWith(string_view prefix) const {
        TrieNode* curr = root.get();

        for (char c : prefix) {
            if (curr->children[c - 'a'] == nullptr) {
                return false;
            }

            curr = curr->children[c - 'a'].get();
        }

        return true;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */