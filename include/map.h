#ifndef MAP_H
#define MAP_H

#include <vector>

const char WALL = '#';
const char FLOOR = '.';
const char ROOM = 'R';
const char CORRIDOR = 'C';

struct Room {
    int x, y; // Top-left corner
    int width, height;

    bool Intersects(const Room& other) const;
};

struct Map {
    std::vector<std::vector<char>> tiles;

    Map(int width, int height);

    void Generate(float wallProbability);
    void GenerateRoomsAndCorridors(int roomCount, int roomMinSize, int roomMaxSize);
};

#endif // MAP_H
