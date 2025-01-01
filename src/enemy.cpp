#include "enemy.h"
#include <iostream>

Enemy::Enemy(const std::string& type) : type(type) {}

void Enemy::attack() const {
    std::cout << "An enemy of type " << type << " attacks viciously!" << std::endl;
}
