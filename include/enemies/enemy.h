#pragma once

#include "raylib.h"
#include "objects/object.h"
#include <vector>
#include <memory>

class Player;

class Enemy {
public:
    Enemy(Vector2 pos, float spd, Color col, int hp);

    virtual void Update(Vector2 playerPosition, float deltaTime, const std::vector<Object>& objects, Player& player, std::vector<std::shared_ptr<Enemy>>& enemies);
    void Draw() const;
    virtual void TakeDamage(int damage);
    bool IsAlive() const;
    Vector2 GetPosition() const;

protected:
    Vector2 position;
    float speed;
    Color color;
    int health;
    float width;
    float attackCooldown;
    float lastAttackTime;
    float pushbackStrength;
    float collisionRadius;
    bool active;
};