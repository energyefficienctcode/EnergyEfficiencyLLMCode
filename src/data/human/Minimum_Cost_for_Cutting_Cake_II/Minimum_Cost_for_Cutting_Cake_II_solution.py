from typing import List


class Solution:
    def minimumCost(self, m: int, n: int, h: List[int], v: List[int]) -> int:
        h.sort()
        v.sort()
        sumh = sum(h)
        sumv = sum(v)
        res = 0
        while h and v:
            if h[-1] > v[-1]:
                res += h[-1] + sumv
                sumh -= h.pop()
            else:
                res += v[-1] + sumh
                sumv -= v.pop()
        return res + sumh + sumv

# Test cases for the Python solution
def testSolution(solution):
    # Test case 1: Simple case with small costs
    m = 3
    n = 2
    horizontalCut = [1, 3]
    verticalCut = [5]
    expected_result = 13  # Cutting order: choose horizontal 2 and 1, vertical 2 and 1
    assert solution.minimumCost(m, n, horizontalCut, verticalCut) == expected_result, f"Test case 1 failed. Expected {expected_result}."

    # Test case 2: All horizontal cuts more expensive than vertical cuts
    m = 2
    n = 2
    horizontalCut = [7]
    verticalCut = [4]
    expected_result = 15  # Prioritize horizontal cuts: [7, 6, 5] then vertical cuts: [2, 1]
    assert solution.minimumCost(m, n, horizontalCut, verticalCut) == expected_result, f"Test case 2 failed. Expected {expected_result}."

    # Test case 3: Equal costs for all cuts
    m, n = 2, 2
    horizontalCut = [3]
    verticalCut = [3]
    expected_result = 9  # Either order works, costs are symmetric
    assert solution.minimumCost(m, n, horizontalCut, verticalCut) == expected_result, f"Test case 3 failed. Expected {expected_result}."

    # Test case 4: Large cake with increasing costs
    m, n = 5, 4
    horizontalCut = [1, 2, 3, 4]
    verticalCut = [2, 4, 6]
    expected_result = 49  # Cut order based on largest cuts prioritized
    assert solution.minimumCost(m, n, horizontalCut, verticalCut) == expected_result, f"Test case 4 failed. Expected {expected_result}."

    # Test case 5: Only one horizontal or vertical cut needed
    m, n = 2, 4
    horizontalCut = [10]
    verticalCut = [2, 3, 5]
    expected_result = 30  # Vertical 5, 3, 2, then horizontal 10
    assert solution.minimumCost(m, n, horizontalCut, verticalCut) == expected_result, f"Test case 5 failed. Expected {expected_result}."

    # Test case 6: Large values with mixed costs
    m, n = 3, 3
    horizontalCut = [8, 3]
    verticalCut = [6, 7]
    expected_result = 43  # Mixed cutting order based on priorities
    assert solution.minimumCost(m, n, horizontalCut, verticalCut) == expected_result, f"Test case 6 failed. Expected {expected_result}."

    # Test case 7: Single row or column (only vertical or horizontal cuts)
    m, n = 1, 5
    horizontalCut = []
    verticalCut = [4, 2, 1, 3]
    expected_result = 10  # Only vertical cuts with no horizontal cuts
    assert solution.minimumCost(m, n, horizontalCut, verticalCut) == expected_result, f"Test case 7 failed. Expected {expected_result}."

if __name__ == "__main__":
    solution = Solution()
    for i in range(3000000):
        testSolution(solution)
