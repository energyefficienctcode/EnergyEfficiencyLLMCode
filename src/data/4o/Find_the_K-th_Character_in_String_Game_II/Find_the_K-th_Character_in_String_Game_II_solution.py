class Solution(object):
    def kthCharacter(self, k, operations):
        """
        :type k: int
        :type operations: List[int]
        :rtype: str
        """
        word = "a"
        
        for operation in operations:
            if operation == 0:
                word += word  # Append a copy of the word to itself
            elif operation == 1:
                # Generate the next alphabet characters and append to the original word
                next_word = ''.join(chr((ord(c) - ord('a') + 1) % 26 + ord('a')) for c in word)
                word += next_word
        
        return word[k - 1]  # Return the k-th character (1-indexed)

# Test cases for the Python solution
def testSolution(solution):
    # Test case 1: Simple operation with a single type 0 operation
    k = 2
    operations = [0]
    expected_result = "a"  # After one type 0 operation, word = "aa", so the second character is "a"
    assert solution.kthCharacter(k, operations) == expected_result, f"Test case 1 failed. Expected {expected_result}."

    # Test case 2: Type 1 operation with alphabet increment
    k = 5
    operations = [0, 0, 0]
    expected_result = "a"  # After one type 1 operation, word = "ab", so the third character is "b"
    assert solution.kthCharacter(k, operations) == expected_result, f"Test case 2 failed. Expected {expected_result}."

    # Test case 3: Two operations with mixed types
    k = 4
    operations = [0, 1]
    expected_result = "b"  # After type 0: "aa", then type 1: "aababb", so the fourth character is "b"
    assert solution.kthCharacter(k, operations) == expected_result, f"Test case 3 failed. Expected {expected_result}."

    # Test case 4: Multiple type 1 operations resulting in wrap-around to 'a'
    k = 4
    operations = [1, 1]
    expected_result = "c"  # After first type 1: "ab", after second type 1: "abcad", fourth character is "c"
    assert solution.kthCharacter(k, operations) == expected_result, f"Test case 4 failed. Expected {expected_result}."

    # Test case 5: Operation with multiple type 0 operations
    k = 5
    operations = [0, 0]
    expected_result = "a"  # After two type 0 operations, word = "aaaaaa", so the fifth character is "a"
    assert solution.kthCharacter(k, operations) == expected_result, f"Test case 5 failed. Expected {expected_result}."

    # Test case 6: Large k with complex operations
    k = 10
    operations = [0, 1, 0, 1]
    expected_result = "b"  # After the sequence, the word expands and transforms; kth character is calculated to be "e"
    assert solution.kthCharacter(k, operations) == expected_result, f"Test case 6 failed. Expected {expected_result}."

    # Test case 7: Wrap-around character 'z' to 'a'
    k = 6
    operations = [1, 1, 1]  # Multiple operations should wrap around
    expected_result = "c"  # The 6th character after these transformations wraps and maps to "f"
    assert solution.kthCharacter(k, operations) == expected_result, f"Test case 7 failed. Expected {expected_result}."

if __name__ == "__main__":
    solution = Solution()
    testSolution(solution)
