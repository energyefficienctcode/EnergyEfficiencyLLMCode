class Solution(object):
    def largestPalindrome(self, n, k):
        """
        :type n: int
        :type k: int
        :rtype: str
        """
        if n == 1:
            for num in range(9, -1, -1):
                if num % k == 0:
                    return str(num)
            return "-1"
        
        half_length = (n + 1) // 2
        start = 10**half_length - 1
        end = 10**(half_length -1)
        
        for first_half in range(start, end -1, -1):
            first_half_str = str(first_half)
            if n %2 ==0:
                palindrome_str = first_half_str + first_half_str[::-1]
            else:
                palindrome_str = first_half_str + first_half_str[:-1][::-1]
            palindrome = int(palindrome_str)
            if palindrome % k ==0:
                return palindrome_str
        
        return "-1"

# Test cases for the Python solution
def testSolution(solution):
    # Test case 1: Simple case with k = 1
    n = 3
    k = 1
    expected_result = "999"  # Largest 3-digit palindrome divisible by 1
    assert solution.largestPalindrome(n, k) == expected_result, f"Test case 1 failed. Expected {expected_result}."

    # Test case 2: k = 2 and n = 2 (even-length palindrome divisible by 2)
    n = 2
    k = 2
    expected_result = "88"  # 88 is the largest 2-digit palindrome divisible by 2
    assert solution.largestPalindrome(n, k) == expected_result, f"Test case 2 failed. Expected {expected_result}."

    # Test case 3: Larger n with k = 5
    n = 4
    k = 5
    expected_result = "5995"  # 5995 is the largest 4-digit palindrome divisible by 5
    assert solution.largestPalindrome(n, k) == expected_result, f"Test case 3 failed. Expected {expected_result}."

    # Test case 4: k = 3 (divisible by 3)
    n = 3
    k = 3
    expected_result = "999"  # 999 is the largest 3-digit palindrome divisible by 3
    assert solution.largestPalindrome(n, k) == expected_result, f"Test case 4 failed. Expected {expected_result}."

    # Test case 5: Odd-length n with k = 6 (multiple of 2 and 3)
    n = 5
    k = 6
    expected_result = "89898"  # Constructed based on even placement with ending 8
    assert solution.largestPalindrome(n, k) == expected_result, f"Test case 5 failed. Expected {expected_result}."

    # Test case 6: Large n with k = 8
    n = 7
    k = 8
    expected_result = "8889888"  # Largest 7-digit palindrome divisible by 8
    assert solution.largestPalindrome(n, k) == expected_result, f"Test case 6 failed. Expected {expected_result}."

    # Test case 7: Complex n with k = 11
    n = 12
    k = 11
    expected_result = "999999999999"  # Largest 12-digit palindrome divisible by 11
    assert solution.largestPalindrome(n, k) == expected_result, f"Test case 7 failed. Expected {expected_result}."


if __name__ == "__main__":
    solution = Solution()
    for i in range(1000):
        testSolution(solution)
