public class KthLargest {

    private PriorityQueue<int, int> pq;
    private int cap;

    public KthLargest(int k, int[] nums) {
        cap = k;
        pq = new PriorityQueue<int, int>(k);

        foreach (int num in nums) {
            Add(num);
        }
    }
    
    public int Add(int val) {
        if (pq.Count == cap) {
            int top = pq.Peek();

            if (val <= top) {
                return top;
            }

            pq.Dequeue();
        }

        pq.Enqueue(val, val);
        return pq.Peek();
    }
}

/**
 * Your KthLargest object will be instantiated and called as such:
 * KthLargest obj = new KthLargest(k, nums);
 * int param_1 = obj.Add(val);
 */