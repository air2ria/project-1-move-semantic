#include "Player.hpp"
#include <utility>
 
Player::Player(const std::string& name, const Inventory& inventory)
    : inventory_(inventory), name_(name) {}
 
std::string Player::getName() const {
    return name_;
}
 
Inventory& Player::getInventoryRef() {
    return inventory_;
}
 
Player::Player(const Player& rhs)
    : inventory_(rhs.inventory_), name_(rhs.name_) {}
 
Player::Player(Player&& rhs)
    : inventory_(std::move(rhs.inventory_)), name_(std::move(rhs.name_)) {}
 
Player& Player::operator=(const Player& rhs) {
    if (this != &rhs) {
        inventory_ = rhs.inventory_;
        name_ = rhs.name_;
    }
    return *this;
}
 
Player& Player::operator=(Player&& rhs) {
    if (this != &rhs) {
        inventory_ = std::move(rhs.inventory_);
        name_ = std::move(rhs.name_);
    }
    return *this;
}
 
