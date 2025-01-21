#ifndef ENEMY_H
#define ENEMY_H

#include "raylib.h"
#include "player/player.h"
#include "objects/object.h"
#include <vector>

class Enemy {
public:
    Vector2 position;  // Position of the enemy
    float speed;       // Speed of the enemy
    Color color;       // Color of the enemy
    int health;        // Health of the enemy
    float width;       // Width of the enemy for collision

    // Constructor
    Enemy(Vector2 pos, float spd, Color col, int hp);

    // Virtual Update method to be overridden in derived classes
    virtual void Update(Vector2 playerPosition, float deltaTime, const std::vector<Object>& objects, Player& player);

    void TakeDamage(int damage);
    bool IsAlive() const;
    void Draw() const;
};

#endif
