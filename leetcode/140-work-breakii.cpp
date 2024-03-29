#include "../leetcodeutil.h"

class Solution {
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> dict(wordDict.cbegin(), wordDict.cend());
        return wordBreak(s, dict);
    }
private:
    // >> append({"cats and", "cat sand"}, "dog");
    // {"cats and dog", "cat sand dog"}
    vector<string> append(const vector<string>& prefixes, const string& word) {
        vector<string> results;
        for(const auto& prefix : prefixes)
            results.push_back(prefix + " " + word);
        return results;
    }
    
    const vector<string>& wordBreak(string s, unordered_set<string>& dict) {
        // Already in memory, return directly
        if(mem_.count(s)) return mem_[s];
        
        // Answer for s
        vector<string> ans;
        
        // s in dict, add it to the answer array
        if(dict.count(s)) 
            ans.push_back(s);
        
        for(int j=1;j<s.length();++j) {
            // Check whether right part is a word
            const string& right = s.substr(j);
            if (!dict.count(right)) continue;
            
            // Get the ans for left part
            const string& left = s.substr(0, j);
            const vector<string> left_ans = 
                append(wordBreak(left, dict), right);
            
            // Notice, can not use mem_ here,
            // since we haven't got the ans for s yet.
            ans.insert(ans.end(), left_ans.begin(), left_ans.end());
        }
        
        // memorize and return
        mem_[s].swap(ans);
        return mem_[s];
    }
private:
    unordered_map<string, vector<string>> mem_;
};

// 动态规划求解
class Solution {
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        unordered_map<string, vector<string>> dp;
        return helper(s, dp, wordDict);
    }
    
    vector<string> helper(string s, unordered_map<string, vector<string>>& dp, vector<string>& dict) {
        if (dp.find(s) != dp.end()) return dp[s];
        vector<string> res;
        if (s.empty()) return {""};
        for (string& str : dict) {
            if (s.size() < str.size()) continue;
            if (s.substr(0,str.size()) != str) continue;
            vector<string> later = helper(s.substr(str.size()), dp, dict);
            for (string l : later) {
                res.push_back(str + (l.empty() ? "" : " ") + l);
            }
        }
        return dp[s] = res;
    }
};


int main(int argc, char const *argv[])
{
    
    return 0;
}

