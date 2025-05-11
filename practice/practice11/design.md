# Practice11 – Board Game Lending System

## 1. Program Specification

This program is a lightweight management tool for a local board game café. It keeps track of all board games in inventory, their availability, and current borrowers. The system allows a staff member to check out games to customers, track due dates, and mark games as returned. It helps manage the lending side of the business using a simple data structure and interface. The main entities in the program are games, customers, and the loans connecting them.

---

## 2. Nouns and Verbs

### Key Nouns
- Game → class
- Customer → class
- Loan → class
- Title → attribute
- Name → attribute
- Copies → attribute
- Due date → attribute

### Key Verbs
- Checkout → method
- Return → method
- List games → function
- List loans → function
- Get loan info → method

---

## 3. Class Designs (Headers Only)

```cpp
class Game {
public:
    std::string title;
    int totalCopies;
    int availableCopies;

    Game(const std::string& title, int totalCopies);
    void checkout();
    void returnCopy();
};

class Customer {
public:
    std::string name;

    Customer(const std::string& name);
};

class Loan {
public:
    Game* game;
    Customer* customer;
    std::string dueDate;

    Loan(Game* game, Customer* customer, const std::string& dueDate);
    std::string getLoanInfo() const;
};
