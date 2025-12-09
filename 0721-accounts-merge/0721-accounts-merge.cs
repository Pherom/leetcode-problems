public class Solution {
    public IList<IList<string>> AccountsMerge(IList<IList<string>> accounts) {
        Dictionary<string, int> emailToId = new Dictionary<string, int>();
        Dictionary<int, string> emailIdToName = new Dictionary<int, string>();
        Dictionary<int, int> parent = new();
        int length = accounts.Count;
        int emailId = 0;

        for (int i = 0; i < length; ++i) {
            IList<string> account = accounts[i];
            int accLength = account.Count;

            for (int j = 1; j < accLength; ++j) {
                string email = account[j];

                if (emailToId.TryAdd(email, emailId)) {
                    ++emailId;
                }

                int id = emailToId[email];
                parent[id] = id;
                emailIdToName[id] = account[0];
            }
        }

        int find(Dictionary<int, int> parent, int id) {
            if (parent[id] == id) {
                return id;
            }

            parent[id] = find(parent, parent[id]);
            return parent[id];
        }

        for (int i = 0; i < length; ++i) {
            IList<string> account = accounts[i];
            int accLength = account.Count;
            int firstRep = find(parent, emailToId[account[1]]);

            for (int j = 2; j < accLength; ++j) {
                int rep = find(parent, emailToId[account[j]]);
                
                if (rep != firstRep) {
                    parent[rep] = firstRep;
                }
            }
        }

        Dictionary<int, List<string>> repToEmails = new();

        foreach (var (email, id) in emailToId) {
            int rep = find(parent, id);

            if (!repToEmails.ContainsKey(rep)) {
                repToEmails[rep] = new();
            }

            repToEmails[rep].Add(email);
        }

        foreach(var emails in repToEmails.Values) {
            emails.Sort(StringComparer.Ordinal);
        }

        IList<IList<string>> result  = new List<IList<string>>();

        foreach (var emails in repToEmails.Values) {
            string name = emailIdToName[emailToId[emails[0]]];
            result.Add(new List<string>{ name });
            
            foreach (var email in emails) {
                result.Last().Add(email);
            }
        }

        return result;
    }
}