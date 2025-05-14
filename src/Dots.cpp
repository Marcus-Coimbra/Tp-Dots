#include <iostream>
#include <SFML/Graphics.hpp>

int main(){

    sf::RenderWindow window(sf::VideoMode(400, 300), "Dots version.0.0.1");

    // Loop principal

    while (window.isOpen()){

        sf::Event event;

        while (window.pollEvent(event)){

            if (event.type == sf::Event::Closed)
                window.close();

        }

        window.clear(sf::Color::Black); // fundo preto
        window.display();
    }
    return 0;
}