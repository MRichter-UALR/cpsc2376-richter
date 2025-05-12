#include <iostream>
#include <memory>
#include <string>
#include "TextFilter.h"

void printMenu() {
    std::cout << "\nChoose a text filter:\n";
    std::cout << "1. Reverse\n";
    std::cout << "2. Uppercase\n";
    std::cout << "3. Remove Vowels\n";
    std::cout << "4. Censor Bad Words\n";
    std::cout << "5. Exit\n";
    std::cout << "Enter choice: ";
}

std::unique_ptr<TextFilter> getFilter(int choice) {
    switch (choice) {
    case 1: return std::make_unique<ReverseFilter>();
    case 2: return std::make_unique<UppercaseFilter>();
    case 3: return std::make_unique<RemoveVowelsFilter>();
    case 4: return std::make_unique<CensorFilter>();
    default: return nullptr;
    }
}

int main() {
    std::string input;
    std::cout << "Enter a sentence: ";
    std::getline(std::cin, input);

    while (true) {
        printMenu();
        int choice;
        std::cin >> choice;
        std::cin.ignore(); // clear newline from buffer

        if (choice == 5) break;

        auto filter = getFilter(choice);
        if (filter) {
            std::string result = filter->apply(input);
            std::cout << "Filtered Result: " << result << "\n";
        }
        else {
            std::cout << "Invalid choice. Try again.\n";
        }
    }

    std::cout << "Goodbye!\n";
    return 0;
}
