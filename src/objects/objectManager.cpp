#include "objects/objectmanager.h"
#include <algorithm>


void AddObject(std::vector<Object>& objects, int x, int y, int width, int height) {
    objects.push_back(Object(x, y, width, height));
}

void RemoveInactiveObjects(std::vector<Object>& objects) {
    objects.erase(
        std::remove_if(objects.begin(), objects.end(), [](const Object& obj) { return !obj.IsActive(); }),
        objects.end()
    );
}
