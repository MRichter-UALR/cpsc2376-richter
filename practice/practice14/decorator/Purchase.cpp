#include "Purchase.h"

// SimplePurchase implementation
SimplePurchase::SimplePurchase(double baseCost) : cost(baseCost) {}

double SimplePurchase::getCost() const {
    return cost;
}

// Base Decorator
PurchaseDecorator::PurchaseDecorator(std::unique_ptr<Purchase> inner)
    : wrapped(std::move(inner)) {
}

// TaxDecorator: adds 10% tax
TaxDecorator::TaxDecorator(std::unique_ptr<Purchase> inner)
    : PurchaseDecorator(std::move(inner)) {
}

double TaxDecorator::getCost() const {
    return wrapped->getCost() * 1.10; // Adds 10%
}

// ShippingFeeDecorator: adds flat $5
ShippingFeeDecorator::ShippingFeeDecorator(std::unique_ptr<Purchase> inner)
    : PurchaseDecorator(std::move(inner)) {
}

double ShippingFeeDecorator::getCost() const {
    return wrapped->getCost() + 5.0;
}

// DiscountDecorator: reduces cost by percentage
DiscountDecorator::DiscountDecorator(std::unique_ptr<Purchase> inner, double percentOff)
    : PurchaseDecorator(std::move(inner)), discountRate(percentOff) {
}

double DiscountDecorator::getCost() const {
    return wrapped->getCost() * (1.0 - discountRate);
}
