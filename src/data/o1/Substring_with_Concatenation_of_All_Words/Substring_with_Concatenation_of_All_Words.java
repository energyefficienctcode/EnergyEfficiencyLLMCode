import java.util.*;

class Solution {
    public List<Integer> findSubstring(String s, String[] words) {
        List<Integer> result = new ArrayList<>();
        if(s == null || words == null || words.length == 0) return result;
        
        int wordLen = words[0].length();
        int totalWords = words.length;
        int totalLen = wordLen * totalWords;
        
        if(s.length() < totalLen) return result;
        
        // Build frequency map
        Map<String, Integer> wordCount = new HashMap<>();
        for(String word : words){
            wordCount.put(word, wordCount.getOrDefault(word, 0) + 1);
        }
        
        for(int i = 0; i < wordLen; i++){
            int left = i;
            int count = 0;
            Map<String, Integer> currentCount = new HashMap<>();
            
            for(int j = i; j <= s.length() - wordLen; j += wordLen){
                String word = s.substring(j, j + wordLen);
                if(wordCount.containsKey(word)){
                    currentCount.put(word, currentCount.getOrDefault(word, 0) + 1);
                    count++;
                    
                    while(currentCount.get(word) > wordCount.get(word)){
                        String leftWord = s.substring(left, left + wordLen);
                        currentCount.put(leftWord, currentCount.get(leftWord) - 1);
                        count--;
                        left += wordLen;
                    }
                    
                    if(count == totalWords){
                        result.add(left);
                        String leftWord = s.substring(left, left + wordLen);
                        currentCount.put(leftWord, currentCount.get(leftWord) - 1);
                        count--;
                        left += wordLen;
                    }
                }
                else{
                    currentCount.clear();
                    count = 0;
                    left = j + wordLen;
                }
            }
        }
        
        return result;
    }
}

public class Substring_with_Concatenation_of_All_Words {
public static void runTests(Solution solution) {
    // Test case 1: Simple match with all words used exactly once
    String s = "barfoothefoobarman";
    String[] words = {"foo", "bar"};
    int[] expected_result = {0, 9};
    assert Arrays.equals(solution.findSubstring(s, words).stream().sorted().mapToInt(i -> i).toArray(), expected_result) : "Test case 1 failed. Expected " + Arrays.toString(expected_result);

    // Test case 2: Multiple possible starting indices with different word orders
    s = "wordgoodgoodgoodbestword";
    words = new String[]{"word", "good", "best", "word"};
    expected_result = new int[]{};
    assert Arrays.equals(solution.findSubstring(s, words).stream().sorted().mapToInt(i -> i).toArray(), expected_result) : "Test case 2 failed. Expected " + Arrays.toString(expected_result);

    // Test case 3: Words overlap at different positions
    s = "barfoofoobarthefoobarman";
    words = new String[]{"bar", "foo", "the"};
    expected_result = new int[]{6, 9, 12};
    assert Arrays.equals(solution.findSubstring(s, words).stream().sorted().mapToInt(i -> i).toArray(), expected_result) : "Test case 3 failed. Expected " + Arrays.toString(expected_result);

    // Test case 4: Full match where all words repeat
    s = "lingmindraboofooowingdingbarrwingmonkeypoundcake";
    words = new String[]{"fooo", "barr", "wing", "ding", "wing"};
    expected_result = new int[]{13};
    assert Arrays.equals(solution.findSubstring(s, words).stream().sorted().mapToInt(i -> i).toArray(), expected_result) : "Test case 4 failed. Expected " + Arrays.toString(expected_result);

    // Test case 5: Single word list
    s = "foobarfoobar";
    words = new String[]{"foobar"};
    expected_result = new int[]{0, 6};
    assert Arrays.equals(solution.findSubstring(s, words).stream().sorted().mapToInt(i -> i).toArray(), expected_result) : "Test case 5 failed. Expected " + Arrays.toString(expected_result);

    // Test case 6: No match due to missing words
    s = "aaa";
    words = new String[]{"aa", "aa"};
    expected_result = new int[]{};
    assert Arrays.equals(solution.findSubstring(s, words).stream().sorted().mapToInt(i -> i).toArray(), expected_result) : "Test case 6 failed. Expected " + Arrays.toString(expected_result);

    // Test case 7: Empty string s
    s = "";
    words = new String[]{"foo", "bar"};
    expected_result = new int[]{};
    assert Arrays.equals(solution.findSubstring(s, words).stream().sorted().mapToInt(i -> i).toArray(), expected_result) : "Test case 7 failed. Expected " + Arrays.toString(expected_result);
}

    public static void main(String[] args) {
        Solution solution = new Solution();
        for (int i = 0; i < 3000000; i++) {
            runTests(solution); // Ensure your test cases are implemented inside runTests
        }
    }
}

    