#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    vector<long long> countKConstraintSubstrings(string s, int k, vector<vector<int>>& queries) {
        int n = s.size();
        vector<long long> answer;
        
        for (const auto& query : queries) {
            int l = query[0], r = query[1];
            long long count = 0;
            
            for (int i = l; i <= r; ++i) {
                int zeros = 0, ones = 0;
                for (int j = i; j <= r; ++j) {
                    if (s[j] == '0') zeros++;
                    else ones++;
                    
                    if (zeros <= k || ones <= k) {
                        count++;
                    } else {
                        break;
                    }
                }
            }
            
            answer.push_back(count);
        }
        
        return answer;
    }
};

//  Test cases for the C++ solution
#include <cassert>

// Test cases for the C++ solution
void testSolution(Solution& solution) {
    // Test case 1: Single character satisfying any constraint
    std::string s = "0";
    int k = 1;
    std::vector<std::vector<int>> queries = {{0, 0}};
    std::vector<long long> expected_result = {1};  // Only one substring: "0", which satisfies the constraint
    assert(solution.countKConstraintSubstrings(s, k, queries) == expected_result && "Test case 1 failed.");

    // Test case 2: All zeros with multiple queries
    s = "0000";
    k = 2;
    queries = {{0, 1}, {1, 3}};
    expected_result = {3, 6};  // Substrings "00", "0" (3 substrings for [0,1]) and all 6 substrings for [1,3]
    assert(solution.countKConstraintSubstrings(s, k, queries) == expected_result && "Test case 2 failed.");

    // Test case 3: Mixed binary string with k = 2
    s = "0001111";
    k = 2;
    queries = {{0, 6}};
    expected_result = {26};  // Substrings with either one 0 or one 1 within specified ranges
    assert(solution.countKConstraintSubstrings(s, k, queries) == expected_result && "Test case 3 failed.");

    // Test case 4: Substring range that includes all characters
    s = "101";
    k = 2;
    queries = {{0, 2}};
    expected_result = {6};  // All substrings satisfy the k-constraint as k = 2
    assert(solution.countKConstraintSubstrings(s, k, queries) == expected_result && "Test case 4 failed.");

    // Test case 5: Alternating binary string with larger k
    s = "010101";
    k = 3;
    queries = {{0, 3}, {2, 5}};
    expected_result = {10, 10};  // All substrings within these ranges satisfy k-constraint since k = 3
    assert(solution.countKConstraintSubstrings(s, k, queries) == expected_result && "Test case 5 failed.");

    // Test case 6: Large binary string with a single 1
    s = "010101";
    k = 1;
    queries = {{0, 5}, {1, 4}, {2, 3}};
    expected_result = {15, 9, 3};  // Substrings with at most 1 "1" and varying numbers of "0"
    assert(solution.countKConstraintSubstrings(s, k, queries) == expected_result && "Test case 6 failed.");

    // Test case 7: k less than the number of either 0s or 1s
    s = "111000";
    k = 2;
    queries = {{0, 2}, {3, 5}};
    expected_result = {6, 6};  // Only individual "1"s or "0"s and one pair satisfy the k-constraint
    assert(solution.countKConstraintSubstrings(s, k, queries) == expected_result && "Test case 7 failed.");
}

int main() {
    Solution solution;
    for (int i = 0; i < 655360; ++i) {
        testSolution(solution);  
    }
    return 0;
}
