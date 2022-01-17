#include <algorithm>
#include <exception>
#include <functional>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <stdexcept>
#include <string>
#include <vector>

#include "item.hpp"
#include "new_order.hpp"

// Open-closed Principle - open for extensions, closed for modification
// We refactor our PaymentProcessor to allow adding new payment methods.

/*
 * PAYMENT PROCESSOR
 */

struct PaymentProcessorAbstractOC {
    virtual void Pay(const std::string &security_code) const = 0;
    virtual void DisplayInfo() const = 0;

    PaymentProcessorAbstractOC() = default;
    virtual ~PaymentProcessorAbstractOC() = default;

    PaymentProcessorAbstractOC(PaymentProcessorAbstractOC &) = delete;
    PaymentProcessorAbstractOC(PaymentProcessorAbstractOC &&) = delete;
    auto operator=(PaymentProcessorAbstractOC &) = delete;
    auto operator=(PaymentProcessorAbstractOC &&) = delete;
};

/*
 * PAYMENT PROCESSOR CREDIT
 */

struct PaymentProcessorCreditOC final : public PaymentProcessorAbstractOC {
    explicit PaymentProcessorCreditOC(NewOrder &new_order)
        : new_order_{new_order} {}

    void Pay(const std::string &security_code) const override {
        std::cout << "Processing credit payment type\n";
        std::cout << "Verifying security code: " << security_code << '\n';
        new_order_.SetStatus(Status::Paid);
    }

    void DisplayInfo() const override {
        std::cout << "Credit payment processor for order :"
                  << std::to_string(new_order_.GetId()) << '\n';
    }

  private:
    NewOrder &new_order_;
};

/*
 * PAYMENT PROCESSOR DEBIT
 */

struct PaymentProcessorDebitOC final : public PaymentProcessorAbstractOC {
    explicit PaymentProcessorDebitOC(NewOrder &new_order)
        : new_order_{new_order} {}

    void Pay(const std::string &security_code) const override {
        std::cout << "Processing debit payment type\n";
        std::cout << "Verifying security code: " << security_code << '\n';
        new_order_.SetStatus(Status::Paid);
    }

    void DisplayInfo() const override {
        std::cout << "Debit payment processor for order :"
                  << std::to_string(new_order_.GetId()) << '\n';
    }

  private:
    NewOrder &new_order_;
};

/*
 * PAYMENT PROCESSOR PAYPAL
 */

struct PaymentProcessorPaypalOC final : public PaymentProcessorAbstractOC {
    explicit PaymentProcessorPaypalOC(NewOrder &new_order)
        : new_order_{new_order} {}

    void Pay(const std::string &security_code) const override {
        std::cout << "Processing paypal payment type\n";
        std::cout << "Verifying security code: " << security_code << '\n';
        new_order_.SetStatus(Status::Paid);
    }

    void DisplayInfo() const override {
        std::cout << "Paypal payment processor for order :"
                  << std::to_string(new_order_.GetId()) << '\n';
    }

  private:
    NewOrder &new_order_;
};

/*
 * MAIN
 */

auto main() -> int {
    Item item1{"Keyboard", 1, 50.0};
    Item item2{"SSD", 1, 150.0};
    Item item3{"USB cable", 2, 5.0};
    NewOrder an_order{};

    an_order.AddItem(item1);
    an_order.AddItem(item2);
    an_order.AddItem(item3);

    an_order.PrintOrder();

    PaymentProcessorDebitOC proc1{an_order};
    proc1.DisplayInfo();
    proc1.Pay("65379");

    PaymentProcessorCreditOC proc2{an_order};
    proc2.DisplayInfo();
    proc2.Pay("996366");

    PaymentProcessorPaypalOC proc3{an_order};
    proc3.DisplayInfo();
    proc3.Pay("123123");

    return 0;
}
