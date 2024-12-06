from collections import Counter

class Solution(object):
    def minWindow(self, s, t):
        """
        :type s: str
        :type t: str
        :rtype: str
        """
        if not s or not t:
            return ""

        dict_t = Counter(t)
        required = len(dict_t)
        l, r = 0, 0
        formed = 0
        window_counts = {}
        ans = float("inf"), None, None

        while r < len(s):
            character = s[r]
            window_counts[character] = window_counts.get(character, 0) + 1

            if character in dict_t and window_counts[character] == dict_t[character]:
                formed += 1

            while l <= r and formed == required:
                character = s[l]

                if r - l + 1 < ans[0]:
                    ans = (r - l + 1, l, r)

                window_counts[character] -= 1
                if character in dict_t and window_counts[character] < dict_t[character]:
                    formed -= 1

                l += 1

            r += 1

        return "" if ans[0] == float("inf") else s[ans[1]: ans[2] + 1]

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
    s = "aaabbbccc"
    t = "abc"
    expected_result = "abc"
    assert solution.minWindow(s, t) == expected_result, f"Test case 7 failed. Expected {expected_result}."

if __name__ == "__main__":
    solution = Solution()
    testSolution(solution)
