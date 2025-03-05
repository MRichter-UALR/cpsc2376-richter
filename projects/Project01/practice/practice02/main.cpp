#include <iostream>
#include <fstream>
#include <iomanip>

const std::string FILE_NAME = "account_balance.txt";

// Function to read balance from file
double readBalanceFromFile() {
    std::ifstream file(FILE_NAME);
    double balance = 100.00; // Default balance if file doesn't exist
    
    if (file.is_open()) {
        file >> balance;
        file.close();
    } else {
        std::ofstream newFile(FILE_NAME);
        newFile << balance;
        newFile.close();
        std::cout << "Initializing account with $100.00...\n";
    }
    
    return balance;
}

// Function to write balance to file
void writeBalanceToFile(double balance) {
    std::ofstream file(FILE_NAME);
    if (file.is_open()) {
        file << balance;
        file.close();
    } else {
        std::cerr << "Error: Unable to save balance.\n";
    }
}

// Function to check balance
void checkBalance(double balance) {
    std::cout << "Your current balance is: $" << std::fixed << std::setprecision(2) << balance << "\n";
}

// Function to deposit money
double deposit(double balance) {
    double amount;
    std::cout << "Enter deposit amount: ";
    std::cin >> amount;
    
    if (amount <= 0) {
        std::cout << "Error: Deposit amount must be positive.\n";
        return balance;
    }
    
    balance += amount;
    writeBalanceToFile(balance);
    std::cout << "Deposit successful. Your new balance is: $" << std::fixed << std::setprecision(2) << balance << "\n";
    return balance;
}

// Function to withdraw money
double withdraw(double balance) {
    double amount;
    std::cout << "Enter withdrawal amount: ";
    std::cin >> amount;
    
    if (amount <= 0) {
        std::cout << "Error: Withdrawal amount must be positive.\n";
        return balance;
    }
    if (amount > balance) {
        std::cout << "Error: Insufficient funds. Your balance is $" << std::fixed << std::setprecision(2) << balance << ".\n";
        return balance;
    }
    
    balance -= amount;
    writeBalanceToFile(balance);
    std::cout << "Withdrawal successful. Your new balance is: $" << std::fixed << std::setprecision(2) << balance << "\n";
    return balance;
}

int main() {
    double balance = readBalanceFromFile();
    int choice;
    
    std::cout << "Welcome to Your Bank Account!\n";
    
    do {
        std::cout << "\nMenu:\n1. Check Balance\n2. Deposit Money\n3. Withdraw Money\n4. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        
        switch (choice) {
            case 1:
                checkBalance(balance);
                break;
            case 2:
                balance = deposit(balance);
                break;
            case 3:
                balance = withdraw(balance);
                break;
            case 4:
                std::cout << "Thank you for using the bank account system. Goodbye!\n";
                break;
            default:
                std::cout << "Invalid choice. Please enter a number between 1 and 4.\n";
        }
    } while (choice != 4);
    
    return 0;
}
