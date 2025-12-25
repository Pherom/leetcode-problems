public class SnapshotArray {

    List<List<(int Snap, int Val)>> snapsByIndex;
    private int snapsTaken;

    public SnapshotArray(int length) {
        snapsByIndex = new List<List<(int Snap, int Val)>>(length);
        for (int i = 0; i < length; ++i) {
            snapsByIndex.Add(new List<(int Snap, int Val)>());
        }
        snapsTaken = 0;
    }
    
    public void Set(int index, int val) {
        List<(int Snap, int Val)> snaps = snapsByIndex[index];

        if (snaps.Count == 0) {
            snaps.Add((snapsTaken, val));
        } else {
            if (snaps.Last().Snap == snapsTaken) {
                snaps[^1] = (snapsTaken, val);
            } else {
                snaps.Add((snapsTaken, val));
            }
        }
    }
    
    public int Snap() {
        return snapsTaken++;
    }
    
    public int Get(int index, int snap_id) {
        if (snapsByIndex[index] == null) {
            return 0;
        }

        int left = 0;
        int right = snapsByIndex[index].Count - 1;
        int res = 0;

        while (left <= right) {
            int mid = (left + right) / 2;
            int midSnap = snapsByIndex[index][mid].Snap;
            int midVal = snapsByIndex[index][mid].Val;

            if (midSnap == snap_id) {
                return midVal;
            } else if (midSnap < snap_id) {
                res = midVal;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        return res;
    }
}

/**
 * Your SnapshotArray object will be instantiated and called as such:
 * SnapshotArray obj = new SnapshotArray(length);
 * obj.Set(index,val);
 * int param_2 = obj.Snap();
 * int param_3 = obj.Get(index,snap_id);
 */