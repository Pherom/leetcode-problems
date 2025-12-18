public class Solution {
    public int LeastInterval(char[] tasks, int n) {
        int[] counters = new int[26];

        foreach (char task in tasks) {
            ++counters[task - 'A'];
        }

        PriorityQueue<int, int> pq = new PriorityQueue<int, int>();

        for (int i = 0; i < 26; ++i) {
            int count = counters[i];

            if (count > 0) {
                pq.Enqueue(count, -1 * count);
            }
        }

        Queue<(int, int)> que = new Queue<(int, int)>();

        int time = 0;
        while (pq.Count > 0 || que.Count > 0) {
            while (que.Count > 0) {
                int scheduledOn = que.Peek().Item1;
                int c = que.Peek().Item2;
                
                if (scheduledOn <= time) {
                    pq.Enqueue(c, -1 * c);
                    que.Dequeue();
                } else {
                    break;
                }
            }

            ++time;

            if (pq.Count > 0) {
                int count = pq.Dequeue();

                if (--count > 0) {
                    que.Enqueue((time + n, count));
                }
            }
        }

        return time;
    }
}