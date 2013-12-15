#include <iostream>		/* cin, cout */
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <string>		/* string */

using namespace std;

int rollDice();
void allowedToPlay(bool* allowed, double* moneyPlayers, int numPlayers);
int playAll(int* choicePlayers, int numPlayers, int sumOfDie);
void playRound(int* choicePlayers, bool* allowed, double* moneyPlayers, int numPlayers, int sumOfDie);
void printMoney(double* moneyPlayers, int numPlayers); 

int main () {

	// Seeds the random function
	srand(time(NULL));

	int numPlayers; // The number of players

	// Enter the number of players
	do {

		cout << "Enter between 2-9 more players. \n";

		cin >> numPlayers;

	} while ((numPlayers > 9) || (numPlayers < 2));

	bool* allowed = new bool[numPlayers + 1]; // new bool[numPlayers]; // True if allowed to play, false otherwise
	double* moneyPlayers = new double[numPlayers + 1]; // the money of the players
	int* choicePlayers = new int[numPlayers + 1]; // 0 if cho, 1 if han the choices of the player

	// Sets all of the people's money to 500
	for(int i = 0; i < numPlayers + 1; i++) {

		moneyPlayers[i] = 500.0;

	}

	int round; // Handles if you do not want to play or are not allowed to play
	int sumOfDie;

	do {

		sumOfDie = rollDice() % 2;
		allowedToPlay(allowed, moneyPlayers, numPlayers);

		if (allowed[0]) {

			round = playAll(choicePlayers, numPlayers, sumOfDie);
			playRound(choicePlayers, allowed, moneyPlayers, numPlayers, sumOfDie);

			if(round == 0) {

				printMoney(moneyPlayers, numPlayers);

			}

			if (round == -1 ) {

				printf("\nYou leave with $%f!", moneyPlayers[0]);

			}

		} else {

			round = -1;
			printf("\nYou leave with $%f!", moneyPlayers[0]);

		}

	} while (round == 0);

	delete [] allowed;
	delete [] moneyPlayers;
	delete [] choicePlayers;

	getchar();
	getchar();

	return 0;

}

// Rolls the dice
int rollDice() {

	int die1;
	int die2;

	die1 = rand() % 6 + 1;
	die2 = rand() % 6 + 1;

	printf("\nThe first die rolls a %d, and the second die rolls a %d", die1, die2);

	return die1 + die2;

}

// Plays all of the players, 0 for cho and 1 for han
int playAll(int* choicePlayers, int numPlayers, int sumOfDie) {

	string choiceYou;

	cout << endl;

	cout << "Do you want Cho (even) or Han (odd) or Pass? Make sure you put it in lowercase letters. \n";

	cin >> choiceYou;

	// Play others
	for (int i = 1; i < (numPlayers + 1); i++) {

		int decision = rand() % 2;

		choicePlayers[i] = decision;

	}

	// Play you
	if (choiceYou.compare("cho") == 0) {

		choicePlayers[0] = 0;

		return 0;

	} else if (choiceYou.compare("han") == 0) {

		choicePlayers[0] = 1;

		return 0;

	} else if (!choiceYou.compare("pass") == 0) {

		if (sumOfDie == 0) {

			choicePlayers[0] = 1;

			return 0;

		} else {

			choicePlayers[0] = 0;

			return 0;

		}

	} else {

		return -1 ;

	}

}

// Checks if players are allowed to play
void allowedToPlay(bool* allowed, double* moneyPlayers, int numPlayers) {

	for(int i = 0; i < (numPlayers + 1); i++){

		if (moneyPlayers[i] < 50) {

			allowed[i] = false;

		} else {

			allowed[i] = true;

		}


	}
}

// Plays the round for the players who are allowed to play
void playRound(int* choicePlayers, bool* allowed, double* moneyPlayers, int numPlayers, int sumOfDie) {

	double prizePool = 0;
	int countWinners = 0;

	for (int i = 0; i < (numPlayers + 1); i++) {

		if (allowed[i] == true) {

			moneyPlayers[i] -= 50;

			if (sumOfDie == choicePlayers[i]) {

				countWinners++;

			} else {

				prizePool += 50;

			}

		}
	}

	for (int i = 0; i < (numPlayers + 1); i++) {

		double distribution = prizePool / countWinners;

		if ((choicePlayers[i] == sumOfDie) && (allowed[i] == true)) {

			moneyPlayers[i] += (distribution + 50);

		}
	}
}

// Prints out the money that each player has
void printMoney(double* moneyPlayers, int numPlayers) {

	cout << endl;

	printf("You: %.2f \n", moneyPlayers[0]);

	for(int i = 1; i < (numPlayers + 1); i++) {

		printf("Player%d: %.2f \n", i + 1, moneyPlayers[i]);

	}

}