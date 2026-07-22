#include <array>
#include <iostream>
#include <string>
#include <random>
#include <chrono>


// the desired height and width of the screen
constexpr int height = 10;
constexpr int width = 20;
constexpr int levelSize = height * width;
int level[levelSize] = {};
std::string levelRender;
struct Vector2{int x; int y;};

void drawLevel(){
    // loops for the number of the tiles
    for(int i = 0; i < levelSize; i++){
        // adds a new line every 10 tiles
        if(i % width == 0){
            std::cout<<"\n";
        }
        // prints the number at the current index of the level, spaces for readablity
        std::cout<<level[i]<<"  ";
    }
}


int main(){
    // random number generation
    std::random_device rng;
    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::mt19937 gen(rng() ^ seed);
    std::uniform_int_distribution<int> moveDist(1,4);

    // starts in the center
    Vector2 walkerPos = {width/2,height/2};
    // the amount of time the drunkard will move
    int reps = 75;
    // the starting pos of the dunkard
    // loop for the number of reps
    for(int i = 0; i < reps; i++){
        // makes the current position of the dunkard into an open spot
        level[(walkerPos.y * width) + walkerPos.x] = 1;
        bool vaildMove = false;
        while(!vaildMove){
            // gets a random number 1-4
            int dir = moveDist(gen);
            vaildMove = true;
            /*1 = up, 2 = down, 3 = left, 4 = right*/
            switch(dir){
                case 1:
                    if(walkerPos.y > 0){
                        walkerPos.y -= 1;
                    } 
                    break;
                case 2:
                    if(walkerPos.y < height - 1){
                        walkerPos.y += 1;
                    }
                    break;
                case 3:
                    if(walkerPos.x > 0){
                        walkerPos.x -= 1;
                    }
                    break;
                case 4:
                    if(walkerPos.x < width - 1){
                        walkerPos.x += 1;
                    }
                    break;
                default:
                    vaildMove = false;
                    break;
            }
        }
    }
    drawLevel();
    return 0;
}
