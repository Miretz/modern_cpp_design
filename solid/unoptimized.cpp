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

// Too many code smells

struct Item {
    Item(std::string item, int quantity, float price)
        : item_{std::move(item)}, quantity_{quantity}, price_{price} {}
    std::string item_;
    int quantity_;
    float price_;
};

class Order {
  public:
    void AddItem(const Item &new_item) { items_.push_back(new_item); };
    [[nodiscard]] auto TotalPrice() const -> float {
        return std::accumulate(items_.begin(), items_.end(), 0.0f,
                               [](float sum, const auto &item) {
                                   return sum + (item.price_ * item.quantity_);
                               });
    };
    void Pay(const std::string &payment_type,
             const std::string &security_code) {
        std::cout << "Pay: " << payment_type << '\t' << security_code << '\n';
    }

    void PrintOrder() const {
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
        std::cout << '\n';
    };

  private:
    std::vector<Item> items_;
    std::string status_{"open"};
};

auto main() -> int {
    Item item1{"Keyboard", 1, 50.0};
    Item item2{"SSD", 1, 150.0};
    Item item3{"USB cable", 2, 5.0};
    Order an_order{};

    an_order.AddItem(item1);
    an_order.AddItem(item2);
    an_order.AddItem(item3);

    an_order.PrintOrder();

    std::cout << "The total price is: " << an_order.TotalPrice() << "\n\n";
    try {
        an_order.Pay("debit", "09878");
    } catch (const std::exception &t) {
        std::cout << t.what() << '\n';
    }

    try {
        an_order.Pay("credit", "96553");
    } catch (const std::exception &t) {
        std::cout << t.what() << '\n';
    }

    return 0;
}
