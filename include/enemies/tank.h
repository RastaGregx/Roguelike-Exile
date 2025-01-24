#pragma once

#include "enemies/enemy.h"
#include "raylib.h"
#include <string>  // Include the <string> header to use std::string

class Tank : public Enemy {
public:
    // Constructor to initialize Tank with position, speed, color, health, and armor
    Tank(Vector2 pos, float spd, Color col, int hp, float armor, const std::string& texturePath = "");

    // Override Update method
    void Update(Vector2 playerPosition, float deltaTime, const std::vector<Object>& objects, Player& player, std::vector<std::shared_ptr<Enemy>>& enemies) override;

    // Override TakeDamage method
    void TakeDamage(int damage) override;

    // Method to check if the tank has a valid texture
    bool hasTexture() const;

    // Method to retrieve the tank's texture
    Texture2D getTexture() const;

private:
    float armor; // Reduces incoming damage
    Texture2D texture; // Texture for the tank sprite
};
