#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int trap(vector<int>& height) {
        if (height.empty()) return 0;

        int n = height.size();
        int left = 0, right = n - 1;
        int leftMax = 0, rightMax = 0;
        int trappedWater = 0;

        while (left <= right) {
            if (height[left] <= height[right]) {
                if (height[left] >= leftMax) {
                    leftMax = height[left];
                } else {
                    trappedWater += leftMax - height[left];
                }
                left++;
            } else {
                if (height[right] >= rightMax) {
                    rightMax = height[right];
                } else {
                    trappedWater += rightMax - height[right];
                }
                right--;
            }
        }

        return trappedWater;
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