class SnapshotArray {
private:
    vector<map<int, int>> vec;
    int snapsTaken;

public:
    SnapshotArray(int length)
    : vec(length, map<int, int>{})
    , snapsTaken{0}
    {}
    
    void set(int index, int val) {
        auto it = vec[index].find(snapsTaken);

        if (it == vec[index].end()) {
            vec[index].insert({snapsTaken, val});
        } else {
            vec[index][snapsTaken] = val;
        }
    }
    
    int snap() {
        return snapsTaken++;
    }
    
    int get(int index, int snap_id) {
        auto it = vec[index].upper_bound(snap_id);

        if (it == vec[index].begin()) {
            return 0;
        }

        return std::prev(it)->second;
    }
};

/**
 * Your SnapshotArray object will be instantiated and called as such:
 * SnapshotArray* obj = new SnapshotArray(length);
 * obj->set(index,val);
 * int param_2 = obj->snap();
 * int param_3 = obj->get(index,snap_id);
 */