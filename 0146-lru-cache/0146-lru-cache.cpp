class LRUCache {
private:
    unordered_map<int, list<pair<int, int>>::iterator> mp;
    list<pair<int, int>> lst;
    int capacity;

public:
    LRUCache(int capacity)
    : mp{}
    , lst{}
    , capacity{capacity}
    {    
    }
    
    int get(int key) {
        auto it = mp.find(key);

        if (it == mp.end()) {
            return -1;
        }

        lst.splice(lst.begin(), lst, it->second);
        return it->second->second;
    }
    
    void put(int key, int value) {
        auto it = mp.find(key);

        if (it == mp.end()) {
            lst.push_front({key, value});
            it = mp.insert({key, lst.begin()}).first;

            if (lst.size() > capacity) {
                mp.erase(lst.back().first);
                lst.pop_back();
            }
        } else {
            lst.splice(lst.begin(), lst, it->second);
            it->second->second = value;
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */