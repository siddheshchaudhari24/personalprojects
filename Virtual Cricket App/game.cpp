#include "game.h"
#include <unistd.h>

using namespace std;

Game :: Game(){

	playersPerTeam = 4;
	maxBalls = 6;
	totalPlayers = 11;

	players[0] = "Virat";
	players[1] = "Rohit";
	players[2] = "Dhawan";
	players[3] = "Pant";
	players[4] = "Karthik";
	players[5] = "KLRahul";
	players[6] = "Jadeja";
	players[7] = "Hardik";
	players[8] = "Bumrah";
	players[9] = "BKumar";
	players[10] = "Ishant";

	isFirstInnings = false;
	teamA.name = "Team-A";
	teamB.name = "Team-B";

}

void Game::welcome(){
	cout<<"==============================================================================================\n";
	cout<<"************************************** CRIC-IN ***********************************************\n\n";
	cout<<"                             WELCOME TO VIRTUAL CRICKET                                       \n\n";
	cout<<"==============================================================================================\n";
	cout<<endl;
	cout<<"----------------------------------------------------------------------------------------------\n";
	cout<<"*************************************INSTRUCTIONS*********************************************\n";
	cout<<"----------------------------------------------------------------------------------------------\n";
	cout<<"|                                                                                            |\n";
	cout<<"| 1. Create 2 teams (Team-A and Team-B with 4 players                                        |\n";
	cout<<"|    each) from a given pool of 11 players.                                                  |\n";
	cout<<"| 2. Lead the toss and decide the choice of play.                                            |\n";
	cout<<"| 3. Innings will be of 6 balls.                                                             |\n";
	cout<<"----------------------------------------------------------------------------------------------\n";
}

void Game::showAllPlayers(){
	cout<<endl;
	cout<<"----------------------------------------------------------------------------------------------\n";
	cout<<"**********************************POOL OF PLAYERS*********************************************\n";
	for(int i = 0 ; i < totalPlayers ; i++){
		cout<<"\t\t\t\t["<< i << "]" << players[i] << endl;
	}
}

int Game :: takeIntegerInput(){
	int n=0;

	while(!(cin>>n)){
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(),'\n');
		cout<<"Invalid Input!! Please try again with valid input..";
	}

	return n;
}

bool Game :: validateSelectedPlayer (int index) {
	int n;
	vector<Player> players;

	players = teamA.players;
	n = players.size();
	for(int i = 0 ; i < n ; i++){
		if (players[i].id == index){
			return false;
		}
	}

	players = teamB.players;
	n = players.size();
	for(int i = 0 ; i < n ; i++){
		if (players[i].id == index){
			return false;
		}
	}

	return true;
}

void Game :: selectPlayers(){

	cout<<endl;
	cout<<"----------------------------------------------------------------------------------------------\n";
	cout<<"|******************************CREATE TEAM-A & TEAM-B*****************************************|" << endl;
	cout<<"----------------------------------------------------------------------------------------------\n";

	for(int i=0 ; i < playersPerTeam; i++){
		//Add a player to Team-A
		teamASelection:
			cout << endl << "Select a player " << i + 1 <<" of Team-A -- ";

			int playerIndexTeamA = takeIntegerInput();

			if(playerIndexTeamA < 0 || playerIndexTeamA > 10){
				cout << endl << "Please select from the given players" << endl;
				goto teamASelection;

			} else if(!validateSelectedPlayer(playerIndexTeamA)){
				cout<< endl << "The player has been already selected!!"<<endl;
				goto teamASelection;
			}

			else {
				Player teamAPlayer;
				teamAPlayer.id = playerIndexTeamA;
				teamAPlayer.name = players[playerIndexTeamA]; //players string containing name of the players
				teamA.players.push_back(teamAPlayer);    //players -> vector in team header

			}



		//Add a player to Team-B
		teamBSelection:
			cout << endl << "Select a player " << i + 1 <<" of Team-B -- ";

			int playerIndexTeamB = takeIntegerInput();

			if(playerIndexTeamB<0 || playerIndexTeamB > 10){
				cout << endl << "Please select from the given players" << endl;
				goto teamBSelection;

			} else if(!validateSelectedPlayer(playerIndexTeamB)){
				cout<< endl << "The player has been already selected!!"<<endl;
				goto teamBSelection;
			}

			else {
				Player teamBPlayer;
				teamBPlayer.id = playerIndexTeamB;
				teamBPlayer.name = players[playerIndexTeamB]; //players string containing name of the players
				teamB.players.push_back(teamBPlayer);    //players -> vector in team header

			}
	}

}

