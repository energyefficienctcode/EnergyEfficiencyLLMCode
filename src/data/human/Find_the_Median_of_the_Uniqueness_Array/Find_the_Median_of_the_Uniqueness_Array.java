import java.util.HashMap;
import java.util.Map;

class Solution {
    public int medianOfUniquenessArray(int[] A) {
        int n = A.length, left = 1, right = n;
        long total = (long) n * (n + 1) / 2;
        while (left < right) {
            int k = (left + right) / 2;
            if (atmost(A, k) * 2 >= total) {
                right = k;
            } else {
                left = k + 1;
            }
        }
        return left;
    }

    private long atmost(int[] A, int k) {
        long res = 0;
        Map<Integer, Integer> count = new HashMap<>();
        int i = 0;
        for (int j = 0; j < A.length; j++) {
            count.put(A[j], count.getOrDefault(A[j], 0) + 1);
            while (count.size() > k) {
                count.put(A[i], count.get(A[i]) - 1);
                if (count.get(A[i]) == 0) {
                    count.remove(A[i]);
                }
                i++;
            }
            res += j - i + 1;
        }
        return res;
    }
}

public class Find_the_Median_of_the_Uniqueness_Array {
public static void runTests(Solution solution) {
    // Test case 1: Small array with unique elements
    int[] nums1 = {1, 2, 3};
    int expected_result1 = 1;  // Subarrays have distinct counts, median is 1
    assert solution.medianOfUniquenessArray(nums1) == expected_result1 : "Test case 1 failed. Expected " + expected_result1;

    // Test case 2: Array with repeated elements
    int[] nums2 = {1, 1, 2};
    int expected_result2 = 1;  // Subarrays have distinct counts, median is 1
    assert solution.medianOfUniquenessArray(nums2) == expected_result2 : "Test case 2 failed. Expected " + expected_result2;

    // Test case 3: All identical elements
    int[] nums3 = {4, 4, 4, 4};
    int expected_result3 = 1;  // All subarrays have 1 unique element
    assert solution.medianOfUniquenessArray(nums3) == expected_result3 : "Test case 3 failed. Expected " + expected_result3;

    // Test case 4: Array with two distinct elements
    int[] nums4 = {5, 6, 5, 6};
    int expected_result4 = 2;  // Subarrays have distinct counts, median is 2
    assert solution.medianOfUniquenessArray(nums4) == expected_result4 : "Test case 4 failed. Expected " + expected_result4;

    // Test case 5: Increasing sequence of elements
    int[] nums5 = {1, 2, 3, 4};
    int expected_result5 = 2;  // Subarrays have distinct counts, median is 2
    assert solution.medianOfUniquenessArray(nums5) == expected_result5 : "Test case 5 failed. Expected " + expected_result5;

    // Test case 6: Mixed values with multiple subarrays having the same uniqueness count
    int[] nums6 = {2, 1, 2, 3};
    int expected_result6 = 2;  // Subarrays have distinct counts, median is 2
    assert solution.medianOfUniquenessArray(nums6) == expected_result6 : "Test case 6 failed. Expected " + expected_result6;

    // Test case 7: Array with no repeats
    int[] nums7 = {3, 4, 3, 4, 5};
    int expected_result7 = 2;  // Subarrays have distinct counts, median is 2
    assert solution.medianOfUniquenessArray(nums7) == expected_result7 : "Test case 7 failed. Expected " + expected_result7;
}

    public static void main(String[] args) {
        Solution solution = new Solution();
        for (int i = 0; i < 10000000; i++) {
            runTests(solution); // Ensure your test cases are implemented inside runTests
        }
    }
}

    