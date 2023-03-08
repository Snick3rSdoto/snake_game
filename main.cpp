#include <SFML/Graphics.hpp>
#include "map.h"
//#include "view.h"
#include <iostream>
#define speedSnake 0.05

// class BlueBox {
//     float dx, dy, x, y, speed;
//     int w, h;
//     sf::Texture texture;
//     sf::Sprite sprite;
//     sf::String name;
//     BlueBox (sf::Image &image, float X, float Y, int W, int H, sf::String Name){
//         x = X; y = Y; w = W; h = H; name = Name;
//         speed = 0; dx = 0; dy = 0;
//         texture.loadFromImage(image);
//         sprite.setTexture(texture);
//         //sprite.setOrigin(w / 2, h / 2);
//     }
// };

class Player{
    public:
    float x, y, w, h, dx, dy, speed = 0;
    int dir = 0;
    sf::String File;
    sf::Image image;
    sf::Texture texture;
    sf::Sprite sprite;
    Player(sf::String F, int X, int Y, float W, float H){
        File = F;
        w = W; h = H;
        image.loadFromFile("images/" + File);
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        x = X; y = Y;
        sprite.setTextureRect(sf::IntRect(w,h,w,h));
    }
void update(float time){
    switch (dir){
        case 0: dx = speed; dy = 0;  break;
        case 1: dx = -speed; dy = 0; break;
        case 2: dx = 0; dy = speed;  break;
        case 3: dx = 0; dy = -speed; break;
    }
    x += dx*time;
    y += dy*time;
    sprite.setPosition(x,y);
}
 int getDx() {return dx;}
};

int main(){
    sf::RenderWindow window(sf::VideoMode(1280, 800), "SFML works!"); //W,H
    //view.reset(sf::FloatRect(0,0,640,400));



    sf::Image map_image;
    map_image.loadFromFile("images/map.png");
    sf::Texture map;
    map.loadFromImage(map_image);
    sf::Sprite s_map;
    s_map.setTexture(map);

    Player p("snake.png", 641, 385, 30.0, 30.0);
    sf::Clock clock;

    bool turnLeft = false, turnRight=false, turnUp=false, turnDown=false;
        float blockTurn = 0;
    while (window.isOpen()){
 
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time/800;

        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
            window.close();
}

    blockTurn += speedSnake*time;

    int getX = p.x;
    int getY = p.y;
  
    float blockTurnX2 = float(getX)/32;
    float blockTurnY2 = float(getY)/32;

    float blockTurnX = blockTurnX2 - int(blockTurnX2);
    float blockTurnY = blockTurnY2 - int(blockTurnY2);

    float check = 0.03125;
    if(p.dir==0){check = 0.03125;}
    if(p.dir==1){check = 0;}
    if(p.dir==2){check = 0.03125;}
    if(p.dir==3){check = 0;}


    //std::cout<<getX<<'\t'<<getY<<'\t'<<turnLeft<<'\t'<<turnRight<<'\t'<<turnUp<<'\t'<<turnDown<<'\t'<<blockTurnX<<"   "<<blockTurnY<<"   "<<blockTurn<<'\n';

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        if(p.dir!=0 || turnDown || turnUp)
        turnLeft = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        if(p.dir!=1 || turnDown || turnUp)
        turnRight = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        if(p.dir!=2 || turnLeft || turnRight)
        turnUp = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        if(p.dir!=3 || turnLeft || turnRight)
        turnDown = true;
    }


        if(turnLeft && p.dir!=0 && blockTurnY==check && blockTurn>1){
            p.dir = 1; p.speed = speedSnake; 
            turnLeft = false;
            blockTurn = 0;
        }
        if(turnRight && p.dir!=1 && blockTurnY==check && blockTurn>1){
            p.dir = 0; p.speed = speedSnake; 
            turnRight = false;
            blockTurn = 0;
        }
        if(turnUp && p.dir!=2 && blockTurnX==check && blockTurn>1){
            p.dir = 3; p.speed = speedSnake; 
            turnUp = false;
            blockTurn = 0;
        }
        if(turnDown && p.dir!=3 && blockTurnX==check && blockTurn>1){
            p.dir = 2; p.speed = speedSnake; 
            turnDown = false;
            blockTurn = 0;
        }
    //camera(p.x, p.y);
    //camera();

    p.update(time);
    //window.setView(view);
    window.clear();

    for (int i = 0; i< HEIGHT_MAP; ++i){
        for (int j = 0; j<WIDTH_MAP; ++j){
            if (TileMap[i][j] == ' ') s_map.setTextureRect(sf::IntRect(32, 0, 32, 32));
            if (TileMap[i][j] == 'F') s_map.setTextureRect(sf::IntRect(0, 0, 32, 32));
            if (TileMap[i][j] == '0') s_map.setTextureRect(sf::IntRect(64, 0, 32, 32));

            s_map.setPosition(j *  32, i * 32);
            window.draw(s_map);
        }
    }
    window.draw(p.sprite);
    window.display();
}

return 0;
}