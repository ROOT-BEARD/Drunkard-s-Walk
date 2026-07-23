#ifndef LEVELGENERATOR_H
#define LEVELGENERATOR_H

#include <vector>

struct Vector2
{
    int x;
    int y;
};

class LevelGenerator
{
private:
    int generateNum();

public:
    std::vector<int> generateLevel(int width, int height);
};

#endif