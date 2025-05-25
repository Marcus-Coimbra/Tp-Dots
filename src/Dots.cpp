#include <SFML/Graphics.hpp>
#include <cstring>

using namespace std;

enum Clik {
	VAZIO, CHEIO
};
enum EstadoPonto {
	NENHUM, JOGADOR1, JOGADOR2
};

class Linha {
public:
	sf::RectangleShape shape;
	Clik estado;

	Linha() :
			estado(VAZIO) {
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
				shape.setFillColor(sf::Color(0, 0, 0, 130));
			}
		} else {
			if (estado == CHEIO) {
				shape.setFillColor(sf::Color::Black);
			} else {
				shape.setFillColor(sf::Color(0, 0, 0, 0));
			}
		}
	}

	void checarClique(float mouseX, float mouseY) {
		if (shape.getGlobalBounds().contains(mouseX, mouseY)
				&& estado == VAZIO) {
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
	EstadoPonto ponto, turno;

	Linha *linhaSuperior;
	Linha *linhaInferior;
	Linha *linhaEsquerda;
	Linha *linhaDireita;

	Quadrado() :
			ponto(NENHUM), turno(JOGADOR1), linhaSuperior(nullptr), linhaInferior(
					nullptr), linhaEsquerda(nullptr), linhaDireita(nullptr) {
		shape.setSize(sf::Vector2f(0, 0));
		shape.setPosition(0, 0);
		shape.setFillColor(sf::Color(0, 0, 0, 0));
	}

	Quadrado(float x, float y, float dim) :
			ponto(NENHUM), turno(JOGADOR1), linhaSuperior(nullptr), linhaInferior(
					nullptr), linhaEsquerda(nullptr), linhaDireita(nullptr) {
		shape.setSize(sf::Vector2f(dim, dim));
		shape.setPosition(x, y);
		shape.setFillColor(sf::Color(0, 0, 0, 0));
	}

	void atualizar() {
		if (ponto == JOGADOR1) {
			shape.setFillColor(sf::Color::Blue);
		} else if (ponto == JOGADOR2) {
			shape.setFillColor(sf::Color::Red);
		} else {
			shape.setFillColor(sf::Color(0, 0, 0, 0));
		}
	}

	void checarPonto() {
		if (linhaSuperior->estado == CHEIO && linhaInferior->estado == CHEIO
				&& linhaEsquerda->estado == CHEIO
				&& linhaDireita->estado == CHEIO) {
			if (ponto == NENHUM) {
				ponto = turno;
			}
		}
	}

	void desenhar(sf::RenderWindow &window) {
		window.draw(shape);
	}
};

class Tabuleiro {
public:
	Linha linhasVerticais[7][6];
	Linha linhasHorizontais[6][7];
	Quadrado quadrados[6][6];

private:
	const int dim = 50;
	const int gros = 8;
	const int space = 2 * gros;

public:
	Tabuleiro() {
		for (int i = 0; i < 7; i++) {
			for (int j = 0; j < 6; j++) {
				float x = (i * dim) + (i * space) + 295;
				float y = (j * dim) + (j * space) + 80 + gros;
				linhasVerticais[i][j] = Linha(x, y, gros, dim);
			}
		}

		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 7; j++) {
				float x = (i * dim) + (i * space) + 300 + gros;
				float y = (j * dim) + (j * space) + 75;
				linhasHorizontais[i][j] = Linha(x, y, dim, gros);
			}
		}

		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 6; j++) {
				float x = (i * dim) + (i * space) + 295 + gros;
				float y = (j * dim) + (j * space) + 75 + gros;
				quadrados[i][j] = Quadrado(x, y, dim + gros);
			}
		}

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
	}

	bool checarClique(float mouseX, float mouseY, EstadoPonto turnoAtual) {
		bool clicou = false;
		for (int i = 0; i < 7; i++) {
			for (int j = 0; j < 6; j++) {
				if (linhasVerticais[i][j].shape.getGlobalBounds().contains(
						mouseX, mouseY)
						&& linhasVerticais[i][j].estado == VAZIO) {
					linhasVerticais[i][j].estado = CHEIO;
					clicou = true;
				}
			}
		}
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 7; j++) {
				if (linhasHorizontais[i][j].shape.getGlobalBounds().contains(
						mouseX, mouseY)
						&& linhasHorizontais[i][j].estado == VAZIO) {
					linhasHorizontais[i][j].estado = CHEIO;
					clicou = true;
				}
			}
		}
		return clicou;
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

		const float raio = 10.0f;
		for (int i = 0; i < 7; i++) {
			for (int j = 0; j < 7; j++) {
				float x = (i * dim) + (i * space) + 299;
				float y = (j * dim) + (j * space) + 79;
				sf::CircleShape ponto(raio);
				ponto.setFillColor(sf::Color(255, 255, 255));
				ponto.setPosition(x - raio, y - raio);
				window.draw(ponto);
			}
		}
	}
};

