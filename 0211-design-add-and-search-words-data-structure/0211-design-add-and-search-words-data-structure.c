
typedef struct TrieNode TrieNode;

struct TrieNode {
    TrieNode* children[26];
    bool isWord;
};

typedef struct {
    TrieNode* root;
} WordDictionary;


TrieNode* trieNodeCreate() {
    TrieNode* res = (TrieNode*)malloc(sizeof(TrieNode));

    if (res == NULL) {
        return NULL;
    }

    memset(res->children, 0, sizeof(TrieNode*) * 26);
    res->isWord = false;

    return res;
}

void trieNodeDestroy(TrieNode** node) {
    if (node == NULL || *node == NULL) {
        return;
    }

    for (int i = 0; i < 26; ++i) {
        trieNodeDestroy((*node)->children + i);
    }

    free(*node);
    *node = NULL;
}

WordDictionary* wordDictionaryCreate() {
    TrieNode* root = trieNodeCreate();

    if (root == NULL) {
        return NULL;
    }

    WordDictionary* wd = (WordDictionary*)malloc(sizeof(WordDictionary));

    if (wd == NULL) {
        trieNodeDestroy(&root);
        return NULL;
    }

    wd->root = root;
    return wd;
}

void wordDictionaryAddWord(WordDictionary* wd, char* word) {
    if (wd == NULL || word == NULL) {
        return;
    }

    TrieNode* curr = wd->root;

    for (char* p = word; *p != '\0'; ++p) {
        TrieNode* next = curr->children[*p - 'a'];

        if (next == NULL) {
            next = trieNodeCreate();
            curr->children[*p - 'a'] = next;
        }

        curr = next;
    }

    curr->isWord = true;
}

static bool trieNodeSearchFrom(TrieNode* from, char* word) {
    if (from == NULL) {
        return false;
    }

    TrieNode* curr = from;

    for (char *p = word; *p != '\0'; ++p) {
        if (*p == '.') {
            for (int i = 0; i < 26; ++i) {
                if (trieNodeSearchFrom(curr->children[i], p + 1)) {
                    return true;
                }
            }

            return false;
        }

        TrieNode* next = curr->children[*p - 'a'];

        if (next == NULL) {
            return false;
        }

        curr = next;
    }

    return curr->isWord;
}

bool wordDictionarySearch(WordDictionary* wd, char* word) {
    if (wd == NULL || word == NULL) {
        return false;
    }

    return trieNodeSearchFrom(wd->root, word);
}

void wordDictionaryFree(WordDictionary* wd) {
    if (wd == NULL) {
        return;
    }

    trieNodeDestroy(&(wd->root));
    free(wd);
}

/**
 * Your WordDictionary struct will be instantiated and called as such:
 * WordDictionary* obj = wordDictionaryCreate();
 * wordDictionaryAddWord(obj, word);
 
 * bool param_2 = wordDictionarySearch(obj, word);
 
 * wordDictionaryFree(obj);
*/