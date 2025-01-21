#include "player/attack.h"
#include "raymath.h"
#include <iostream>

bool CheckCollision(const Rectangle& rect1, const Rectangle& rect2) {
    return (rect1.x < rect2.x + rect2.width &&
            rect1.x + rect1.width > rect2.x &&
            rect1.y < rect2.y + rect2.height &&
            rect1.y + rect1.height > rect2.y);
}

void Attack::Shoot(Vector2 position, Vector2 direction) {
    if (Vector2Length(direction) > 0) {
        direction = Vector2Normalize(direction); // Normalize the direction
    }

    float speed = 500.0f; 
    Vector2 velocity = Vector2Scale(direction, speed);

    std::cout << "Projectile velocity: " << velocity.x << ", " << velocity.y << std::endl;

    this->projectiles.push_back(Projectile(position, velocity, 10.0f, BLUE));
}

void Attack::Update(float deltaTime, std::vector<Enemy>& enemies, const std::vector<Object>& objects) {
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

void Attack::Draw() const {
    for (const auto& proj : projectiles) {
        if (proj.active) {
            DrawCircleV(proj.position, proj.radius, proj.color);
        }
    }
}
