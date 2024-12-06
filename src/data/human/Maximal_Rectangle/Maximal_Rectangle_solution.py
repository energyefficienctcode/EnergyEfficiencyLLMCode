class Solution:
    def maximalRectangle(self, matrix):
        if not matrix or not matrix[0]:
            return 0
        n = len(matrix[0])
        height = [0] * (n + 1)
        ans = 0
        for row in matrix:
            for i in range(n):
                height[i] = height[i] + 1 if row[i] == '1' else 0
            stack = [-1]
            for i in range(n + 1):
                while height[i] < height[stack[-1]]:
                    h = height[stack.pop()]
                    w = i - 1 - stack[-1]
                    ans = max(ans, h * w)
                stack.append(i)
        return ans

# 65 / 65 test cases passed.
# Status: Accepted
# Runtime: 120 ms
# 100%

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
