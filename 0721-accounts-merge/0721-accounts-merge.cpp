class Solution {
private:
    int find(vector<int>& parent, int u) {
        if (parent[u] == u) {
            return u;
        }

        parent[u] = find(parent, parent[u]);
        return parent[u];
    }

public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        vector<vector<string>>::size_type n = accounts.size();
        unordered_map<string, int> emailToId{};
        int emailId = 0;

        for (vector<string>& acc : accounts) {
            vector<string>::size_type accSize = acc.size();

            for (int i = 1; i < accSize; ++i) {
                auto it = emailToId.find(acc[i]);

                if (it == emailToId.end()) {
                    emailToId.insert({acc[i], emailId++});
                }
            }
        }

        vector<int> parent(emailId);
        std::iota(parent.begin(), parent.end(), 0);

        int resSize = emailId;

        for (vector<string>& acc : accounts) {
            vector<string>::size_type accSize = acc.size();
            int firstRep = find(parent, emailToId[acc[1]]);

            for (int i = 2; i < accSize; ++i) {
                int id = emailToId[acc[i]];
                int rep = find(parent, id);

                if (firstRep != rep) {
                    --resSize;
                    parent[rep] = firstRep;
                }
            }
        }

        vector<set<string>> temp(resSize, set<string>{});
        unordered_map<int, int> repToIdx{};
        vector<string> idxToName(resSize);
        int idx = 0;

        for (vector<string> const& acc : accounts) {
            vector<string>::size_type accSize = acc.size();
            int rep = find(parent, emailToId[acc[1]]);

            auto it = repToIdx.find(rep);

            if (it == repToIdx.end()) {
                repToIdx.insert({rep, idx++});
            }

            int idx = repToIdx[rep];
            set<string>& newAcc = temp[idx];
            idxToName[idx] = acc[0];

            for (int i = 1; i < accSize; ++i) {
                newAcc.insert(acc[i]);
            }
        }

        vector<vector<string>> result{};
        result.reserve(resSize);

        for (int i = 0; i < resSize; ++i) {
            result.push_back(vector<string>{idxToName[i]});
            
            for (string const& email : temp[i]) {
                result[i].push_back(email);
            }
        }

        return result;
    }
};