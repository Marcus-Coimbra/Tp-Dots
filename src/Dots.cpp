#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstring>
#include <iostream>

using namespace std;

enum Clik {
	VAZIO, CHEIO
};

class Linha {
public:
	sf::RectangleShape shape;
	Clik estado;

	Linha() : estado(VAZIO) {
		shape.setSize(sf::Vector2f(0, 0));
		shape.setPosition(0, 0);
		shape.setFillColor(sf::Color(0, 0, 0, 0));
	}

	Linha(float x, float y, float width, float height) {
		shape.setSize(sf::Vector2f(width, height));
		shape.setPosition(x, y);
		shape.setFillColor(sf::Color(0, 0, 0, 0));
		estado = VAZIO;
	}

	void atualizar(float mouseX, float mouseY) {
		if (shape.getGlobalBounds().contains(mouseX, mouseY)) {
			if (estado == CHEIO) {
				shape.setFillColor(sf::Color::Black);
			} else {
				shape.setFillColor(sf::Color(0, 0, 0, 100));
			}
		} else {
			if (estado == CHEIO) {
				shape.setFillColor(sf::Color::Black);
			} else {
				shape.setFillColor(sf::Color(0, 0, 0, 0));
			}
		}
	}

	bool checarClique(float mouseX, float mouseY) {
		if (shape.getGlobalBounds().contains(mouseX, mouseY) && estado == VAZIO) {
			estado = CHEIO;
			return true; // Retorna true se foi clicado com sucesso
		}
		return false;
	}

	void desenhar(sf::RenderWindow &window) {
		window.draw(shape);
	}
};

class Quadrado {
public:
	sf::RectangleShape shape;
	Clik ponto;

	Linha *linhaSuperior;
	Linha *linhaInferior;
	Linha *linhaEsquerda;
	Linha *linhaDireita;

	Quadrado() : ponto(VAZIO), linhaSuperior(nullptr), linhaInferior(nullptr), linhaEsquerda(nullptr), linhaDireita(nullptr) {
		shape.setSize(sf::Vector2f(0, 0));
		shape.setPosition(0, 0);
		shape.setFillColor(sf::Color(0, 0, 0, 0));
	}

	Quadrado(float x, float y, float dim) : linhaSuperior(nullptr), linhaInferior(nullptr), linhaEsquerda(nullptr), linhaDireita(nullptr) {
		shape.setSize(sf::Vector2f(dim, dim));
		shape.setPosition(x, y);
		shape.setFillColor(sf::Color(0, 0, 0, 0));
		ponto = VAZIO;
	}

	void atualizar() {
		if (ponto == CHEIO) {
			shape.setFillColor(sf::Color::Blue);
		} else {
			shape.setFillColor(sf::Color(0, 0, 0, 0));
		}
	}

	bool checarPonto() {
		if (ponto == VAZIO && linhaSuperior->estado == CHEIO && linhaInferior->estado == CHEIO &&
			linhaEsquerda->estado == CHEIO && linhaDireita->estado == CHEIO) {
			ponto = CHEIO;
			return true; // Retorna true se fez ponto
		}
		return false;
	}

	void desenhar(sf::RenderWindow &window) {
		window.draw(shape);
	}
};

class Tabuleiro {
private:
	Linha linhasVerticais[7][6];
	Linha linhasHorizontais[6][7];

	Quadrado quadrados[6][6];

	const int dim = 50;
	const int gros = 8;
	const int space = 2 * gros;

public:
	// Sons
	sf::SoundBuffer bufferClique;
	sf::SoundBuffer bufferPonto;
	sf::Sound somClique;
	sf::Sound somPonto;

