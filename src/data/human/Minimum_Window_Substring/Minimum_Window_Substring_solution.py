import collections


class Solution:
    def minWindow(self, s: str, t: str) -> str:
        if len(s) < len(t):
            return ""
        needstr = collections.defaultdict(int)
        for ch in t:
            needstr[ch] += 1
        needcnt = len(t)
        res = (0, float('inf'))
        start = 0
        for end, ch in enumerate(s):
            if needstr[ch] > 0:
                needcnt -= 1
            needstr[ch] -= 1
            if needcnt == 0:
                while True:
                    tmp = s[start]
                    if needstr[tmp] == 0:
                        break
                    needstr[tmp] += 1
                    start += 1
                if end - start < res[1] - res[0]:
                    res = (start, end)
                needstr[s[start]] += 1
                needcnt += 1
                start += 1
        return '' if res[1] > len(s) else s[res[0]:res[1]+1]

# Test cases for the Python solution
def testSolution(solution):
    # Test case 1: Small substring found at the beginning
    s = "ADOBECODEBANC"
    t = "ABC"
    expected_result = "BANC"
    assert solution.minWindow(s, t) == expected_result, f"Test case 1 failed. Expected {expected_result}."

    # Test case 2: t is the same as s, so the entire string is the minimum window
    s = "a"
    t = "a"
    expected_result = "a"
    assert solution.minWindow(s, t) == expected_result, f"Test case 2 failed. Expected {expected_result}."

    # Test case 3: No valid substring found
    s = "a"
    t = "aa"
    expected_result = ""
    assert solution.minWindow(s, t) == expected_result, f"Test case 3 failed. Expected {expected_result}."

    # Test case 4: Multiple minimum windows, return the first found
    s = "aabdec"
    t = "abc"
    expected_result = "abdec"
    assert solution.minWindow(s, t) == expected_result, f"Test case 4 failed. Expected {expected_result}."

    # Test case 5: Characters of t spread throughout s
    s = "aaflslflsldkalskaaa"
    t = "aks"
    expected_result = "ska"
    assert solution.minWindow(s, t) == expected_result, f"Test case 5 failed. Expected {expected_result}."

    # Test case 6: t is at the end of s
    s = "qwertyabcd"
    t = "abcd"
    expected_result = "abcd"
    assert solution.minWindow(s, t) == expected_result, f"Test case 6 failed. Expected {expected_result}."

    # Test case 7: Multiple occurrences of characters in t
    s = "ADOBECODEBANC"
    t = "ABC"
    expected_result = "BANC"
    assert solution.minWindow(s, t) == expected_result, f"Test case 7 failed. Expected {expected_result}."

if __name__ == "__main__":
    solution = Solution()
    for i in range(300000):
        testSolution(solution)
