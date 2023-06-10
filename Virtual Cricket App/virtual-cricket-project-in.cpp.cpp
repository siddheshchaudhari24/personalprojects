#include "game.h"

using namespace std;

int main() {
	Game game;
	game.welcome();

	cout << "Press Enter to Continue";
	cin.ignore(numeric_limits<streamsize>::max(),'\n');

	game.showAllPlayers();

	cout << "Press Enter to Continue";
	cin.ignore(numeric_limits<streamsize>::max(),'\n');

	game.selectPlayers();
	game.showTeamPlayer();

	cout << "Press Enter to Toss";
	cin.ignore(numeric_limits<streamsize>::max(),'\n');

	cin.ignore(numeric_limits<streamsize>::max(),'\n');

	game.toss();

	game.startFirstInnings();

	game.startSecondInnings();

	game.matchSummary();

	return 0;
}
