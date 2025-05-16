#include <iostream>
#include <SFML/Graphics.hpp>

sf::RectangleShape criaRetangulo(int x,int y,int width,int heigth){
	sf::RectangleShape Retangle(sf::Vector2f(width, heigth));
	sf::setFillColor(sf::Color::Green);

}

enum Estados{
	VAZIO,CHEIO
};

int main() {

	const int Height = 500;
	const int Width = 500;
	const int dim = 50;

	sf::RenderWindow window(sf::VideoMode(Width, Height), "Dots version.0.0.1",
			sf::Style::Close | sf::Style::Titlebar); // so pro cara não estender a tela...
	
	window.setFramerateLimit(90);

	sf::RectangleShape boxes[10][10];
	Estados matriz[10][10];

		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; ++j) {
				boxes[i][j] = criaRetangulo(i,j,dim,dim*2);
				matriz[i][j] = VAZIO;
			}
		}

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
