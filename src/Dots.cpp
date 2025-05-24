#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;

enum Clik {
	VAZIO, CHEIO
};

class Linha {
public:
	sf::RectangleShape shape;
	Clik estado;

	Linha(float x, float y, float width, float height) {
		shape.setSize(sf::Vector2f(width, height));
		shape.setPosition(x, y);
		shape.setFillColor(sf::Color(0, 0, 0, 0)); //cor transparente para se juntar a tela indenpendete de sua cor
		estado = VAZIO;
	}

	void atualizar(float mouseX, float mouseY) {
		//verifica as linhas e modifica a cor de acordo com a posição do mouse
		if (shape.getGlobalBounds().contains(mouseX, mouseY)) {
			if (estado == CHEIO) {
				shape.setFillColor(sf::Color::Black);
			} else {
				shape.setFillColor(sf::Color(0, 0, 0, 100)); // semi-transparente
			}
		} else {
			if (estado == CHEIO) {
				shape.setFillColor(sf::Color::Black);
			} else {
				shape.setFillColor(sf::Color(0, 0, 0, 0)); // transparente
			}
		}
	}

	void checarClique(float mouseX, float mouseY) {
		//Se o mouse estiver sobre a linha quando clicado, muda seu estado para CHEIO
		if (shape.getGlobalBounds().contains(mouseX, mouseY)) {
			estado = CHEIO;
		}
	}

	void desenhar(sf::RenderWindow &window) {
		window.draw(shape);
	}
};

class Quadrado {
public:
	sf::RectangleShape shape;
	Clik ponto;

	Quadrado(float x, float y, float dim) {
		shape.setSize(sf::Vector2f(dim, dim));
		shape.setPosition(x, y);
		shape.setFillColor(sf::Color(0, 0, 0, 0)); //cor transparente para se juntar a tela indenpendete de sua cor
		ponto = VAZIO;
	}

	void atualizar() {
		if (1) {
			if (ponto == CHEIO) {
				shape.setFillColor(sf::Color::Blue);
			} else {
				shape.setFillColor(sf::Color(0, 0, 0, 0));
			}
		} else {
			if (ponto == CHEIO) {
				shape.setFillColor(sf::Color::Blue);
			} else {
				shape.setFillColor(sf::Color(0, 0, 0, 0)); // transparente
			}
		}
	}

	void checarPonto() {
		if (1) {

		}
	}

	void desenhar(sf::RenderWindow &window) {
		window.draw(shape);
	}
};

class Tabuleiro {
private:
	vector<Linha> linhasVerticais;
	vector<Linha> linhasHorizontais;
	vector<Quadrado> Quadrados;

	const int dim = 50;
	const int gros = 8;
	const int space = 2 * gros;

public:
	Tabuleiro() {
		for (int i = 0; i < 7; i++) {
			for (int j = 0; j < 6; j++) {
				float x = (i * dim) + (i * space) + 375;
				float y = (j * dim) + (j * space) + 80 + gros;

				Linha novaLinha(x, y, gros, dim);
				linhasVerticais.push_back(novaLinha); //cria uma linha apos a outra
			}
		}

		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 7; j++) {
				float x = (i * dim) + (i * space) + 380 + gros;
				float y = (j * dim) + (j * space) + 75;

				Linha novaLinha(x, y, dim, gros);
				linhasHorizontais.push_back(novaLinha);
			}
		}
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 6; j++) {
				float x = (i * dim) + (i * space) + 375 + gros;
				float y = (j * dim) + (j * space) + 75 + gros;

				Quadrado novoQuadrado(x, y, (dim + gros)); // + gros e pra completar o espaço faltante
				Quadrados.push_back(novoQuadrado);
			}
		}
	}

	void atualizar(float mouseX, float mouseY) {
		for (int i = 0; i < (int) linhasVerticais.size(); i++) {
			linhasVerticais[i].atualizar(mouseX, mouseY);
		}
		for (int i = 0; i < (int) linhasHorizontais.size(); i++) {
			linhasHorizontais[i].atualizar(mouseX, mouseY);
		}
		for (int i = 0; i < (int) Quadrados.size(); i++) {
			Quadrados[i].atualizar();
		}
	}

	void checarClique(float mouseX, float mouseY) {
		for (int i = 0; i < (int) linhasVerticais.size(); i++) {
			linhasVerticais[i].checarClique(mouseX, mouseY);
		}
		for (int i = 0; i < (int) linhasHorizontais.size(); i++) {
			linhasHorizontais[i].checarClique(mouseX, mouseY);
		}
		for (int i = 0; i < (int) Quadrados.size(); i++) {
			Quadrados[i].checarPonto();
		}
	}

	void desenhar(sf::RenderWindow &window) {
		for (int i = 0; i < (int) linhasVerticais.size(); i++) {
			linhasVerticais[i].desenhar(window);
		}
		for (int i = 0; i < (int) linhasHorizontais.size(); i++) {
			linhasHorizontais[i].desenhar(window);
		}
		for (int i = 0; i < (int) Quadrados.size(); i++) {
			Quadrados[i].desenhar(window);
		}

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
	Jogo() : //lista de inicialização para membro janela
			window(sf::VideoMode(1000, 600), "Dots version 0.9",
					sf::Style::Close | sf::Style::Titlebar) {
		window.setFramerateLimit(90);
	}

	void executar() {
		while (window.isOpen()) {
			sf::Event event;
			float mouseX = sf::Mouse::getPosition(window).x;
			float mouseY = sf::Mouse::getPosition(window).y;

			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed)
					window.close();

				if (event.type == sf::Event::MouseButtonPressed)
					tabuleiro.checarClique(mouseX, mouseY);
			}

			tabuleiro.atualizar(mouseX, mouseY);

			window.clear(sf::Color(143, 188, 194));
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
