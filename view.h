#include <SFML/Graphics.hpp>

sf::View view;

sf::View camera(float x, float y){
    view.setCenter(x, y);
    return view;
}


sf::View camera(){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {view.zoom(1.0100f);}
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {view.zoom(0.9000f);}

    return view;
}
