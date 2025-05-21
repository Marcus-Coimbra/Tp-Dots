#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/audio.hpp>

enum Click {
	VAZIO, CHEIO
};

sf::RectangleShape CriaLinhas(int x, int y, int width, int height) {

	sf::RectangleShape retangulo(sf::Vector2f(width, height));
	retangulo.setFillColor(sf::Color::Black);
	retangulo.setOutlineColor(sf::Color::Green);
	retangulo.setOutlineThickness(2.0f);
	retangulo.setPosition(x, y);

	return retangulo;
}

void Desenhalinhas(sf::RenderWindow &window, sf::RectangleShape linhas[8][8],
		float x, float y) {

	sf::Color cor;
	for (int i = 0; i < 8; i++) { //linhas na horizontal
		for (int j = 0; j < 8; j++) {
			if (linhas[i][j].getGlobalBounds().contains(x, y)) {
				cor = sf::Color::Yellow;
			} else {
				cor = sf::Color::Black;
			}

			linhas[i][j].setFillColor(cor);
			window.draw(linhas[i][j]);
		}
	}
}

int main() {

	const int HEIGHT = 500;
	const int WIDTH = 800;

	const int comprimento = 50;
	const int espessura = 5;

	//janela do jogo
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Dots version.0.0.1",
			sf::Style::Close | sf::Style::Titlebar); // so pro cara não estender a tela...
	window.setFramerateLimit(90);

	sf::RectangleShape linhasVertical[8][8]; //matriz que desenha linhas verticais
	sf::RectangleShape linhasHorizontal[8][8]; //matriz que desenha linhas horizontais
	 matriz[8][8];
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			linhasVertical[8][8]
		}
	}

	// Loop principal
	while (window.isOpen()) {

		float x = sf::Mouse::getPosition().x;
		float y = sf::Mouse::getPosition().y;

		sf::Event event;

		while (window.pollEvent(event)) {

			CriaLinhas(x, y, espessura, comprimento);

			if (event.type == sf::Event::Closed)
				window.close();

		}

		window.clear(sf::Color::White); // fundo preto
		window.display();
	}
	return 0;
}
