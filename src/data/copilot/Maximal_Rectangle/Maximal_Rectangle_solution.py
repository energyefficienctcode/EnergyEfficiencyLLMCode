class Solution(object):
    def maximalRectangle(self, matrix):
        """
        :type matrix: List[List[str]]
        :rtype: int
        """
        if not matrix or not matrix[0]:
            return 0

        rows, cols = len(matrix), len(matrix[0])
        heights = [0] * cols
        max_area = 0

        for row in matrix:
            for col in range(cols):
                heights[col] = heights[col] + 1 if row[col] == '1' else 0

            max_area = max(max_area, self.largestRectangleArea(heights))

        return max_area

    def largestRectangleArea(self, heights):
        stack = []
        max_area = 0
        heights.append(0)  # Append a zero to handle remaining bars in stack

        for i in range(len(heights)):
            while stack and heights[i] < heights[stack[-1]]:
                h = heights[stack.pop()]
                width = i if not stack else i - stack[-1] - 1
                max_area = max(max_area, h * width)
            stack.append(i)

        heights.pop()  # Remove the appended zero
        return max_area

# Test cases for the Python solution
def testSolution(solution):
    # Test case 1: Small matrix with a single rectangle
    matrix = [
        ["1", "0", "1", "0", "0"],
        ["1", "0", "1", "1", "1"],
        ["1", "1", "1", "1", "1"],
        ["1", "0", "0", "1", "0"]
    ]
    expected_result = 6
    assert solution.maximalRectangle(matrix) == expected_result, f"Test case 1 failed. Expected {expected_result}."

    # Test case 2: All 1's matrix
    matrix = [
        ["1", "1"],
        ["1", "1"]
    ]
    expected_result = 4
    assert solution.maximalRectangle(matrix) == expected_result, f"Test case 2 failed. Expected {expected_result}."

    # Test case 3: Matrix with no 1's
    matrix = [
        ["0", "0"],
        ["0", "0"]
    ]
    expected_result = 0
    assert solution.maximalRectangle(matrix) == expected_result, f"Test case 3 failed. Expected {expected_result}."

    # Test case 4: Single row matrix with alternating 1's and 0's
    matrix = [
        ["1", "0", "1", "0", "1"]
    ]
    expected_result = 1
    assert solution.maximalRectangle(matrix) == expected_result, f"Test case 4 failed. Expected {expected_result}."

    # Test case 5: Single column matrix with consecutive 1's
    matrix = [
        ["1"],
        ["1"],
        ["0"],
        ["1"],
        ["1"]
    ]
    expected_result = 2
    assert solution.maximalRectangle(matrix) == expected_result, f"Test case 5 failed. Expected {expected_result}."

    # Test case 6: Large matrix with one large rectangle of 1's
    matrix = [
        ["1", "1", "1", "1"],
        ["1", "1", "1", "1"],
        ["1", "1", "1", "1"]
    ]
    expected_result = 12
    assert solution.maximalRectangle(matrix) == expected_result, f"Test case 6 failed. Expected {expected_result}."

    # Test case 7: Sparse matrix with isolated 1's
    matrix = [
        ["1", "0", "0", "1"],
        ["0", "0", "0", "0"],
        ["0", "1", "0", "0"],
        ["0", "0", "1", "1"]
    ]
    expected_result = 2
    assert solution.maximalRectangle(matrix) == expected_result, f"Test case 7 failed. Expected {expected_result}."

if __name__ == "__main__":
    solution = Solution()
    for i in range(300000):
        testSolution(solution)