class Player {
public:
	EstadoPonto ponto;
	int pontuacao;
	Quadrado* quadrados[6][6];

	Player(EstadoPonto ponto) :
	    ponto(ponto), pontuacao(0) {
	}

	void AtualizaQuadrado() {
		int novosPontos = 0;
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 6; j++) {
				quadrados[i][j]->turno = ponto;

				if (quadrados[i][j]->ponto == NENHUM) {
					quadrados[i][j]->checarPonto();
					if (quadrados[i][j]->ponto == ponto) {
						novosPontos++;
					}
				}

				quadrados[i][j]->atualizar();
			}
		}
		pontuacao += novosPontos;
	}


	int getPontuacao() const {
		return pontuacao;
	}

	void setPontuacao(int p) {
		pontuacao = p;
	}
};

class Jogo {
private:
	sf::RenderWindow window;
	Tabuleiro tabuleiro;
	Player jogador1;
	Player jogador2;
	Player *jogadorAtual;

public:
	Jogo() :
			window(sf::VideoMode(1000, 600), "Dots version 1.2",
					sf::Style::Close | sf::Style::Titlebar), jogador1(JOGADOR1), jogador2(
					JOGADOR2) {
		jogadorAtual = &jogador1;
		window.setFramerateLimit(90);

		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 6; j++) {
				jogador1.quadrados[i][j] = &tabuleiro.quadrados[i][j];
				jogador2.quadrados[i][j] = &tabuleiro.quadrados[i][j];
			}
		}
	}

	void trocarTurno() {
		jogadorAtual = (jogadorAtual == &jogador1) ? &jogador2 : &jogador1;
	}

	void open() {
		while (window.isOpen()) {
			sf::Event event;
			float mouseX = sf::Mouse::getPosition(window).x;
			float mouseY = sf::Mouse::getPosition(window).y;

			tabuleiro.atualizar(mouseX, mouseY);

			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed)
					window.close();

				if (event.type == sf::Event::MouseButtonPressed) {
					bool clicou = tabuleiro.checarClique(mouseX, mouseY,
							jogadorAtual->ponto);
					if (clicou) {
						int antes = jogadorAtual->getPontuacao();
						jogadorAtual->AtualizaQuadrado();

						int depois = 0;
						for (int i = 0; i < 6; i++) {
							for (int j = 0; j < 6; j++) {
								if (tabuleiro.quadrados[i][j].ponto
										== jogadorAtual->ponto) {
									depois++;
								}
							}
						}

						jogadorAtual->setPontuacao(depois);

						if (depois == antes) {
							trocarTurno();
						}
					}
				}
			}

			window.clear(sf::Color(14, 230, 64));
			tabuleiro.desenhar(window);
			window.display();
		}
	}
};

int main() {
	Jogo jogo;
	jogo.open();
	return 0;
}
