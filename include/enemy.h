#ifndef ENEMY_H
#define ENEMY_H

#include <string>

class Enemy {
public:
    Enemy(const std::string& type);
    void attack() const;

private:
    std::string type;
};

#endif // ENEMY_H
