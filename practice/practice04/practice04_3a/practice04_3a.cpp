#include <iostream>
#include <list>
#include <string>
#include <limits>  // Required for std::numeric_limits

// Function to display the menu
void showMenu() {
    std::cout << "\nTask Manager - Manage Your To-Do List\n";
    std::cout << "--------------------------------------\n";
    std::cout << "1. Add Task\n";
    std::cout << "2. Remove Task\n";
    std::cout << "3. Show Tasks\n";
    std::cout << "4. Exit\n";
    std::cout << "Choose an option: ";
}

int main() {
    std::list<std::string> tasks;  // Using std::list to store tasks
    int choice;  // User menu selection

    std::cout << "Welcome to the Task Manager!\n";
    std::cout << "You can add, remove, and view your tasks using this simple interface.\n";

    while (true) {
        showMenu();  // Display the menu
        std::cin >> choice;

        // Validate input to prevent infinite loops
        if (std::cin.fail()) {
            std::cin.clear();  // Clear error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Discard invalid input
            std::cout << "Invalid input! Please enter a number between 1 and 4.\n";
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Handle newline character

        if (choice == 1) {
            // Add a task
            std::string task;
            std::cout << "Enter task: ";
            std::getline(std::cin, task);
            tasks.push_back(task);
            std::cout << "Task added!\n";

        }
        else if (choice == 2) {
            // Remove a task
            if (tasks.empty()) {
                std::cout << "No tasks to remove.\n";
            }
            else {
                int index;
                std::cout << "Enter task number to remove: ";
                std::cin >> index;

                if (std::cin.fail() || index < 1 || index > tasks.size()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid task number.\n";
                }
                else {
                    auto it = tasks.begin();
                    std::advance(it, index - 1);
                    tasks.erase(it);
                    std::cout << "Task removed!\n";
                }
            }
        }
        else if (choice == 3) {
            // Show tasks
            if (tasks.empty()) {
                std::cout << "No tasks available.\n";
            }
            else {
                std::cout << "Tasks:\n";
                int i = 1;
                for (const auto& task : tasks) {
                    std::cout << i++ << ". " << task << "\n";
                }
            }
        }
        else if (choice == 4) {
            // Exit program
            std::cout << "Exiting Task Manager. Goodbye!\n";
            break;
        }
        else {
            // Invalid menu option
            std::cout << "Invalid choice! Please select a number between 1 and 4.\n";
        }
    }

    return 0;
}
