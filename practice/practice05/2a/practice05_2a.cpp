#include <iostream>
#include <vector>
#include <numeric>
#include <string>

int main() {
    std::vector<int> numbers;
    int number;
    std::string input;
    
    std::cout << "Welcome to the Sum and Product Calculator!" << std::endl;
    std::cout << "You will enter integers one by one. Type 'a' or press Enter to stop." << std::endl;
    
    while (true) {
        std::cout << "Enter an integer (or type a non-number to stop): ";
        std::getline(std::cin, input);

        // Check if input is a valid number
        try {
            if (input.empty()) {
                throw std::invalid_argument("Input is empty.");
            }
            number = std::stoi(input);
            numbers.push_back(number);
        } catch (...) {
            // Exit loop if non-numeric input is encountered
            break;
        }
    }

    if (numbers.empty()) {
        std::cout << "No numbers were entered." << std::endl;
        return 0;
    }

    // Calculate the sum and product of the numbers
    int sum = std::accumulate(numbers.begin(), numbers.end(), 0);
    int product = std::accumulate(numbers.begin(), numbers.end(), 1, std::multiplies<int>());

    std::cout << "\nSum of elements: " << sum << std::endl;
    std::cout << "Product of elements: " << product << std::endl;

    // Ask if the user wants to enter new numbers
    std::cout << "\nWould you like to enter new numbers? (y/n): ";
    std::getline(std::cin, input);
    if (input == "y" || input == "Y") {
        main(); // Restart the program
    }

    return 0;
}
