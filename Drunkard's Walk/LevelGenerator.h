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
    int generateNum(const std::vector<float> &bias);
    std::vector<float> generateBias(int lastDir, float biaScale);

public:
    std::vector<int> generateLevel(int width, int height, int steps);
};

#endif