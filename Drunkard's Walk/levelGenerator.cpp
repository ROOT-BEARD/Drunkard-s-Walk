#include <random>
#include <chrono>
#include "LevelGenerator.h"
#include <vector>

// generates and returns a random int between 1 and 4
int LevelGenerator::generateNum(const std::vector<float> &bias)
{
    // random number generations
    static std::random_device rng;
    static auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    static std::mt19937 gen(rng() ^ seed);
    std::discrete_distribution<int> moveDist(bias.begin(), bias.end()); /*1 = up, 2 = down, 3 = left, 4 = right*/
    return moveDist(gen) + 1;
}

std::vector<float> LevelGenerator::generateBias(int lastDir, float backwardsBias, float forwardsBias)
{

    float upBias = 1;
    float downBias = 1;
    float leftBias = 1;
    float rightBias = 1;

    switch (lastDir)
    {
    case 1:
        downBias = backwardsBias;
        break;
    case 2:
        upBias = backwardsBias;
        break;
    case 3:
        rightBias = backwardsBias;
        break;
    case 4:
        leftBias = backwardsBias;
        break;
    }

    switch (lastDir)
    {
    case 1:
        upBias = forwardsBias;
        break;
    case 2:
        downBias = forwardsBias;
        break;
    case 3:
        leftBias = forwardsBias;
        break;
    case 4:
        rightBias = forwardsBias;
        break;
    }
    return {upBias, downBias, leftBias, rightBias};
}

/* generates a level layout within the width and height of the desired level in tiles
(ex, 320pixel height level of 32 pixel tiles would be a height of 10).*/
std::vector<int> LevelGenerator::generateLevel(int width, int height, int steps, float backwardsBias, float forwardsBias)
{
    int curSteps = 0;
    if (width <= 0 || height <= 0)
    {
        return {};
    }

    std::vector<int> level(height * width, 0);
    // starts in the center
    Vector2 walkerPos = {width / 2, height / 2};
    // the amount of time the drunkard will move
    // the starting pos of the dunkard
    // loop for the number of steps

    std::vector<float> bias = {1, 1, 1, 1};
    int dir;
    while (curSteps < steps)
    {
        bool vaildMove = false;
        while (!vaildMove)
        {
            // gets a random number 1-4
            dir = generateNum(bias);
            /*1 = up, 2 = down, 3 = left, 4 = right*/
            switch (dir)
            {
            case 1:
                if (walkerPos.y > 0)
                {
                    walkerPos.y -= 1;
                    vaildMove = true;
                }
                break;
            case 2:
                if (walkerPos.y < height - 1)
                {
                    walkerPos.y += 1;
                    vaildMove = true;
                }
                break;
            case 3:
                if (walkerPos.x > 0)
                {
                    walkerPos.x -= 1;
                    vaildMove = true;
                }
                break;
            case 4:
                if (walkerPos.x < width - 1)
                {
                    walkerPos.x += 1;
                    vaildMove = true;
                }
                break;
            }
            if (!vaildMove)
                bias = {1, 1, 1, 1};
        }
        // makes the current position of the dunkard into an open spot
        if (level[(walkerPos.y * width) + walkerPos.x] == 0)
        {
            level[(walkerPos.y * width) + walkerPos.x] = 1;
            curSteps += 1;
        }
        bias = generateBias(dir, backwardsBias, forwardsBias);
    }
    return level;
}