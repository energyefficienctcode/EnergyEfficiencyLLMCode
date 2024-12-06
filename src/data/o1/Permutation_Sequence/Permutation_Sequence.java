import java.util.ArrayList;
import java.util.List;

class Solution {
    public String getPermutation(int n, int k) {
        // Initialize factorial lookup
        int[] factorial = new int[n + 1];
        factorial[0] = 1;
        for(int i = 1; i <= n; i++) {
            factorial[i] = factorial[i - 1] * i;
        }
        
        // Adjust k to be zero-based
        k--;
        
        // Initialize a list of numbers to get indices
        List<Integer> numbers = new ArrayList<>();
        for(int i = 1; i <= n; i++) {
            numbers.add(i);
        }
        
        StringBuilder sb = new StringBuilder();
        
        for(int i = n; i >= 1; i--) {
            int f = factorial[i - 1];
            int index = k / f;
            sb.append(numbers.get(index));
            numbers.remove(index);
            k %= f;
        }
        
        return sb.toString();
    }
}

public class Permutation_Sequence {
public static void runTests(Solution solution) {
    // Test case 1: Smallest input where n = 1
    int n1 = 1;
    int k1 = 1;
    String expected_result1 = "1";
    assert solution.getPermutation(n1, k1).equals(expected_result1) : "Test case 1 failed. Expected " + expected_result1;

    // Test case 2: n = 3, k = 3 (Third permutation of [1, 2, 3])
    int n2 = 3;
    int k2 = 3;
    String expected_result2 = "213";
    assert solution.getPermutation(n2, k2).equals(expected_result2) : "Test case 2 failed. Expected " + expected_result2;

    // Test case 3: n = 4, k = 9 (Ninth permutation of [1, 2, 3, 4])
    int n3 = 4;
    int k3 = 9;
    String expected_result3 = "2314";
    assert solution.getPermutation(n3, k3).equals(expected_result3) : "Test case 3 failed. Expected " + expected_result3;

    // Test case 4: n = 4, k = 1 (First permutation of [1, 2, 3, 4])
    int n4 = 4;
    int k4 = 1;
    String expected_result4 = "1234";
    assert solution.getPermutation(n4, k4).equals(expected_result4) : "Test case 4 failed. Expected " + expected_result4;

    // Test case 5: n = 4, k = 24 (Last permutation of [1, 2, 3, 4])
    int n5 = 4;
    int k5 = 24;
    String expected_result5 = "4321";
    assert solution.getPermutation(n5, k5).equals(expected_result5) : "Test case 5 failed. Expected " + expected_result5;

    // Test case 6: n = 5, k = 16 (Middle permutation of [1, 2, 3, 4, 5])
    int n6 = 5;
    int k6 = 16;
    String expected_result6 = "14352";
    assert solution.getPermutation(n6, k6).equals(expected_result6) : "Test case 6 failed. Expected " + expected_result6;

    // Test case 7: Large n = 6 to test algorithm's efficiency
    int n7 = 6;
    int k7 = 400;
    String expected_result7 = "425361";
    assert solution.getPermutation(n7, k7).equals(expected_result7) : "Test case 7 failed. Expected " + expected_result7;
}

    public static void main(String[] args) {
        Solution solution = new Solution();
        for (int i = 0; i < 10000000; i++) {
            runTests(solution); // Ensure your test cases are implemented inside runTests
        }
    }
}

    