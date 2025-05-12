#pragma once
#include <memory>

// Base interface
class Purchase {
public:
    virtual double getCost() const = 0;
    virtual ~Purchase() = default;
};

// Concrete base purchase
class SimplePurchase : public Purchase {
public:
    explicit SimplePurchase(double baseCost);
    double getCost() const override;

private:
    double cost;
};

// Base Decorator
class PurchaseDecorator : public Purchase {
public:
    explicit PurchaseDecorator(std::unique_ptr<Purchase> inner);
    virtual ~PurchaseDecorator() = default;

protected:
    std::unique_ptr<Purchase> wrapped;
};

// TaxDecorator: adds 10% tax
class TaxDecorator : public PurchaseDecorator {
public:
    explicit TaxDecorator(std::unique_ptr<Purchase> inner);
    double getCost() const override;
};

// ShippingFeeDecorator: adds flat $5 shipping
class ShippingFeeDecorator : public PurchaseDecorator {
public:
    explicit ShippingFeeDecorator(std::unique_ptr<Purchase> inner);
    double getCost() const override;
};

// DiscountDecorator: subtracts percentage from total
class DiscountDecorator : public PurchaseDecorator {
public:
    DiscountDecorator(std::unique_ptr<Purchase> inner, double percentOff);
    double getCost() const override;

private:
    double discountRate; // 0.10 for 10% off
};
