// attack.h

bool CheckCollision(const Rectangle& rect1, const Rectangle& rect2) {
    return (rect1.x < rect2.x + rect2.width &&
            rect1.x + rect1.width > rect2.x &&
            rect1.y < rect2.y + rect2.height &&
            rect1.y + rect1.height > rect2.y);
}

class Attack {
public:
    struct Projectile {
        Vector2 position;
        Vector2 velocity;
        float radius;
        Color color;
        bool active;  // Is the projectile still active?

        // Constructor
        Projectile(Vector2 pos, Vector2 vel, float r, Color col)
            : position(pos), velocity(vel), radius(r), color(col), active(true) {}
    };

    std::vector<Projectile> projectiles;

    void Shoot(Vector2 position, Vector2 velocity, float radius, Color color) {
        projectiles.push_back(Projectile(position, velocity, radius, color));
    }

    void Update(float deltaTime, const std::vector<Object>& objects) {
        for (auto& proj : projectiles) {
            if (!proj.active) continue;  // Skip inactive projectiles

            // Update position based on velocity
            proj.position.x += proj.velocity.x * deltaTime;
            proj.position.y += proj.velocity.y * deltaTime;

            // Check for collision with each object
            for (const auto& obj : objects) {
                if (CheckCollision({ proj.position.x - proj.radius, proj.position.y - proj.radius, proj.radius * 2, proj.radius * 2 }, obj.rect)) {
                    proj.active = false;  // Stop the projectile when it hits an object
                    break;  // No need to check further objects once we hit one
                }
            }
        }
    }

    void Draw() {
        for (const auto& proj : projectiles) {
            if (proj.active) {
                DrawCircleV(proj.position, proj.radius, proj.color);
            }
        }
    }
};
