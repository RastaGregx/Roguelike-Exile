#ifndef ATTACK_H
#define ATTACK_H
#include "raylib.h"

#include "enemies/enemy.h"  // Include Enemy header
#include "objects/object.h" 

#include <vector>
#include <algorithm>

// Declare CheckCollision (no definition here)
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

    void Shoot(Vector2 position, Vector2 velocity, float radius, Color color) {
        projectiles.push_back(Projectile(position, velocity, radius, color));
    }

    void Update(float deltaTime, std::vector<Enemy>& enemies, const std::vector<Object>& objects) {
        for (auto& proj : projectiles) {
            if (!proj.active) continue;

            proj.position.x += proj.velocity.x * deltaTime;
            proj.position.y += proj.velocity.y * deltaTime;

            // Collision with objects
            for (const auto& obj : objects) {
                if (CheckCollision({ proj.position.x - proj.radius, proj.position.y - proj.radius, proj.radius * 2, proj.radius * 2 }, obj.rect)) {
                    proj.active = false;
                    break;
                }
            }

            // Collision with enemies
            for (auto& enemy : enemies) {
                if (proj.active && enemy.IsAlive() &&
                    CheckCollisionCircles(proj.position, proj.radius, enemy.position, 20.0f)) {
                    enemy.TakeDamage(10);
                    proj.active = false;
                    break;
                }
            }
        }

        projectiles.erase(
            std::remove_if(projectiles.begin(), projectiles.end(), [](const Projectile& p) { return !p.active; }),
            projectiles.end()
        );
    }

    void Draw() const {
        for (const auto& proj : projectiles) {
            if (proj.active) {
                DrawCircleV(proj.position, proj.radius, proj.color);
            }
        }
    }
};

#endif // ATTACK_H
