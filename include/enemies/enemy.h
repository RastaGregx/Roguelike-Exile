#ifndef ENEMY_H
#define ENEMY_H

#include "raylib.h"
#include <vector>
#include "objects/object.h"

class Enemy {
public:
    Vector2 position;
    float speed;
    Color color;
    int health; // New: Enemy health

    Enemy(Vector2 pos, float spd, Color col, int hp);

    void Update(Vector2 playerPosition, float deltaTime, const std::vector<Object>& objects);
    void TakeDamage(int damage); // New: Reduce health
    bool IsAlive() const;        // New: Check if enemy is still alive
    void Draw() const;
};

#endif // ENEMY_H
