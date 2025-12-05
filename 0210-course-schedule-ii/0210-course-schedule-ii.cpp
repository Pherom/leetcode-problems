class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> adj(numCourses, vector<int>{});
        vector<int> in(numCourses, 0);
        queue<int> que{};
        vector<int> res{};
        res.reserve(numCourses);

        for (vector<int> const& pre : prerequisites) {
            int u = pre[1];
            int v = pre[0];

            adj[pre[1]].push_back(pre[0]);
            ++in[v];
        }

        for (int u = 0; u < numCourses; ++u) {
            if (in[u] == 0) {{
                que.push(u);
            }}
        }

        while(!que.empty()) {
            int u = que.front();
            que.pop();

            res.push_back(u);

            for (int v : adj[u]) {
                --in[v];

                if (in[v] == 0) {
                    que.push(v);
                }
            }
        }

        return res.size() == numCourses ? res : vector<int>{};
    }
};