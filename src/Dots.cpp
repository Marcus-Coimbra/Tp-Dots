#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/audio.hpp>

sf::RectangleShape CriaLinhas
(int x, int y, int grossura, int comprimento){

	sf::RectangleShape retangulo(sf::Vector2f(grossura, comprimento));
	retangulo.setFillColor(sf::Color::Black);
	retangulo.setOutlineColor(sf::Color::Green);
	retangulo.setOutlineThickness(2.0f);
	retangulo.setPosition(x, y);

	return retangulo;
}

void DesenhalinhasVerticais
(sf::RenderWindow &window, float x, float y){

	const int dim = 50;// dimensão de espaço entre os pontos
	const int gros = 10;// espessura das linhas
	const int space = 5;// espaçamento entre as linhas

	sf::RectangleShape linhas[9][8];//matriz que desenha linhas verticais
	// Inicializa as linhas verticais
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 8; j++) {
				int posX = (i * (dim + space)) + 275;//275 é a tela - o espaço ultilizado /2
				int posY = (j * (dim + space)) + 75;//75 é a mesma coisa só que em y
				linhas[i][j] = CriaLinhas(posX, posY, gros, dim);
			}
		}

	sf::Color cor;
	for (int i = 0; i < 9; i++) { //linhas na vertical
		for (int j = 0; j < 8; j++) {
			if (linhas[i][j].getGlobalBounds().contains(x, y)) {// comando para pegar a posição do mouse
				cor = sf::Color::Yellow;
			} else {
				cor = sf::Color::White;
			}

			linhas[i][j].setFillColor(cor);// desenha as linhas de acordo com o resultado
			window.draw(linhas[i][j]);
		}
	}
}

void DesenhalinhasHorizontais
(sf::RenderWindow &window, float x, float y) {

	const int dim = 50;
	const int gros = 10;
	const int space = 5;

	sf::RectangleShape linhas[8][9];//matriz que desenha linhas horizontais
	// Inicializa as linhas horizontais
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 9; j++) {
				int posX = (i * (dim + space)) + 275;
				int posY = (j * (dim + space)) + 75;
				linhas[i][j] = CriaLinhas(posX, posY, dim, gros);
			}
		}

	sf::Color cor;
	for (int i = 0; i < 8; i++) { //linhas na horizontal
		for (int j = 0; j < 9; j++) {
			if (linhas[i][j].getGlobalBounds().contains(x, y)) {
				cor = sf::Color::Yellow;
			} else {
				cor = sf::Color::White;
			}

			linhas[i][j].setFillColor(cor);
			window.draw(linhas[i][j]);
		}
	}
}

sf::CircleShape CriaPonto
(float x, float y, float raio) {
	sf::CircleShape ponto(raio);
	ponto.setFillColor(sf::Color::Black);
	ponto.setPosition(x - raio, y - raio); // para centralizar
	return ponto;
}

void DesenhaPontos
(sf::RenderWindow &window){
	const int dim = 50;// dimensão de espaço entre os pontos
	const int space = 5;// espaçamento entre os pontos
	const float raio = 10.0f;// raio dos pontos

		sf::CircleShape pontos[9][9];//matriz que desenha os pontos
		// Inicializa os pontos
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					float x = (i * (dim + space)) + 280;// o numero só tem 5 a mais que as linhas
					float y = (j * (dim + space)) + 80;// para ficar no meio delas
					pontos[i][j] = CriaPonto(x, y, raio);
				}
			}
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			window.draw(pontos[i][j]);
		}
	}

}

int main() {

	const int HEIGHT = 600;
	const int WIDTH = 1000;//dimenção da tela

	//janela do jogo
	sf::RenderWindow window
	(sf::VideoMode(WIDTH, HEIGHT), "Dots version.1.2",sf::Style::Close | sf::Style::Titlebar);

	window.setFramerateLimit(90);

	// Loop principal
	while (window.isOpen()) {

		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		float x = static_cast<float>(mousePos.x);
		float y = static_cast<float>(mousePos.y);

		sf::Event event;

		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed)
				window.close();

		}

		window.clear(sf::Color::White);

		DesenhalinhasVerticais(window, x, y);
		DesenhalinhasHorizontais(window, x, y);
		DesenhaPontos(window);

		window.display();
	}
	return 0;
}
