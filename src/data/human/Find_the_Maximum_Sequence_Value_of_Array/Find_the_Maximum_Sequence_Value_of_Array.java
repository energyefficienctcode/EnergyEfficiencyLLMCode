import java.util.ArrayList;
import java.util.List;

class Solution {
    private static final int MAX = 128;

    public int maxValue(int[] nums, int k) {
        boolean[][] dp = new boolean[nums.length][MAX];
        
        boolean[][] isMet = new boolean[MAX][k + 1];
        List<int[]> valid = new ArrayList<>();
        valid.add(new int[]{0, 0});
        isMet[0][0] = true;

        for (int i = nums.length - 1; i >= 0; --i) {
            List<int[]> nextValid = new ArrayList<>();
            for (int[] tmp : valid) {
                nextValid.add(tmp);
                if (tmp[1] + 1 <= k && !isMet[tmp[0] | nums[i]][tmp[1] + 1]) {
                    isMet[tmp[0] | nums[i]][tmp[1] + 1] = true;
                    nextValid.add(new int[]{tmp[0] | nums[i], tmp[1] + 1});
                }
                if (tmp[1] + 1 == k) {
                    dp[i][tmp[0] | nums[i]] = true;
                }
                if (tmp[1] == k) {
                    dp[i][tmp[0]] = true;
                }
            }
            valid = nextValid;
        }

        int result = 0;
        
        boolean[] isLeftMet = new boolean[MAX];
        isMet = new boolean[MAX][k + 1];
        valid = new ArrayList<>();
        valid.add(new int[]{0, 0});
        isMet[0][0] = true;

        for (int i = 0; i < nums.length; ++i) {
            List<int[]> nextValid = new ArrayList<>();
            for (int[] tmp : valid) {
                nextValid.add(tmp);
                if (tmp[1] + 1 <= k && !isMet[tmp[0] | nums[i]][tmp[1] + 1]) {
                    isMet[tmp[0] | nums[i]][tmp[1] + 1] = true;
                    nextValid.add(new int[]{tmp[0] | nums[i], tmp[1] + 1});
                }
                if (tmp[1] + 1 == k && !isLeftMet[tmp[0] | nums[i]] && i + 1 < nums.length) {
                    int orResult = tmp[0] | nums[i];
                    isLeftMet[orResult] = true;
                    for (int j = 1; j < MAX; ++j) {
                        if (dp[i + 1][j]) {
                            result = Math.max(result, orResult ^ j);
                        }
                    }
                }
            }
            valid = nextValid;
        }
        
        return result;
    }
}

public class Find_the_Maximum_Sequence_Value_of_Array {
public static void runTests(Solution solution) {
    // Test case 1: Small array with exact 2*k size
    int[] nums1 = {2, 6, 7};
    int k1 = 1;
    int expected_result1 = 5;  // Sequence [1,2] OR 3,4 = 3 XOR 7 = 7
    assert solution.maxValue(nums1, k1) == expected_result1 : "Test case 1 failed. Expected " + expected_result1;

    // Test case 2: Array with increasing elements
    int[] nums2 = {4, 2, 5, 6, 7};
    int k2 = 2;
    int expected_result2 = 2;  // Sequence [2,4] XOR [8] = 6 XOR 8 = 12
    assert solution.maxValue(nums2, k2) == expected_result2 : "Test case 2 failed. Expected " + expected_result2;

    // Test case 3: Array with all identical elements
    int[] nums3 = {3, 3, 3, 3, 3};
    int k3 = 2;
    int expected_result3 = 0;  // All OR operations are equal; XOR will yield 0
    assert solution.maxValue(nums3, k3) == expected_result3 : "Test case 3 failed. Expected " + expected_result3;

    // Test case 4: Array with alternating bits
    int[] nums4 = {5, 10, 5, 10};
    int k4 = 2;
    int expected_result4 = 0;  // Sequence [5,10] XOR [5,10] = 15
    assert solution.maxValue(nums4, k4) == expected_result4 : "Test case 4 failed. Expected " + expected_result4;

    // Test case 5: Array with descending values
    int[] nums5 = {8, 4, 2, 1};
    int k5 = 1;
    int expected_result5 = 12;  // Sequence [8] XOR [4] = 12
    assert solution.maxValue(nums5, k5) == expected_result5 : "Test case 5 failed. Expected " + expected_result5;

    // Test case 6: Array with mixed values
    int[] nums6 = {6, 7, 5, 4, 3, 2};
    int k6 = 3;
    int expected_result6 = 0;  // Choose subarray [6, 7, 5] XOR [4, 3, 2] = 15
    assert solution.maxValue(nums6, k6) == expected_result6 : "Test case 6 failed. Expected " + expected_result6;

    // Test case 7: Large value of k in small array
    int[] nums7 = {1, 2};
    int k7 = 1;
    int expected_result7 = 3;  // Sequence [1] XOR [2] = 3
    assert solution.maxValue(nums7, k7) == expected_result7 : "Test case 7 failed. Expected " + expected_result7;
}

    public static void main(String[] args) {
        Solution solution = new Solution();
        for (int i = 0; i < 300000; i++) {
            runTests(solution); // Ensure your test cases are implemented inside runTests
        }
    }
}

    