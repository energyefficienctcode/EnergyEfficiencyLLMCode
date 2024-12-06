class Solution {
    public long maximumValueSum(int[] nums, int k, int[][] edges) {
        int n = nums.length;
        long originalSum = 0;
        long xorSum = 0;

        for (int num : nums) {
            originalSum += num;
            xorSum += (num ^ k);
        }

        return Math.max(originalSum, xorSum);
    }
}

public class Find_the_Maximum_Sum_of_Node_Values {
public static void runTests(Solution solution) {
    // Test case 1: Simple tree with one operation that maximizes the sum
    int[] nums1 = {1, 2, 1};
    int k1 = 3;
    int[][] edges1 = {{0, 1}, {0, 2}};
    int expected_result1 = 6;
    assert solution.maximumValueSum(nums1, k1, edges1) == expected_result1 : "Test case 1 failed. Expected " + expected_result1;

    // Test case 2: Tree with all nodes benefitting from XOR operation
    int[] nums2 = {2, 3};
    int k2 = 7;
    int[][] edges2 = {{0, 1}};
    int expected_result2 = 9;
    assert solution.maximumValueSum(nums2, k2, edges2) == expected_result2 : "Test case 2 failed. Expected " + expected_result2;

    // Test case 3: Tree with no XOR operation increasing the sum
    int[] nums3 = {7, 8, 9};
    int k3 = 1;
    int[][] edges3 = {{0, 1}, {1, 2}};
    int expected_result3 = 24;
    assert solution.maximumValueSum(nums3, k3, edges3) == expected_result3 : "Test case 3 failed. Expected " + expected_result3;

    // Test case 4: Only one node with a large k that benefits from XOR
    int[] nums4 = {7, 7, 7, 7, 7, 7};
    int k4 = 3;
    int[][] edges4 = {{0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}};
    int expected_result4 = 42;
    assert solution.maximumValueSum(nums4, k4, edges4) == expected_result4 : "Test case 4 failed. Expected " + expected_result4;

    // Test case 5: Tree with a mix of nodes benefiting and not benefiting from XOR
    int[] nums5 = {5, 10, 15, 20};
    int k5 = 7;
    int[][] edges5 = {{0, 1}, {0, 2}, {1, 3}};
    int expected_result5 = 52;
    assert solution.maximumValueSum(nums5, k5, edges5) == expected_result5 : "Test case 5 failed. Expected " + expected_result5;

    // Test case 6: Tree where XOR decreases the sum and should be avoided
    int[] nums6 = {10, 20, 30};
    int k6 = 25;
    int[][] edges6 = {{0, 1}, {1, 2}};
    int expected_result6 = 62;
    assert solution.maximumValueSum(nums6, k6, edges6) == expected_result6 : "Test case 6 failed. Expected " + expected_result6;

    // Test case 7: Multiple nodes with odd XOR benefits
    int[] nums7 = {3, 6, 9, 12, 15};
    int k7 = 5;
    int[][] edges7 = {{0, 1}, {1, 2}, {2, 3}, {3, 4}};
    int expected_result7 = 51;
    assert solution.maximumValueSum(nums7, k7, edges7) == expected_result7 : "Test case 7 failed. Expected " + expected_result7;
}


    public static void main(String[] args) {
        Solution solution = new Solution();
        for (int i = 0; i < 300000000; i++) {
            runTests(solution); // Ensure your test cases are implemented inside runTests
        }
    }
}

    