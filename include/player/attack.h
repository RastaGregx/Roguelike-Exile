#ifndef ATTACK_H
#define ATTACK_H

#include "raylib.h"
#include "enemies/enemy.h"
#include "objects/object.h"

#include <vector>
#include <algorithm>

bool CheckCollision(const Rectangle& rect1, const Rectangle& rect2);

class Attack {
public:
    struct Projectile {
        Vector2 position;
        Vector2 velocity;
        float radius;
        Color color;
        bool active;

        Projectile(Vector2 pos, Vector2 vel, float r, Color col)
            : position(pos), velocity(vel), radius(r), color(col), active(true) {}
    };

    std::vector<Projectile> projectiles;

    void Shoot(Vector2 position, Vector2 direction); // Updated method signature
    void Update(float deltaTime, std::vector<Enemy>& enemies, const std::vector<Object>& objects);
    void Draw() const;
};

#endif // ATTACK_H
