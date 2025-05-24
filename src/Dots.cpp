#include <SFML/Graphics.hpp>
#include <Vector>

using namespace std;

enum Clik {
	VAZIO, CHEIO
};

class Linha {
public:
	sf::RectangleShape shape;
	Clik estado;

	Linha() :
			estado(VAZIO) { //lista de inicialização
		shape.setSize(sf::Vector2f(0, 0));
		shape.setPosition(0, 0);
		shape.setFillColor(sf::Color(0, 0, 0, 0));
	}

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

	Linha *linhaSuperior;
	Linha *linhaInferior;
	Linha *linhaEsquerda;
	Linha *linhaDireita;

	Quadrado() :
			ponto(VAZIO), linhaSuperior(nullptr), linhaInferior(nullptr), linhaEsquerda(
					nullptr), linhaDireita(nullptr) {
		shape.setSize(sf::Vector2f(0, 0));
		shape.setPosition(0, 0);
		shape.setFillColor(sf::Color(0, 0, 0, 0));
	}

	Quadrado(float x, float y, float dim) :
			linhaSuperior(nullptr), linhaInferior(nullptr), linhaEsquerda(
					nullptr), linhaDireita(nullptr) //lista de inicialização de ponteiros
	{
		shape.setSize(sf::Vector2f(dim, dim));
		shape.setPosition(x, y);
		shape.setFillColor(sf::Color(0, 0, 0, 0)); //cor transparente para se juntar a tela indenpendete de sua cor
		ponto = VAZIO;
	}

	void atualizar() {
		if (ponto == CHEIO) {
			shape.setFillColor(sf::Color::Blue);
		} else {
			shape.setFillColor(sf::Color(0, 0, 0, 0));
		}
	}

	void checarPonto() {
		// verifica as 4 linhas entorno do qudrado
		if (linhaSuperior->estado == CHEIO && linhaInferior->estado == CHEIO
				&& linhaEsquerda->estado == CHEIO
				&& linhaDireita->estado == CHEIO) {
			ponto = CHEIO;
		}

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
	Tabuleiro() {
		for (int i = 0; i < 7; i++) {
			for (int j = 0; j < 6; j++) {
				float x = (i * dim) + (i * space) + 375;
				float y = (j * dim) + (j * space) + 80 + gros;

				linhasVerticais[i][j] = Linha(x, y, gros, dim);
			}
		}

		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 7; j++) {
				float x = (i * dim) + (i * space) + 380 + gros;
				float y = (j * dim) + (j * space) + 75;

				linhasHorizontais[i][j] = Linha(x, y, dim, gros);
			}
		}
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 6; j++) {
				float x = (i * dim) + (i * space) + 375 + gros;
				float y = (j * dim) + (j * space) + 75 + gros;

				quadrados[i][j] = Quadrado(x, y, dim + gros); // + gros e pra completar o espaço faltante
			}
		}
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 6; j++) {
				// Cálculo para verificar linhas horizontais e verticais
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
				quadrados[i][j].checarPonto();
				quadrados[i][j].atualizar();
			}
		}
	}

	void checarClique(float mouseX, float mouseY) {
		for (int i = 0; i < 7; i++) {
			for (int j = 0; j < 6; j++) {
				linhasVerticais[i][j].checarClique(mouseX, mouseY);
			}
		}
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 7; j++) {
				linhasHorizontais[i][j].checarClique(mouseX, mouseY);
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

// Desenhar pontos brancos nos entre os espaços
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
			window(sf::VideoMode(1000, 600), "Dots version 1.2",
					sf::Style::Close | sf::Style::Titlebar) {
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
