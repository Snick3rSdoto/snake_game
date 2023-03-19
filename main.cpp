#include <SFML/Graphics.hpp>
#include "map.h"
// #include "view.h"
#include <iostream>
#include <vector>
#include <list>
#define speedSnake 0.05

struct Point
{
    float x;
    float y;
} po[1000];
class BlueBox
{
public:
    float dx, dy, speed;
    int w, h;
    sf::Texture texture;
    sf::Sprite sprite;
    BlueBox(sf::Image &image, float X, float Y, int W, int H)
    {
        w = W;
        h = H;
        speed = 0;
        dx = 0;
        dy = 0;
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        // sprite.setOrigin(w / 2, h / 2);
    }
    virtual void update(float time) = 0;
};

class Tail : public BlueBox
{
    int plus;
public:
    Tail(sf::Image &image, float X, float Y, int W, int H) : BlueBox(image, X, Y, W, H)
    {
        sprite.setTextureRect(sf::IntRect(w, h, w, h));
        po[1].x = X;
        po[1].y = Y;
    }

    void update(float time)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            speed = speedSnake;
        }

        if((int)po[1].x<(int)po[0].x+5 && plus <=1 && speed>0) {po[1].x+=speed*time; plus = 0; //std::cout<<"1\t\n";
        }
        else if((int)po[1].x>(int)po[0].x+5 && plus <=1 && speed>0) {po[1].x-=speed*time; plus = 0;//std::cout<<"2\t\n";
        }
        else {plus = 1; //std::cout<<"5\t\n";
        }

        if((int)po[1].y<(int)po[0].y+5 && plus>=1 && speed>0) {po[1].y+=speed*time; plus = 2;//std::cout<<"3\n";
        }
        else if((int)po[1].y>(int)po[0].y+5 && plus>=1 && speed>0) {po[1].y-=speed*time; plus = 2; //std::cout<<"4\n";
        }
        else {plus = 1; //std::cout<<"6\t\n";
        }

        sprite.setPosition(po[1].x, po[1].y);
        //std::cout<<'\t'<<plus<<'\t'<<speed<<'\t'<<po[1].x<<'\t'<<po[0].x<<'\t'<<po[1].y<<'\t'<<po[0].y<<'\n';
    }
};

class Head : public BlueBox
{
public:
    bool turnLeft = false, turnRight = false, turnUp = false, turnDown = false;
    float blockTurn = 0;
    int dir = 0;
    Head(sf::Image &image, float X, float Y, int W, int H) : BlueBox(image, X, Y, W, H)
    {
        sprite.setTextureRect(sf::IntRect(w, h, w, h));
        po[0].x = X;
        po[0].y = Y;
    }
    void control(float time)
    {
        blockTurn += speedSnake * time;

        int getX = po[0].x;
        int getY = po[0].y;

        float blockTurnX2 = float(getX) / 32;
        float blockTurnY2 = float(getY) / 32;

        float blockTurnX = blockTurnX2 - int(blockTurnX2);
        float blockTurnY = blockTurnY2 - int(blockTurnY2);

        float check = 0.03125;
        if (dir == 0)
        {
            check = 0.03125;
        }
        if (dir == 1)
        {
            check = 0;
        }
        if (dir == 2)
        {
            check = 0.03125;
        }
        if (dir == 3)
        {
            check = 0;
        }

        // std::cout<<getX<<'\t'<<getY<<'\t'<<turnLeft<<'\t'<<turnRight<<'\t'<<turnUp<<'\t'<<turnDown<<'\t'<<blockTurnX<<"   "<<blockTurnY<<"   "<<blockTurn<<'\n';

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            if (dir != 0 || turnDown || turnUp)
                turnLeft = true;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            if (dir != 1 || turnDown || turnUp)
                turnRight = true;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            if (dir != 2 || turnLeft || turnRight)
                turnUp = true;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            if (dir != 3 || turnLeft || turnRight)
                turnDown = true;
        }

