import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

class Solution {
    public List<String> fullJustify(String[] words, int maxWidth) {
        int left = 0;
        List<String> result = new ArrayList<>();

        while (left < words.length) {
            int right = findRight(left, words, maxWidth);
            result.add(justify(left, right, words, maxWidth));
            left = right + 1;
        }

        return result;
    }

    private int findRight(int left, String[] words, int maxWidth) {
        int right = left;
        int sum = words[right++].length();

        while (right < words.length && (sum + 1 + words[right].length()) <= maxWidth)
            sum += 1 + words[right++].length();

        return right - 1;
    }

    private String justify(int left, int right, String[] words, int maxWidth) {
        if (right - left == 0) return padResult(words[left], maxWidth);

        boolean isLastLine = right == words.length - 1;
        int numSpaces = right - left;
        int totalSpace = maxWidth - wordsLength(left, right, words);

        String space = isLastLine ? " " : blank(totalSpace / numSpaces);
        int remainder = isLastLine ? 0 : totalSpace % numSpaces;

        StringBuilder result = new StringBuilder();
        for (int i = left; i <= right; i++)
            result.append(words[i])
                    .append(space)
                    .append(remainder-- > 0 ? " " : "");

        return padResult(result.toString().trim(), maxWidth);
    }

    private int wordsLength(int left, int right, String[] words) {
        int wordsLength = 0;
        for (int i = left; i <= right; i++) wordsLength += words[i].length();
        return wordsLength;
    }

    private String padResult(String result, int maxWidth) {
        return result + blank(maxWidth - result.length());
    }

    private String blank(int length) {
        return new String(new char[length]).replace('\0', ' ');
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

    