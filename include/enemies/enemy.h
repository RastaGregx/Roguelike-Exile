// enemy.h
#ifndef ENEMY_H
#define ENEMY_H

#include "raylib.h"
#include <vector>
#include "object.h"

class Enemy {
public:
    Vector2 position;
    float speed;
    Color color;

    Enemy(Vector2 pos, float spd, Color col);

    void Update(Vector2 playerPosition, float deltaTime, const std::vector<Object>& objects);
    void Draw() const;
};

#endif // ENEMY_H
