#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include "objects/object.h"
#include <vector>

// Manage the objects in the game
void AddObject(std::vector<Object>& objects, int x, int y, int width, int height);
void RemoveInactiveObjects(std::vector<Object>& objects);

#endif
