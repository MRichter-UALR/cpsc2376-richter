#include <iostream>
#include <string>
#include <limits>

int main() {
    float redPotion{ 0.0f };    // Amount of red potion in mL
    float bluePotion{ 0.0f };   // Amount of blue potion in mL
    float* flask{ nullptr };    // Pointer to the selected potion

    std::string choice;
    while (true) {
        // Ask which potion to fill or exit
        std::cout << "Which potion to add to? (Red/Blue) or type Done to finish: ";
        std::getline(std::cin, choice);
        if (choice == "Done" || choice == "done") {
            break;
        }
        if (choice == "Red" || choice == "red") {
            flask = &redPotion;
        }
        else if (choice == "Blue" || choice == "blue") {
            flask = &bluePotion;
        }
        else {
            std::cout << "Invalid choice. Please enter Red, Blue, or Done.\n";
            continue;
        }

        // Ask how much to add
        std::cout << "Enter amount in mL to add: ";
        float amount{ 0.0f };
        std::cin >> amount;
        if (!std::cin) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid number. Try again.\n";
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // Update the selected potion via the pointer
        *flask += amount;

        // Display current levels
        std::cout << "Red potion: " << redPotion << " mL, "
            << "Blue potion: " << bluePotion << " mL\n";
    }

    std::cout << "Final levels -> Red: " << redPotion
        << " mL, Blue: " << bluePotion << " mL\n";
    return 0;
}
