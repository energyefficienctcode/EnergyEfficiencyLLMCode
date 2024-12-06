#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<long long> countKConstraintSubstrings(string s, int k, vector<vector<int>>& queries) {
        int n = s.size();
        
        // Precompute for at most k '0's
        vector<int> max_j0(n, 0);
        int left0 = 0, count0 = 0;
        for(int right = 0; right < n; ++right){
            if(s[right] == '0') count0++;
            while(count0 > k){
                if(s[left0] == '0') count0--;
                left0++;
            }
            max_j0[right] = left0;
        }
        
        // Precompute for at most k '1's
        vector<int> max_j1(n, 0);
        int left1 = 0, count1 = 0;
        for(int right = 0; right < n; ++right){
            if(s[right] == '1') count1++;
            while(count1 > k){
                if(s[left1] == '1') count1--;
                left1++;
            }
            max_j1[right] = left1;
        }
        
        // Precompute prefix sums for C1 and C2
        vector<long long> prefixC1(n, 0);
        vector<long long> prefixC2(n, 0);
        prefixC1[0] = right_count(max_j0, 0);
        prefixC2[0] = right_count(max_j1, 0);
        for(int i = 1; i < n; ++i){
            prefixC1[i] = prefixC1[i-1] + right_count(max_j0, i);
            prefixC2[i] = prefixC2[i-1] + right_count(max_j1, i);
        }
        
        // Function to get C1 and C2 for a range [li, ri]
        auto get_sum = [&](const vector<long long>& prefix, int li, int ri) -> long long {
            if(li > 0) return prefix[ri] - prefix[li-1];
            else return prefix[ri];
        };
        
        // Process each query
        vector<long long> answer;
        for(auto &q : queries){
            int li = q[0];
            int ri = q[1];
            // C1: substrings with at most k '0's
            long long C1 = get_sum(prefixC1, li, ri);
            // C2: substrings with at most k '1's
            long long C2 = get_sum(prefixC2, li, ri);
            // C3: substrings with length <=k
            int L = ri - li +1;
            int minLK = min(k, L);
            long long C3 = ((long long)minLK * (minLK +1)) /2;
            // Total substrings satisfying the condition
            long long total = C1 + C2 - C3;
            answer.push_back(total);
        }
        
        return answer;
    }
    
private:
    // Helper function to calculate number of substrings ending at 'right'
    long long right_count(const vector<int>& max_j, int right){
        return (long long)(right - max_j[right] +1);
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
