class Solution {
    public String largestPalindrome(int n, int k) {
        int firstHalfDigits = (n + 1) / 2;
        long maxFirstHalf = pow10(firstHalfDigits) - 1;
        long minFirstHalf = firstHalfDigits == 1 ? 0 : pow10(firstHalfDigits - 1);
        
        for(long first = maxFirstHalf; first >= minFirstHalf; first--){
            String firstHalfStr = String.valueOf(first);
            String palindrome;
            
            if(n % 2 == 0){
                String reversed = new StringBuilder(firstHalfStr).reverse().toString();
                palindrome = firstHalfStr + reversed;
            }
            else{
                String reversed = new StringBuilder(firstHalfStr.substring(0, firstHalfDigits - 1)).reverse().toString();
                palindrome = firstHalfStr + reversed;
            }
            
            if(isDivisible(palindrome, k)){
                // Ensure no leading zeros for n > 1
                if(palindrome.length() == n && (n == 1 || palindrome.charAt(0) != '0')){
                    return palindrome;
                }
            }
        }
        
        return "-1";
    }
    
    private long pow10(int digits){
        long res = 1;
        for(int i = 0; i < digits; i++) {
            res *= 10;
        }
        return res;
    }
    
    private boolean isDivisible(String numStr, int k){
        long mod = 0;
        for(char c : numStr.toCharArray()){
            mod = (mod * 10 + (c - '0')) % k;
            if(mod == 0 && c == '0'){
                // Early exit if the number is zero
                return true;
            }
        }
        return mod == 0;
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
    assert solution.largestPalindrome(n7, k7).equals(expected_result7) : "Test case 7 failed. Expected " + expected_result7;
}

    public static void main(String[] args) {
        Solution solution = new Solution();
        for (int i = 0; i < 30000000; i++) {
            runTests(solution); // Ensure your test cases are implemented inside runTests
        }
    }
}

    