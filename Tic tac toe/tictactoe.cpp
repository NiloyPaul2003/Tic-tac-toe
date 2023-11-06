#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

char board[3][3] = { { '1', '2', '3' },
                    { '4', '5', '6' },
                    { '7', '8', '9' } };

char currentPlayer = 'X';
int moves = 0;
bool singlePlayerMode = false;

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void drawBoard() {
    clearScreen();
    cout << "Tic-Tac-Toe" << endl;
    cout << "-------------" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    cout << "-------------" << endl;
}

// Rest of the code remains the same


bool makeMove(int choice) {
    int row = (choice - 1) / 3;
    int col = (choice - 1) % 3;

    if (choice < 1 || choice > 9 || board[row][col] == 'X' || board[row][col] == 'O') {
        return false;
    }

    board[row][col] = currentPlayer;
    return true;
}

bool checkWin() {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == currentPlayer && board[i][1] == currentPlayer && board[i][2] == currentPlayer) {
            return true;
        }
        if (board[0][i] == currentPlayer && board[1][i] == currentPlayer && board[2][i] == currentPlayer) {
            return true;
        }
    }
    if (board[0][0] == currentPlayer && board[1][1] == currentPlayer && board[2][2] == currentPlayer) {
        return true;
    }
    if (board[0][2] == currentPlayer && board[1][1] == currentPlayer && board[2][0] == currentPlayer) {
        return true;
    }
    return false;
}

void computerMove() {
    int emptySpots[9];
    int emptyCount = 0;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                emptySpots[emptyCount++] = i * 3 + j + 1;
            }
        }
    }

    if (emptyCount > 0) {
        int randomIndex = rand() % emptyCount;
        makeMove(emptySpots[randomIndex]);
    }
}

int main() {
    while (true) {
        drawBoard();

        int choice;
        cout << "Choose a mode:" << endl;
        cout << "1. Two-player mode" << endl;
        cout << "2. Single-player mode" << endl;
        cin >> choice;

        if (choice == 2) {
            singlePlayerMode = true;
        }

        while (true) {
            drawBoard();

            int choice;
            cout << "Player " << currentPlayer << ", enter your choice (1-9): ";
            cin >> choice;

            if (makeMove(choice)) {
                moves++;
                if (checkWin()) {
                    drawBoard();
                    if (singlePlayerMode && currentPlayer == 'O') {
                        cout << "You win!" << endl;
                    } else if (singlePlayerMode && currentPlayer == 'X') {
                        cout << "Computer wins!" << endl;
                    } else {
                        cout << "Player " << currentPlayer << " wins!" << endl;
                    }
                    break;
                } else if (moves == 9) {
                    drawBoard();
                    cout << "It's a draw!" << endl;
                    break;
                } else {
                    if (singlePlayerMode && currentPlayer == 'X') {
                        computerMove();
                    } else {
                        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
                    }
                }
            } else {
                cout << "Invalid move. Try again." << endl;
            }
        }

        cout << "Play again? (1 for yes, 0 for no): ";
        cin >> choice;
        if (choice == 0) {
            break;
        }

        // Reset the game
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                board[i][j] = '1' + i * 3 + j;
            }
        }
        currentPlayer = 'X';
        moves = 0;
        singlePlayerMode = false;
    }

    return 0;
}
