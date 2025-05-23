#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/audio.hpp>

sf::RectangleShape CriaLinhas
(int x, int y, int grossura, int comprimento){

	sf::RectangleShape retangulo(sf::Vector2f(grossura, comprimento));
	retangulo.setFillColor(sf::Color(0,0,0));
	//retangulo.setOutlineColor(sf::Color::Green);
	//retangulo.setOutlineThickness(2.0f);
	retangulo.setPosition(x, y);

	return retangulo;
}

void DesenhalinhasVerticais
(sf::RenderWindow &window, float x, float y){

	const int dim = 40;// dimensão de espaço entre os pontos
	const int gros = 6;// espessura das linhas
	const int space = 3*gros;// espaçamento entre as linhas

	sf::RectangleShape linhas[9][8];//matriz que desenha linhas verticais
	// Inicializa as linhas verticais
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 8; j++) {
				int posX = (i*dim)+(i*space) + 275;
				int posY = (j*dim)+(j*space) + 80 + gros;
				linhas[i][j] = CriaLinhas(posX, posY, gros, dim);
			}
		}

	sf::Color cor;
	for (int i = 0; i < 9; i++) { //linhas na vertical
		for (int j = 0; j < 8; j++) {
			if (linhas[i][j].getGlobalBounds().contains(x, y)) {// comando para pegar a posição do mouse
				cor = sf::Color(80,80,80);
			} else {
				cor = sf::Color(255,255,255);
			}

			linhas[i][j].setFillColor(cor);// desenha as linhas de acordo com o resultado
			window.draw(linhas[i][j]);
		}
	}
}

void DesenhalinhasHorizontais
(sf::RenderWindow &window, float x, float y) {

	const int dim = 40;
	const int gros = 6;
	const int space = 3*gros;

	sf::RectangleShape linhas[8][9];//matriz que desenha linhas horizontais
	// Inicializa as linhas horizontais
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 9; j++) {
				int posX = (i*dim)+(i*space) + 280 + gros;
				int posY = (j*dim)+(j*space) + 75;
				linhas[i][j] = CriaLinhas(posX, posY, dim, gros);
			}
		}

	sf::Color cor;
	for (int i = 0; i < 8; i++) { //linhas na horizontal
		for (int j = 0; j < 9; j++) {
			if (linhas[i][j].getGlobalBounds().contains(x, y)) {
				cor = sf::Color(80,80,80);
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
	const int space = 8;// espaçamento entre os pontos
	const float raio = 9.0f;// raio dos pontos

		sf::CircleShape pontos[9][9];//matriz que desenha os pontos
		// Inicializa os pontos
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					float x = (i*dim)+(i*space) + 277;// o numero só tem 5 a mais que as linhas
					float y = (j*dim)+(j*space) + 77;;// para ficar no meio delas
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
	(sf::VideoMode(WIDTH, HEIGHT), "Dots version.0.9",sf::Style::Close | sf::Style::Titlebar);

	window.setFramerateLimit(90);

	// Loop principal
	while (window.isOpen()) {

		float x = sf::Mouse::getPosition(window).x;
		float y = sf::Mouse::getPosition(window).y;

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
