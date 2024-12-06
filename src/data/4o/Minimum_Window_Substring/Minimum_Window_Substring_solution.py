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
        
        t_count = Counter(t)
        current_count = Counter()
        required = len(t_count)
        formed = 0
        
        left, right = 0, 0
        min_len = float('inf')
        min_window = (0, 0)
        
        while right < len(s):
            char = s[right]
            current_count[char] += 1
            
            if char in t_count and current_count[char] == t_count[char]:
                formed += 1
            
            while left <= right and formed == required:
                char = s[left]
                
                if right - left + 1 < min_len:
                    min_len = right - left + 1
                    min_window = (left, right)
                
                current_count[char] -= 1
                if char in t_count and current_count[char] < t_count[char]:
                    formed -= 1
                
                left += 1
            
            right += 1
        
        left, right = min_window
        return s[left:right + 1] if min_len != float('inf') else ""

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
