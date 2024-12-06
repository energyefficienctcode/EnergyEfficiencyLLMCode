class Solution {
    public boolean isNumber(String s) {
        s = s.trim();

        boolean pointSeen = false;
        boolean eSeen = false;
        boolean numberSeen = false;
        boolean numberAfterE = true;
        for (int i = 0; i < s.length(); i++) {
            if ('0' <= s.charAt(i) && s.charAt(i) <= '9') {
                numberSeen = true;
                numberAfterE = true;
            } else if (s.charAt(i) == '.') {
                if (eSeen || pointSeen) {
                    return false;
                }
                pointSeen = true;
            } else if (s.charAt(i) == 'e') {
                if (eSeen || !numberSeen) {
                    return false;
                }
                numberAfterE = false;
                eSeen = true;
            } else if (s.charAt(i) == '-' || s.charAt(i) == '+') {
                if (i != 0 && s.charAt(i - 1) != 'e') {
                    return false;
                }
            } else {
                return false;
            }
        }

        return numberSeen && numberAfterE;
    }
}

public class Valid_Number {
public static void runTests(Solution solution) {
    // Test case 1: Simple valid integer
    String s1 = "2";
    boolean expected_result1 = true;
    assert solution.isNumber(s1) == expected_result1 : "Test case 1 failed. Expected " + expected_result1;

    // Test case 2: Valid negative decimal
    String s2 = "-0.1";
    boolean expected_result2 = true;
    assert solution.isNumber(s2) == expected_result2 : "Test case 2 failed. Expected " + expected_result2;

    // Test case 3: Valid integer with exponent
    String s3 = "-90E3";
    boolean expected_result3 = false;
    assert solution.isNumber(s3) == expected_result3 : "Test case 3 failed. Expected " + expected_result3;

    // Test case 4: Invalid string with letters
    String s4 = "abc";
    boolean expected_result4 = false;
    assert solution.isNumber(s4) == expected_result4 : "Test case 4 failed. Expected " + expected_result4;

    // Test case 5: Invalid number with misplaced decimal
    String s5 = "99e2.5";
    boolean expected_result5 = false;
    assert solution.isNumber(s5) == expected_result5 : "Test case 5 failed. Expected " + expected_result5;

    // Test case 6: Valid number with positive sign
    String s6 = "+6e-1";
    boolean expected_result6 = true;
    assert solution.isNumber(s6) == expected_result6 : "Test case 6 failed. Expected " + expected_result6;

    // Test case 7: Invalid string with only exponent
    String s7 = "e3";
    boolean expected_result7 = false;
    assert solution.isNumber(s7) == expected_result7 : "Test case 7 failed. Expected " + expected_result7;

    // Test case 8: Valid decimal without digits after dot
    String s8 = "4.";
    boolean expected_result8 = true;
    assert solution.isNumber(s8) == expected_result8 : "Test case 8 failed. Expected " + expected_result8;

    // Test case 9: Invalid number with double signs
    String s9 = "-+3";
    boolean expected_result9 = false;
    assert solution.isNumber(s9) == expected_result9 : "Test case 9 failed. Expected " + expected_result9;

    // Test case 10: Valid negative number with exponent and decimal
    String s10 = "-123.456e789";
    boolean expected_result10 = true;
    assert solution.isNumber(s10) == expected_result10 : "Test case 10 failed. Expected " + expected_result10;
}


    public static void main(String[] args) {
        Solution solution = new Solution();
        for (int i = 0; i < 100000000; i++) {
            runTests(solution); // Ensure your test cases are implemented inside runTests
        }
    }
}

    