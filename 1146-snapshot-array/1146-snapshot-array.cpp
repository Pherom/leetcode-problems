class SnapshotArray {
private:
    vector<vector<pair<int, int>>> versionsByIdx;
    int snapsTaken;

public:
    SnapshotArray(int length)
    : versionsByIdx(length, vector<pair<int, int>>{})
    , snapsTaken{0}
    {}
    
    void set(int index, int val) {
        vector<pair<int ,int>>& versions = versionsByIdx[index];

        if (!versions.empty() && versions.back().first == snapsTaken) {
            versions.back().second = val;
        } else {
            versions.push_back({snapsTaken, val});
        }
    }
    
    int snap() {
        return snapsTaken++;
    }
    
    int get(int index, int snap_id) {
        vector<pair<int, int>>& versions = versionsByIdx[index];
        int left = 0;
        int right = versions.size() - 1;

        int floor_idx = -1;
        while (left <= right) {
            int mid = (left + right) / 2;

            if (versions[mid].first <= snap_id) {
                floor_idx = mid;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        if (floor_idx == -1) {
            return 0;
        }

        return versions[floor_idx].second;
    }
};

/**
 * Your SnapshotArray object will be instantiated and called as such:
 * SnapshotArray* obj = new SnapshotArray(length);
 * obj->set(index,val);
 * int param_2 = obj->snap();
 * int param_3 = obj->get(index,snap_id);
 */