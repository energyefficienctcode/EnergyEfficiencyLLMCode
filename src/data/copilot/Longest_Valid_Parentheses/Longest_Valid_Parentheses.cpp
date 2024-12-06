#include <string>
#include <stack>
using namespace std;

class Solution {
public:
    int longestValidParentheses(string s) {
        stack<int> stk;
        stk.push(-1);
        int max_len = 0;

        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == '(') {
                stk.push(i);
            } else {
                stk.pop();
                if (stk.empty()) {
                    stk.push(i);
                } else {
                    max_len = max(max_len, i - stk.top());
                }
            }
        }

        return max_len;
    }
};

//  Test cases for the C++ solution
#include <cassert>

// Test cases for the C++ solution
void testSolution(Solution& solution) {
    // Test case 1: Simple valid parentheses
    std::string s = "(()";
    int expected_result = 2;
    assert(solution.longestValidParentheses(s) == expected_result && "Test case 1 failed.");

    // Test case 2: All parentheses are valid
    s = ")()())";
    expected_result = 4;
    assert(solution.longestValidParentheses(s) == expected_result && "Test case 2 failed.");

    // Test case 3: No valid parentheses
    s = "(((";
    expected_result = 0;
    assert(solution.longestValidParentheses(s) == expected_result && "Test case 3 failed.");

    // Test case 4: Entire string is valid parentheses
    s = "()()()";
    expected_result = 6;
    assert(solution.longestValidParentheses(s) == expected_result && "Test case 4 failed.");

    // Test case 5: Nested valid parentheses
    s = "((()))";
    expected_result = 6;
    assert(solution.longestValidParentheses(s) == expected_result && "Test case 5 failed.");

    // Test case 6: Mixed valid and invalid parentheses
    s = "(()))())(";
    expected_result = 4;
    assert(solution.longestValidParentheses(s) == expected_result && "Test case 6 failed.");

    // Test case 7: Empty string
    s = "";
    expected_result = 0;
    assert(solution.longestValidParentheses(s) == expected_result && "Test case 7 failed.");
}


int main() {
    Solution solution;
    for (int i = 0; i < 2621440; ++i) {
        testSolution(solution);  
    }
    return 0;
}
