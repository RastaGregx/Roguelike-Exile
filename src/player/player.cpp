#include "player/player.h"
#include <iostream>

Player::Player(const std::string& name) : name(name) {}

void Player::greet() const {
    std::cout << "Hello, I am " << name << ", ready for adventure!" << std::endl;
}
