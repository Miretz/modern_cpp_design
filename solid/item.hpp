#ifndef ITEM_HPP_
#define ITEM_HPP_

#include <string>

struct Item {
    Item(std::string item, int quantity, float price)
        : item_{std::move(item)}, quantity_{quantity}, price_{price} {}
    std::string item_;
    int quantity_;
    float price_;
};

#endif