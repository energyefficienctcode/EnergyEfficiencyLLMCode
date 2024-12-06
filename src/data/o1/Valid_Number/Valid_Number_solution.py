class Solution(object):
    def isNumber(self, s):
        """
        :type s: str
        :rtype: bool
        """
        s = s.strip()
        if not s:
            return False
        
        seen_digit = False
        seen_dot = False
        seen_e = False
        seen_digit_after_e = True
        
        for i, c in enumerate(s):
            if c.isdigit():
                seen_digit = True
                if seen_e:
                    seen_digit_after_e = True
            elif c in ['+', '-']:
                if i != 0 and s[i-1] not in ['e', 'E']:
                    return False
            elif c == '.':
                if seen_dot or seen_e:
                    return False
                seen_dot = True
            elif c in ['e', 'E']:
                if seen_e or not seen_digit:
                    return False
                seen_e = True
                seen_digit_after_e = False
            else:
                return False
        
        return seen_digit and seen_digit_after_e


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
    testSolution(solution)