	Tabuleiro() {
		// Carregar sons
		if (!bufferClique.loadFromFile("click.ogg")) {
			cout << "Erro ao carregar click.ogg\n";
		}
		if (!bufferPonto.loadFromFile("ponto.ogg")) {
			cout << "Erro ao carregar ponto.ogg\n";
		}
		somClique.setBuffer(bufferClique);
		somPonto.setBuffer(bufferPonto);

		// Inicializar linhas verticais
		for (int i = 0; i < 7; i++) {
			for (int j = 0; j < 6; j++) {
				float x = (i * dim) + (i * space) + 375;
				float y = (j * dim) + (j * space) + 80 + gros;
				linhasVerticais[i][j] = Linha(x, y, gros, dim);
			}
		}

		// Inicializar linhas horizontais
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 7; j++) {
				float x = (i * dim) + (i * space) + 380 + gros;
				float y = (j * dim) + (j * space) + 75;
				linhasHorizontais[i][j] = Linha(x, y, dim, gros);
			}
		}

		// Inicializar quadrados
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 6; j++) {
				float x = (i * dim) + (i * space) + 375 + gros;
				float y = (j * dim) + (j * space) + 75 + gros;
				quadrados[i][j] = Quadrado(x, y, dim + gros);
			}
		}

		// Atribuir linhas aos quadrados
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 6; j++) {
				quadrados[i][j].linhaSuperior = &linhasHorizontais[i][j];
				quadrados[i][j].linhaInferior = &linhasHorizontais[i][j + 1];
				quadrados[i][j].linhaEsquerda = &linhasVerticais[i][j];
				quadrados[i][j].linhaDireita = &linhasVerticais[i + 1][j];
			}
		}
	}

	void atualizar(float mouseX, float mouseY) {
		for (int i = 0; i < 7; i++) {
			for (int j = 0; j < 6; j++) {
				linhasVerticais[i][j].atualizar(mouseX, mouseY);
			}
		}
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 7; j++) {
				linhasHorizontais[i][j].atualizar(mouseX, mouseY);
			}
		}
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 6; j++) {
				quadrados[i][j].atualizar();
			}
		}
	}

	void checarClique(float mouseX, float mouseY) {
		bool clicouLinha = false;
		for (int i = 0; i < 7; i++) {
			for (int j = 0; j < 6; j++) {
				if (linhasVerticais[i][j].checarClique(mouseX, mouseY)) {
					clicouLinha = true;
				}
			}
		}
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 7; j++) {
				if (linhasHorizontais[i][j].checarClique(mouseX, mouseY)) {
					clicouLinha = true;
				}
			}
		}

		// Se clicou numa linha, tocar som
		if (clicouLinha) {
			somClique.play();
		}

		// Verificar pontos
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 6; j++) {
				if (quadrados[i][j].checarPonto()) {
					somPonto.play();
				}
			}
		}
	}

	void desenhar(sf::RenderWindow &window) {
		for (int i = 0; i < 7; i++) {
			for (int j = 0; j < 6; j++) {
				linhasVerticais[i][j].desenhar(window);
			}
		}
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 7; j++) {
				linhasHorizontais[i][j].desenhar(window);
			}
		}
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 6; j++) {
				quadrados[i][j].desenhar(window);
			}
		}

		// Desenhar pontos brancos
		const float raio = 10.0f;
		for (int i = 0; i < 7; i++) {
			for (int j = 0; j < 7; j++) {
				float x = (i * dim) + (i * space) + 379;
				float y = (j * dim) + (j * space) + 79;
				sf::CircleShape ponto(raio);
				ponto.setFillColor(sf::Color(255, 255, 255));
				ponto.setPosition(x - raio, y - raio);
				window.draw(ponto);
			}
		}
	}
};

class Jogo {
private:
	sf::RenderWindow window;
	Tabuleiro tabuleiro;

public:
	Jogo() : window(sf::VideoMode(1000, 600), "Dots version 1.3", sf::Style::Close | sf::Style::Titlebar) {
		window.setFramerateLimit(90);
	}

	void executar() {
		while (window.isOpen()) {
			sf::Event event;
			float mouseX = sf::Mouse::getPosition(window).x;
			float mouseY = sf::Mouse::getPosition(window).y;

			tabuleiro.atualizar(mouseX, mouseY);

			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed)
					window.close();

				if (event.type == sf::Event::MouseButtonPressed)
					tabuleiro.checarClique(mouseX, mouseY);
			}

			window.clear(sf::Color(133, 199, 194));
			tabuleiro.desenhar(window);
			window.display();
		}
	}
};

int main() {
	Jogo jogo;
	jogo.executar();
	return 0;
}
