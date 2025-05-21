#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/audio.hpp>

sf::RectangleShape CriaLinhas
(int x, int y, int grossura, int comprimento) {

	sf::RectangleShape retangulo(sf::Vector2f(grossura, comprimento));
	retangulo.setFillColor(sf::Color::Black);
	retangulo.setOutlineColor(sf::Color::Green);
	retangulo.setOutlineThickness(1.0f);
	retangulo.setPosition(x, y);

	return retangulo;
}

void DesenhalinhasVerticais
(sf::RenderWindow &window, sf::RectangleShape linhas[9][8],float x, float y) {

	sf::Color cor;
	for (int i = 0; i < 9; i++) { //linhas na horizontal
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

void DesenhalinhasHorizontais
(sf::RenderWindow &window, sf::RectangleShape linhas[8][9],float x, float y) {

	sf::Color cor;
	for (int i = 0; i < 8; i++) { //linhas na horizontal
		for (int j = 0; j < 9; j++) {
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

	const int dim = 50;
	const int gros = 5;

	//janela do jogo
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Dots version.0.2",
			sf::Style::Close | sf::Style::Titlebar); // so pro cara não estender a tela...
	window.setFramerateLimit(90);

	sf::RectangleShape linhasVertical[9][8]; //matriz que desenha linhas verticais
	sf::RectangleShape linhasHorizontal[8][9]; //matriz que desenha linhas horizontais
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 8; j++) {
			linhasVertical[i][j] = CriaLinhas((i * dim)+185, (j * dim)+40, gros, dim);
		}
	}
	for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 9; j++) {
				linhasHorizontal[i][j] = CriaLinhas((i * dim)+185, (j * dim)+40, dim, gros);
			}
		}

	// Loop principal
	while (window.isOpen()) {

		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		float x = static_cast<float>(mousePos.x);
		float y = static_cast<float>(mousePos.y);

		sf::Event event;

		while (window.pollEvent(event)) {

			//if(event.type == sf::Event::MouseButtonPressed){
				//int linha = sf::Mouse::getPosition().x / dim;
				//int coluna = sf::Mouse::getPosition().y / dim;
			//}

			if (event.type == sf::Event::Closed)
				window.close();

		}

		window.clear(sf::Color::Black);

		DesenhalinhasVerticais(window, linhasVertical, x, y);
		DesenhalinhasHorizontais(window, linhasHorizontal, x, y);

		window.display();
	}
	return 0;
}
