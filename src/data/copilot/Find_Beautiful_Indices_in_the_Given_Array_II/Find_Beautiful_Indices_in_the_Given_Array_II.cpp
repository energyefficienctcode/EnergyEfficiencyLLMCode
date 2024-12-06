#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    vector<int> beautifulIndices(string s, string a, string b, int k) {
        vector<int> result;
        int n = s.size();
        int a_len = a.size();
        int b_len = b.size();

        vector<int> a_indices;
        vector<int> b_indices;

        for (int i = 0; i <= n - a_len; ++i) {
            if (s.substr(i, a_len) == a) {
                a_indices.push_back(i);
            }
        }

        for (int j = 0; j <= n - b_len; ++j) {
            if (s.substr(j, b_len) == b) {
                b_indices.push_back(j);
            }
        }

        for (int i : a_indices) {
            for (int j : b_indices) {
                if (abs(j - i) <= k) {
                    result.push_back(i);
                    break;
                }
            }
        }

        return result;
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
