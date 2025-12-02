class Solution {
public:
    int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital) {
        vector<int>::size_type n = profits.size();

        vector<pair<int, int>> profByCap{};
        profByCap.reserve(n);

        //Zip profits and capital
        for (vector<int>::size_type i = 0; i < n; ++i) {
            profByCap.push_back({capital[i], profits[i]});
            if (capital[i] <= w) {
                
            }
        }

        //Sort by capital
        sort(profByCap.begin(), profByCap.end(), [](pair<int, int> const& first, pair<int, int> const& second) {
            return first.first < second.first;
        });

        priority_queue<int> possibleProfitsPQ{};
        int i = 0;

        while (k > 0) {
            while (i < n && profByCap[i].first <= w) {
                possibleProfitsPQ.push(profByCap[i].second);
                ++i;
            }

            if (possibleProfitsPQ.empty()) {
                return w;
            }

            w += possibleProfitsPQ.top();
            possibleProfitsPQ.pop();
            --k;
        }

        return w;
    }
};