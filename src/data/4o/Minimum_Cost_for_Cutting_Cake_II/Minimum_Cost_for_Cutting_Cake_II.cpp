#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    long long minimumCost(int m, int n, vector<int>& horizontalCut, vector<int>& verticalCut) {
        // Sort cuts in descending order to prioritize more expensive cuts first
        sort(horizontalCut.rbegin(), horizontalCut.rend());
        sort(verticalCut.rbegin(), verticalCut.rend());

        long long totalCost = 0;
        int hPieces = 1, vPieces = 1;
        int i = 0, j = 0;

        // Use a greedy approach to add the most expensive cuts first
        while (i < horizontalCut.size() && j < verticalCut.size()) {
            if (horizontalCut[i] >= verticalCut[j]) {
                totalCost += static_cast<long long>(horizontalCut[i]) * vPieces;
                hPieces++;
                i++;
            } else {
                totalCost += static_cast<long long>(verticalCut[j]) * hPieces;
                vPieces++;
                j++;
            }
        }

        // Add remaining horizontal cuts
        while (i < horizontalCut.size()) {
            totalCost += static_cast<long long>(horizontalCut[i]) * vPieces;
            i++;
        }

        // Add remaining vertical cuts
        while (j < verticalCut.size()) {
            totalCost += static_cast<long long>(verticalCut[j]) * hPieces;
            j++;
        }

        return totalCost;
    }
};

//  Test cases for the C++ solution
#include <cassert>

// Test cases for the C++ solution
void testSolution(Solution& solution) {
    // Test case 1: Simple case with small costs
    int m = 3, n = 2;
    std::vector<int> horizontalCut = {1, 3};
    std::vector<int> verticalCut = {5};
    int expected_result = 13;  // Cutting order: choose horizontal 2 and 1, vertical 2 and 1
    assert(solution.minimumCost(m, n, horizontalCut, verticalCut) == expected_result && "Test case 1 failed.");

    // Test case 2: All horizontal cuts more expensive than vertical cuts
    m = 2;
    n = 2;
    horizontalCut = {7};
    verticalCut = {4};
    expected_result = 15;  // Prioritize horizontal cuts: [7, 6, 5] then vertical cuts: [2, 1]
    assert(solution.minimumCost(m, n, horizontalCut, verticalCut) == expected_result && "Test case 2 failed.");

    // Test case 3: Equal costs for all cuts
    m = 2;
    n = 2;
    horizontalCut = {3};
    verticalCut = {3};
    expected_result = 9;  // Either order works, costs are symmetric
    assert(solution.minimumCost(m, n, horizontalCut, verticalCut) == expected_result && "Test case 3 failed.");

    // Test case 4: Large cake with increasing costs
    m = 5;
    n = 4;
    horizontalCut = {1, 2, 3, 4};
    verticalCut = {2, 4, 6};
    expected_result = 49;  // Cut order based on largest cuts prioritized
    assert(solution.minimumCost(m, n, horizontalCut, verticalCut) == expected_result && "Test case 4 failed.");

    // Test case 5: Only one horizontal or vertical cut needed
    m = 2;
    n = 4;
    horizontalCut = {10};
    verticalCut = {2, 3, 5};
    expected_result = 30;  // Vertical 5, 3, 2, then horizontal 10
    assert(solution.minimumCost(m, n, horizontalCut, verticalCut) == expected_result && "Test case 5 failed.");

    // Test case 6: Large values with mixed costs
    m = 3;
    n = 3;
    horizontalCut = {8, 3};
    verticalCut = {6, 7};
    expected_result = 43;  // Mixed cutting order based on priorities
    assert(solution.minimumCost(m, n, horizontalCut, verticalCut) == expected_result && "Test case 6 failed.");

    // Test case 7: Single row or column (only vertical or horizontal cuts)
    m = 1;
    n = 5;
    horizontalCut = {};
    verticalCut = {4, 2, 1, 3};
    expected_result = 10;  // Only vertical cuts with no horizontal cuts
    assert(solution.minimumCost(m, n, horizontalCut, verticalCut) == expected_result && "Test case 7 failed.");
}

int main() {
    Solution solution;
    for (int i = 0; i < 2621440; ++i) {
        testSolution(solution);  
    }
    return 0;
}
