class Solution(object):
    def trap(self, height):
        """
        :type height: List[int]
        :rtype: int
        """
        if not height:
            return 0

        left, right = 0, len(height) - 1
        left_max, right_max = height[left], height[right]
        water_trapped = 0

        while left < right:
            if left_max < right_max:
                left += 1
                left_max = max(left_max, height[left])
                water_trapped += left_max - height[left]
            else:
                right -= 1
                right_max = max(right_max, height[right])
                water_trapped += right_max - height[right]

        return water_trapped

# Test cases for the Python solution
def testSolution(solution):
    # Test case 1: Basic case with a simple trap
    height = [0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1]
    expected_result = 6
    assert solution.trap(height) == expected_result, f"Test case 1 failed. Expected {expected_result}."

    # Test case 2: No water trapped as the elevation is strictly increasing
    height = [0, 1, 2, 3, 4]
    expected_result = 0
    assert solution.trap(height) == expected_result, f"Test case 2 failed. Expected {expected_result}."

    # Test case 3: Water trapped only at one location
    height = [3, 0, 2, 0, 4]
    expected_result = 7
    assert solution.trap(height) == expected_result, f"Test case 3 failed. Expected {expected_result}."

    # Test case 4: Only two bars, no water can be trapped
    height = [1, 2]
    expected_result = 0
    assert solution.trap(height) == expected_result, f"Test case 4 failed. Expected {expected_result}."

    # Test case 5: Large plateau with no trapping
    height = [4, 4, 4, 4]
    expected_result = 0
    assert solution.trap(height) == expected_result, f"Test case 5 failed. Expected {expected_result}."

    # Test case 6: Complex elevation with multiple trap areas
    height = [0, 2, 0, 2, 0, 2]
    expected_result = 4
    assert solution.trap(height) == expected_result, f"Test case 6 failed. Expected {expected_result}."

    # Test case 7: Empty height list
    height = []
    expected_result = 0
    assert solution.trap(height) == expected_result, f"Test case 7 failed. Expected {expected_result}."

if __name__ == "__main__":
    solution = Solution()
    for i in range(1000000):
        testSolution(solution)