void Game :: showTeamPlayer (){
	vector<Player> teamAPlayers = teamA.players;
	vector<Player> teamBPlayers = teamB.players;
	cout << endl;
	cout << "--------------------------" << "\t\t" << "--------------------------"<< endl;
	cout << "      TEAM A PLAYERS      " << "\t\t" << "      TEAM B PLAYERS      "<< endl;
	cout << "--------------------------" << "\t\t" << "--------------------------"<< endl;
	for(int i = 0; i < playersPerTeam; i++){
		cout  << "\t[" << i << "]" << setw(8) <<  teamAPlayers[i].name << "\t\t\t" << "\t[" << i << "]" << setw(8) <<  teamBPlayers[i].name << endl;
	}
	cout << "--------------------------" << "\t\t" << "--------------------------"<< endl;
}

void Game :: toss() {
	cout << endl;
	cout << "----------------------------------------------------------------------------------------------" << endl;
	cout << "|===================================== LET'S TOSS ============================================|" << endl;
	cout << "----------------------------------------------------------------------------------------------" << endl;

	sleep(1);

	cout << "Tossing Coin ..."<<endl;
	sleep(2);

	srand(time(NULL));

	int random;
	random = rand()%2;

	switch(random){
	case 0:
		cout <<"Team A won the toss"<< endl;
		tossChoice(teamA);
		break;
	case 1:
		cout <<"Team B won the toss"<< endl;
		tossChoice(teamB);
		break;
	}
}

void Game :: tossChoice(Team tossWinnerTeam) {
	cout<<endl;
	cout << "Enter 1 to bat or 2 to Bowl: "<<endl
			<< "1.Bat" << endl
			<< "2.Bowl" << endl;

	int tossInput = takeIntegerInput();

	cin.ignore(numeric_limits<streamsize>::max(),'\n');

	switch(tossInput) {
		case 1:
			cout << endl << tossWinnerTeam.name << " won the toss and chose to Bat first"<< endl;
			if(tossWinnerTeam.name.compare("Team-A") == 0){
				battingTeam = &teamA;
				bowlingTeam = &teamB;
			}else{ //Team-B is the toss Winner
				battingTeam = &teamB;
				bowlingTeam = &teamA;
			}
			break;
		case 2:
			cout << endl << tossWinnerTeam.name << " won the toss and chose to Bowl first"<< endl;
			if(tossWinnerTeam.name.compare("Team-A")==0){
				bowlingTeam = &teamA;
				battingTeam = &teamB;
			}else{ //Team-B is the toss Winner
				bowlingTeam = &teamB;
				battingTeam = &teamA;
			}
			break;
		default:
			cout << "Invalid Input. Please try again.." << endl;
			tossChoice(tossWinnerTeam);
			break;
	}
}

void Game :: startFirstInnings(){
	cout << endl;
	cout << "\t\t ||| FIRST INNINGS START |||"<<endl<<endl;
	isFirstInnings = true;
	initializePlayers();
	playInnings();
}

void Game :: startSecondInnings(){
	cout << endl;
	cout << "\t\t ||| SECOND INNINGS START |||"<<endl<<endl;
	isFirstInnings = false;
	Team tempTeam = *battingTeam;
	*battingTeam = *bowlingTeam;
	*bowlingTeam = tempTeam;
	initializePlayers();
	playInnings();
}
void Game :: initializePlayers(){
	batsman = &battingTeam->players[0];
	bowler = &bowlingTeam->players[0];

	cout << battingTeam->name << "-" << batsman->name <<" is batting." << endl;
	cout << bowlingTeam->name << "-" << bowler->name <<" is bowling." << endl <<endl;
}

void Game :: playInnings() {

	for(int i = 0; i < maxBalls ; i++){

		cout << "Press Enter to Bowl";
		cin.ignore(numeric_limits<streamsize>::max(),'\n');

		cout << "Bowling..." << endl;
		sleep(1);
		bat();
		if(!validateInningsScore()){
			break;
		}
	}
}

void Game :: bat() {
	srand(time(NULL));
	int runScored = rand() % 7;

	// Updating batting team and batsman score
	batsman->runScored = batsman->runScored + runScored;
	battingTeam->totalRunsScored = battingTeam->totalRunsScored + runScored;
	batsman->ballsPlayed = batsman->ballsPlayed + 1;

	// Updating bowling team and bowler score
	bowler->ballsBowled = bowler->ballsBowled + 1;
	bowlingTeam->totalBallsBowled = bowlingTeam->totalBallsBowled + 1;
	bowler->runsGiven = bowler->runsGiven + runScored;


	if(runScored != 0){
		cout << endl << bowler->name << " to " << batsman->name << " " << runScored << " runs!"<< endl << endl;
		showGameScorecard();

	}else{
		cout << bowler->name << " to " << batsman->name << " OUT!!"<<endl<<endl;

		battingTeam->wicketsLost = battingTeam->wicketsLost + 1;
		bowler->wicketsTaken = bowler->wicketsTaken + 1;

		showGameScorecard();

		int nextPlayerIndex = battingTeam->wicketsLost;
		batsman = &battingTeam->players[nextPlayerIndex];
	}
}

