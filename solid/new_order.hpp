#ifndef NEW_ORDER_HPP_
#define NEW_ORDER_HPP_

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

#endif