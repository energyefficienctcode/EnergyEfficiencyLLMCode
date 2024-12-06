#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int trap(vector<int>& height) {
        int left = 0, right = height.size() - 1;
        int left_max = 0, right_max = 0;
        int trapped = 0;
        
        while (left < right) {
            if (height[left] < height[right]) {
                if (height[left] >= left_max) {
                    left_max = height[left];
                } else {
                    trapped += left_max - height[left];
                }
                left++;
            } else {
                if (height[right] >= right_max) {
                    right_max = height[right];
                } else {
                    trapped += right_max - height[right];
                }
                right--;
            }
        }
        
        return trapped;
    }
};

//  Test cases for the C++ solution
#include <cassert>

void testSolution(Solution& solution) {
    // Test case 1: Basic case with a simple trap
    std::vector<int> height = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    int expected_result = 6;
    assert(solution.trap(height.data(), height.size()) == expected_result && "Test case 1 failed.");

    // Test case 2: No water trapped as the elevation is strictly increasing
    height = {0, 1, 2, 3, 4};
    expected_result = 0;
    assert(solution.trap(height.data(), height.size()) == expected_result && "Test case 2 failed.");

    // Test case 3: Water trapped only at one location
    height = {3, 0, 2, 0, 4};
    expected_result = 7;
    assert(solution.trap(height.data(), height.size()) == expected_result && "Test case 3 failed.");

    // Test case 4: Only two bars, no water can be trapped
    height = {1, 2};
    expected_result = 0;
    assert(solution.trap(height.data(), height.size()) == expected_result && "Test case 4 failed.");

    // Test case 5: Large plateau with no trapping
    height = {4, 4, 4, 4};
    expected_result = 0;
    assert(solution.trap(height.data(), height.size()) == expected_result && "Test case 5 failed.");

    // Test case 6: Complex elevation with multiple trap areas
    height = {0, 2, 0, 2, 0, 2};
    expected_result = 4;
    assert(solution.trap(height.data(), height.size()) == expected_result && "Test case 6 failed.");

    // Test case 7: Empty height list
    height = {};
    expected_result = 0;
    assert(solution.trap(height.data(), height.size()) == expected_result && "Test case 7 failed.");
}

int main() {
    Solution solution;
    for (int i = 0; i < 6400000; ++i) {
        testSolution(solution);  
    }
    return 0;
}
