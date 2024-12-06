#include <vector>
#include <string>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    struct TrieNode {
        bool isEnd;
        vector<TrieNode*> children;
        TrieNode() : isEnd(false), children(26, nullptr) {}
    };
    
    void insert(TrieNode* root, const string& word) {
        TrieNode* node = root;
        for(char c : word){
            if(!node->children[c - 'a']){
                node->children[c - 'a'] = new TrieNode();
            }
            node = node->children[c - 'a'];
        }
    }
    
    int minValidStrings(vector<string>& words, string target) {
        TrieNode* root = new TrieNode();
        for(auto &word : words){
            insert(root, word);
        }
        
        int n = target.size();
        vector<int> dp(n + 1, INT32_MAX);
        dp[0] = 0;
        
        for(int i = 0; i < n; ++i){
            if(dp[i] == INT32_MAX) continue;
            TrieNode* node = root;
            for(int j = i; j < n; ++j){
                char c = target[j];
                if(!node->children[c - 'a']) break;
                node = node->children[c - 'a'];
                dp[j + 1] = min(dp[j + 1], dp[i] + 1);
            }
        }
        
        return dp[n] == INT32_MAX ? -1 : dp[n];
    }
};

//  Test cases for the C++ solution
#include <cassert>

void testSolution(Solution& solution) {
    // Test case 1: Exact match with words as prefixes
    std::vector<std::string> words = {"ab", "abc", "bc"};
    std::string target = "abc";
    int expected_result = 1;  // "abc" matches exactly with one of the words
    assert(solution.minValidStrings(words, target) == expected_result && "Test case 1 failed.");

    // Test case 2: Multiple valid prefixes required to form target
    words = {"a", "b", "c"};
    target = "abc";
    expected_result = 3;  // Minimum 3 strings: "a" + "b" + "c"
    assert(solution.minValidStrings(words, target) == expected_result && "Test case 2 failed.");

    // Test case 3: Target cannot be formed
    words = {"abc", "aaaaa", "bcdef"};
    target = "aabcdabc";
    expected_result = 3;  // No possible way to form "abcd" with given words
    assert(solution.minValidStrings(words, target) == expected_result && "Test case 3 failed.");

    // Test case 4: Single word matches the whole target
    words = {"hello", "world", "helloworld"};
    target = "helloworld";
    expected_result = 1;  // "helloworld" directly matches
    assert(solution.minValidStrings(words, target) == expected_result && "Test case 4 failed.");

    // Test case 5: Overlapping prefixes required
    words = {"abababab", "ab"};
    target = "ababaababa";
    expected_result = 2;  // Minimum 2 strings: "abababab" + "ab"
    assert(solution.minValidStrings(words, target) == expected_result && "Test case 5 failed.");

    // Test case 6: Words contain all characters but not in prefix form
    words = {"abcdef"};
    target = "xyz";
    expected_result = -1;  // "xyz" can't be formed using the words as prefixes
    assert(solution.minValidStrings(words, target) == expected_result && "Test case 6 failed.");

    // Test case 7: Prefixes with varying lengths
    words = {"ab", "a", "abc", "bc", "c"};
    target = "abc";
    expected_result = 1;  // "abc" can be matched directly
    assert(solution.minValidStrings(words, target) == expected_result && "Test case 7 failed.");
}

int main() {
    Solution solution;
    for (int i = 0; i < 327680; ++i) {
        testSolution(solution);  
    }
    return 0;
}
