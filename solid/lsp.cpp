#include <algorithm>
#include <exception>
#include <functional>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "item.hpp"
#include "new_order.hpp"

// Liskov Substitution Principle - subclasses should substitute each other
// without altering the program

/*
 * PAYMENT PROCESSOR
 */

struct PaymentProcessorAbstract {
    virtual void Pay() = 0;
    virtual void DisplayInfo() const = 0;

    PaymentProcessorAbstract() = default;
    virtual ~PaymentProcessorAbstract() = default;

    PaymentProcessorAbstract(PaymentProcessorAbstract &) = delete;
    PaymentProcessorAbstract(PaymentProcessorAbstract &&) = delete;
    auto operator=(PaymentProcessorAbstract &) = delete;
    auto operator=(PaymentProcessorAbstract &&) = delete;
};

/*
 * PAYMENT PROCESSOR CREDIT
 */

struct PaymentProcessorCredit final : public PaymentProcessorAbstract {
    explicit PaymentProcessorCredit(NewOrder &new_order,
                                    std::string security_code)
        : new_order_{new_order}, security_code_{std::move(security_code)} {}

    void Pay() override {
        std::cout << "Processing credit payment type\n";
        std::cout << "Verifying security code: " << security_code_ << '\n';
        new_order_.SetStatus(Status::Paid);
    }

    void DisplayInfo() const override {
        std::cout << "Credit payment processor for order "
                  << std::to_string(new_order_.GetId()) << '\n';
    }

  private:
    NewOrder &new_order_;
    std::string security_code_;
};

/*
 * PAYMENT PROCESSOR PAYPAL
 */

struct PaymentProcessorPaypal final : public PaymentProcessorAbstract {
    explicit PaymentProcessorPaypal(NewOrder &new_order,
                                    std::string email_address)
        : new_order_{new_order}, email_address_{std::move(email_address)} {}

    void Pay() override {
        std::cout << "Processing paypal payment type\n";
        std::cout << "Verifying email address: " << email_address_ << '\n';
        verified_ = true;
        new_order_.SetStatus(Status::Paid);
    }

    void DisplayInfo() const override {
        std::cout << "Paypal payment processor for order "
                  << std::to_string(new_order_.GetId()) << '\n';
    }

  private:
    NewOrder &new_order_;
    std::string email_address_;
    bool verified_{false};
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

    PaymentProcessorCredit proc1{an_order, "65221"};
    proc1.DisplayInfo();
    proc1.Pay();

    PaymentProcessorPaypal proc2{an_order, "example@example.com"};
    proc2.DisplayInfo();
    proc2.Pay();

    return 0;
}
