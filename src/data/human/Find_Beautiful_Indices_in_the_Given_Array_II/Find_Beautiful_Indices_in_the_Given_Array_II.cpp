#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    void getPatternMatchingIndex(string& s, string& a, vector<int>& v){
        string t = a + "@" + s;
        vector<int> lps(1, 0);
        for(int i = 1; i < t.size(); ++i){
            int ind = lps[i-1]; 
            while(ind > 0 && t[ind] != t[i]) { ind = lps[ind-1]; }
            lps.push_back((t[ind] == t[i])?ind + 1 : 0);
        }
        for(int i = 0; i < lps.size(); ++i){
            if(lps[i] == a.size()) v.push_back(i - 2*a.size());
        }
    }

    vector<int> beautifulIndices(string s, string a, string b, int k) {
        vector<int> ans, v1, v2;
        getPatternMatchingIndex(s, a, v1);
        getPatternMatchingIndex(s, b, v2);
        for(int i = 0, j = 0; i < v1.size(); ++i){
            while(j < v2.size() && v1[i] > v2[j] && abs(v1[i] - v2[j]) > k) j++;
            if(j < v2.size() && abs(v1[i] - v2[j]) <= k) ans.push_back(v1[i]);
        }
        return ans;
    }
};

//  Test cases for the C++ solution
#include <cassert>

// Test cases for the C++ solution
void testSolution(Solution& solution) {
    // Test case 1: Simple case with one beautiful index
    std::string s = "abcde";
    std::string a = "ab";
    std::string b = "de";
    int k = 4;
    std::vector<int> expected_result = {0};
    assert(solution.beautifulIndices(s, a, b, k) == expected_result && "Test case 1 failed.");

    // Test case 2: Multiple beautiful indices
    s = "ababab";
    a = "ab";
    b = "ba";
    k = 1;
    expected_result = {0, 2, 4};
    assert(solution.beautifulIndices(s, a, b, k) == expected_result && "Test case 2 failed.");

    // Test case 3: No beautiful indices
    s = "isawsquirrelnearmysquirrelhouseohmy";
    a = "my";
    b = "squirrel";
    k = 15;
    expected_result = {16, 33};
    assert(solution.beautifulIndices(s, a, b, k) == expected_result && "Test case 3 failed.");

    // Test case 4: Overlapping matches with larger k
    s = "abababab";
    a = "ab";
    b = "ab";
    k = 2;
    expected_result = {0, 2, 4, 6};
    assert(solution.beautifulIndices(s, a, b, k) == expected_result && "Test case 4 failed.");

    // Test case 5: Only one match each for a and b, within range k
    s = "abcdef";
    a = "abc";
    b = "def";
    k = 5;
    expected_result = {0};
    assert(solution.beautifulIndices(s, a, b, k) == expected_result && "Test case 5 failed.");

    // Test case 6: Overlapping b close to the end of a with k = 0
    s = "abcd";
    a = "a";
    b = "a";
    k = 4;
    expected_result = {0};
    assert(solution.beautifulIndices(s, a, b, k) == expected_result && "Test case 6 failed.");

    // Test case 7: Non-overlapping multiple beautiful indices with exact k distance
    s = "aaaaaa";
    a = "aa";
    b = "aa";
    k = 2;
    expected_result = {0, 1, 2, 3, 4};
    assert(solution.beautifulIndices(s, a, b, k) == expected_result && "Test case 7 failed.");
}


int main() {
    Solution solution;
    for (int i = 0; i < 163840; ++i) {
        testSolution(solution);  
    }
    return 0;
}
