#include<iostream>
#include<vector>
using namespace std;
enum gamestate { PLAYING, X_WIN, O_WIN, DRAW };
class chessgame {
private:
	vector<vector<char>> board;
	char currentplayer;
	gamestate state;

	gamestate checkwinner() {
		for (int i = 0; i < 3; i++) {
			if (board[i][0] != '.' && board[i][1] == board[i][0] && board[i][2] == board[i][1]) {
				return (board[i][0] == 'X') ? X_WIN : O_WIN;
			}
			if (board[0][i] != '.' && board[1][i] == board[0][i] && board[2][i] == board[1][i]) {
				return (board[0][i] == 'X') ? X_WIN : O_WIN;
			}
		}
		int flag = 1;
		for (int i = 0; i < 2; i++) {
			if (board[i][i] == '.') { flag = 0; break; }
			if (board[i][i] != board[i + 1][i + 1]) {
				flag = 0;
				break;
			}
		}
		if (flag) {
			return (board[0][0] == 'X') ? X_WIN : O_WIN;
		}
		flag = 1;
		for (int i = 0; i < 2; i++) {
			if (board[i][2 - i] == '.') {
				flag = 0;
				break;
			}
			if (board[i][2 - i] != board[i + 1][1 - i]) {
				flag = 0;
				break;
			}
		}
		if (flag) {
			return (board[0][2] == 'X') ? X_WIN : O_WIN;
		}
		flag = 1;
		for (int i = 0; i < 3; i++) {
			if (!flag) { break; }
			for (int j = 0; j < 3; j++) {
				if (board[i][j] == '.') { flag = 0; break; }
			}
		}
		if (flag) {
			return DRAW;
		}
		return PLAYING;
	}


	bool playermove(int row, int col) {
		if (row > 3 || col > 3 || row < 1 || col < 1) {
			cout << "WRONG INPUT!\n";
			return 0;
		}
		row--; col--;
		if (board[row][col] == '.') {
			board[row][col] = currentplayer;
			if (currentplayer == 'X') { currentplayer = 'O'; }
			else { currentplayer = 'X'; }
			cout << "SUCCESS MOVE\n";
			return 1;
		}
		else {
			cout << "This place has been occupied orz\n";
			return 0;
		}
	}
public:
	gamestate get_gamestate() {
		return state;
	}

	bool move(int row, int col) {
		bool p = playermove(row, col);
		if (p) {
			state = checkwinner();
		}
		return p;
	}

	char get_player() {
		return currentplayer;
	}

	void show() {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				cout << board[i][j] << ' ';
			}
			cout << '\n';
		}
	}

	chessgame() {
		board = vector<vector<char>>(3, vector<char>(3, '.'));
		state = PLAYING;
		currentplayer = 'X';
	}
};

int main() {
	int a, b;
	chessgame now;
	cout << "This is a 3_3chessgame,Welcom!\n";
	while (now.get_gamestate() == PLAYING) {
		cout << "please " << now.get_player() << "_player input your row and column\n";
		cin >> a >> b;
		if (now.move(a, b)) {
			now.show();
		}
	}
	if (now.get_gamestate() == X_WIN) {
		cout << "666 " << 'X' << "_player win!";
	}
	else if (now.get_gamestate() == O_WIN) {
		cout << "666 " << 'O' << "_player win!";
	}
	else {
		cout << "GOOD GAME DRAW ENDING";
	}
	return 0;
}