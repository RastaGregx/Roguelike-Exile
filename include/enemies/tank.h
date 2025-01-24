#pragma once

#include "enemies/enemy.h"

class Tank : public Enemy {
public:
    Tank(Vector2 pos, float spd, Color col, int hp, float armor);

    void Update(Vector2 playerPosition, float deltaTime, const std::vector<Object>& objects, Player& player, std::vector<std::shared_ptr<Enemy>>& enemies) override;
    void TakeDamage(int damage) override;

private:
    float armor; // Reduces incoming damage
};
