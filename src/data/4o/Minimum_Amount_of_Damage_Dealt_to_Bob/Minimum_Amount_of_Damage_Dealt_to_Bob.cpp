#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    long long minDamage(int power, vector<int>& damage, vector<int>& health) {
        using Enemy = pair<int, int>; // {damage, health}
        priority_queue<Enemy> pq;
        
        int n = damage.size();
        long long totalDamage = 0;

        // Push all enemies into the priority queue with damage as the key for prioritization
        for (int i = 0; i < n; ++i) {
            pq.push({damage[i], health[i]});
        }

        while (!pq.empty()) {
            auto [currDamage, currHealth] = pq.top();
            pq.pop();

            // Calculate the number of seconds needed to defeat this enemy
            int secondsToKill = (currHealth + power - 1) / power;

            // Add the damage this enemy will deal over that time
            totalDamage += (long long)currDamage * secondsToKill;

            // Deal with the next most damaging enemy in the queue
        }

        return totalDamage;
    }
};

//  Test cases for the C++ solution
#include <cassert>

// Test cases for the C++ solution
void testSolution(Solution& solution) {
    // Test case 1: One enemy with minimal damage
    int power = 10;
    std::vector<int> damage = {5};
    std::vector<int> health = {10};
    int expected_result = 5;  // Only one enemy, Bob takes 5 damage per second for 1 second
    assert(solution.minDamage(power, damage, health) == expected_result && "Test case 1 failed.");

    // Test case 2: Multiple enemies with the same health and damage
    power = 4;
    damage = {1, 2, 3, 4};
    health = {4, 5, 6, 8};
    expected_result = 39;  // All enemies have equal priority; Bob takes 9 seconds of damage with 3 damage per second
    assert(solution.minDamage(power, damage, health) == expected_result && "Test case 2 failed.");

    // Test case 3: Varying health and damage, higher power
    power = 1;
    damage = {1, 1, 1, 1};
    health = {1, 2, 3, 4};
    expected_result = 20;  // Optimal order: kill 3rd enemy first, then 1st, then 2nd
    assert(solution.minDamage(power, damage, health) == expected_result && "Test case 3 failed.");

    // Test case 4: Power equal to the maximum health, minimal damage
    power = 8;
    damage = {40};
    health = {59};
    expected_result = 320;  // Bob takes damage for 8 seconds from the only enemy
    assert(solution.minDamage(power, damage, health) == expected_result && "Test case 4 failed.");

    // Test case 5: High damage but low power, requiring strategic elimination
    power = 2;
    damage = {10, 1, 5};
    health = {6, 10, 4};
    expected_result = 65;  // Order: kill 3rd enemy first, then 1st, then 2nd
    assert(solution.minDamage(power, damage, health) == expected_result && "Test case 5 failed.");

    // Test case 6: Power greater than all health, instant kills
    power = 50;
    damage = {3, 4, 2};
    health = {5, 8, 6};
    expected_result = 16;  // All enemies are killed immediately; minimal damage taken
    assert(solution.minDamage(power, damage, health) == expected_result && "Test case 6 failed.");

    // Test case 7: Different damage, minimal power, and high health
    power = 1;
    damage = {3, 8, 2};
    health = {5, 4, 7};
    expected_result = 91;  // Complex order needed for minimum damage; each enemy has low power effect
    assert(solution.minDamage(power, damage, health) == expected_result && "Test case 7 failed.");
}

int main() {
    Solution solution;
    for (int i = 0; i < 2621440; ++i) {
        testSolution(solution);  
    }
    return 0;
}
