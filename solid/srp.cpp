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

// Single responsibility principle - splitting Order and Payment into separate
// classes

struct Item {
  Item(std::string_view item, int quantity, float price)
      : item_{item}, quantity_{quantity}, price_{price} {}
  std::string_view item_;
  int quantity_;
  float price_;
};

/*
 * Order
 */

enum class Status { Open, Paid };

static uint32_t last_order_id = 0;

class NewOrder {
public:
  void AddItem(const Item &new_item);
  [[nodiscard]] float TotalPrice() const;
  void SetStatus(Status status);
  void PrintOrder() const;
  [[nodiscard]] const uint32_t &GetId() const;

private:
  uint32_t id{last_order_id++}; // should be proper UUID generator - this is
                                // just an example
  std::vector<Item> items_;
  Status status_{Status::Open};
};

void NewOrder::AddItem(const Item &new_item) { items_.push_back(new_item); }

void NewOrder::PrintOrder() const {
  std::cout << "The id of the order is " << id << ", with items:\n";
  static constexpr auto column_width = 20;
  std::cout << std::left << std::setw(column_width) << "Item" << std::left
            << std::setw(column_width) << "Quantity" << std::left
            << std::setw(column_width) << "Price" << std::left
            << std::setw(column_width) << "Total" << '\n';
  std::for_each(items_.begin(), items_.end(), [&](const auto &item) {
    std::cout << std::left << std::setw(column_width) << item.item_ << std::left
              << std::setw(column_width) << item.quantity_ << std::left
              << std::setw(column_width) << item.price_ << std::left
              << std::setw(column_width) << (item.quantity_ * item.price_)
              << '\n';
  });
  std::cout << "The status is "
            << ((status_ == Status::Paid) ? "Paid" : "Open");
  std::cout << '\n';
}

float NewOrder::TotalPrice() const {
  float total{0.0f};
  for (auto &item : items_) {
    total += static_cast<float>(item.quantity_) * item.price_;
  }
  return total;
}

void NewOrder::SetStatus(Status status) { status_ = status; }

const uint32_t &NewOrder::GetId() const { return id; }

/*
 * PAYMENT PROCESSOR
 */

struct PaymentProcessor {
  explicit PaymentProcessor(NewOrder &new_order) : new_order_{new_order} {}

  void DisplayInfo() const;
  void PayDebit(std::string_view security_code) const;
  void PayCredit(std::string_view security_code) const;
  void PayPaypal(std::string_view security_code) const;

private:
  NewOrder &new_order_;
};

void PaymentProcessor::PayDebit(std::string_view security_code) const {
  std::cout << "Processing debit payment type\n";
  std::cout << "Verifying security code: " << security_code << '\n';
  new_order_.SetStatus(Status::Paid);
}
void PaymentProcessor::PayCredit(std::string_view security_code) const {
  std::cout << "Processing credit payment type\n";
  std::cout << "Verifying security code: " << security_code << '\n';
  new_order_.SetStatus(Status::Paid);
}
void PaymentProcessor::PayPaypal(std::string_view security_code) const {
  std::cout << "Processing paypal payment type\n";
  std::cout << "Verifying security code: " << security_code << '\n';
  new_order_.SetStatus(Status::Paid);
}
void PaymentProcessor::DisplayInfo() const {
  std::cout << "Payment processor for order: "
            << std::to_string(new_order_.GetId()) << '\n';
}

int main() {
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
