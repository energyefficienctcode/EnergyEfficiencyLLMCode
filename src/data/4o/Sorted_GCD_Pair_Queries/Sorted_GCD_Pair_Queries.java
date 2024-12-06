import java.util.*;

class Solution {
    public int[] gcdValues(int[] nums, long[] queries) {
        List<Integer> gcdPairs = new ArrayList<>();
        int n = nums.length;

        // Calculate GCD for all possible pairs and store them in gcdPairs
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                gcdPairs.add(gcd(nums[i], nums[j]));
            }
        }

        // Sort gcdPairs in ascending order
        Collections.sort(gcdPairs);

        // Answer each query
        int[] answer = new int[queries.length];
        for (int i = 0; i < queries.length; i++) {
            if (queries[i] < gcdPairs.size()) {
                answer[i] = gcdPairs.get((int) queries[i]);
            } else {
                answer[i] = -1; // If the query is out of bounds
            }
        }

        return answer;
    }

    // Helper function to calculate GCD
    private int gcd(int a, int b) {
        if (b == 0) return a;
        return gcd(b, a % b);
    }
}


public class Sorted_GCD_Pair_Queries {
    public static void runTests(Solution solution) {
        // Test case 1
        int[] nums = {2, 3};
        long[] queries = {0};
        int[] expectedResult = {1};  // Only one pair, GCD(2, 3) = 1
        assert java.util.Arrays.equals(solution.gcdValues(nums, queries), expectedResult)
                : "Test case 1 failed. Expected " + java.util.Arrays.toString(expectedResult);

        // Test case 2
        nums = new int[]{2, 3, 4};
        queries = new long[]{0, 2, 2};
        expectedResult = new int[]{1, 2, 2};  // GCD pairs sorted: [2, 2, 1]
        assert java.util.Arrays.equals(solution.gcdValues(nums, queries), expectedResult)
                : "Test case 2 failed. Expected " + java.util.Arrays.toString(expectedResult);

        // Test case 3
        nums = new int[]{4, 8, 12};
        queries = new long[]{0, 1, 2};
        expectedResult = new int[]{4, 4, 4};  // GCD pairs sorted: [4, 4, 4]
        assert java.util.Arrays.equals(solution.gcdValues(nums, queries), expectedResult)
                : "Test case 3 failed. Expected " + java.util.Arrays.toString(expectedResult);

        // Test case 4
        nums = new int[]{2, 3, 5, 7};
        queries = new long[]{0, 1, 2, 3, 4, 5};
        expectedResult = new int[]{1, 1, 1, 1, 1, 1};  // GCDs are all 1 for prime pairs
        assert java.util.Arrays.equals(solution.gcdValues(nums, queries), expectedResult)
                : "Test case 4 failed. Expected " + java.util.Arrays.toString(expectedResult);

        // Test case 5
        nums = new int[]{4, 4, 2, 1};
        queries = new long[]{5, 3, 1, 0};
        expectedResult = new int[]{4, 2, 1, 1};  // GCD pairs sorted: [4, 4, 2, 2, 2, 1]
        assert java.util.Arrays.equals(solution.gcdValues(nums, queries), expectedResult)
                : "Test case 5 failed. Expected " + java.util.Arrays.toString(expectedResult);

        // Test case 6
        nums = new int[]{100000, 100000};
        queries = new long[]{0};
        expectedResult = new int[]{100000};  // Only one GCD of the pair: [100000]
        assert java.util.Arrays.equals(solution.gcdValues(nums, queries), expectedResult)
                : "Test case 6 failed. Expected " + java.util.Arrays.toString(expectedResult);
    }
    public static void main(String[] args) {
        Solution solution = new Solution();
        for (int i = 0; i < 20000; i++) {
            runTests(solution); // Ensure your test cases are implemented inside runTests
        }
    }
}

    