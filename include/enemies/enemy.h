#ifndef ENEMY_H
#define ENEMY_H

#include "raylib.h"
#include "player/player.h"
#include "objects/object.h" // Assuming Object is defined here
#include <vector>
#include <memory>

class Enemy {
protected:
    int health;

    Color color;
    float speed;
    float width;
    float attackCooldown;
    float lastAttackTime;
    float pushbackStrength;
    float collisionRadius;

public:
    Vector2 position;
    Enemy(Vector2 pos, float spd, Color col, int hp);
    Enemy(const Enemy& other) = default;
    Enemy(Enemy&& other) noexcept = default;
    Enemy& operator=(const Enemy& other) = default;
    Enemy& operator=(Enemy&& other) noexcept = default;
    virtual ~Enemy() = default;

    virtual void Update(Vector2 playerPosition, float deltaTime, const std::vector<Object>& objects, Player& player, std::vector<std::shared_ptr<Enemy>>& enemies);
    virtual void Draw() const;
    virtual void TakeDamage(int damage);
    bool IsAlive() const;
    Vector2 GetPosition() const;
    
};

#endif
