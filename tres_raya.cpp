#include <iostream>
#include <array>
#include <string>
#include <cctype>
#include <limits>

using Board = std::array<char, 9>;

void printBoard(const Board &b) {
    std::cout << "\n";
    for (int i = 0; i < 9; i += 3) {
        std::cout << " " << (b[i]   == ' ' ? char('1' + i)   : b[i]) << " |"
                  << " " << (b[i+1] == ' ' ? char('1' + i + 1) : b[i+1]) << " |"
                  << " " << (b[i+2] == ' ' ? char('1' + i + 2) : b[i+2]) << "\n";
        if (i < 6) std::cout << "---+---+---\n";
    }
    std::cout << "\n";
}

bool checkWin(const Board &b, char player) {
    const int wins[8][3] = {
        {0,1,2}, {3,4,5}, {6,7,8},  // Filas.
        {0,3,6}, {1,4,7}, {2,5,8},  // Columnas.
        {0,4,8}, {2,4,6}  // Diagonales.
    };
    for (auto &w : wins) {
        if (b[w[0]] == player && b[w[1]] == player && b[w[2]] == player)
            return true;
    }
    return false;
}

bool isDraw(const Board &b) {
    for (char c : b)
        if (c == ' ')
            return false;
    return true;
}

int readMove(const Board &b, char currentPlayer) {
    while (true) {
        std::string line;
        std::cout << "Jugador " << currentPlayer << ", introduce una casilla (1-9): ";
        if (!std::getline(std::cin, line)) {
            std::cout << "\nEntrada terminada. Saliendo...\n";
            std::exit(0);
        }

        if (line.empty() || !std::isdigit(line[0])) {
            std::cout << "Entrada no válida. Escribe un número del 1 al 9.\n";
            continue;
        }

        int pos = line[0] - '1';
        if (pos < 0 || pos > 8) {
            std::cout << "Número fuera de rango. Elige entre 1 y 9.\n";
            continue;
        }

        if (b[pos] != ' ') {
            std::cout << "Casilla ocupada. Elige otra.\n";
            continue;
        }

        return pos;
    }
}

bool playAgainPrompt() {
    while (true) {
        std::string s;
        std::cout << "¿Jugar otra vez? (s/n): ";
        if (!std::getline(std::cin, s)) std::exit(0);
        if (s.empty()) continue;
        char c = std::tolower(static_cast<unsigned char>(s[0]));
        if (c == 's' || c == 'y') return true;
        if (c == 'n') return false;
        std::cout << "Respuesta no válida. Escribe 's' o 'n'.\n";
    }
}

int main() {
    std::cout << "TRES EN RAYA\n";
    std::cout << "Dos jugadores: X y O.\n";
    std::cout << "Distribución de casillas:\n";
    std::cout << " 1 | 2 | 3\n";
    std::cout << "---+---+---\n";
    std::cout << " 4 | 5 | 6\n";
    std::cout << "---+---+---\n";
    std::cout << " 7 | 8 | 9\n\n";

    do {
        Board board;
        board.fill(' ');
        char current = 'X';
        bool finished = false;

        while (!finished) {
            printBoard(board);
            int move = readMove(board, current);
            board[move] = current;

            if (checkWin(board, current)) {
                printBoard(board);
                std::cout << "¡Jugador " << current << " ha ganado!\n";
                finished = true;
            } else if (isDraw(board)) {
                printBoard(board);
                std::cout << "Empate. No hay más movimientos.\n";
                finished = true;
            } else {
                current = (current == 'X') ? 'O' : 'X';
            }
        }
    } while (playAgainPrompt());

    std::cout << "Gracias por jugar. ¡Adiós!\n";
    return 0;
}