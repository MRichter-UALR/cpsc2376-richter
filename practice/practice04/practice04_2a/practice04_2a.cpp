#include <iostream>
#include <limits>
#include <ctype.h>  // For checking valid characters

// Function template to perform basic arithmetic operations
template <typename T>
T calculate(T num1, T num2, char operation) {
    switch (operation) {
    case '+': return num1 + num2;
    case '-': return num1 - num2;
    case '*': return num1 * num2;
    case '/':
        if (num2 != 0) {
            return num1 / num2;
        }
        else {
            std::cout << "Error: Division by zero.\n";
            return 0;
        }
    default:
        std::cout << "Invalid operation.\n";
        return 0;
    }
}

// Function to get a valid number from the user
template <typename T>
T getValidNumber() {
    T num;
    while (true) {
        std::cout << "Enter a number: ";
        std::cin >> num;

        // If user enters invalid data (not a number), clear the input and ask again
        if (std::cin.fail()) {
            std::cin.clear();  // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Ignore incorrect input
            std::cout << "Invalid input. Please enter a valid number.\n";
        }
        else {
            return num;  // If valid, return the number
        }
    }
}

// Function to get a valid operation from the user
char getValidOperation() {
    char operation;
    while (true) {
        std::cout << "Enter operation (+, -, *, /): ";
        std::cin >> operation;

        if (operation == '+' || operation == '-' || operation == '*' || operation == '/') {
            return operation;  // If valid, return the operation
        }
        else {
            std::cout << "Invalid operation. Please enter one of the following: +, -, *, /.\n";
        }
    }
}

int main() {
    // Introductory text to explain what the program does
    std::cout << "Welcome to the Calculator Program!\n";
    std::cout << "This program allows you to perform basic arithmetic operations (+, -, *, /)\n";
    std::cout << "You can enter both integer and decimal numbers.\n\n";

    double num1, num2;   // For handling both int and double
    char operation;
    char choice;

    do {
        // Get valid numbers from the user
        num1 = getValidNumber<double>();  // Can handle both int and double
        num2 = getValidNumber<double>();

        // Get a valid operation from the user
        operation = getValidOperation();

        // Perform the calculation using double type
        double result = calculate(num1, num2, operation);

        // Output the result
        std::cout << "Result: " << result << std::endl;

        // Ask the user if they want to perform another calculation
        std::cout << "Would you like to perform another calculation (y/n)? ";
        std::cin >> choice;

        // Clear the input buffer to handle any leftover input
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    } while (choice == 'y' || choice == 'Y');

    std::cout << "Thank you for using the calculator!\n";
    return 0;
}
