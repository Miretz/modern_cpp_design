#include <algorithm>
#include <exception>
#include <functional>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

// Liskov Substitution Principle - subclasses should substitute each other
// without altering the program

struct Item {
    Item(std::string item, int quantity, float price)
        : item_{std::move(item)}, quantity_{quantity}, price_{price} {}
    std::string item_;
    int quantity_;
    float price_;
};

/*
 * Order
 */

enum class Status { Open, Paid };

auto get_new_id() -> uint32_t {
    static uint32_t last_order_id = 0;
    last_order_id++;
    return last_order_id;
}

class NewOrder {
  public:
    void AddItem(const Item &new_item) { items_.push_back(new_item); }
    [[nodiscard]] auto TotalPrice() const -> float {
        return std::accumulate(
            items_.begin(), items_.end(), 0.0f,
            [](float sum, const auto &item) {
                return sum + static_cast<float>(item.quantity_) * item.price_;
            });
    }
    void SetStatus(Status status) { status_ = status; }
    auto GetStatus() const -> Status { return status_; }
    void PrintOrder() const {
        std::cout << "The id of the order is " << id << ", with items:\n";
        static constexpr auto column_width = 20;
        std::cout << std::left << std::setw(column_width) << "Item" << std::left
                  << std::setw(column_width) << "Quantity" << std::left
                  << std::setw(column_width) << "Price" << std::left
                  << std::setw(column_width) << "Total" << '\n';
        std::for_each(items_.begin(), items_.end(), [&](const auto &item) {
            std::cout << std::left << std::setw(column_width) << item.item_
                      << std::left << std::setw(column_width) << item.quantity_
                      << std::left << std::setw(column_width) << item.price_
                      << std::left << std::setw(column_width)
                      << (item.quantity_ * item.price_) << '\n';
        });
        std::cout << "The status is ";
        if (status_ == Status::Paid) {
            std::cout << "Paid";
        } else {
            std::cout << "Open";
        }
        std::cout << '\n';
    }

    [[nodiscard]] auto GetId() const -> const uint32_t & { return id; }

  private:
    uint32_t id{get_new_id()};
    std::vector<Item> items_;
    Status status_{Status::Open};
};

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
