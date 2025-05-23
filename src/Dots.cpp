#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/audio.hpp>

enum Clik{
	VAZIO,CHEIO
};

void Eventos(sf::RenderWindow *window){
	sf::Event event;

			while ((*window).pollEvent(event)) {

				if (event.type == sf::Event::Closed)
					(*window).close();

			}
}

sf::RectangleShape CriaLinhas(int x, int y, int grossura, int comprimento) {

	sf::RectangleShape retangulo(sf::Vector2f(grossura, comprimento));
	retangulo.setFillColor(sf::Color(0, 0, 0));
	retangulo.setOutlineColor(sf::Color::Green);
	retangulo.setOutlineThickness(2.0f);
	retangulo.setPosition(x, y);

	return retangulo;
}

sf::CircleShape CriaPonto(float x, float y, float raio) {
	sf::CircleShape ponto(raio);
	ponto.setFillColor(sf::Color::Black);
	ponto.setPosition(x - raio, y - raio); // para centralizar
	return ponto;
}

void DesenhalinhasVerticais(sf::RenderWindow &window,Clik (&matriz)[13][13], float x, float y) {

	const int dim = 40;	// dimensão de espaço das linhas
	const int gros = 8;	// grossura das linhas
	const int space = 3 * gros;	// espaçamento entre as linhas

	sf::RectangleShape linhas[7][6];	//matriz que desenha linhas verticais
	// Inicializa as linhas verticais
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 6; j++) {
			int posX = (i * dim) + (i * space) + 375;
			int posY = (j * dim) + (j * space) + 80 + gros;//5 a mais que as linhas verticais para ter espaço em branco entre eles

			matriz[i][j] = VAZIO;
			linhas[i][j] = CriaLinhas(posX, posY, gros, dim);
		}
	}

	sf::Color cor;
	for (int i = 0; i < 7; i++) { //linhas na vertical
		for (int j = 0; j < 6; j++) {
			if (linhas[i][j].getGlobalBounds().contains(x, y)) { // comando para pegar a posição do mouse
				cor = sf::Color(80, 80, 80);
			} else {
				cor = sf::Color(255, 255, 255);
			}

			linhas[i][j].setFillColor(cor); // desenha as linhas de acordo com o resultado
			window.draw(linhas[i][j]);
		}
	}
}

void DesenhalinhasHorizontais(sf::RenderWindow &window,Clik (&matriz)[13][13], float x, float y) {

	const int dim = 40;
	const int gros = 8;
	const int space = 3 * gros;

	sf::RectangleShape linhas[6][7]; //matriz que desenha linhas horizontais
	// Inicializa as linhas horizontais
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 7; j++) {
			int posX = (i * dim) + (i * space) + 380 + gros;
			int posY = (j * dim) + (j * space) + 75;


			matriz[i+7][j+6] = VAZIO; //gambiarra para colocacar todas as linhas na mesma matriz
			linhas[i][j] = CriaLinhas(posX, posY, dim, gros);
		}
	}

	sf::Color cor;
	for (int i = 0; i < 6; i++) { //linhas na horizontal
		for (int j = 0; j < 7; j++) {
			if (linhas[i][j].getGlobalBounds().contains(x, y)) {
				cor = sf::Color(80, 80, 80);
			} else {
				cor = sf::Color::White;
			}

			linhas[i][j].setFillColor(cor);
			window.draw(linhas[i][j]);
		}
	}
}

void DesenhaPontos(sf::RenderWindow &window) {
	const int dim = 50; // dimensão de espaço entre os pontos
	const int space = 14; // espaçamento entre os pontos
	const float raio = 14.0f; // raio dos pontos
	const int gros = 3;	// grossura das linhas pela metade para centralizar

	sf::CircleShape pontos[7][7]; //matriz que desenha os pontos
	// Inicializa os pontos
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			float x = (i * dim) + (i * space) + 375 + gros;
			float y = (j * dim) + (j * space) + 75 + gros;;
			;		// para ficar no meio delas
			pontos[i][j] = CriaPonto(x, y, raio);
		}
	}
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			window.draw(pontos[i][j]);
		}
	}

}

int main() {

	const int HEIGHT = 600;
	const int WIDTH = 1000;		//dimenção da tela

	//janela do jogo
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Dots version.0.9",
			sf::Style::Close | sf::Style::Titlebar);

	window.setFramerateLimit(90);

	// Loop principal
	while (window.isOpen()) {

		float mouseX = sf::Mouse::getPosition(window).x;
		float mouseY = sf::Mouse::getPosition(window).y;

		Clik matriz[13][13];

		Eventos(&window);

		window.clear(sf::Color::White);

		DesenhalinhasVerticais(window,matriz, mouseX, mouseY);
		DesenhalinhasHorizontais(window,matriz, mouseX, mouseY);
		DesenhaPontos(window);

		window.display();
	}
	return 0;
}
