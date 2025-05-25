#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// ================= ENUMS =================
enum Clik { VAZIO, CHEIO };
enum Dono { NENHUM, JOGADOR, COMPUTADOR };

// ================= CLASSE LINHA =================
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

// ================= CLASSE QUADRADO =================
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

    Quadrado(float x, float y, float dim) {
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
        }
        return false;
    }

    void desenhar(sf::RenderWindow& window) {
        window.draw(shape);
    }
};

// ================= CLASSE TABULEIRO =================
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
        criarTabuleiro();
    }

    void criarTabuleiro() {
        // Linhas verticais
        for (int i = 0; i < 7; i++) {
            for (int j = 0; j < 6; j++) {
                float x = (i * dim) + (i * space) + 375;
                float y = (j * dim) + (j * space) + 80 + gros;
                linhasVerticais[i][j] = Linha(x, y, gros, dim);
            }
        }

        // Linhas horizontais
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 7; j++) {
                float x = (i * dim) + (i * space) + 380 + gros;
                float y = (j * dim) + (j * space) + 75;
                linhasHorizontais[i][j] = Linha(x, y, dim, gros);
            }
        }

        // Quadrados
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 6; j++) {
                float x = (i * dim) + (i * space) + 375 + gros;
                float y = (j * dim) + (j * space) + 75 + gros;
                quadrados[i][j] = Quadrado(x, y, dim + gros);
            }
        }

        // Ligações dos quadrados às linhas
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

        // Desenhar pontos
        const float raio = 10.0f;
        for (int i = 0; i < 7; i++) {
            for (int j = 0; j < 7; j++) {
                float x = (i * 50) + (i * 16) + 379;
                float y = (j * 50) + (j * 16) + 79;
                sf::CircleShape ponto(raio);
                ponto.setFillColor(sf::Color::White);
                ponto.setPosition(x - raio, y - raio);
                window.draw(ponto);
            }
        }
    }

    void reset() {
        criarTabuleiro();
    }

    Linha(&getLinhasVerticais())[7][6] {
        return linhasVerticais;
    }

    Linha(&getLinhasHorizontais())[6][7] {
        return linhasHorizontais;
    }
};

// ================= CLASSE JOGO =================
class JogoContraPC {
private:
    sf::RenderWindow window;
    Tabuleiro tabuleiro;
    bool turnoJogador;

    int pontosJogador;
    int pontosComputador;

    sf::Font fonte;
    sf::Text textoPlacar;
    sf::RectangleShape botaoReset;
    sf::Text textoReset;

public:
    JogoContraPC() :
        window(sf::VideoMode(1000, 600), "Dots - Player vs PC", sf::Style::Close | sf::Style::Titlebar),
        turnoJogador(true),
        pontosJogador(0),
        pontosComputador(0) {

        window.setFramerateLimit(90);
        srand(static_cast<unsigned>(time(0)));

        fonte.loadFromFile("arial.ttf");

        textoPlacar.setFont(fonte);
        textoPlacar.setCharacterSize(24);
        textoPlacar.setPosition(30, 30);
        textoPlacar.setFillColor(sf::Color::Black);

        botaoReset.setSize(sf::Vector2f(150, 40));
        botaoReset.setFillColor(sf::Color(200, 200, 200));
        botaoReset.setPosition(30, 500);

        textoReset.setFont(fonte);
        textoReset.setCharacterSize(20);
        textoReset.setString("Reiniciar");
        textoReset.setPosition(50, 510);
        textoReset.setFillColor(sf::Color::Black);
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

                if (event.type == sf::Event::MouseButtonPressed) {
                    if (botaoReset.getGlobalBounds().contains(mouseX, mouseY)) {
                        resetarJogo();
                    } else if (turnoJogador) {
                        if (realizarCliqueJogador(mouseX, mouseY)) {
                            bool fezPonto = tabuleiro.verificarQuadradoFeito(JOGADOR);
                            if (fezPonto) {
                                pontosJogador++;
                            }
                            if (!fezPonto) {
                                turnoJogador = false;
                            }
                        }
                    }
                }
            }

            if (!turnoJogador) {
                sf::sleep(sf::milliseconds(500));
                realizarJogadaComputador();
            }

            atualizarTextoPlacar();

            window.clear(sf::Color(133, 199, 194));
            tabuleiro.desenhar(window);
            window.draw(textoPlacar);
            window.draw(botaoReset);
            window.draw(textoReset);
            window.display();
        }
    }

    void atualizarTextoPlacar() {
        textoPlacar.setString("Jogador: " + to_string(pontosJogador) +
            "  PC: " + to_string(pontosComputador));
    }

    void resetarJogo() {
        tabuleiro.reset();
        pontosJogador = 0;
        pontosComputador = 0;
        turnoJogador = true;
    }

    bool realizarCliqueJogador(float mouseX, float mouseY) {
        bool clicou = false;
        auto& linhasVerticais = tabuleiro.getLinhasVerticais();
        auto& linhasHorizontais = tabuleiro.getLinhasHorizontais();

        for (int i = 0; i < 7; i++) {
            for (int j = 0; j < 6; j++) {
                if (linhasVerticais[i][j].shape.getGlobalBounds().contains(mouseX, mouseY)
                    && linhasVerticais[i][j].estado == VAZIO) {
                    linhasVerticais[i][j].estado = CHEIO;
                    clicou = true;
                }
            }
        }

        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 7; j++) {
                if (linhasHorizontais[i][j].shape.getGlobalBounds().contains(mouseX, mouseY)
                    && linhasHorizontais[i][j].estado == VAZIO) {
                    linhasHorizontais[i][j].estado = CHEIO;
                    clicou = true;
                }
            }
        }

        return clicou;
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

                bool fezPonto = tabuleiro.verificarQuadradoFeito(COMPUTADOR);
                if (fezPonto) {
                    pontosComputador++;
                    jogando = true;
                    sf::sleep(sf::milliseconds(300));
                } else {
                    turnoJogador = true;
                }
            }
        }
    }
};

// ================= MAIN =================
int main() {
    JogoContraPC jogo;
    jogo.executar();
    return 0;
}