        if (turnLeft && dir != 0 && blockTurnY == check && blockTurn > 2)
        {
            dir = 1;
            speed = speedSnake;
            turnLeft = false;
            blockTurn = 0;
        }
        if (turnRight && dir != 1 && blockTurnY == check && blockTurn > 2)
        {
            dir = 0;
            speed = speedSnake;
            turnRight = false;
            blockTurn = 0;
        }
        if (turnUp && dir != 2 && blockTurnX == check && blockTurn > 2)
        {
            dir = 3;
            speed = speedSnake;
            turnUp = false;
            blockTurn = 0;
        }
        if (turnDown && dir != 3 && blockTurnX == check && blockTurn > 2)
        {
            dir = 2;
            speed = speedSnake;
            turnDown = false;
            blockTurn = 0;
        }
    }

    void update(float time)
    {
        switch (dir)
        {
        case 0:
            dx = speed;
            dy = 0;
            break;
        case 1:
            dx = -speed;
            dy = 0;
            break;
        case 2:
            dx = 0;
            dy = speed;
            break;
        case 3:
            dx = 0;
            dy = -speed;
            break;
        }
        po[0].x += dx * time;
        po[0].y += dy * time;
        sprite.setPosition(po[0].x, po[0].y);
    }
    int getDx() { return dx; }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 800), "SFML works!"); // W,H
    // view.reset(sf::FloatRect(0,0,640,400));

    sf::Image map_image;
    map_image.loadFromFile("../images/map.png");
    sf::Texture map;
    map.loadFromImage(map_image);
    sf::Sprite s_map;
    s_map.setTexture(map);

    sf::Image heroImage;
    heroImage.loadFromFile("../images/snake.png");

    sf::Image tailImage;
    tailImage.loadFromFile("../images/snake.png");

    Head p(heroImage, 641, 385, 30, 30);
    // Tail t(tailImage, 614, 390, 20, 20);

    sf::Clock clock;

    int size = 1;
    std::list<BlueBox *> box;
    std::list<BlueBox *>::iterator it;

    for (int i = 1; i <= size; ++i)
    {
        box.push_back(new Tail(tailImage, 646 - 32 * i, 390, 20, 20));
    }
    bool flag = true;
    while (window.isOpen())
    {

        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 800;

        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
        {
            if (flag){
                size++;
                box.push_back(new Tail(tailImage, po[size -1].x+5, po[size -1].y+5, 20, 20));
                //std::cout<<po[size -1].x<<"X   "<<po[size -1].y<<"Y\n";
                //std::cout<<po[0].x<<"    "<<po[0].y<<"   "<<po[1].x<<"  "<<po[1].y<<'\n';
                std::cout<<p.speed<<"   "<<time<<'\n';
                flag = false;
            }
        }
        else{
            flag = true;
        }
        // std::cout<<size<<'\n';

        // if (*po[1].x!=po[0].x) {po[1]+=speedSnake;}

        // camera(p.x, p.y);
        // camera();
        p.control(time);
        p.update(time);
        // t.update(time);
        for (it = box.begin(); it != box.end(); ++it)
        {
            (*it)->update(time);
        }
        // window.setView(view);
        window.clear();

        for (int i = 0; i < HEIGHT_MAP; ++i)
        {
            for (int j = 0; j < WIDTH_MAP; ++j)
            {
                if (TileMap[i][j] == ' ')
                    s_map.setTextureRect(sf::IntRect(32, 0, 32, 32));
                if (TileMap[i][j] == 'F')
                    s_map.setTextureRect(sf::IntRect(0, 0, 32, 32));
                if (TileMap[i][j] == '0')
                    s_map.setTextureRect(sf::IntRect(64, 0, 32, 32));

                s_map.setPosition(j * 32, i * 32);
                window.draw(s_map);
            }
        }
        window.draw(p.sprite);
        // window.draw(t.sprite);
        for (it = box.begin(); it != box.end(); ++it)
        {
            window.draw((*it)->sprite);
        }
        window.display();

    }

    return 0;
}