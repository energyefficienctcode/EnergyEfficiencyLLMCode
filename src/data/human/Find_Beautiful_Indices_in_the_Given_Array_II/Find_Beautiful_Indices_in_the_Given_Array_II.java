import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

class Solution {
    void getPatternMatchingIndex(String s, String a, List<Integer> v) {
        String t = a + "@" + s;
        List<Integer> lps = new ArrayList<>();
        lps.add(0);
        for (int i = 1; i < t.length(); ++i) {
            int ind = lps.get(i - 1);
            while (ind > 0 && t.charAt(ind) != t.charAt(i)) {
                ind = lps.get(ind - 1);
            }
            lps.add((t.charAt(ind) == t.charAt(i)) ? ind + 1 : 0);
        }
        for (int i = 0; i < lps.size(); ++i) {
            if (lps.get(i) == a.length()) v.add(i - 2 * a.length());
        }
    }

    public List<Integer> beautifulIndices(String s, String a, String b, int k) {
        List<Integer> ans = new ArrayList<>();
        List<Integer> v1 = new ArrayList<>();
        List<Integer> v2 = new ArrayList<>();
        getPatternMatchingIndex(s, a, v1);
        getPatternMatchingIndex(s, b, v2);
        for (int i = 0, j = 0; i < v1.size(); ++i) {
            while (j < v2.size() && v1.get(i) > v2.get(j) && Math.abs(v1.get(i) - v2.get(j)) > k) j++;
            if (j < v2.size() && Math.abs(v1.get(i) - v2.get(j)) <= k) ans.add(v1.get(i));
        }
        return ans;
    }
}

public class Find_Beautiful_Indices_in_the_Given_Array_II {
public static void runTests(Solution solution) {
    // Test case 1: Simple case with one beautiful index
    String s1 = "abcde";
    String a1 = "ab";
    String b1 = "de";
    int k1 = 4;
    List<Integer> expected_result1 = Arrays.asList(0);
    assert solution.beautifulIndices(s1, a1, b1, k1).equals(expected_result1) : "Test case 1 failed. Expected " + expected_result1;

    // Test case 2: Multiple beautiful indices
    String s2 = "ababab";
    String a2 = "ab";
    String b2 = "ba";
    int k2 = 1;
    List<Integer> expected_result2 = Arrays.asList(0, 2, 4);
    assert solution.beautifulIndices(s2, a2, b2, k2).equals(expected_result2) : "Test case 2 failed. Expected " + expected_result2;

    // Test case 3: No beautiful indices
    String s3 = "isawsquirrelnearmysquirrelhouseohmy";
    String a3 = "my";
    String b3 = "squirrel";
    int k3 = 15;
    List<Integer> expected_result3 = Arrays.asList(16, 33);
    assert solution.beautifulIndices(s3, a3, b3, k3).equals(expected_result3) : "Test case 3 failed. Expected " + expected_result3;

    // Test case 4: Overlapping matches with larger k
    String s4 = "abababab";
    String a4 = "ab";
    String b4 = "ab";
    int k4 = 2;
    List<Integer> expected_result4 = Arrays.asList(0, 2, 4, 6);
    assert solution.beautifulIndices(s4, a4, b4, k4).equals(expected_result4) : "Test case 4 failed. Expected " + expected_result4;

    // Test case 5: Only one match each for a and b, within range k
    String s5 = "abcdef";
    String a5 = "abc";
    String b5 = "def";
    int k5 = 5;
    List<Integer> expected_result5 = Arrays.asList(0);
    assert solution.beautifulIndices(s5, a5, b5, k5).equals(expected_result5) : "Test case 5 failed. Expected " + expected_result5;

    // Test case 6: Overlapping b close to the end of a with k = 0
    String s6 = "abcd";
    String a6 = "a";
    String b6 = "a";
    int k6 = 4;
    List<Integer> expected_result6 = Arrays.asList(0);
    assert solution.beautifulIndices(s6, a6, b6, k6).equals(expected_result6) : "Test case 6 failed. Expected " + expected_result6;

    // Test case 7: Non-overlapping multiple beautiful indices with exact k distance
    String s7 = "aaaaaa";
    String a7 = "aa";
    String b7 = "aa";
    int k7 = 2;
    List<Integer> expected_result7 = Arrays.asList(0, 1, 2, 3, 4);
    assert solution.beautifulIndices(s7, a7, b7, k7).equals(expected_result7) : "Test case 7 failed. Expected " + expected_result7;
}

    public static void main(String[] args) {
        Solution solution = new Solution();
        for (int i = 0; i < 3000000; i++) {
            runTests(solution); // Ensure your test cases are implemented inside runTests
        }
    }
}

    