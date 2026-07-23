#include <random>
#include <chrono>
#include "LevelGenerator.h"
#include <vector>

// generates and returns a random int between 1 and 4
int LevelGenerator::generateNum()
{
    // random number generation
    static std::random_device rng;
    static auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    static std::mt19937 gen(rng() ^ seed);
    static std::uniform_int_distribution<int> moveDist(1, 4);
    return moveDist(gen);
}

/* generates a level layout within the width and height of the desired level in tiles
(ex, 320pixel height level of 32 pixel tiles would be a height of 10).*/
std::vector<int> LevelGenerator::generateLevel(int width, int height)
{
    if (width <= 0 || height <= 0)
    {
        return {};
    }

    std::vector<int> level(height * width, 0);
    // starts in the center
    Vector2 walkerPos = {width / 2, height / 2};
    // the amount of time the drunkard will move
    int reps = 75;
    // the starting pos of the dunkard
    // loop for the number of reps
    for (int i = 0; i < reps; i++)
    {
        // makes the current position of the dunkard into an open spot
        level[(walkerPos.y * width) + walkerPos.x] = 1;
        bool vaildMove = false;
        while (!vaildMove)
        {
            // gets a random number 1-4
            int dir = generateNum();
            vaildMove = true;
            /*1 = up, 2 = down, 3 = left, 4 = right*/
            switch (dir)
            {
            case 1:
                if (walkerPos.y > 0)
                {
                    walkerPos.y -= 1;
                }
                break;
            case 2:
                if (walkerPos.y < height - 1)
                {
                    walkerPos.y += 1;
                }
                break;
            case 3:
                if (walkerPos.x > 0)
                {
                    walkerPos.x -= 1;
                }
                break;
            case 4:
                if (walkerPos.x < width - 1)
                {
                    walkerPos.x += 1;
                }
                break;
            default:
                vaildMove = false;
                break;
            }
        }
    }
    return level;
}