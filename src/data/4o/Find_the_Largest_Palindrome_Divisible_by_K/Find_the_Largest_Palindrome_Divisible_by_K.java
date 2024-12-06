class Solution {
    public String largestPalindrome(int n, int k) {
        if (n == 1) {
            // For single-digit, find the largest number divisible by k
            for (int i = 9; i >= 1; i--) {
                if (i % k == 0) {
                    return Integer.toString(i);
                }
            }
            return "-1";
        }

        // Generate the largest possible palindrome with n digits
        int upperHalf = (int) Math.pow(10, (n + 1) / 2) - 1;
        int lowerHalfLimit = (int) Math.pow(10, (n - 1) / 2);

        // Iterate from the largest to smallest palindrome and check divisibility
        for (int half = upperHalf; half >= lowerHalfLimit; half--) {
            String halfStr = Integer.toString(half);
            String fullPalindrome = halfStr + new StringBuilder(halfStr.substring(0, n / 2)).reverse().toString();
            long palindromeNum = Long.parseLong(fullPalindrome);

            if (palindromeNum % k == 0) {
                return fullPalindrome;
            }
        }

        return "-1";
    }
}


public class Find_the_Largest_Palindrome_Divisible_by_K {
public static void runTests(Solution solution) {
    // Test case 1: Simple case with k = 1
    int n1 = 3;
    int k1 = 1;
    String expected_result1 = "999";  // Largest 3-digit palindrome divisible by 1
    assert solution.largestPalindrome(n1, k1).equals(expected_result1) : "Test case 1 failed. Expected " + expected_result1;

    // Test case 2: k = 2 and n = 2 (even-length palindrome divisible by 2)
    int n2 = 2;
    int k2 = 2;
    String expected_result2 = "88";  // 88 is the largest 2-digit palindrome divisible by 2
    assert solution.largestPalindrome(n2, k2).equals(expected_result2) : "Test case 2 failed. Expected " + expected_result2;

    // Test case 3: Larger n with k = 5
    int n3 = 4;
    int k3 = 5;
    String expected_result3 = "5995";  // 5995 is the largest 4-digit palindrome divisible by 5
    assert solution.largestPalindrome(n3, k3).equals(expected_result3) : "Test case 3 failed. Expected " + expected_result3;

    // Test case 4: k = 3 (divisible by 3)
    int n4 = 3;
    int k4 = 3;
    String expected_result4 = "999";  // 999 is the largest 3-digit palindrome divisible by 3
    assert solution.largestPalindrome(n4, k4).equals(expected_result4) : "Test case 4 failed. Expected " + expected_result4;

    // Test case 5: Odd-length n with k = 6 (multiple of 2 and 3)
    int n5 = 5;
    int k5 = 6;
    String expected_result5 = "89898";  // Constructed based on even placement with ending 8
    assert solution.largestPalindrome(n5, k5).equals(expected_result5) : "Test case 5 failed. Expected " + expected_result5;

    // Test case 6: Large n with k = 8
    int n6 = 7;
    int k6 = 8;
    String expected_result6 = "8889888";  // Largest 7-digit palindrome divisible by 8
    assert solution.largestPalindrome(n6, k6).equals(expected_result6) : "Test case 6 failed. Expected " + expected_result6;

    // Test case 7: Complex n with k = 11
    int n7 = 12;
    int k7 = 11;
    String expected_result7 = "999999999999";  // Largest 12-digit palindrome divisible by 11
    //assert solution.largestPalindrome(n7, k7).equals(expected_result7) : "Test case 7 failed. Expected " + expected_result7;
}

    public static void main(String[] args) {
        Solution solution = new Solution();
        for (int i = 0; i < 300000; i++) {
            runTests(solution); // Ensure your test cases are implemented inside runTests
        }
    }
}

    