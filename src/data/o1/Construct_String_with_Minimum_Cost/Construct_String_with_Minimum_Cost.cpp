#include <vector>
#include <string>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    int minimumCost(string target, vector<string>& words, vector<int>& costs) {
        int n = target.size();
        // Initialize DP array with INF
        vector<long long> dp(n + 1, LLONG_MAX);
        dp[0] = 0;
        
        // Iterate through each position in target
        for(int i = 0; i < n; ++i){
            if(dp[i] == LLONG_MAX) continue; // Skip unreachable positions
            
            // Try all words
            for(int j = 0; j < words.size(); ++j){
                string word = words[j];
                int cost = costs[j];
                int len = word.size();
                
                // Check if the word matches the substring starting at position i
                if(i + len > n) continue;
                if(target.substr(i, len) == word){
                    if(dp[i + len] > dp[i] + (long long)cost){
                        dp[i + len] = dp[i] + (long long)cost;
                    }
                }
            }
        }
        
        return dp[n] == LLONG_MAX ? -1 : (int)dp[n];
    }
};

//  Test cases for the C++ solution
#include <cassert>

// Test cases for the C++ solution
void testSolution(Solution& solution) {
    // Test case 1: Simple case with exact match and different costs
    std::string target = "abcdef";
    std::vector<std::string> words = {"abdef", "abc", "d", "def", "ef"};
    std::vector<int> costs = {100, 1, 1, 10, 5};
    int expected_result = 7;
    assert(solution.minimumCost(target, words, costs) == expected_result && "Test case 1 failed.");

    // Test case 2: Using a combination of single and multiple characters
    target = "aaaa";
    words = {"z", "zz", "zzz"};
    costs = {1, 10, 100};
    expected_result = -1;
    assert(solution.minimumCost(target, words, costs) == expected_result && "Test case 2 failed.");

    // Test case 3: No possible way to construct target
    target = "abccba";
    words = {"abc", "ab", "ccba", "c", "ba"};
    costs = {10, 1, 20, 5, 2};
    expected_result = 13;
    assert(solution.minimumCost(target, words, costs) == expected_result && "Test case 3 failed.");

    // Test case 4: Exact matches with overlapping options
    target = std::string(1000, 'a');
    words = {"a", "aa", "aaa"};
    costs = {1, 2, 3};
    expected_result = 1000;
    assert(solution.minimumCost(target, words, costs) == expected_result && "Test case 4 failed.");

    // Test case 5: Large overlap possibilities with minimum cost
    target = "xyzxyzxyz";
    words = {"xyz", "xy", "zxy", "yz", "xyzxyz"};
    costs = {5, 3, 6, 2, 8};
    expected_result = 13;
    assert(solution.minimumCost(target, words, costs) == expected_result && "Test case 5 failed.");

    // Test case 6: Only one word needed
    target = "code";
    words = {"code", "ode", "de"};
    costs = {10, 8, 7};
    expected_result = 10;  // "code" matches entirely with cost 10
    assert(solution.minimumCost(target, words, costs) == expected_result && "Test case 6 failed.");

    // Test case 7: Multiple paths but all paths are not possible
    target = "abcd";
    words = {"ab", "cd", "ef"};
    costs = {3, 4, 5};
    expected_result = 7;  // "ab" + "cd" gives the target with cost 3 + 4 = 7
    assert(solution.minimumCost(target, words, costs) == expected_result && "Test case 7 failed.");
}

int main() {
    Solution solution;
    for (int i = 0; i < 81920; ++i) {
        testSolution(solution);  
    }
    return 0;
}