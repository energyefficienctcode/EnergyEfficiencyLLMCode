class Solution:
    def fullJustify(self, words, maxWidth):
        res, cur, num_of_letters = [], [], 0
        for w in words:
            if num_of_letters + len(w) + len(cur) > maxWidth:
                for i in range(maxWidth - num_of_letters):
                    cur[i%(len(cur)-1 or 1)] += ' '
                res.append(''.join(cur))
                cur, num_of_letters = [], 0
            cur += [w]
            num_of_letters += len(w)
        return res + [' '.join(cur).ljust(maxWidth)]

# Test cases for the Python solution
def testSolution(solution):
    # Test case 1: Simple case with exact fit
    words = ["This", "is", "an", "example", "of", "text", "justification."]
    maxWidth = 16
    expected_result = [
        "This    is    an",
        "example  of text",
        "justification.  "
    ]
    assert solution.fullJustify(words, maxWidth) == expected_result, f"Test case 1 failed. Expected {expected_result}."

    # Test case 2: Single word that exactly matches maxWidth
    words = ["Justify"]
    maxWidth = 7
    expected_result = ["Justify"]
    assert solution.fullJustify(words, maxWidth) == expected_result, f"Test case 2 failed. Expected {expected_result}."

    # Test case 3: Single word shorter than maxWidth
    words = ["Hello"]
    maxWidth = 10
    expected_result = ["Hello     "]
    assert solution.fullJustify(words, maxWidth) == expected_result, f"Test case 3 failed. Expected {expected_result}."

    # Test case 4: Multiple words, last line left-justified
    words = ["What", "must", "be", "acknowledgment", "shall", "be"]
    maxWidth = 16
    expected_result = [
        "What   must   be",
        "acknowledgment  ",
        "shall be        "
    ]
    assert solution.fullJustify(words, maxWidth) == expected_result, f"Test case 4 failed. Expected {expected_result}."

    # Test case 5: Uneven space distribution
    words = ["Science", "is", "what", "we", "understand", "well", "enough", "to", "explain"]
    maxWidth = 20
    expected_result = [
        "Science  is  what we",
        "understand      well",
        "enough to explain   "
    ]
    assert solution.fullJustify(words, maxWidth) == expected_result, f"Test case 5 failed. Expected {expected_result}."

    # Test case 6: Only one word per line, lines longer than words
    words = ["Single", "word", "per", "line"]
    maxWidth = 10
    expected_result = ["Single    ", "word   per", "line      "]
    assert solution.fullJustify(words, maxWidth) == expected_result, f"Test case 6 failed. Expected {expected_result}."

    # Test case 7: All words fit into one line, exact width
    words = ["One", "line", "test"]
    maxWidth = 12
    expected_result = ["One     line", "test        "]
    assert solution.fullJustify(words, maxWidth) == expected_result, f"Test case 7 failed. Expected {expected_result}."

if __name__ == "__main__":
    solution = Solution()
    for i in range(1000000):
        testSolution(solution)
