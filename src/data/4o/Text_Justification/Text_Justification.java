import java.util.*;

class Solution {
    public List<String> fullJustify(String[] words, int maxWidth) {
        List<String> result = new ArrayList<>();
        int index = 0;

        while (index < words.length) {
            int totalChars = words[index].length();
            int last = index + 1;

            // Find how many words can fit in the current line
            while (last < words.length) {
                if (totalChars + 1 + words[last].length() > maxWidth) break;
                totalChars += 1 + words[last].length();
                last++;
            }

            StringBuilder sb = new StringBuilder();
            int numberOfWords = last - index;
            int numberOfSpaces = maxWidth - totalChars;

            // Handle last line or lines with only one word
            if (last == words.length || numberOfWords == 1) {
                for (int i = index; i < last; i++) {
                    sb.append(words[i]);
                    if (i < last - 1) sb.append(" ");
                }
                while (sb.length() < maxWidth) {
                    sb.append(" ");
                }
            } else {
                int spacesBetweenWords = numberOfSpaces / (numberOfWords - 1);
                int extraSpaces = numberOfSpaces % (numberOfWords - 1);

                for (int i = index; i < last; i++) {
                    sb.append(words[i]);
                    if (i < last - 1) {
                        for (int j = 0; j <= (spacesBetweenWords + (i - index < extraSpaces ? 1 : 0)); j++) {
                            sb.append(" ");
                        }
                    }
                }
            }

            result.add(sb.toString());
            index = last;
        }

        return result;
    }
}

public class Text_Justification {
public static void runTests(Solution solution) {
    // Test case 1: Simple case with exact fit
    String[] words1 = {"This", "is", "an", "example", "of", "text", "justification."};
    int maxWidth1 = 16;
    List<String> expected_result1 = Arrays.asList(
        "This    is    an",
        "example  of text",
        "justification.  "
    );
    assert solution.fullJustify(words1, maxWidth1).equals(expected_result1) : "Test case 1 failed. Expected " + expected_result1;

    // Test case 2: Single word that exactly matches maxWidth
    String[] words2 = {"Justify"};
    int maxWidth2 = 7;
    List<String> expected_result2 = Arrays.asList("Justify");
    assert solution.fullJustify(words2, maxWidth2).equals(expected_result2) : "Test case 2 failed. Expected " + expected_result2;

    // Test case 3: Single word shorter than maxWidth
    String[] words3 = {"Hello"};
    int maxWidth3 = 10;
    List<String> expected_result3 = Arrays.asList("Hello     ");
    assert solution.fullJustify(words3, maxWidth3).equals(expected_result3) : "Test case 3 failed. Expected " + expected_result3;

    // Test case 4: Multiple words, last line left-justified
    String[] words4 = {"What", "must", "be", "acknowledgment", "shall", "be"};
    int maxWidth4 = 16;
    List<String> expected_result4 = Arrays.asList(
        "What   must   be",
        "acknowledgment  ",
        "shall be        "
    );
    assert solution.fullJustify(words4, maxWidth4).equals(expected_result4) : "Test case 4 failed. Expected " + expected_result4;

    // Test case 5: Uneven space distribution
    String[] words5 = {"Science", "is", "what", "we", "understand", "well", "enough", "to", "explain"};
    int maxWidth5 = 20;
    List<String> expected_result5 = Arrays.asList(
        "Science  is  what we",
        "understand      well",
        "enough to explain   "
    );
    assert solution.fullJustify(words5, maxWidth5).equals(expected_result5) : "Test case 5 failed. Expected " + expected_result5;

    // Test case 6: Only one word per line, lines longer than words
    String[] words6 = {"Single", "word", "per", "line"};
    int maxWidth6 = 10;
    List<String> expected_result6 = Arrays.asList("Single    ", "word   per", "line      ");
    assert solution.fullJustify(words6, maxWidth6).equals(expected_result6) : "Test case 6 failed. Expected " + expected_result6;

    // Test case 7: All words fit into one line, exact width
    String[] words7 = {"One", "line", "test"};
    int maxWidth7 = 12;
    List<String> expected_result7 = Arrays.asList("One     line", "test        ");
    assert solution.fullJustify(words7, maxWidth7).equals(expected_result7) : "Test case 7 failed. Expected " + expected_result7;
}


    public static void main(String[] args) {
        Solution solution = new Solution();
        for (int i = 0; i < 5000000; i++) {
            runTests(solution); // Ensure your test cases are implemented inside runTests
        }
    }
}

    