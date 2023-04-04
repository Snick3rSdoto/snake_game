#include <SFML/Graphics.hpp>
const int HEIGHT_MAP = 25;
const int WIDTH_MAP = 40;
//2
sf::String TileMap[HEIGHT_MAP] = {
    "0000000000000000000000000000000000000000",
    "0                                      0",
    "0                                      0",
    "0                                      0",
    "0                                      0",
    "0                                      0",
    "0                                      0",
    "0                                      0",
    "0                                      0",
    "0                                      0",
    "0                                      0",
    "0                                      0",
    "0                         0            0",
    "0                                      0",
    "0                                      0",
    "0                                      0",
    "0                                      0",
    "0                                      0",
    "0                                      0",
    "0                                      0",
    "0                                      0",
    "0                                      0",
    "0                                      0",
    "0                                      0",
    "0000000000000000000000000000000000000000",
};

void randomMapGenerate() {

    int randomElementX = 0;
    int randomElementY = 0;
    srand(time(0));
    int countStone = 12;

    while (countStone) {
        randomElementX = 1 + rand() % (WIDTH_MAP - 1);
        randomElementY = 1 + rand() % (HEIGHT_MAP -1);
        if (TileMap[randomElementY][randomElementX] == ' ') {
            TileMap[randomElementY][randomElementX] = 'F';
            countStone--;
        }
    }
}
void randomMapGenerate2() {

    int randomElementX = 0;
    int randomElementY = 0;
    srand(time(0));
    int countStone2 = 1;

    while (countStone2) {
        randomElementX = 1 + rand() % (WIDTH_MAP - 1);
        randomElementY = 1 + rand() % (HEIGHT_MAP -1);
        if (TileMap[randomElementY][randomElementX] == ' ') {
            TileMap[randomElementY][randomElementX] = 'F';
            countStone2--;
        }
    }
}
