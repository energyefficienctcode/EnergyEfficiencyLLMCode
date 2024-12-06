from typing import List


class Solution:
    def beautifulIndices(self, s: str, a: str, b: str, k: int) -> List[int]:
        def kmp(s):
           dp = [0] * len(s)
           for i in range(1, len(s)):
               cur = dp[i - 1]
               while cur and s[i] != s[cur]:
                   cur = dp[cur - 1]
               dp[i] = cur + (s[i] == s[cur])
           return dp

        n, la, lb = len(s), len(a), len(b)
        v1 = kmp(a + '#' + s)
        v2 = kmp(b + '#' + s)
        ii = [i - la - la for i,v in enumerate(v1) if v >= la]
        jj = [j - lb - lb for j,v in enumerate(v2) if v >= lb]
        res = []
        j = 0
        for i in ii:
            while j < len(jj) and jj[j] < i - k:
                j += 1
            if j < len(jj) and jj[j] <= i + k:
                res.append(i)
        return res

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
