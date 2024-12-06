import math
class Solution:
    # @param {integer} n
    # @param {integer} k
    # @return {string}
    def getPermutation(self, n, k):
        numbers = [i for i in range(1, n+1)]
        permutation = ''
        k -= 1
        while n > 0:
            n -= 1
            # get the index of current digit
            index, k = divmod(k, math.factorial(n))
            permutation += str(numbers[index])
            # remove handled number
            numbers.remove(numbers[index])

        return permutation

# Test cases for the Python solution
def testSolution(solution):
    # Test case 1: Smallest input where n = 1
    n, k = 1, 1
    expected_result = "1"
    assert solution.getPermutation(n, k) == expected_result, f"Test case 1 failed. Expected {expected_result}."

    # Test case 2: n = 3, k = 3 (Third permutation of [1, 2, 3])
    n, k = 3, 3
    expected_result = "213"
    assert solution.getPermutation(n, k) == expected_result, f"Test case 2 failed. Expected {expected_result}."

    # Test case 3: n = 4, k = 9 (Ninth permutation of [1, 2, 3, 4])
    n, k = 4, 9
    expected_result = "2314"
    assert solution.getPermutation(n, k) == expected_result, f"Test case 3 failed. Expected {expected_result}."

    # Test case 4: n = 4, k = 1 (First permutation of [1, 2, 3, 4])
    n, k = 4, 1
    expected_result = "1234"
    assert solution.getPermutation(n, k) == expected_result, f"Test case 4 failed. Expected {expected_result}."

    # Test case 5: n = 4, k = 24 (Last permutation of [1, 2, 3, 4])
    n, k = 4, 24
    expected_result = "4321"
    assert solution.getPermutation(n, k) == expected_result, f"Test case 5 failed. Expected {expected_result}."

    # Test case 6: n = 5, k = 16 (Middle permutation of [1, 2, 3, 4, 5])
    n, k = 5, 16
    expected_result = "14352"
    assert solution.getPermutation(n, k) == expected_result, f"Test case 6 failed. Expected {expected_result}."

    # Test case 7: Large n = 6 to test algorithm's efficiency
    n, k = 6, 400
    expected_result = "425361"
    assert solution.getPermutation(n, k) == expected_result, f"Test case 7 failed. Expected {expected_result}."

if __name__ == "__main__":
    solution = Solution()
    for i in range(1000000):
        testSolution(solution)