class Solution(object):
    def isMatch(self, s, p):
        """
        :type s: str
        :type p: str
        :rtype: bool
        """
        transfer = {}
        state = 0
        
        for char in p:
            if char == '*':
                transfer[state, char] = state
            else:
                transfer[state, char] = state + 1
                state += 1
        
        accept = state
        states = {0}
        
        for char in s:
            states = {transfer.get((at, token)) for at in states if at is not None for token in (char, '*', '?')}
        
        return accept in states

# Test cases for the Python solution
def testSolution(solution):
    # Test case 1: Simple match with exact pattern
    s = "abcd"
    p = "abcd"
    expected_result = True
    assert solution.isMatch(s, p) == expected_result, f"Test case 1 failed. Expected {expected_result}."

    # Test case 2: Pattern with '?' matching a single character
    s = "abcd"
    p = "a?cd"
    expected_result = True
    assert solution.isMatch(s, p) == expected_result, f"Test case 2 failed. Expected {expected_result}."

    # Test case 3: Pattern with '*' matching any sequence of characters
    s = "abcd"
    p = "a*d"
    expected_result = True
    assert solution.isMatch(s, p) == expected_result, f"Test case 3 failed. Expected {expected_result}."

    # Test case 4: Pattern with '*' matching an empty sequence
    s = "abcd"
    p = "a*cd"
    expected_result = True
    assert solution.isMatch(s, p) == expected_result, f"Test case 4 failed. Expected {expected_result}."

    # Test case 5: No match due to extra characters in pattern
    s = "abc"
    p = "abcd"
    expected_result = False
    assert solution.isMatch(s, p) == expected_result, f"Test case 5 failed. Expected {expected_result}."

    # Test case 6: Multiple '*' characters and '?' in the pattern
    s = "abefcdgiescdfimde"
    p = "ab*cd?i*de"
    expected_result = True
    assert solution.isMatch(s, p) == expected_result, f"Test case 6 failed. Expected {expected_result}."

    # Test case 7: Empty pattern matching an empty string
    s = ""
    p = ""
    expected_result = True
    assert solution.isMatch(s, p) == expected_result, f"Test case 7 failed. Expected {expected_result}."

    # Test case 8: Pattern with only '*' should match any string
    s = "anything"
    p = "*"
    expected_result = True
    assert solution.isMatch(s, p) == expected_result, f"Test case 8 failed. Expected {expected_result}."

if __name__ == "__main__":
    solution = Solution()
    for i in range(300000):
        testSolution(solution)
