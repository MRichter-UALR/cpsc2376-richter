#include <iostream>
#include <string>

void greet(std::string name = "Guest", std::string prefix = "Hello") {
    // This outputs the greeting, using the provided prefix and name
    std::cout << prefix << ", " << name << "!\n";
}

int main() {
    int choice;
    std::string name, prefix;
    char restartChoice;

    do {
        // Display instructions and the menu
        std::cout << "Welcome to the Greeting System!\n";
        std::cout << "1. Default Greeting\n";
        std::cout << "2. Greet by Name\n";
        std::cout << "3. Custom Greeting\n";
        std::cout << "Choose an option: ";
        std::cin >> choice;

        // Clear the input buffer before calling getline
        std::cin.ignore(); // Ignore the leftover newline character

        // Handle the user's choice
        switch (choice) {
        case 1:
            // Default greeting
            greet();  // This calls the greet function with default parameters
            break;

        case 2:
            // Greet by name
            std::cout << "Enter name: ";
            std::getline(std::cin, name);  // Read the full name
            greet(name);  // Pass the entered name, using the default "Hello" prefix
            break;

        case 3:
            // Custom greeting
            std::cout << "Enter greeting prefix: ";
            std::getline(std::cin, prefix);  // Read the custom prefix
            std::cout << "Enter name: ";
            std::getline(std::cin, name);  // Read the custom name
            greet(name, prefix);  // Call greet with both custom prefix and name
            break;

        default:
            std::cout << "Invalid choice! Please select a valid option.\n";
            break;
        }

        // Ask the user if they want to start over or exit
        std::cout << "Would you like to start over (y/n)? ";
        std::cin >> restartChoice;

    } while (restartChoice == 'y' || restartChoice == 'Y');  // Repeat if the user enters 'y' or 'Y'

    std::cout << "Thank you for using the Greeting System! Goodbye!\n";  // Exit message
    return 0;
}
