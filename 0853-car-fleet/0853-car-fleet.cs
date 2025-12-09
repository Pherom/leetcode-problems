public class Solution {
    public int CarFleet(int target, int[] position, int[] speed) {
        int n = position.Length;
        var posTime = new (int Pos, double Time)[n];

        for (int i = 0; i < n; ++i) {
            double time = (double)(target - position[i]) / speed[i];
            posTime[i] = (position[i], time);
        }

        Array.Sort(posTime, (first, second) => {
            return first.Pos.CompareTo(second.Pos);
        });

        double currTime = posTime[n - 1].Time;
        int fleets = n;
        for (int i = n - 2; i >= 0; --i) {
            if (posTime[i].Time <= currTime) {
                --fleets;
            } else {
                currTime = posTime[i].Time;
            }
        }

        return fleets;
    }
}