#ifndef OBJECT_H
#define OBJECT_H

#include "raylib.h"

class Object {
public:
    Rectangle rect;  // Rectangle representing the object (e.g., a wall)

    // Constructor to initialize the object
    Object(float x, float y, float width, float height) {
        rect = {x, y, width, height};
    }

    // Check if the player collides with the object
    bool CheckCollision(Rectangle playerRect) {
        return CheckCollisionRecs(playerRect, rect);
    }
};

#endif // OBJECT_H
