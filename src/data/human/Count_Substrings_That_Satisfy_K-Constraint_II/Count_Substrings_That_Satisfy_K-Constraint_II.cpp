#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    
    vector<long long> countKConstraintSubstrings(string s, int k, vector<vector<int>>& queries) 
    {
        int n = s.size();
        vector <long long> ans,pre(n),prev(n);
        int l = 0,zeros=0,ones=0;
        for(int r=0;r<n;r++)
        {
            if(s[r]=='1') ones++;
            else zeros++;
            while(zeros > k && ones > k)
            {
                if(s[l]=='1') ones--;
                else zeros--;
                l++;
            }
            prev[r] = l;
        }

        pre[0]=1;
        for(int i=1;i<n;i++)
        {
            pre[i] = pre[i-1] + i-prev[i]+1;
        }
        for(auto &q : queries)
        {
            long long l = q[0];
            long long r = q[1];
            long long cur = 0;
            long long pos=r+1;
            while(l<=r)
            {
                long long mid = (l+r)/2;
                if(prev[mid]>=q[0])
                {
                    pos=mid;
                    r=mid-1;
                } 
                else l=mid+1;
            }

            
            if(pos<=q[1])
            {
                cur+=pre[q[1]];
                if(pos>0)cur-=pre[pos-1];
            }
            cur+=(pos-q[0])*(pos-q[0]+1)/2;
            
            ans.push_back(cur);
        }
        return ans;
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
