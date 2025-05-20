#include <iostream>
#include <SFML/Graphics.hpp>

enum Click{
	VAZIO, CHEIO
};

int main() {

	const int Height = 500;
	const int Width = 500;

	sf::RenderWindow window(sf::VideoMode(Width, Height), "Dots version.0.0.1",
			sf::Style::Close | sf::Style::Titlebar); // so pro cara não estender a tela...

	window.setFramerateLimit(90);

	// Loop principal
	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed)
				window.close();

		}

		window.clear(sf::Color::Black); // fundo preto
		window.display();
	}
	return 0;
}
