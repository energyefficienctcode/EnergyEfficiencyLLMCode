#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();
        stack<int> st;
        int maxArea = 0;

        for (int i = 0; i <= n; i++) {
            int h = (i == n) ? 0 : heights[i];
            while (!st.empty() && h < heights[st.top()]) {
                int height = heights[st.top()];
                st.pop();
                int width = st.empty() ? i : i - st.top() - 1;
                maxArea = max(maxArea, height * width);
            }
            st.push(i);
        }

        return maxArea;
    }
};

//  Test cases for the C++ solution
#include <cassert>
// Test cases for the C++ solution
void testSolution(Solution& solution) {
    // Test case 1: Simple case with increasing heights
    std::vector<int> heights = {2, 1, 5, 6, 2, 3};
    int expected_result = 10;
    assert(solution.largestRectangleArea(heights) == expected_result && "Test case 1 failed.");

    // Test case 2: All bars of the same height
    heights = {2, 2, 2, 2, 2};
    expected_result = 10;
    assert(solution.largestRectangleArea(heights) == expected_result && "Test case 2 failed.");

    // Test case 3: Single bar
    heights = {5};
    expected_result = 5;
    assert(solution.largestRectangleArea(heights) == expected_result && "Test case 3 failed.");

    // Test case 4: Decreasing bar heights
    heights = {6, 5, 4, 3, 2, 1};
    expected_result = 12;
    assert(solution.largestRectangleArea(heights) == expected_result && "Test case 4 failed.");

    // Test case 5: Bars with alternating heights
    heights = {1, 3, 2, 1, 2};
    expected_result = 5;
    assert(solution.largestRectangleArea(heights) == expected_result && "Test case 5 failed.");

    // Test case 6: Empty histogram (no bars)
    heights = {};
    expected_result = 0;
    assert(solution.largestRectangleArea(heights) == expected_result && "Test case 6 failed.");

    // Test case 7: Bars with large values
    heights = {1000, 1000, 1000, 1000};
    expected_result = 4000;
    assert(solution.largestRectangleArea(heights) == expected_result && "Test case 7 failed.");
}


int main() {
    Solution solution;
    for (int i = 0; i < 1310720; ++i) {
        testSolution(solution);  
    }
    return 0;
}
