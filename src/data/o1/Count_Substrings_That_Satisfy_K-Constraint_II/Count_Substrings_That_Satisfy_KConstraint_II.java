class Solution {
    public long[] countKConstraintSubstrings(String s, int k, int[][] queries) {
        int q = queries.length;
        long[] answer = new long[q];
        
        // Precompute prefix sums of 0's and 1's
        int n = s.length();
        int[] prefixZeros = new int[n + 1];
        int[] prefixOnes = new int[n + 1];
        
        for(int i = 0; i < n; i++) {
            prefixZeros[i + 1] = prefixZeros[i] + (s.charAt(i) == '0' ? 1 : 0);
            prefixOnes[i + 1] = prefixOnes[i] + (s.charAt(i) == '1' ? 1 : 0);
        }
        
        for(int idx = 0; idx < q; idx++) {
            int li = queries[idx][0];
            int ri = queries[idx][1];
            answer[idx] = countSubstrings(s, li, ri, k, prefixZeros, prefixOnes);
        }
        
        return answer;
    }
    
    private long countSubstrings(String s, int li, int ri, int k, int[] prefixZeros, int[] prefixOnes) {
        // Total number of substrings in [li, ri]
        int N = ri - li +1;
        long totalSubstrings = ((long)N * (N +1)) /2;
        
        // Count of substrings with at most k 0's
        long countAtMostK0 = atMost(s, li, ri, k, '0', prefixZeros);
        
        // Count of substrings with at most k 1's
        long countAtMostK1 = atMost(s, li, ri, k, '1', prefixOnes);
        
        // Overlap: substrings with at most k 0's AND at most k 1's
        // Which implies substrings with length <=k +k =2k
        long overlap = 0;
        int L = Math.min(2 * k, N);
        overlap = ((long)L * (L +1)) /2;
        
        return countAtMostK0 + countAtMostK1 - overlap;
    }
    
    private long atMost(String s, int li, int ri, int k, char targetChar, int[] prefixCount) {
        int count =0;
        long res =0;
        int left = li;
        
        for(int right = li; right <= ri; right++) {
            if(s.charAt(right) == targetChar) {
                count++;
            }
            
            while(count >k) {
                if(s.charAt(left) == targetChar) {
                    count--;
                }
                left++;
            }
            
            res += (right - left +1);
        }
        
        return res;
    }
}


public class Count_Substrings_That_Satisfy_KConstraint_II {
    public static void runTests(Solution solution) {
        // Test case 1: Single character satisfying any constraint
        String s1 = "0";
        int k1 = 1;
        int[][] queries1 = {{0, 0}};
        long[] expected_result1 = {1};  // Only one substring: "0", which satisfies the constraint
        assert java.util.Arrays.equals(solution.countKConstraintSubstrings(s1, k1, queries1), expected_result1) : "Test case 1 failed. Expected " + java.util.Arrays.toString(expected_result1);

        // Test case 2: All zeros with multiple queries
        String s2 = "0000";
        int k2 = 2;
        int[][] queries2 = {{0, 1}, {1, 3}};
        long[] expected_result2 = {3, 6};  // Substrings "00", "0" (3 substrings for [0,1]) and all 6 substrings for [1,3]
        assert java.util.Arrays.equals(solution.countKConstraintSubstrings(s2, k2, queries2), expected_result2) : "Test case 2 failed. Expected " + java.util.Arrays.toString(expected_result2);

        // Test case 3: Mixed binary string with k = 1
        String s3 = "0001111";
        int k3 = 2;
        int[][] queries3 = {{0, 6}};
        long[] expected_result3 = {26};  // Substrings with either one 0 or one 1 within specified ranges
        assert java.util.Arrays.equals(solution.countKConstraintSubstrings(s3, k3, queries3), expected_result3) : "Test case 3 failed. Expected " + java.util.Arrays.toString(expected_result3);

        // Test case 4: Substring range that includes all characters
        String s4 = "101";
        int k4 = 2;
        int[][] queries4 = {{0, 2}};
        long[] expected_result4 = {6};  // All substrings satisfy the k-constraint as k = 2
        assert java.util.Arrays.equals(solution.countKConstraintSubstrings(s4, k4, queries4), expected_result4) : "Test case 4 failed. Expected " + java.util.Arrays.toString(expected_result4);

        // Test case 5: Alternating binary string with larger k
        String s5 = "010101";
        int k5 = 3;
        int[][] queries5 = {{0, 3}, {2, 5}};
        long[] expected_result5 = {10, 10};  // All substrings within these ranges satisfy k-constraint since k = 3
        assert java.util.Arrays.equals(solution.countKConstraintSubstrings(s5, k5, queries5), expected_result5) : "Test case 5 failed. Expected " + java.util.Arrays.toString(expected_result5);

        // Test case 6: Large binary string with a single 1
        String s6 = "010101";
        int k6 = 1;
        int[][] queries6 = {{0, 5}, {1, 4}, {2, 3}};
        long[] expected_result6 = {15, 9, 3};  // Substrings with at most 1 "1" and varying numbers of "0"
        assert java.util.Arrays.equals(solution.countKConstraintSubstrings(s6, k6, queries6), expected_result6) : "Test case 6 failed. Expected " + java.util.Arrays.toString(expected_result6);

        // Test case 7: k less than the number of either 0s or 1s
        String s7 = "111000";
        int k7 = 2;
        int[][] queries7 = {{0, 2}, {3, 5}};
        long[] expected_result7 = {6, 6};  // Only individual "1"s or "0"s and one pair satisfy the k-constraint
        assert java.util.Arrays.equals(solution.countKConstraintSubstrings(s7, k7, queries7), expected_result7) : "Test case 7 failed. Expected " + java.util.Arrays.toString(expected_result7);
    }


    public static void main(String[] args) {
        Solution solution = new Solution();
        for (int i = 0; i < 30000000; i++) {
            runTests(solution); // Ensure your test cases are implemented inside runTests
        }
    }
}

    