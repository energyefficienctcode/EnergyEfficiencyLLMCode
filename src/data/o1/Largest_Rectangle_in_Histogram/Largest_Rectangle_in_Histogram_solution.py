class Solution(object):
    def largestRectangleArea(self, heights):
        """
        :type heights: List[int]
        :rtype: int
        """
        stack = []
        max_area = 0
        heights.append(0)  # Append a sentinel to pop all remaining bars
        
        for i, h in enumerate(heights):
            while stack and heights[stack[-1]] > h:
                top = stack.pop()
                height = heights[top]
                width = i if not stack else i - stack[-1] - 1
                max_area = max(max_area, height * width)
            stack.append(i)
        
        return max_area


# Test cases for the Python solution
def testSolution(solution):
    # Test case 1: Simple case with increasing heights
    heights = [2, 1, 5, 6, 2, 3]
    expected_result = 10
    assert solution.largestRectangleArea(heights) == expected_result, f"Test case 1 failed. Expected {expected_result}."

    # Test case 2: All bars of the same height
    heights = [2, 2, 2, 2, 2]
    expected_result = 10
    assert solution.largestRectangleArea(heights) == expected_result, f"Test case 2 failed. Expected {expected_result}."

    # Test case 3: Single bar
    heights = [5]
    expected_result = 5
    assert solution.largestRectangleArea(heights) == expected_result, f"Test case 3 failed. Expected {expected_result}."

    # Test case 4: Decreasing bar heights
    heights = [6, 5, 4, 3, 2, 1]
    expected_result = 12
    assert solution.largestRectangleArea(heights) == expected_result, f"Test case 4 failed. Expected {expected_result}."

    # Test case 5: Bars with alternating heights
    heights = [1, 3, 2, 1, 2]
    expected_result = 5
    assert solution.largestRectangleArea(heights) == expected_result, f"Test case 5 failed. Expected {expected_result}."

    # Test case 6: Empty histogram (no bars)
    heights = []
    expected_result = 0
    assert solution.largestRectangleArea(heights) == expected_result, f"Test case 6 failed. Expected {expected_result}."

    # Test case 7: Bars with large values
    heights = [1000, 1000, 1000, 1000]
    expected_result = 4000
    assert solution.largestRectangleArea(heights) == expected_result, f"Test case 7 failed. Expected {expected_result}."

if __name__ == "__main__":
    solution = Solution()
    for i in range(1000000):
        testSolution(solution)
