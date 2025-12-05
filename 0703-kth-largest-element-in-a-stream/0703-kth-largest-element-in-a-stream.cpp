class KthLargest {
private:
    priority_queue<int, vector<int>, greater<int>> pq{};
    int k;

public:
    KthLargest(int k, vector<int>& nums) : k{k} {
        int n = nums.size();
        int m = min(k, n);
        int i = 0;

        for (; i < m; ++i) {
            pq.push(nums[i]);
        }

        for (; i < n; ++i) {
            add(nums[i]);
        }
    }
    
    int add(int val) {
        if (pq.size() == k) {
            int top = pq.top();

            if (val <= top) {
                return top;
            }

            pq.pop();
        }
        
        pq.push(val);
        return pq.top();
    }
};

/**
 * Your KthLargest object will be instantiated and called as such:
 * KthLargest* obj = new KthLargest(k, nums);
 * int param_1 = obj->add(val);
 */