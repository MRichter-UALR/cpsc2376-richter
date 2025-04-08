#include <iostream>
#include <limits>
#include "Fraction.h"
#include "MixedFraction.h"

// Helper: Get valid integer input
int getInt(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) break;
        std::cout << "Invalid input. Please enter an integer.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return value;
}

// Helper: Get a new Fraction from user input
Fraction getFractionInput(const std::string& label = "Enter") {
    while (true) {
        int num = getInt(label + " numerator: ");
        int den = getInt(label + " denominator: ");
        try {
            return Fraction(num, den);
        }
        catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << " Try again.\n";
        }
    }
}

int main() {
    Fraction current; // starts at 0/1
    bool running = true;

    while (running) {
        std::cout << "\nCurrent Fraction: " << current << "\n\n";
        std::cout << "Options:\n";
        std::cout << "1. Enter a fraction manually\n";
        std::cout << "2. Add a fraction\n";
        std::cout << "3. Subtract a fraction\n";
        std::cout << "4. Multiply by a fraction\n";
        std::cout << "5. Divide by a fraction\n";
        std::cout << "6. Display as Mixed Fraction\n";
        std::cout << "7. Clear Fraction\n";
        std::cout << "8. Exit\n";

        int choice = getInt("Choose an option: ");

        try {
            switch (choice) {
            case 1:
                current = getFractionInput("Enter new");
                break;
            case 2: {
                Fraction f = getFractionInput("Add");
                current = current + f;
                break;
            }
            case 3: {
                Fraction f = getFractionInput("Subtract");
                current = current - f;
                break;
            }
            case 4: {
                Fraction f = getFractionInput("Multiply by");
                current = current * f;
                break;
            }
            case 5: {
                Fraction f = getFractionInput("Divide by");
                current = current / f;
                break;
            }
            case 6: {
                MixedFraction mf(current);
                std::cout << "Mixed Fraction: " << mf << "\n";
                break;
            }
            case 7:
                current = Fraction(); // reset to 0/1
                std::cout << "Fraction reset to 0/1.\n";
                break;
            case 8:
                running = false;
                std::cout << "Goodbye!\n";
                break;
            default:
                std::cout << "Invalid choice. Try again.\n";
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Exception: " << e.what() << "\n";
        }
    }

    return 0;
}
