#include <iostream>
#include <string>
#include "LevelGenerator.h"

// the desired height and width of the screen
int height = 10;
int width = 20;
std::string levelRender;

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
        std::cout << level[i] << "  ";
    }
}

int main()
{
    LevelGenerator generator;
    std::vector<int> level = generator.generateLevel(width, height);

    drawLevel(width, level);
    system("pause");
    return 0;
}
