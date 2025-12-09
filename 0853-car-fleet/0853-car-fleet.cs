public class Solution {
    public int CarFleet(int target, int[] position, int[] speed) {
        int n = position.Length;
        var timeLeft = new double[target + 1];

        for (int i = 0; i < n; ++i) {
            timeLeft[position[i]] = (double)(target - position[i]) / speed[i];
        }

        double currTime = 0;
        int fleets = 0;
        for (int i = target; i >= 0; --i) {
            double tl = timeLeft[i];

            if (tl > currTime) {
                ++fleets;
                currTime = tl;
            }
        }

        return fleets;
    }
}