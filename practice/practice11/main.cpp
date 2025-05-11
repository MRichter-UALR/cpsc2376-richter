// main.cpp
// Practice11 – Board Game Lending System

#include <iostream>
#include <vector>
#include <string>

class Game {
public:
    std::string title;
    int totalCopies;
    int availableCopies;

    Game(const std::string& title, int totalCopies)
        : title(title), totalCopies(totalCopies), availableCopies(totalCopies) {
    }

    void checkout() {
        if (availableCopies > 0) {
            --availableCopies;
        }
        else {
            std::cout << "No available copies of \"" << title << "\".\n";
        }
    }

    void returnCopy() {
        if (availableCopies < totalCopies) {
            ++availableCopies;
        }
        else {
            std::cout << "All copies of \"" << title << "\" are already returned.\n";
        }
    }
};

class Customer {
public:
    std::string name;

    Customer(const std::string& name) : name(name) {}
};

class Loan {
public:
    Game* game;
    Customer* customer;
    std::string dueDate;

    Loan(Game* game, Customer* customer, const std::string& dueDate)
        : game(game), customer(customer), dueDate(dueDate) {
    }

    std::string getLoanInfo() const {
        return customer->name + " borrowed \"" + game->title + "\" due on " + dueDate;
    }
};

void listGames(const std::vector<Game>& games) {
    std::cout << "\nGame Inventory:\n";
    for (const auto& game : games) {
        std::cout << " - " << game.title
            << " | Available: " << game.availableCopies
            << " / " << game.totalCopies << "\n";
    }
}

void listLoans(const std::vector<Loan>& loans) {
    std::cout << "\nActive Loans:\n";
    for (const auto& loan : loans) {
        std::cout << " - " << loan.getLoanInfo() << "\n";
    }
}

int main() {
    std::vector<Game> games = {
        Game("Catan", 3),
        Game("Ticket to Ride", 2),
        Game("Carcassonne", 4)
    };

    std::vector<Customer> customers = {
        Customer("Alice"),
        Customer("Bob"),
        Customer("Charlie")
    };

    std::vector<Loan> loans;

    games[0].checkout();
    loans.emplace_back(&games[0], &customers[0], "2025-05-17");

    games[1].checkout();
    loans.emplace_back(&games[1], &customers[1], "2025-05-18");

    games[0].returnCopy();

    listGames(games);
    listLoans(loans);

    return 0;
}
