class MyHashMap {
private:
    vector<list<pair<int, int>>> mp{};
    static constexpr size_t capacity = 10000;

public:
    MyHashMap()
    : mp(capacity, list<pair<int, int>>{})
    {}
    
    void put(int key, int value) {
        list<pair<int, int>>& lst = mp[key % capacity];

        for (pair<int, int>& kv : lst) {
            if (kv.first == key) {
                kv.second = value;
                return;
            }
        }

        lst.push_back({key, value});
    }
    
    int get(int key) {
        list<pair<int, int>>& lst = mp[key % capacity];

        for (pair<int, int>& kv : lst) {
            if (kv.first == key) {
                return kv.second;
            }
        }

        return -1;
    }
    
    void remove(int key) {
        list<pair<int, int>>& lst = mp[key % capacity];

        auto it = find_if(lst.begin(), lst.end(), [key](pair<int, int>& p) {
            return p.first == key;
        });

        if (it == lst.end()) {
            return;
        }

        lst.erase(it);
    }
};

/**
 * Your MyHashMap object will be instantiated and called as such:
 * MyHashMap* obj = new MyHashMap();
 * obj->put(key,value);
 * int param_2 = obj->get(key);
 * obj->remove(key);
 */