import java.util.Arrays;

class Solution {
    public long minimumCost(int m, int n, int[] h, int[] v) {
        Arrays.sort(h);
        Arrays.sort(v);
        long sumH = 0, sumV = 0, res = 0;
        for (int x : h) sumH += x;
        for (int x : v) sumV += x;

        int i = h.length - 1, j = v.length - 1;
        while (i >= 0 && j >= 0) {
            if (h[i] > v[j]) {
                res += h[i] + sumV;
                sumH -= h[i--];
            } else {
                res += v[j] + sumH;
                sumV -= v[j--];
            }
        }
        return res + sumH + sumV;
    }
}

public class Minimum_Cost_for_Cutting_Cake_II {
public static void runTests(Solution solution) {
    // Test case 1: Simple case with small costs
    int m1 = 3;
    int n1 = 2;
    int[] horizontalCut1 = {1, 3};
    int[] verticalCut1 = {5};
    int expected_result1 = 13;
    assert solution.minimumCost(m1, n1, horizontalCut1, verticalCut1) == expected_result1 : "Test case 1 failed. Expected " + expected_result1;

    // Test case 2: All horizontal cuts more expensive than vertical cuts
    int m2 = 2;
    int n2 = 2;
    int[] horizontalCut2 = {7};
    int[] verticalCut2 = {4};
    int expected_result2 = 15;
    assert solution.minimumCost(m2, n2, horizontalCut2, verticalCut2) == expected_result2 : "Test case 2 failed. Expected " + expected_result2;

    // Test case 3: Equal costs for all cuts
    int m3 = 2;
    int n3 = 2;
    int[] horizontalCut3 = {3};
    int[] verticalCut3 = {3};
    int expected_result3 = 9;
    assert solution.minimumCost(m3, n3, horizontalCut3, verticalCut3) == expected_result3 : "Test case 3 failed. Expected " + expected_result3;

    // Test case 4: Large cake with increasing costs
    int m4 = 5;
    int n4 = 4;
    int[] horizontalCut4 = {1, 2, 3, 4};
    int[] verticalCut4 = {2, 4, 6};
    int expected_result4 = 49;
    assert solution.minimumCost(m4, n4, horizontalCut4, verticalCut4) == expected_result4 : "Test case 4 failed. Expected " + expected_result4;

    // Test case 5: Only one horizontal or vertical cut needed
    int m5 = 2;
    int n5 = 4;
    int[] horizontalCut5 = {10};
    int[] verticalCut5 = {2, 3, 5};
    int expected_result5 = 30;
    assert solution.minimumCost(m5, n5, horizontalCut5, verticalCut5) == expected_result5 : "Test case 5 failed. Expected " + expected_result5;

    // Test case 6: Large values with mixed costs
    int m6 = 3;
    int n6 = 3;
    int[] horizontalCut6 = {8, 3};
    int[] verticalCut6 = {6, 7};
    int expected_result6 = 43;
    assert solution.minimumCost(m6, n6, horizontalCut6, verticalCut6) == expected_result6 : "Test case 6 failed. Expected " + expected_result6;

    // Test case 7: Single row or column (only vertical or horizontal cuts)
    int m7 = 1;
    int n7 = 5;
    int[] horizontalCut7 = {};
    int[] verticalCut7 = {4, 2, 1, 3};
    int expected_result7 = 10;
    assert solution.minimumCost(m7, n7, horizontalCut7, verticalCut7) == expected_result7 : "Test case 7 failed. Expected " + expected_result7;
}


    public static void main(String[] args) {
        Solution solution = new Solution();
        for (int i = 0; i < 30000000; i++) {
            runTests(solution); // Ensure your test cases are implemented inside runTests
        }
    }
}

    