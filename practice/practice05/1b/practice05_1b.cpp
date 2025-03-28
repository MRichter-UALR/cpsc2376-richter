#include <iostream>
#include <vector>
#include <string>
#include <sstream>

int main() {
    while (true) { // Outer loop to allow restarting the process
        std::vector<int> numbers;  // Vector to store valid integers
        std::string input;         // String to hold user input
        int number;                // Temporary variable to store each valid number

        // Clear instructions and example inputs
        std::cout << "Welcome to the Reverse Order Program!" << std::endl;
        std::cout << "This program will collect integers from you, store them in a list, "
                     "and print them in reverse order using iterators." << std::endl;
        std::cout << "To enter numbers, simply type them with spaces between them (e.g., '10 20 30'). "
                     "To stop, enter any non-number (e.g., 'a') or press Enter without typing anything." << std::endl;
        std::cout << "Example: Enter '5 10 15 20' to enter numbers or 'a' to stop." << std::endl;

        while (true) {  // Inner loop for entering numbers
            std::cout << "Enter integers (enter a non-number to stop): ";
            std::getline(std::cin, input);  // Read the entire line of input

            // If input is empty (no input was given, just Enter pressed), ask to continue or stop
            if (input.empty()) {
                char choice;
                std::cout << "You have not entered anything. Do you want to continue? (y/n): ";
                std::cin >> choice;
                std::cin.ignore();  // Ignore remaining newline character
                if (choice == 'n' || choice == 'N') {
                    break;  // Exit the loop if user chooses 'n'
                }
                continue;  // Otherwise, prompt again
            }

            std::stringstream ss(input);  // Convert the input string to a stringstream
            bool valid_input = false;     // Flag to check if we can successfully extract numbers

            // Try to convert each part of the string to an integer
            while (ss >> number) {
                numbers.push_back(number); // If conversion is successful, add the number to the vector
                valid_input = true;         // At least one valid number was found
            }

            // If ss failed (it means we encountered a non-numeric input)
            if (ss.fail()) {
                // Ask user if they want to continue or stop after entering a non-number
                char choice;
                std::cout << "Non-number entered. Do you want to stop? (y/n): ";
                std::cin >> choice;
                std::cin.ignore();  // Ignore remaining newline character
                if (choice == 'y' || choice == 'Y') {
                    break;  // Exit the loop if user chooses 'y'
                }
                // Otherwise, continue prompting for input
                continue;
            }
        }

        // Output the numbers in reverse order
        if (!numbers.empty()) {
            std::cout << "The numbers in reverse order are: ";
            for (auto it = numbers.rbegin(); it != numbers.rend(); ++it) {
                std::cout << *it << " ";  // Print each number in reverse order
            }
            std::cout << std::endl;
        } else {
            std::cout << "No valid numbers were entered." << std::endl; // If no valid numbers were entered
        }

        // Ask the user if they want to start over or exit
        char restart_choice;
        std::cout << "Do you want to enter new numbers? (y/n): ";
        std::cin >> restart_choice;
        std::cin.ignore();  // Ignore remaining newline character
        if (restart_choice == 'n' || restart_choice == 'N') {
            break;  // Exit the outer loop if user chooses 'n'
        }
    }

    return 0;
}
