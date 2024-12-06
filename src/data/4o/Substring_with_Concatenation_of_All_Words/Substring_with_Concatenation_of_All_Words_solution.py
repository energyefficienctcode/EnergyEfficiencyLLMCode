from collections import Counter

class Solution(object):
    def findSubstring(self, s, words):
        """
        :type s: str
        :type words: List[str]
        :rtype: List[int]
        """
        if not s or not words:
            return []
        
        word_len = len(words[0])
        word_count = len(words)
        total_len = word_len * word_count
        word_freq = Counter(words)
        result = []
        
        for i in range(len(s) - total_len + 1):
            seen_words = Counter()
            for j in range(0, total_len, word_len):
                word = s[i + j:i + j + word_len]
                if word in word_freq:
                    seen_words[word] += 1
                    if seen_words[word] > word_freq[word]:
                        break
                else:
                    break
            if seen_words == word_freq:
                result.append(i)
        
        return result

# Test cases for the Python solution
def testSolution(solution):
    # Test case 1: Simple match with all words used exactly once
    s = "barfoothefoobarman"
    words = ["foo", "bar"]
    expected_result = [0, 9]
    assert sorted(solution.findSubstring(s, words)) == sorted(expected_result), f"Test case 1 failed. Expected {expected_result}."

    # Test case 2: Multiple possible starting indices with different word orders
    s = "wordgoodgoodgoodbestword"
    words = ["word", "good", "best", "word"]
    expected_result = []
    assert sorted(solution.findSubstring(s, words)) == sorted(expected_result), f"Test case 2 failed. Expected {expected_result}."

    # Test case 3: Words overlap at different positions
    s = "barfoofoobarthefoobarman"
    words = ["bar", "foo", "the"]
    expected_result = [6, 9, 12]
    assert sorted(solution.findSubstring(s, words)) == sorted(expected_result), f"Test case 3 failed. Expected {expected_result}."

    # Test case 4: Full match where all words repeat
    s = "lingmindraboofooowingdingbarrwingmonkeypoundcake"
    words = ["fooo", "barr", "wing", "ding", "wing"]
    expected_result = [13]
    assert sorted(solution.findSubstring(s, words)) == sorted(expected_result), f"Test case 4 failed. Expected {expected_result}."

    # Test case 5: Single word list
    s = "foobarfoobar"
    words = ["foobar"]
    expected_result = [0, 6]
    assert sorted(solution.findSubstring(s, words)) == sorted(expected_result), f"Test case 5 failed. Expected {expected_result}."

    # Test case 6: No match due to missing words
    s = "aaa"
    words = ["aa", "aa"]
    expected_result = []
    assert sorted(solution.findSubstring(s, words)) == sorted(expected_result), f"Test case 6 failed. Expected {expected_result}."

    # Test case 7: Empty string s
    s = ""
    words = ["foo", "bar"]
    expected_result = []
    assert sorted(solution.findSubstring(s, words)) == sorted(expected_result), f"Test case 7 failed. Expected {expected_result}."

if __name__ == "__main__":
    solution = Solution()
    for i in range(100000):
        testSolution(solution)
