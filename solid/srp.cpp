#include <algorithm>
#include <exception>
#include <functional>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

#include "item.hpp"
#include "new_order.hpp"

// Single responsibility principle - splitting Order and Payment into separate
// classes

/*
 * PAYMENT PROCESSOR
 */

struct PaymentProcessor {
    explicit PaymentProcessor(NewOrder &new_order) : new_order_{new_order} {}

    void DisplayInfo() const;
    void PayDebit(const std::string &security_code) const;
    void PayCredit(const std::string &security_code) const;
    void PayPaypal(const std::string &security_code) const;

  private:
    NewOrder &new_order_;
};

void PaymentProcessor::PayDebit(const std::string &security_code) const {
    std::cout << "Processing debit payment type\n";
    std::cout << "Verifying security code: " << security_code << '\n';
    new_order_.SetStatus(Status::Paid);
}
void PaymentProcessor::PayCredit(const std::string &security_code) const {
    std::cout << "Processing credit payment type\n";
    std::cout << "Verifying security code: " << security_code << '\n';
    new_order_.SetStatus(Status::Paid);
}
void PaymentProcessor::PayPaypal(const std::string &security_code) const {
    std::cout << "Processing paypal payment type\n";
    std::cout << "Verifying security code: " << security_code << '\n';
    new_order_.SetStatus(Status::Paid);
}
void PaymentProcessor::DisplayInfo() const {
    std::cout << "Payment processor for order: "
              << std::to_string(new_order_.GetId()) << '\n';
}

auto main() -> int {
    Item item1{"Keyboard", 1, 50.0};
    Item item2{"SSD", 1, 150.0};
    Item item3{"USB cable", 2, 5.0};
    NewOrder an_order{};

    an_order.AddItem(item1);
    an_order.AddItem(item2);
    an_order.AddItem(item3);

    an_order.PrintOrder();

    PaymentProcessor proc1{an_order};
    proc1.DisplayInfo();
    proc1.PayCredit("65379");

    PaymentProcessor proc2{an_order};
    proc2.DisplayInfo();
    proc2.PayDebit("996366");

    PaymentProcessor proc3{an_order};
    proc3.DisplayInfo();
    proc3.PayDebit("123123");

    return 0;
}
