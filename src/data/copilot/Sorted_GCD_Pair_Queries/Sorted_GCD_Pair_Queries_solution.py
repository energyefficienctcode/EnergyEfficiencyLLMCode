import math

class Solution(object):
    def gcdValues(self, nums, queries):
        """
        :type nums: List[int]
        :type queries: List[int]
        :rtype: List[int]
        """
        gcd_pairs = []
        n = len(nums)
        
        # Calculate GCD for all pairs
        for i in range(n):
            for j in range(i + 1, n):
                gcd_pairs.append(math.gcd(nums[i], nums[j]))
        
        # Sort the GCD pairs
        gcd_pairs.sort()
        
        # Answer the queries
        answer = [gcd_pairs[q] for q in queries]
        
        return answer

# Test cases for the Python solution
def testSolution(solution):
    # Test case 1: Simple case with two numbers
    nums = [2, 3]
    queries = [0]
    expected_result = [1]  # Only one pair, GCD(2, 3) = 1
    assert solution.gcdValues(nums, queries) == expected_result, f"Test case 1 failed. Expected {expected_result}."

    # Test case 2: Multiple pairs with diverse GCDs
    nums = [2, 3, 4]
    queries = [0, 2, 2]
    expected_result = [1, 2, 2]  # GCD pairs sorted: [2, 2, 1]
    assert solution.gcdValues(nums, queries) == expected_result, f"Test case 2 failed. Expected {expected_result}."

    # Test case 3: All numbers are multiples of a common number
    nums = [4, 8, 12]
    queries = [0, 1, 2]
    expected_result = [4, 4, 4]  # GCD pairs sorted: [4, 4, 4]
    assert solution.gcdValues(nums, queries) == expected_result, f"Test case 3 failed. Expected {expected_result}."

    # Test case 4: GCD results in multiple distinct values
    nums = [2, 3, 5, 7]
    queries = [0, 1, 2, 3, 4, 5]
    expected_result = [1, 1, 1, 1, 1, 1]  # GCDs are all 1 for prime pairs
    assert solution.gcdValues(nums, queries) == expected_result, f"Test case 4 failed. Expected {expected_result}."

    # Test case 5: GCD values with repeated elements in nums
    nums = [4, 4, 2, 1]
    queries = [5, 3, 1, 0]
    expected_result = [4, 2, 1, 1]  # GCD pairs sorted: [4, 4, 2, 2, 2, 1]
    assert solution.gcdValues(nums, queries) == expected_result, f"Test case 5 failed. Expected {expected_result}."

    # Test case 6: Large number with single pair
    nums = [100000, 100000]
    queries = [0]
    expected_result = [100000]  # Only one GCD of the pair: [100000]
    assert solution.gcdValues(nums, queries) == expected_result, f"Test case 6 failed. Expected {expected_result}."


if __name__ == "__main__":
    solution = Solution()
    for i in range(100):
        testSolution(solution)
