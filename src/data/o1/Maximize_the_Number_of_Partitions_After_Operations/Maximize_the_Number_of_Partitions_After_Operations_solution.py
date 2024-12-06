class Solution(object):
    def maxPartitionsAfterOperations(self, s, k):
        """
        :type s: str
        :type k: int
        :rtype: int
        """
        def count_partitions(s, k):
            partitions = 0
            freq = {}
            distinct = 0
            start = 0
            for end, char in enumerate(s):
                if char not in freq or freq[char] == 0:
                    distinct += 1
                freq[char] = freq.get(char, 0) + 1
                while distinct > k:
                    freq[s[start]] -= 1
                    if freq[s[start]] == 0:
                        distinct -= 1
                    start += 1
                # If the current window is the longest possible with <=k distinct characters
                if end == len(s) - 1 or (end + 1 < len(s) and self._will_exceed(s, end + 1, freq, distinct, k)):
                    partitions += 1
                    freq = {}
                    distinct = 0
                    start = end + 1
            return partitions

        def max_partitions(s, k):
            return count_partitions(s, k)

        max_part = count_partitions(s, k)
        for i in range(len(s)):
            original_char = s[i]
            for c in 'abcdefghijklmnopqrstuvwxyz':
                if c == original_char:
                    continue
                new_s = s[:i] + c + s[i+1:]
                current_part = count_partitions(new_s, k)
                if current_part > max_part:
                    max_part = current_part
        return max_part

    def _will_exceed(self, s, next_index, freq, distinct, k):
        if next_index >= len(s):
            return False
        char = s[next_index]
        if char not in freq or freq[char] == 0:
            return distinct + 1 > k
        return False

# Test cases for the Python solution
def testSolution(solution):
    # Test case 1: Single character string
    s = "a"
    k = 1
    expected_result = 1
    assert solution.maxPartitionsAfterOperations(s, k) == expected_result, f"Test case 1 failed. Expected {expected_result}."

    # Test case 2: No change needed to partition optimally
    s = "accca"
    k = 2
    expected_result = 3
    assert solution.maxPartitionsAfterOperations(s, k) == expected_result, f"Test case 2 failed. Expected {expected_result}."

    # Test case 3: Change one character to maximize partitions
    s = "abac"
    k = 2
    expected_result = 2
    assert solution.maxPartitionsAfterOperations(s, k) == expected_result, f"Test case 3 failed. Expected {expected_result}."

    # Test case 4: Entire string has more than k distinct characters, requiring changes
    s = "aabaab"
    k = 3
    expected_result = 1
    assert solution.maxPartitionsAfterOperations(s, k) == expected_result, f"Test case 4 failed. Expected {expected_result}."

    # Test case 5: Optimal choice without changing characters
    s = "xxyz"
    k = 1
    expected_result = 4
    assert solution.maxPartitionsAfterOperations(s, k) == expected_result, f"Test case 5 failed. Expected {expected_result}."

    # Test case 6: Large k that allows full string as one partition
    s = "abcdefgh"
    k = 8
    expected_result = 1
    assert solution.maxPartitionsAfterOperations(s, k) == expected_result, f"Test case 6 failed. Expected {expected_result}."

    # Test case 7: k smaller than distinct characters in s, requiring multiple partitions
    s = "abcabcabc"
    k = 1
    expected_result = 9
    assert solution.maxPartitionsAfterOperations(s, k) == expected_result, f"Test case 7 failed. Expected {expected_result}."



if __name__ == "__main__":
    solution = Solution()
    for i in range(10000):
        testSolution(solution)
