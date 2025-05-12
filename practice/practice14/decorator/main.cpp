#include <iostream>
#include <memory>
#include "Purchase.h"

void printMenu() {
    std::cout << "\nSelect decorators to apply:\n";
    std::cout << "1. Add 10% Tax\n";
    std::cout << "2. Add $5 Shipping Fee\n";
    std::cout << "3. Apply Discount (%)\n";
    std::cout << "4. Done\n";
}

int main() {
    double baseCost;
    std::cout << "Enter base cost of the purchase: $";
    std::cin >> baseCost;

    std::unique_ptr<Purchase> purchase = std::make_unique<SimplePurchase>(baseCost);
    int choice;

    while (true) {
        printMenu();
        std::cout << "Choice: ";
        std::cin >> choice;

        if (choice == 1) {
            purchase = std::make_unique<TaxDecorator>(std::move(purchase));
        }
        else if (choice == 2) {
            purchase = std::make_unique<ShippingFeeDecorator>(std::move(purchase));
        }
        else if (choice == 3) {
            double percent;
            std::cout << "Enter discount percentage (e.g. 15 for 15%): ";
            std::cin >> percent;
            purchase = std::make_unique<DiscountDecorator>(std::move(purchase), percent / 100.0);
        }
        else if (choice == 4) {
            break;
        }
        else {
            std::cout << "Invalid option.\n";
        }
    }

    std::cout << "Final cost: $" << purchase->getCost() << "\n";
    return 0;
}
