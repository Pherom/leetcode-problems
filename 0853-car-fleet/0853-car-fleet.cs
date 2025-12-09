public class Solution {
    public int CarFleet(int target, int[] position, int[] speed) {
        int n = position.Length;
        var posTime = position.Zip(speed, (p, s) => (Pos: p, Time: (double)(target - p) / s))
                              .OrderByDescending(pt => pt.Pos)
                              .ToList();

        double currTime = posTime[0].Time;
        int fleets = n;
        for (int i = 1; i < n; ++i) {
            if (posTime[i].Time <= currTime) {
                --fleets;
            } else {
                currTime = posTime[i].Time;
            }
        }

        return fleets;
    }
}