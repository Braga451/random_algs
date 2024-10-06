class Solution {
public:
    int numUniqueEmails(vector<string>& emails) {
        unordered_map<string, bool> map;
        
        int unique = 0;
        
        for (const string& email : emails) {
            int separatorIndex = email.find("@");

            string local = email.substr(0, separatorIndex);
            local = local.substr(0, local.find("+"));
            std::erase(local, '.');
            string domain = email.substr(separatorIndex, email.length());

            if (!map.contains(local + domain)) {
                map[local + domain] = true;
                unique++;
            }
        }

        return unique;
    }
};
