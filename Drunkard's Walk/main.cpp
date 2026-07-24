#include <iostream>
#include <string>
#include "LevelGenerator.h"

void drawLevel(int width, std::vector<int> level)
{
    // loops for the number of the tiles
    for (int i = 0; i < level.size(); i++)
    {
        // adds a new line every width number of tiles
        if (i % width == 0)
        {
            std::cout << "\n";
        }
        // prints the number at the current indesdx of the level, the added spaces are for readablity
        if (level[i] == 1)
        {
            std::cout << "\033[31m" << level[i] << "\033[0m" << "  ";
        }
        else
        {
            std::cout << level[i] << "  ";
        }
    }
}

int main()
{
    LevelGenerator generator;
    // the desired height and width of the screen
    int height;
    int width;
    int steps;

    std::cout << "Width: ";
    std::cin >> width;
    std::cout << "Height: ";
    std::cin >> height;
    std::cout << "Steps: ";
    std::cin >> steps;

    std::vector<int> level = generator.generateLevel(width, height, steps);

    drawLevel(width, level);
    system("pause");
    return 0;
}
