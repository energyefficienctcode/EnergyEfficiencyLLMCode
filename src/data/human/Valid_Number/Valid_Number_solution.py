class Solution(object):
  def isNumber(self, s):
      """
      :type s: str
      :rtype: bool
      """
      #define a DFA
      state = [{}, 
              {'blank': 1, 'sign': 2, 'digit':3, '.':4}, 
              {'digit':3, '.':4},
              {'digit':3, '.':5, 'e':6, 'blank':9},
              {'digit':5},
              {'digit':5, 'e':6, 'blank':9},
              {'sign':7, 'digit':8},
              {'digit':8},
              {'digit':8, 'blank':9},
              {'blank':9}]
      currentState = 1
      for c in s:
          if c >= '0' and c <= '9':
              c = 'digit'
          if c == ' ':
              c = 'blank'
          if c in ['+', '-']:
              c = 'sign'
          if c not in state[currentState].keys():
              return False
          currentState = state[currentState][c]
      if currentState not in [3,5,8,9]:
          return False
      return True

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
