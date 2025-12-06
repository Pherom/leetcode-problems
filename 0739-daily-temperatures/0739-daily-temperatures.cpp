class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        vector<int>::size_type n = temperatures.size();
        vector<int> answer(n, 0);
        stack<int> maxIdxStack{};

        for (int i = n - 1; i >= 0; --i) {
            while (!maxIdxStack.empty() && temperatures[maxIdxStack.top()] <= temperatures[i]) {
                maxIdxStack.pop();
            }

            if (!maxIdxStack.empty()) {
                answer[i] = maxIdxStack.top() - i;
            }

            maxIdxStack.push(i);
        }

        return answer;
    }
};