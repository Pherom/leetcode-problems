class Solution {
private:
    string_view find(unordered_map<string_view, string_view>& emailToParent, string_view email) {
        if (email == emailToParent[email]) {
            return email;
        }

        emailToParent[email] = find(emailToParent, emailToParent[email]);
        return emailToParent[email];
    }

public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        unordered_map<string_view, string_view> emailToName{};
        unordered_map<string_view, string_view> emailToParent{};
        vector<vector<string>>::size_type n = accounts.size();

        for (vector<string>& acc : accounts) {
            vector<string>::size_type accSize = acc.size();
            string_view name = acc[0];

            for (int i = 1; i < accSize; ++i) {
                string_view email = acc[i];
                emailToParent[email] = email;
                emailToName[email] = name;
            }
        }

        for (vector<string>& acc : accounts) {
            vector<string>::size_type accSize = acc.size();
            string_view firstRep = find(emailToParent, acc[1]);

            for (int i = 2; i < accSize; ++i) {
                string_view rep = find(emailToParent, acc[i]);

                if (firstRep != rep) {
                    emailToParent[rep] = firstRep;
                }
            }
        }

        unordered_map<string_view, vector<string_view>> repToEmails{};

        for (pair<string_view, string_view> const& p : emailToParent) {
            string_view rep = find(emailToParent, p.first);

            auto it = repToEmails.find(rep);

            if (it == repToEmails.end()) {
                repToEmails.insert({rep, vector<string_view>{}});
            }

            repToEmails[rep].push_back(p.first);
        }

        for (pair<string_view, vector<string_view>> const& p : repToEmails) {
            std::sort(repToEmails[p.first].begin(), repToEmails[p.first].end());
        }

        vector<vector<string>> result{};
        result.reserve(n);

        for (pair<string_view, vector<string_view>> const& p : repToEmails) {
            result.push_back(vector<string>{string{emailToName[p.first]}});

            for (string_view email : p.second) {
                result.back().push_back(string{email});
            }
        }

        return result;
    }
};