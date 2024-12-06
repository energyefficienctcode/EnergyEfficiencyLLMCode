import bisect
import collections
from typing import List


class Solution:
    def gcdValues(self, nums: List[int], queries: List[int]) -> List[int]:
        

        max_gcd = max(nums)
        # counter = collections.Counter(nums) # freq count of numbers, can do manually too
        # Counter does slow down the python code on leetcode especially
        # Tried with a defaultdict and normal dict, both gave similar results
        # So prefer to use defaultdict
        counter = collections.defaultdict(int)
        for n in nums:
            counter[n] += 1

        gcd = [0] * (max_gcd + 1) # we wanna reach index of max_gcd

        for i in range(max_gcd, 0, -1): # go from max_gcd -> 1
            count = 0 # count of numbers that are i or multiples of i
            for j in range(i, max_gcd + 1, i): # since we need multiples of i, add step of i
                count += counter[j]

            # now we find the total pairs we can form and add that to gcd
            gcd[i] = count * (count - 1) // 2

            # now use exclusion to remove double counted pairs
            # This starts from 2nd multiple of i
            for j in range(2 * i, max_gcd + 1, i):
                gcd[i] -= gcd[j]

        # now prefix sum array
        prefix = [0] * (max_gcd + 1)
        curr = 0
        for i in range(1, max_gcd + 1):
            curr += gcd[i]
            prefix[i] += curr

        # now process the queries
        res = []
        for q in queries:
            res.append(bisect.bisect_right(prefix, q))

            # we will implement our binary search for practice
            # This is also slower on leetcode, so prefer to use bisect when you can
            # But remember, might be asked to implement the binary search, so keep practicing
            # lo, hi = 1, max_gcd + 1
            # while lo < hi:
            #     mid = lo + (hi - lo) // 2
            #     if prefix[mid] <= q: # look higher. Remember, we want mid = gcd that is just greater than where we find q. So if <= q, this doesnt have our answer and we look higher
            #         lo = mid + 1
            #     else: # but if prefix[mid] > q, we wanna look lower and this CAN be our answer, cuz we want smallest gcd where prefix > q
            #         hi = mid # ending up with hi = mid, means dont need +1 in mid calc
            # res.append(lo)

        return res

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
