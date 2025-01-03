#ifndef OBJECT_H
#define OBJECT_H

#include "raylib.h"

class Object {
public:
    Rectangle rect;  // Rectangle representing the object (e.g., a wall)
    bool active;     // A flag to track if the object is active

    // Constructor to initialize the object
    Object(float x, float y, float width, float height) 
        : rect{x, y, width, height}, active(true) {}

    // Check if the player collides with the object (now const)
    bool CheckCollision(Rectangle playerRect) const {
        return CheckCollisionRecs(playerRect, rect);
    }

    // Method to check if the object is active
    bool IsActive() const {
        return active;
    }

    // Method to deactivate the object (if needed)
    void SetActive(bool isActive) {
        active = isActive;
    }
};

#endif // OBJECT_H
