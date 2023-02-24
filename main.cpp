//main222
#include <SFML/Graphics.hpp>
#include "map.h"
class Player{
public:
float x,y,w,h,dx, dy, speed = 0;
int dir = 0;
sf::String File;
sf::Image image;
sf::Texture texture;
sf::Sprite sprite;

Player(sf::String F, int X, int Y, float W, float H){
File = F;
w = W; h = H;
image.loadFromFile("images/" + File);
image.createMaskFromColor(sf::Color(41, 33, 59));
texture.loadFromImage(image);
sprite.setTexture(texture);
x = X; y = Y;
sprite.setTextureRect(sf::IntRect(w,h,w,h));
}

void update(float time){
        switch (dir){
        case 0: dx = speed; dy = 0; break;
        case 1: dx = -speed; dy = 0; break;
        case 2: dx = 0; dy = speed; break;
        case 3: dx = 0; dy = -speed; break;
    }
    x += dx*time;
    y += dy*time;
    speed = 0;
    sprite.setPosition(x,y);
}
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 800), "SFML works!"); //(W, H)

    sf::Image map_image;
    map_image.loadFromFile("images/map.png");
    sf::Texture map;
    map.loadFromImage(map_image);
    sf::Sprite s_map;
    s_map.setTexture(map);

    Player p("hero.png", 250, 250, 96.0, 96.0);

    float CurrentFrame = 0;
    sf::Clock clock;

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time/800;
      
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            p.dir = 1; p.speed = 0.1;
            CurrentFrame+=0.01*time;
            if (CurrentFrame >= 3) {CurrentFrame -= 3;}
            p.sprite.setTextureRect(sf::IntRect(96*int(CurrentFrame),96,96,96));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            p.dir = 0; p.speed = 0.1;
            CurrentFrame+=0.01*time;
            if (CurrentFrame >= 3) {CurrentFrame -= 3;}
            p.sprite.setTextureRect(sf::IntRect(96*int(CurrentFrame),192,96,96));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            p.dir = 3; p.speed = 0.1;
            CurrentFrame+=0.01*time;
            if (CurrentFrame >= 3) {CurrentFrame -= 3;}
            p.sprite.setTextureRect(sf::IntRect(96*int(CurrentFrame),288,96,96));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            p.dir = 2; p.speed = 0.1;
            CurrentFrame+=0.01*time;
            if (CurrentFrame >= 3) {CurrentFrame -= 3;}
            p.sprite.setTextureRect(sf::IntRect(96*int(CurrentFrame),0,96,96));
        }
        p.update(time);
        window.clear();


for(int i=0; i<HEIGHT_MAP; ++i){
for(int j=0; j<WIDTH_MAP; ++j){
    if (TileMap[i][j]==' ') s_map.setTextureRect(sf::IntRect(32, 0, 32,32));
    if (TileMap[i][j]=='F') s_map.setTextureRect(sf::IntRect(0, 0, 32,32));
    if (TileMap[i][j]=='0') s_map.setTextureRect(sf::IntRect(64, 0, 32,32));

    s_map.setPosition(j*32, i*32);
    window.draw(s_map);
}
}

        window.draw(p.sprite);
        window.display();
    }

    return 0;
}