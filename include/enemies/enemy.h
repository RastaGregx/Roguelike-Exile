#ifndef ENEMY_H
#define ENEMY_H

#include "raylib.h"
#include "player/player.h"
#include "objects/object.h"
#include <vector>
#include <cmath>

class Enemy {
public:
    Vector2 position;  // Position of the enemy
    float speed;       // Speed of the enemy
    Color color;       // Color of the enemy
    int health;        // Health of the enemy
    float width;       // Collision width of the enemy

    // Pushback and attack cooldown
    float attackCooldown;      // Time between attacks
    float lastAttackTime;      // Time of the last attack
    float pushbackStrength;    // Pushback distance when enemy attacks
    float collisionRadius;     // Radius for enemy collision detection

    // Constructor
    Enemy(Vector2 pos, float spd, Color col, int hp);

    // Factory function to create an enemy with level scaling
    static Enemy CreateEnemy(Vector2 pos, int level);

    // Update method to handle movement and interactions
    virtual void Update(Vector2 playerPosition, float deltaTime, const std::vector<Object>& objects, Player& player, std::vector<Enemy>& enemies);


    // Damage and status methods
    void TakeDamage(int damage);
    bool IsAlive() const;

    // Draw the enemy
    void Draw() const;
};

#endif
