#include <iostream>
#include <vector>
#include <limits>
#include <cstdlib>
#include <ctime>
using namespace std;

char board[3][3];
char currentPlayer;
bool singlePlayer = false;

void initBoard() {
    char start = '1';
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = start++;
}

void showBoard() {
    cout << "\n";
    for (int i = 0; i < 3; i++) {
        cout << " ";
        for (int j = 0; j < 3; j++) {
            cout << board[i][j];
            if (j < 2) cout << " | ";
        }
        if (i < 2) cout << "\n-----------\n";
    }
    cout << "\n";
}

bool isDraw() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] != 'X' && board[i][j] != 'O')
                return false;
    return true;
}

bool isWin() {
    for (int i = 0; i < 3; i++)
        if (board[i][0] == currentPlayer &&
            board[i][1] == currentPlayer &&
            board[i][2] == currentPlayer)
            return true;
    for (int j = 0; j < 3; j++)
        if (board[0][j] == currentPlayer &&
            board[1][j] == currentPlayer &&
            board[2][j] == currentPlayer)
            return true;
    if (board[0][0] == currentPlayer &&
        board[1][1] == currentPlayer &&
        board[2][2] == currentPlayer)
        return true;
    if (board[0][2] == currentPlayer &&
        board[1][1] == currentPlayer &&
        board[2][0] == currentPlayer)
        return true;
    return false;
}

bool makeMove(int pos) {
    int row = (pos - 1) / 3;
    int col = (pos - 1) % 3;
    if (pos < 1 || pos > 9) return false;
    if (board[row][col] == 'X' || board[row][col] == 'O') return false;
    board[row][col] = currentPlayer;
    return true;
}

void switchPlayer() {
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}

int getRandomMove() {
    vector<int> free;
    for (int i = 1; i <= 9; ++i) {
        int row = (i - 1) / 3;
        int col = (i - 1) % 3;
        if (board[row][col] != 'X' && board[row][col] != 'O')
            free.push_back(i);
    }
    if (!free.empty()) return free[rand() % free.size()];
    return -1;
}

void playGame() {
    currentPlayer = 'X';
    initBoard();
    while (true) {
        showBoard();
        if (!singlePlayer || currentPlayer == 'X') {
            cout << "Player " << currentPlayer << ", choose a cell (1-9): ";
            int move;
            cin >> move;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input.\n";
                continue;
            }
            if (!makeMove(move)) {
                cout << "Cell unavailable. Try again.\n";
                continue;
            }
        } else {
            int aiMove = getRandomMove();
            cout << "AI chose: " << aiMove << "\n";
            makeMove(aiMove);
        }
        if (isWin()) {
            showBoard();
            cout << "Player " << currentPlayer << " wins!\n";
            break;
        }
        if (isDraw()) {
            showBoard();
            cout << "It's a draw!\n";
            break;
        }
        switchPlayer();
    }
}

int main() {
    srand(time(0));
    char again;
    do {
        cout << "Choose Mode:\n1. Single Player (You vs AI)\n2. Two Player\nPick (1 or 2): ";
        int mode;
        cin >> mode;
        singlePlayer = (mode == 1);
        playGame();
        cout << "Play again? (y/n): ";
        cin >> again;
    } while (again == 'y' || again == 'Y');
    cout << "Thanks for playing.\n";
    return 0;
}
