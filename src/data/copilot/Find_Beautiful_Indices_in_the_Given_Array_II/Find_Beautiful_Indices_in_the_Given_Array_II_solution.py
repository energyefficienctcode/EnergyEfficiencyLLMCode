class Solution(object):
    def beautifulIndices(self, s, a, b, k):
        """
        :type s: str
        :type a: str
        :type b: str
        :type k: int
        :rtype: List[int]
        """
        a_len, b_len = len(a), len(b)
        a_indices = [i for i in range(len(s) - a_len + 1) if s[i:i + a_len] == a]
        b_indices = [j for j in range(len(s) - b_len + 1) if s[j:j + b_len] == b]
        
        beautiful_indices = []
        for i in a_indices:
            for j in b_indices:
                if abs(j - i) <= k:
                    beautiful_indices.append(i)
                    break
        
        return sorted(beautiful_indices)

# Test cases for the Python solution
def testSolution(solution):
    # Test case 1: Simple case with one beautiful index
    s = "abcde"
    a = "ab"
    b = "de"
    k = 4
    expected_result = [0]
    assert solution.beautifulIndices(s, a, b, k) == expected_result, f"Test case 1 failed. Expected {expected_result}."

    # Test case 2: Multiple beautiful indices
    s = "ababab"
    a = "ab"
    b = "ba"
    k = 1
    expected_result = [0, 2, 4]
    assert solution.beautifulIndices(s, a, b, k) == expected_result, f"Test case 2 failed. Expected {expected_result}."

    # Test case 3: No beautiful indices
    s = "isawsquirrelnearmysquirrelhouseohmy"
    a = "my"
    b = "squirrel"
    k = 15
    expected_result = [16, 33]
    assert solution.beautifulIndices(s, a, b, k) == expected_result, f"Test case 3 failed. Expected {expected_result}."

    # Test case 4: Overlapping matches with larger k
    s = "abababab"
    a = "ab"
    b = "ab"
    k = 2
    expected_result = [0, 2, 4, 6]
    assert solution.beautifulIndices(s, a, b, k) == expected_result, f"Test case 4 failed. Expected {expected_result}."

    # Test case 5: Only one match each for a and b, within range k
    s = "abcdef"
    a = "abc"
    b = "def"
    k = 5
    expected_result = [0]
    assert solution.beautifulIndices(s, a, b, k) == expected_result, f"Test case 5 failed. Expected {expected_result}."

    # Test case 6: Overlapping b close to the end of a with k = 0
    s = "abcd"
    a = "a"
    b = "a"
    k = 4
    expected_result = [0]
    assert solution.beautifulIndices(s, a, b, k) == expected_result, f"Test case 6 failed. Expected {expected_result}."

    # Test case 7: Non-overlapping multiple beautiful indices with exact k distance
    s = "aaaaaa"
    a = "aa"
    b = "aa"
    k = 2
    expected_result = [0, 1, 2, 3, 4]
    assert solution.beautifulIndices(s, a, b, k) == expected_result, f"Test case 7 failed. Expected {expected_result}."


if __name__ == "__main__":
    solution = Solution()
    for i in range(1000000):
        testSolution(solution)
