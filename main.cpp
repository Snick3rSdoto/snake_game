#include <SFML/Graphics.hpp>
#include "map.h"
#include <iostream>
class Player {
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

    sf::Image map_image;
    map_image.loadFromFile("images/map.png");
    sf::Texture map;
    map.loadFromImage(map_image);
    sf::Sprite s_map;
    s_map.setTexture(map);

    Player p("snake.png", 641, 385, 31.0, 31.0);
    sf::Clock clock;

    bool turnLeft = false, turnRight=false, turnUp=false, turnDown=false;
    float blokTurnX = 0;
    float blokTurnY = 0;
    while (window.isOpen()){
 
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time/800;

        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
            window.close();
}
    int getX = p.x;
    int getY = p.y;
  
    blokTurnX += 0.05*time;
    blokTurnY += 0.05*time;

    //std::cout<<getX<<'\t'<<getY<<'\t'<<turnLeft<<'\t'<<turnRight<<'\t'<<turnUp<<'\t'<<turnDown<<'\t'<<blokTurnX<<'\t'<<blokTurnY<<'\n';

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


        if(turnLeft && p.dir!=0 && getY%32==1 && blokTurnX>20){
            p.dir = 1; p.speed = 0.05; 
            turnLeft = false;
            blokTurnY = 0;
        }
        if(turnRight && p.dir!=1 && getY%32==1 && blokTurnX>20){
            p.dir = 0; p.speed = 0.05; 
            turnRight = false;
            blokTurnY = 0;
        }
        if(turnUp && p.dir!=2 && getX%32==1 && blokTurnY>20){
            p.dir = 3; p.speed = 0.05; 
            turnUp = false;
            blokTurnX = 0;
        }
        if(turnDown && p.dir!=3 && getX%32==1 && blokTurnY>20){
            p.dir = 2; p.speed = 0.05; 
            turnDown = false;
            blokTurnX = 0;
        }


    p.update(time);

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