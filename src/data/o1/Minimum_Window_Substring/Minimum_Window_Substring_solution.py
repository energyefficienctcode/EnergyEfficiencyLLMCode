class Solution(object):
    def minWindow(self, s, t):
        """
        :type s: str
        :type t: str
        :rtype: str
        """
        from collections import Counter

        if not t or not s:
            return ""
        
        dict_t = Counter(t)
        required = len(dict_t)
        
        # Filter all the characters from s into a new list along with their index
        # The filtering is done so as to have only characters that are present in t
        filtered_s = []
        for i, char in enumerate(s):
            if char in dict_t:
                filtered_s.append((i, char))
        
        l, r = 0, 0
        formed = 0
        window_counts = {}
        ans = float("inf"), None, None
        
        while r < len(filtered_s):
            character = filtered_s[r][1]
            window_counts[character] = window_counts.get(character, 0) + 1
            
            if window_counts[character] == dict_t[character]:
                formed += 1
            
            # Try and contract the window till the point it ceases to be 'desirable'
            while l <= r and formed == required:
                character = filtered_s[l][1]
                
                start = filtered_s[l][0]
                end = filtered_s[r][0]
                
                if end - start + 1 < ans[0]:
                    ans = (end - start + 1, start, end)
                
                window_counts[character] -= 1
                if window_counts[character] < dict_t[character]:
                    formed -= 1
                
                l += 1
            
            r += 1
        
        return "" if ans[0] == float("inf") else s[ans[1]:ans[2]+1]


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
