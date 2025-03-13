#include "../../practice03.cpp"  // This goes up two directories to reach practice03.cpp
#include <cassert>
#include <iostream>
#include <vector>

// Test sumRange function
void testSumRange() {
    assert(MathUtils::sumRange(1, 5) == 10);  // 1 + 2 + 3 + 4 = 10
    assert(MathUtils::sumRange(0, 0) == 0);    // Edge case: start == end
    assert(MathUtils::sumRange(-5, 0) == -15); // Sum: -5 + -4 + -3 + -2 + -1 = -15
    std::cout << "sumRange tests passed!" << std::endl;
}

// Test containsNegative function
void testContainsNegative() {
    std::vector<int> values1 = { 3, -1, 5, 7 };
    std::vector<int> values2 = { 3, 1, 5, 7 };
    std::vector<int> values3 = {};

    assert(MathUtils::containsNegative(values1) == true);  // Contains negative number
    assert(MathUtils::containsNegative(values2) == false); // All positive numbers
    assert(MathUtils::containsNegative(values3) == false); // Empty vector

    std::cout << "containsNegative tests passed!" << std::endl;
}

// Test findMax function
void testFindMax() {
    std::vector<int> values1 = { 3, 5, 1, 7 }; // Should return 7 as the max value
    std::vector<int> values2 = { 3, 3, 3, 3 }; // All numbers equal
    std::vector<int> values3 = {};           // Empty vector

    assert(MathUtils::findMax(values1) == 7);  // This should pass if the code works
    assert(MathUtils::findMax(values2) == 3);  // All values equal, so 3 is returned
    assert(MathUtils::findMax(values3) == 0);  // Empty vector, returns 0

    std::cout << "findMax tests passed!" << std::endl;
}

int main() {
    testSumRange();
    testContainsNegative();
    testFindMax();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}
