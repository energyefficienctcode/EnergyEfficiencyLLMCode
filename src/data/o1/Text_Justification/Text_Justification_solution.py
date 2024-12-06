class Solution(object):
    def fullJustify(self, words, maxWidth):
        """
        :type words: List[str]
        :type maxWidth: int
        :rtype: List[str]
        """
        result = []
        current_line = []
        num_of_letters = 0

        for word in words:
            if num_of_letters + len(word) + len(current_line) > maxWidth:
                if len(current_line) == 1:
                    line = current_line[0] + ' ' * (maxWidth - num_of_letters)
                else:
                    total_spaces = maxWidth - num_of_letters
                    spaces_between_words = total_spaces // (len(current_line) - 1)
                    extra_spaces = total_spaces % (len(current_line) - 1)
                    
                    line = ""
                    for i in range(len(current_line) - 1):
                        line += current_line[i]
                        line += ' ' * (spaces_between_words + (1 if i < extra_spaces else 0))
                    line += current_line[-1]
                result.append(line)
                current_line = []
                num_of_letters = 0
            current_line.append(word)
            num_of_letters += len(word)
        
        # Last line
        line = ' '.join(current_line)
        line += ' ' * (maxWidth - len(line))
        result.append(line)
        
        return result


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
