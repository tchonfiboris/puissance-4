#include <iostream>
#include <vector>

const int ROWS = 6;
const int COLS = 7;

class ConnectFour {
public:
    ConnectFour() {
        board.resize(ROWS, std::vector<char>(COLS, '.'));
    }

    void display() {
        for (const auto& row : board) {
            for (char cell : row) {
                std::cout << cell << ' ';
            }
            std::cout << std::endl;
        }
        std::cout << "0 1 2 3 4 5 6" << std::endl; // Colonnes
    }

    bool dropPiece(int col, char piece) {
        if (col < 0 || col >= COLS) return false;

        for (int row = ROWS - 1; row >= 0; --row) {
            if (board[row][col] == '.') {
                board[row][col] = piece;
                return true;
            }
        }
        return false; // Colonne pleine
    }

    bool checkWin(char piece) {
        // Check horizontal, vertical, and diagonal
        return checkDirection(piece) || checkDirection(piece, true, false) || checkDirection(piece, false, true);
    }

private:
    std::vector<std::vector<char>> board;

    bool checkDirection(char piece, bool checkDiagonalRight = false, bool checkDiagonalLeft = false) {
        for (int row = 0; row < ROWS; ++row) {
            for (int col = 0; col < COLS; ++col) {
                if (board[row][col] == piece) {
                    if (checkHorizontal(row, col, piece) || checkVertical(row, col, piece)) {
                        return true;
                    }
                    if (checkDiagonalRight && checkDiagonal(row, col, piece, 1, 1)) return true;
                    if (checkDiagonalLeft && checkDiagonal(row, col, piece, 1, -1)) return true;
                }
            }
        }
        return false;
    }

    bool checkHorizontal(int row, int col, char piece) {
        if (col + 3 < COLS) {
            return board[row][col + 1] == piece &&
                   board[row][col + 2] == piece &&
                   board[row][col + 3] == piece;
        }
        return false;
    }

    bool checkVertical(int row, int col, char piece) {
        if (row + 3 < ROWS) {
            return board[row + 1][col] == piece &&
                   board[row + 2][col] == piece &&
                   board[row + 3][col] == piece;
        }
        return false;
    }

    bool checkDiagonal(int row, int col, char piece, int rowDir, int colDir) {
        for (int i = 1; i < 4; ++i) {
            int newRow = row + i * rowDir;
            int newCol = col + i * colDir;
            if (newRow < 0 || newRow >= ROWS || newCol < 0 || newCol >= COLS || board[newRow][newCol] != piece) {
                return false;
            }
        }
        return true;
    }
};

int main() {
    ConnectFour game;
    char currentPlayer = 'X';
    int column;

    while (true) {
        game.display();
        std::cout << "Joueur " << currentPlayer << ", choisissez une colonne (0-6) : ";
        std::cin >> column;

        if (game.dropPiece(column, currentPlayer)) {
            if (game.checkWin(currentPlayer)) {
                game.display();
                std::cout << "Le joueur " << currentPlayer << " a gagné !" << std::endl;
                break;
            }
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X'; // Change de joueur
        } else {
            std::cout << "Colonne pleine ou invalide ! Essayez à nouveau." << std::endl;
        }
    }

    return 0;
}