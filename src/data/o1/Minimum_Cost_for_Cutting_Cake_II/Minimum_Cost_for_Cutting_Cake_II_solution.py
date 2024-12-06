class Solution(object):
    def minimumCost(self, m, n, horizontalCut, verticalCut):
        """
        :type m: int
        :type n: int
        :type horizontalCut: List[int]
        :type verticalCut: List[int]
        :rtype: int
        """
        horizontalCut.sort()
        verticalCut.sort()
        i, j = 0, 0
        horizontal_pieces, vertical_pieces = 1, 1
        total_cost = 0
        len_h = len(horizontalCut)
        len_v = len(verticalCut)
        
        while i < len_h and j < len_v:
            if horizontalCut[i] < verticalCut[j]:
                total_cost += horizontalCut[i] * vertical_pieces
                horizontal_pieces += 1
                i += 1
            else:
                total_cost += verticalCut[j] * horizontal_pieces
                vertical_pieces += 1
                j += 1
        
        while i < len_h:
            total_cost += horizontalCut[i] * vertical_pieces
            horizontal_pieces += 1
            i += 1
        
        while j < len_v:
            total_cost += verticalCut[j] * horizontal_pieces
            vertical_pieces += 1
            j += 1
        
        return total_cost

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
    testSolution(solution)
