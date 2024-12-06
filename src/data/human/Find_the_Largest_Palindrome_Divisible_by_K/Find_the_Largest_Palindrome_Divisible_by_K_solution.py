class Solution:
    def largestPalindrome(self, n: int, k: int) -> str:
        if k == 1:
            return '9' * n
        elif k == 2:
            if n <= 2:
                return '8' * n
            else:
                return '8' + '9' * (n - 2) + '8'
        elif k == 3 or k == 9:
            return '9' * n
        elif k == 4:
            if n <= 4:
                return '8' * n
            else:
                return '88' + '9' * (n - 4) + '88'
        elif k == 5:
            if n <= 2:
                return '5' * n
            else:
                return '5' + '9' * (n - 2) + '5'
        elif k == 6:
            if n <= 2:
                return '6' * n
            elif n % 2 == 1:
                l = n // 2 - 1
                return '8' + '9' * l + '8' + '9' * l + '8'
            else:
                l = n // 2 - 2
                return '8' + '9' * l + '77' + '9' * l + '8'
        elif k == 8:
            if n <= 6:
                return '8' * n
            else:
                return '888' + '9' * (n - 6) + '888'
        else:
            dic = {0: '', 1: '7', 2: '77', 3: '959', 4: '9779', 5: '99799', 6: '999999', 7: '9994999',
                       8: '99944999', 9: '999969999', 10: '9999449999', 11: '99999499999'}
            l, r = divmod(n, 12)
            return '999999' * l + dic[r] + '999999' * l

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
    for i in range(1000000):
        testSolution(solution)
