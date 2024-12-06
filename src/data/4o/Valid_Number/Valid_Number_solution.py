class Solution(object):
    def isNumber(self, s):
        """
        :type s: str
        :rtype: bool
        """
        def is_integer(s):
            if not s:
                return False
            if s[0] in ['+', '-']:
                s = s[1:]
            return s.isdigit()

        def is_decimal(s):
            if not s:
                return False
            if s[0] in ['+', '-']:
                s = s[1:]
            if '.' not in s:
                return False
            left, right = s.split('.', 1)
            if not left and not right:
                return False
            if left and not left.isdigit():
                return False
            if right and not right.isdigit():
                return False
            return True

        if 'e' in s or 'E' in s:
            base, exp = s.split('e') if 'e' in s else s.split('E')
            return (is_integer(base) or is_decimal(base)) and is_integer(exp)
        return is_integer(s) or is_decimal(s)

# Test cases for the Python solution
def testSolution(solution):
    # Test case 1: Simple valid integer
    s = "2"
    expected_result = True
    assert solution.isNumber(s) == expected_result, f"Test case 1 failed. Expected {expected_result}."

    # Test case 2: Valid negative decimal
    s = "-0.1"
    expected_result = True
    assert solution.isNumber(s) == expected_result, f"Test case 2 failed. Expected {expected_result}."

    # Test case 3: Valid integer with exponent
    s = "-90E3"
    expected_result = False
    assert solution.isNumber(s) == expected_result, f"Test case 4 failed. Expected {expected_result}."

    # Test case 4: Invalid string with letters
    s = "abc"
    expected_result = False
    assert solution.isNumber(s) == expected_result, f"Test case 5 failed. Expected {expected_result}."

    # Test case 5: Invalid number with misplaced decimal
    s = "99e2.5"
    expected_result = False
    assert solution.isNumber(s) == expected_result, f"Test case 6 failed. Expected {expected_result}."

    # Test case 6: Valid number with positive sign
    s = "+6e-1"
    expected_result = True
    assert solution.isNumber(s) == expected_result, f"Test case 7 failed. Expected {expected_result}."

    # Test case 7: Invalid string with only exponent
    s = "e3"
    expected_result = False
    assert solution.isNumber(s) == expected_result, f"Test case 8 failed. Expected {expected_result}."

    # Test case 8: Valid decimal without digits after dot
    s = "4."
    expected_result = True
    assert solution.isNumber(s) == expected_result, f"Test case 9 failed. Expected {expected_result}."

    # Test case 9: Invalid number with double signs
    s = "-+3"
    expected_result = False
    assert solution.isNumber(s) == expected_result, f"Test case 10 failed. Expected {expected_result}."

    # Test case 10: Valid negative number with exponent and decimal
    s = "-123.456e789"
    expected_result = True
    assert solution.isNumber(s) == expected_result, f"Test case 11 failed. Expected {expected_result}."

if __name__ == "__main__":
    solution = Solution()
    for i in range(1000000):
        testSolution(solution)
