class Solution(object):
    def gcdValues(self, nums, queries):
        from math import gcd
        from collections import defaultdict

        n = len(nums)
        gcd_freq = defaultdict(int)
        
        # Count frequency of each number
        freq = defaultdict(int)
        for num in nums:
            freq[num] += 1
        
        unique_nums = sorted(freq.keys())
        max_num = unique_nums[-1]
        
        # Count GCD frequencies using inclusion-exclusion
        count = [0] * (max_num + 2)
        for num in unique_nums:
            for multiple in range(num, max_num + 1, num):
                count[num] += freq[multiple]
        
        # Now, calculate the number of pairs for each GCD
        gcd_count = defaultdict(int)
        for g in range(max_num, 0, -1):
            c = count[g]
            if c >= 2:
                total = c * (c - 1) // 2
                multiple = 2 * g
                while multiple <= max_num:
                    total -= gcd_count[multiple]
                    multiple += g
                gcd_count[g] = total
        
        # Create a sorted list of GCDs
        sorted_gcds = []
        for g in sorted(gcd_count.keys()):
            sorted_gcds.extend([g] * gcd_count[g])
        
        # Answer the queries
        answer = []
        for q in queries:
            if q < len(sorted_gcds):
                answer.append(sorted_gcds[q])
            else:
                answer.append(-1)  # or some error value
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
    testSolution(solution)
