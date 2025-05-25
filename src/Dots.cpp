#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <random>

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
			if (estado == CHEIO)
				shape.setFillColor(sf::Color::Black);
			else
				shape.setFillColor(sf::Color(0, 0, 0, 130));
		} else {
			if (estado == CHEIO)
				shape.setFillColor(sf::Color::Black);
			else
				shape.setFillColor(sf::Color(0, 0, 0, 0));
		}
	}

	void checarClique(float mouseX, float mouseY) {
		if (shape.getGlobalBounds().contains(mouseX, mouseY) && estado == VAZIO)
			estado = CHEIO;
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
		if (ponto == JOGADOR1)
			shape.setFillColor(sf::Color::Blue);
		else if (ponto == JOGADOR2)
			shape.setFillColor(sf::Color::Red);
		else
			shape.setFillColor(sf::Color(0, 0, 0, 0));
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
		for (int i = 0; i < 7; i++)
			for (int j = 0; j < 6; j++)
				linhasVerticais[i][j].atualizar(mouseX, mouseY);

		for (int i = 0; i < 6; i++)
			for (int j = 0; j < 7; j++)
				linhasHorizontais[i][j].atualizar(mouseX, mouseY);
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
		for (int i = 0; i < 7; i++)
			for (int j = 0; j < 6; j++)
				linhasVerticais[i][j].desenhar(window);

		for (int i = 0; i < 6; i++)
			for (int j = 0; j < 7; j++)
				linhasHorizontais[i][j].desenhar(window);

		for (int i = 0; i < 6; i++)
			for (int j = 0; j < 6; j++)
				quadrados[i][j].desenhar(window);

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
	Quadrado *quadrados[6][6];

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
	sf::SoundBuffer bufferLinha;
	sf::SoundBuffer bufferPonto;
	sf::SoundBuffer bufferLose;
	sf::SoundBuffer bufferWin;
	sf::SoundBuffer bufferFundo;

	sf::Sound somLinha;
	sf::Sound somPonto;
	sf::Sound somLose;
	sf::Sound somWin;
	sf::Sound somFundo;

	sf::Texture TextureRestartImage;
	sf::Texture TextureYouWinImage;
	sf::Texture TextureYouLoseImage;

	sf::Sprite RestartImage;
	sf::Sprite YouWinImage;
	sf::Sprite YouLoseImage;

public:
	Jogo() :
			window(sf::VideoMode(1000, 600), "Dots version 2.0",
					sf::Style::Close | sf::Style::Titlebar), jogador1(JOGADOR1), jogador2(
					JOGADOR2) {

		srand((unsigned) time(0));
		jogadorAtual = &jogador1;

		window.setFramerateLimit(60);
		// imagem restart
		TextureRestartImage.loadFromFile("Imagens/reiniciar.png");
		TextureRestartImage.setSmooth(true);
		RestartImage.setTexture(TextureRestartImage, true);
		RestartImage.setScale(0.1f, 0.1f);
		RestartImage.setPosition(475, 525);
		// imagem you win
		TextureYouWinImage.loadFromFile("Imagens/you-win.png");
		TextureYouWinImage.setSmooth(true);

		// imagem you lose
		TextureYouLoseImage.loadFromFile("Imagens/you-lose.png");
		TextureYouLoseImage.setSmooth(true);

		for (int i = 0; i < 6; i++)
			for (int j = 0; j < 6; j++) {
				jogador1.quadrados[i][j] = &tabuleiro.quadrados[i][j];
				jogador2.quadrados[i][j] = &tabuleiro.quadrados[i][j];
			}

		if (!bufferLinha.loadFromFile("Sons/linha.ogg")) {
			cout << "Erro ao carregar linha.ogg\n";
		}
		if (!bufferPonto.loadFromFile("Sons/ponto.ogg")) {
			cout << "Erro ao carregar ponto.ogg\n";
		}
		if (!bufferLose.loadFromFile("Sons/Derrota.ogg")) {
			cout << "Erro ao carregar Derrota.ogg\n";
		}
		if (!bufferWin.loadFromFile("Sons/Vitoria.ogg")) {
			cout << "Erro ao carregar Vitoria.ogg\n";
		}
		if (!bufferFundo.loadFromFile("Sons/Musica-Fundo.ogg")) {
			cout << "Erro ao carregar Musica-Fundo.ogg\n";
		}
		if (!TextureRestartImage.loadFromFile("Imagens/reiniciar.png")) {
			cout << "Erro ao carregar reiniciar.png\n";
		}
		if (!TextureYouWinImage.loadFromFile("Imagens/you-win.png")) {
			cout << "Erro ao carregar you-win.png\n";
		}
		if (!TextureYouLoseImage.loadFromFile("Imagens/you-lose.png")) {
			cout << "Erro ao carregar you-lose.png\n";
		}

		somLinha.setBuffer(bufferLinha);
		somPonto.setBuffer(bufferPonto);
		somLose.setBuffer(bufferLose);
		somLose.setLoop(true);
		somWin.setBuffer(bufferWin);
		somWin.setLoop(true);
		somFundo.setBuffer(bufferFundo);
		somFundo.setLoop(true);

		somFundo.setVolume(20);
		somFundo.play();

	}

private:
	bool jogoTerminado() {
		for (int i = 0; i < 6; i++)
			for (int j = 0; j < 6; j++)
				if (tabuleiro.quadrados[i][j].ponto == NENHUM)
					return false;
		return true;
	}

public:
	void trocarTurno() {
		if (jogadorAtual == &jogador1) {
			jogadorAtual = &jogador2;

		} else if (jogadorAtual == &jogador2) {
			jogadorAtual = &jogador1;
		}
	}

	void reiniciarJogo() {
		for (int i = 0; i < 7; i++)
			for (int j = 0; j < 6; j++)
				tabuleiro.linhasVerticais[i][j].estado = VAZIO;

		for (int i = 0; i < 6; i++)
			for (int j = 0; j < 7; j++)
				tabuleiro.linhasHorizontais[i][j].estado = VAZIO;

		for (int i = 0; i < 6; i++)
			for (int j = 0; j < 6; j++) {
				tabuleiro.quadrados[i][j].ponto = NENHUM;
				tabuleiro.quadrados[i][j].turno = JOGADOR1;
				tabuleiro.quadrados[i][j].atualizar();
			}

		jogador1.setPontuacao(0);
		jogador2.setPontuacao(0);
		jogadorAtual = &jogador1;
		somLose.stop();
		somWin.stop();
		somFundo.play();
	}

	void jogadaBot() {
		sf::sleep(sf::milliseconds(700)); // Pequeno delay para simular pensamento

		// Tentar completar um quadrado
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 6; j++) {
				Quadrado &q = tabuleiro.quadrados[i][j];

				int ladosCheios = 0;
				if (q.linhaSuperior->estado == CHEIO)
					ladosCheios++;
				if (q.linhaInferior->estado == CHEIO)
					ladosCheios++;
				if (q.linhaEsquerda->estado == CHEIO)
					ladosCheios++;
				if (q.linhaDireita->estado == CHEIO)
					ladosCheios++;

				if (ladosCheios == 3 && q.ponto == NENHUM) {
					if (q.linhaSuperior->estado == VAZIO)
						q.linhaSuperior->estado = CHEIO;
					else if (q.linhaInferior->estado == VAZIO)
						q.linhaInferior->estado = CHEIO;
					else if (q.linhaEsquerda->estado == VAZIO)
						q.linhaEsquerda->estado = CHEIO;
					else if (q.linhaDireita->estado == VAZIO)
						q.linhaDireita->estado = CHEIO;

					somLinha.play();

					int antes = jogadorAtual->getPontuacao();
					jogadorAtual->AtualizaQuadrado();

					int depois = 0;
					for (int m = 0; m < 6; m++) {
						for (int n = 0; n < 6; n++) {
							if (tabuleiro.quadrados[m][n].ponto
									== jogadorAtual->ponto) {
								depois++;
							}
						}
					}

					if (depois > antes)
						somPonto.play();
					jogadorAtual->setPontuacao(depois);
					if (depois == antes)
						trocarTurno();
					return; // Jogada feita
				}
			}
		}

		// Caso não haja quadrados para completar, faz jogada aleatória
		vector<Linha*> linhasVazias;

		for (int i = 0; i < 7; i++) {
			for (int j = 0; j < 6; j++) {
				if (tabuleiro.linhasVerticais[i][j].estado == VAZIO) {
					linhasVazias.push_back(&tabuleiro.linhasVerticais[i][j]);
				}
			}
		}
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 7; j++) {
				if (tabuleiro.linhasHorizontais[i][j].estado == VAZIO) {
					linhasVazias.push_back(&tabuleiro.linhasHorizontais[i][j]);
				}
			}
		}

		if (!linhasVazias.empty()) {
			int indice = rand() % linhasVazias.size();
			linhasVazias[indice]->estado = CHEIO;
			somLinha.play();

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

			if (depois > antes)
				somPonto.play();
			jogadorAtual->setPontuacao(depois);
			if (depois == antes)
				trocarTurno();
		}
	}

	void Eventos(sf::Event event, float mouseX, float mouseY) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::MouseButtonPressed) {
				if (RestartImage.getGlobalBounds().contains(mouseX, mouseY)) {
					somLinha.play();
					reiniciarJogo();
					return; // Evita qualquer outra ação neste clique
				}
				bool clicou = tabuleiro.checarClique(mouseX, mouseY,
						jogadorAtual->ponto);
				if (clicou) {
					somLinha.play(); // Linha feita

					int antes = jogadorAtual->getPontuacao();
					jogadorAtual->AtualizaQuadrado();

					int depois = 0;
					for (int i = 0; i < 6; i++)
						for (int j = 0; j < 6; j++)
							if (tabuleiro.quadrados[i][j].ponto
									== jogadorAtual->ponto)
								depois++;

					if (depois > antes)
						somPonto.play(); // Ponto marcado

					jogadorAtual->setPontuacao(depois);

					// Se não marcou ponto, troca turno
					if (depois == antes) {
						trocarTurno();
					}
				}
			}
		}
	}

	void FimDoJogo() {
		// Verifica se o jogo terminou e mostra o resultado
		if (jogoTerminado()) {
			if (jogador1.getPontuacao() > jogador2.getPontuacao()) {
				YouWinImage.setTexture(TextureYouWinImage, true);
				YouWinImage.setPosition(240, 20);
				window.draw(YouWinImage);

				somFundo.stop();
				somPonto.stop();
				somWin.setVolume(100);
				somWin.getLoop();
				somWin.play();
			} else {
				YouLoseImage.setTexture(TextureYouLoseImage, true);
				YouLoseImage.setPosition(240, 20);
				window.draw(YouLoseImage);

				somFundo.stop();
				somPonto.stop();
				somLose.setVolume(100);
				somLose.getLoop();
				somLose.play();
			}
		}
	}

	void Open() {
		while (window.isOpen()) {
			sf::Event event;
			float mouseX = sf::Mouse::getPosition(window).x;
			float mouseY = sf::Mouse::getPosition(window).y;

			tabuleiro.atualizar(mouseX, mouseY);

			Eventos(event, mouseX, mouseY);

			window.clear(sf::Color(14, 230, 64));
			tabuleiro.desenhar(window);
			window.draw(RestartImage);

			FimDoJogo();

			window.display();

			// Jogada do bot se for a vez dele
			if (jogadorAtual == &jogador2 && !jogoTerminado()) {
				jogadaBot();
			}
		}
	}

};

int main() {
	Jogo jogo;
	jogo.Open();
	return 0;
}
