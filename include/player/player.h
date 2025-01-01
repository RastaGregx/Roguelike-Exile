#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player {
public:
    Player(const std::string& name);
    void greet() const;

private:
    std::string name;
};

#endif // PLAYER_H
