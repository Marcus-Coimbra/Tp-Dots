#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

enum Clik {
    VAZIO, CHEIO
};

enum Dono {
    NENHUM, JOGADOR, COMPUTADOR
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

    void desenhar(sf::RenderWindow& window) {
        window.draw(shape);
    }
};

class Quadrado {
public:
    sf::RectangleShape shape;
    Dono dono;

    Linha* linhaSuperior;
    Linha* linhaInferior;
    Linha* linhaEsquerda;
    Linha* linhaDireita;

    Quadrado() : dono(NENHUM), linhaSuperior(nullptr), linhaInferior(nullptr), linhaEsquerda(nullptr), linhaDireita(nullptr) {
        shape.setSize(sf::Vector2f(0, 0));
        shape.setPosition(0, 0);
        shape.setFillColor(sf::Color(0, 0, 0, 0));
    }

    Quadrado(float x, float y, float dim) : linhaSuperior(nullptr), linhaInferior(nullptr), linhaEsquerda(nullptr), linhaDireita(nullptr) {
        shape.setSize(sf::Vector2f(dim, dim));
        shape.setPosition(x, y);
        shape.setFillColor(sf::Color(0, 0, 0, 0));
        dono = NENHUM;
    }

    void atualizar() {
        if (dono == JOGADOR) {
            shape.setFillColor(sf::Color::Blue);
        } else if (dono == COMPUTADOR) {
            shape.setFillColor(sf::Color::Red);
        } else {
            shape.setFillColor(sf::Color(0, 0, 0, 0));
        }
    }

    bool checarPonto(Dono atual) {
        if (dono == NENHUM &&
            linhaSuperior->estado == CHEIO &&
            linhaInferior->estado == CHEIO &&
            linhaEsquerda->estado == CHEIO &&
            linhaDireita->estado == CHEIO) {
            dono = atual;
            return true;
        } else{
            return false;
        }
    }

    void desenhar(sf::RenderWindow& window) {
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
                quadrados[i][j] = Quadrado(x, y, dim + gros);
            }
        }

        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 6; j++) {
                quadrados[i][j].linhaSuperior = &linhasHorizontais[i][j];
                quadrados[i][j].linhaInferior = &linhasHorizontais[i][j+1];
                quadrados[i][j].linhaEsquerda = &linhasVerticais[i][j];
                quadrados[i][j].linhaDireita = &linhasVerticais[i+1][j];
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

        for (int i = 0; i < 6; i++)
            for (int j = 0; j < 6; j++)
                quadrados[i][j].atualizar();
    }

    bool verificarQuadradoFeito(Dono atual) {
        bool fezPonto = false;
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 6; j++) {
                if (quadrados[i][j].checarPonto(atual)) {
                    fezPonto = true;
                }
            }
        }
        return fezPonto;
    }

    void desenhar(sf::RenderWindow& window) {
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
                float x = (i * dim) + (i * space) + 379;
                float y = (j * dim) + (j * space) + 79;
                sf::CircleShape ponto(raio);
                ponto.setFillColor(sf::Color(255, 255, 255));
                ponto.setPosition(x - raio, y - raio);
                window.draw(ponto);
            }
        }
    }

    Linha(&getLinhasVerticais())[7][6] {
        return linhasVerticais;
    }

    Linha(&getLinhasHorizontais())[6][7] {
        return linhasHorizontais;
    }
};

class JogoContraPC {
private:
    sf::RenderWindow window;
    Tabuleiro tabuleiro;
    bool turnoJogador;

public:
    JogoContraPC() :
        window(sf::VideoMode(1000, 600), "Dots - Player vs PC",
            sf::Style::Close | sf::Style::Titlebar),
        turnoJogador(true) {
        window.setFramerateLimit(90);
        srand(static_cast<unsigned>(time(0)));
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

                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    if (turnoJogador) {
                        bool fezPonto = false;
                        bool linhaMarcada = false;

                        auto& linhasVerticais = tabuleiro.getLinhasVerticais();
                        auto& linhasHorizontais = tabuleiro.getLinhasHorizontais();

                        // Tenta marcar linha horizontal
                        for (int i = 0; i < 6 && !linhaMarcada; i++) {
                            for (int j = 0; j < 7 && !linhaMarcada; j++) {
                                if (linhasHorizontais[i][j].shape.getGlobalBounds().contains(mouseX, mouseY)) {
                                    if (linhasHorizontais[i][j].estado == VAZIO) {
                                        linhasHorizontais[i][j].estado = CHEIO;
                                        linhasHorizontais[i][j].shape.setFillColor(sf::Color::Black);
                                        linhaMarcada = true;
                                        fezPonto = tabuleiro.verificarQuadradoFeito(JOGADOR);
                                    }
                                }
                            }
                        }

                        // Tenta marcar linha vertical
                        for (int i = 0; i < 7 && !linhaMarcada; i++) {
                            for (int j = 0; j < 6 && !linhaMarcada; j++) {
                                if (linhasVerticais[i][j].shape.getGlobalBounds().contains(mouseX, mouseY)) {
                                    if (linhasVerticais[i][j].estado == VAZIO) {
                                        linhasVerticais[i][j].estado = CHEIO;
                                        linhasVerticais[i][j].shape.setFillColor(sf::Color::Black);
                                        linhaMarcada = true;
                                        fezPonto = tabuleiro.verificarQuadradoFeito(JOGADOR);
                                    }
                                }
                            }
                        }

                        if (linhaMarcada && !fezPonto) {
                            turnoJogador = false;
                        }
                    }
                }
            }

            if (!turnoJogador) {
                sf::sleep(sf::milliseconds(500));
                realizarJogadaComputador();
            }

            window.clear(sf::Color(150, 150, 150)); // fundo cinza claro
            tabuleiro.desenhar(window);
            window.display();
        }
    }

    void realizarJogadaComputador() {
        bool jogando = true;
        while (jogando) {
            jogando = false;
            std::vector<Linha*> linhasDisponiveis;

            auto& linhasVerticais = tabuleiro.getLinhasVerticais();
            auto& linhasHorizontais = tabuleiro.getLinhasHorizontais();

            for (int i = 0; i < 7; i++) {
                for (int j = 0; j < 6; j++) {
                    if (linhasVerticais[i][j].estado == VAZIO) {
                        linhasDisponiveis.push_back(&linhasVerticais[i][j]);
                    }
                }
            }

            for (int i = 0; i < 6; i++) {
                for (int j = 0; j < 7; j++) {
                    if (linhasHorizontais[i][j].estado == VAZIO) {
                        linhasDisponiveis.push_back(&linhasHorizontais[i][j]);
                    }
                }
            }

            if (!linhasDisponiveis.empty()) {
                int indice = rand() % linhasDisponiveis.size();
                linhasDisponiveis[indice]->estado = CHEIO;
                linhasDisponiveis[indice]->shape.setFillColor(sf::Color::Black);

                bool fezPonto = tabuleiro.verificarQuadradoFeito(COMPUTADOR);
                if (fezPonto) {
                    jogando = true;
                    sf::sleep(sf::milliseconds(300));
                } else {
                    turnoJogador = true;
                }
            }
        }
    }
};

int main() {
    JogoContraPC jogo;
    jogo.executar();
    return 0;
}
