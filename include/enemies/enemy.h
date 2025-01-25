#pragma once

#include "raylib.h"
#include "objects/object.h"
#include "player/player.h"
#include <vector>
#include <memory>

class Enemy {
public:
    Enemy(Vector2 pos, float spd, Color col, int hp, float w, float h);
    virtual ~Enemy() = default;

    virtual void Update(Vector2 playerPosition, float deltaTime, 
                    const std::vector<Object>& objects, 
                    Player& player, 
                    std::vector<std::shared_ptr<Enemy>>& enemies);
    virtual void TakeDamage(int damage);

    virtual void Draw() const;
    bool IsAlive() const;

    Vector2 GetPosition() const;
    float GetCollisionRadius() const;

protected:
    Vector2 position;
    float speed;
    Color color;
    int health;
    float width;
    float height;

    float collisionRadius;
    float attackCooldown;
    float lastAttackTime;
    bool active; // Indicates if the enemy is active
};
