#include "Inventory.hpp"

#include <stdexcept>
#include <utility>

namespace {
    bool isEmpty(const Item& item) {
        return item.getType() == NONE;
    }
}

Inventory::Inventory(const std::vector<std::vector<Item>>& items, Item* equipped)
    : inventory_grid_(items), equipped_(equipped), weight_(0), item_count_(0) {
    for (const auto& row : inventory_grid_) {
        for (const auto& item : row) {
            if (!isEmpty(item)) {
                weight_ += item.getWeight();
                ++item_count_;
            }
        }
    }
}

Item* Inventory::getEquipped() const {
    return equipped_;
}

void Inventory::equip(Item* itemToEquip) {
    equipped_ = itemToEquip;
}

void Inventory::discardEquipped() {
    if (equipped_ != nullptr) {
        delete equipped_;
        equipped_ = nullptr;
    }
}

std::vector<std::vector<Item>> Inventory::getItems() const {
    return inventory_grid_;
}

float Inventory::getWeight() const {
    return weight_;
}

size_t Inventory::getCount() const {
    return item_count_;
}

Item Inventory::at(const size_t& row, const size_t& col) const {
    if (row >= inventory_grid_.size() || col >= inventory_grid_[row].size()) {
        throw std::out_of_range("Inventory::at: row or column out of bounds");
    }
    return inventory_grid_[row][col];
}

bool Inventory::store(const size_t& row, const size_t& col, const Item& pickup) {
    if (row >= inventory_grid_.size() || col >= inventory_grid_[row].size()) {
        throw std::out_of_range("Inventory::store: row or column out of bounds");
    }

    if (!isEmpty(inventory_grid_[row][col])) {
        return false;
    }

    inventory_grid_[row][col] = pickup;

    if (!isEmpty(pickup)) {
        weight_ += pickup.getWeight();
        ++item_count_;
    }
    return true;
}

Inventory::Inventory(const Inventory& rhs)
    : inventory_grid_(rhs.inventory_grid_),
      equipped_(rhs.equipped_ != nullptr ? new Item(*rhs.equipped_) : nullptr),
      weight_(rhs.weight_),
      item_count_(rhs.item_count_) {}

Inventory::Inventory(Inventory&& rhs)
    : inventory_grid_(std::move(rhs.inventory_grid_)),
      equipped_(rhs.equipped_),
      weight_(rhs.weight_),
      item_count_(rhs.item_count_) {
    rhs.inventory_grid_.clear();
    rhs.equipped_ = nullptr;
    rhs.weight_ = 0;
    rhs.item_count_ = 0;
}

Inventory& Inventory::operator=(const Inventory& rhs) {
    if (this != &rhs) {
        Item* newEquipped = (rhs.equipped_ != nullptr) ? new Item(*rhs.equipped_) : nullptr;

        delete equipped_;
        equipped_ = newEquipped;

        inventory_grid_ = rhs.inventory_grid_;
        weight_ = rhs.weight_;
        item_count_ = rhs.item_count_;
    }
    return *this;
}

Inventory& Inventory::operator=(Inventory&& rhs) {
    if (this != &rhs) {
        delete equipped_;

        inventory_grid_ = std::move(rhs.inventory_grid_);
        equipped_ = rhs.equipped_;
        weight_ = rhs.weight_;
        item_count_ = rhs.item_count_;

        rhs.inventory_grid_.clear();
        rhs.equipped_ = nullptr;
        rhs.weight_ = 0;
        rhs.item_count_ = 0;
    }
    return *this;
}

Inventory::~Inventory() {
    delete equipped_;
}