bool Game :: validateInningsScore(){

	if (isFirstInnings){
		if(battingTeam->wicketsLost == playersPerTeam || bowlingTeam->totalBallsBowled == maxBalls){
			cout << "\t\t |||| FIRST INNINGS END |||| " << endl << endl;

			cout << battingTeam->name << " " << battingTeam->totalRunsScored << "-" << battingTeam->wicketsLost
					<< " (" << bowlingTeam->totalBallsBowled<<") "<< endl << endl;

			cout << bowlingTeam->name << " needs " << battingTeam->totalRunsScored + 1 << " runs to win the match."<< endl << endl;
			return false;
		}
	} else { 		// Else 2nd Innings
		if(battingTeam->totalRunsScored > bowlingTeam->totalRunsScored+1){
			cout << "\t\t |||| SECOND INNINGS END |||| " << endl << endl;

			cout << battingTeam->name << " " << battingTeam->totalRunsScored << "-" << battingTeam->wicketsLost
								<< " (" << bowlingTeam->totalBallsBowled<<") "<< endl << endl;
			cout << "-------------------------------------------" << endl;
			cout << "\t" <<  battingTeam->name << " has won the Match!!"<< endl;
			cout << "-------------------------------------------" << endl;
			return false;
		}
		else if(battingTeam->wicketsLost == playersPerTeam || bowlingTeam->totalBallsBowled == maxBalls){
			cout << "\t\t |||| SECOND INNINGS END |||| " << endl << endl;

			cout << battingTeam->name << " " << battingTeam->totalRunsScored << "-" << battingTeam->wicketsLost
								<< " (" << bowlingTeam->totalBallsBowled<<") "<< endl << endl;
			cout << "-------------------------------------------" << endl;
			cout << "\t" <<  bowlingTeam->name << " has won the Match!!"<< endl;
			cout << "-------------------------------------------" << endl;
			return false;

		}else if(battingTeam->totalRunsScored == bowlingTeam->totalRunsScored && bowlingTeam->totalBallsBowled == maxBalls){
				cout << "\t\t |||| SECOND INNINGS END |||| " << endl << endl;

				cout << battingTeam->name << " " << battingTeam->totalRunsScored << "-" << battingTeam->wicketsLost
								<< " (" << bowlingTeam->totalBallsBowled<<") "<< endl;
				cout << "-------------------------------------------" << endl;
				cout << "\t"  << " Match is tied" << endl;
				cout << "-------------------------------------------" << endl;
				return false;
		}
	}
	return true;
}

void Game :: showGameScorecard(){
	cout << "----------------------------------------------------------------------------------------------" << endl;
	cout << "\t" << battingTeam->name << " " << battingTeam->totalRunsScored << "-" << battingTeam->wicketsLost << " | " <<"\t"
			<< batsman->name << " " << batsman->runScored << " (" << batsman->ballsPlayed <<") " << "\t" << bowler->name
			<< " " << bowler->ballsBowled << "-" << bowler->runsGiven << "-" << bowler->wicketsTaken << endl;
	cout << "----------------------------------------------------------------------------------------------" << endl;
}

void Game :: matchSummary(){
	vector<Player> teamAPlayers = teamA.players;
	vector<Player> teamBPlayers = teamB.players;
	cout<<endl;
	cout << "|------------------------------------------|"<< endl;
	cout<<"|***************** TEAM A *****************|"<<endl;
	cout << "|------------------------------------------|"<< endl;
	cout <<  "| PLAYER " << "\t BATTING  " << "\t  BOWLING  |" <<endl;
	cout << "|------------------------------------------|"<<endl;
	for(int i = 0; i < playersPerTeam ; i++){
		cout << "|[" << i <<"] " << teamAPlayers[i].name << "\t  " << setw(2) << teamAPlayers[i].runScored << " " << setw(2) << teamAPlayers[i].ballsPlayed <<
				"\t\t "<< setw(2) << teamAPlayers[i].ballsBowled << " " << setw(2) << teamAPlayers[i].runsGiven << " " << setw(2)
				<< teamAPlayers[i].wicketsTaken << "  |"<<endl;
		cout << "|------------------------------------------|"<< endl;
	}
	cout << endl << endl << endl;
	cout << "|------------------------------------------|"<< endl;
	cout << "|***************** TEAM B *****************|"<<endl;
	cout << "|------------------------------------------|"<< endl;
	cout <<  "| PLAYER " << "\t BATTING  " << "\t  BOWLING  |" << endl;
	for(int i = 0; i < playersPerTeam ; i++){
		cout << "| [" << i <<"] " << teamBPlayers[i].name << "\t  " << setw(2) << teamBPlayers[i].runScored << " " << setw(2) << teamBPlayers[i].ballsPlayed <<
						"\t\t "<< setw(2) << teamBPlayers[i].ballsBowled << " " << setw(2) << teamBPlayers[i].runsGiven << " " << setw(2)
						<< teamBPlayers[i].wicketsTaken << "  |"<< endl;
		cout << "|------------------------------------------|"<<endl;

		}
}
