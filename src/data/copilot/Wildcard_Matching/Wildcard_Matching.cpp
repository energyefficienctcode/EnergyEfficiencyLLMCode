#include <vector>
using namespace std;

class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        if (n == 0) return 0;

        int left = 0, right = n - 1;
        int left_max = 0, right_max = 0;
        int water = 0;

        while (left < right) {
            if (height[left] < height[right]) {
                if (height[left] >= left_max) {
                    left_max = height[left];
                } else {
                    water += left_max - height[left];
                }
                ++left;
            } else {
                if (height[right] >= right_max) {
                    right_max = height[right];
                } else {
                    water += right_max - height[right];
                }
                --right;
            }
        }

        return water;
    }
};

//  Test cases for the C++ solution
#include <cassert>

// Test cases for the C++ solution
void testSolution(Solution& solution) {
    // Test case 1: Simple match with exact pattern
    std::string s = "abcd";
    std::string p = "abcd";
    bool expected_result = true;
    assert(solution.isMatch(s, p) == expected_result && "Test case 1 failed.");

    // Test case 2: Pattern with '?' matching a single character
    s = "abcd";
    p = "a?cd";
    expected_result = true;
    assert(solution.isMatch(s, p) == expected_result && "Test case 2 failed.");

    // Test case 3: Pattern with '*' matching any sequence of characters
    s = "abcd";
    p = "a*d";
    expected_result = true;
    assert(solution.isMatch(s, p) == expected_result && "Test case 3 failed.");

    // Test case 4: Pattern with '*' matching an empty sequence
    s = "abcd";
    p = "a*cd";
    expected_result = true;
    assert(solution.isMatch(s, p) == expected_result && "Test case 4 failed.");

    // Test case 5: No match due to extra characters in pattern
    s = "abc";
    p = "abcd";
    expected_result = false;
    assert(solution.isMatch(s, p) == expected_result && "Test case 5 failed.");

    // Test case 6: Multiple '*' characters and '?' in the pattern
    s = "abefcdgiescdfimde";
    p = "ab*cd?i*de";
    expected_result = true;
    assert(solution.isMatch(s, p) == expected_result && "Test case 6 failed.");

    // Test case 7: Empty pattern matching an empty string
    s = "";
    p = "";
    expected_result = true;
    assert(solution.isMatch(s, p) == expected_result && "Test case 7 failed.");

    // Test case 8: Pattern with only '*' should match any string
    s = "anything";
    p = "*";
    expected_result = true;
    assert(solution.isMatch(s, p) == expected_result && "Test case 8 failed.");
}


int main() {
    Solution solution;
    for (int i = 0; i < 327680; ++i) {
        testSolution(solution);  
    }
    return 0;
}
