#include "craps.h"

int main()
{
	srand(time(NULL));
    int total = 500;
	bool outcome;
	outcome = playGame(total);
	exitGame(total);
	if (outcome == true)
		cout << "Great Job at the Craps Table!" << endl;
	else
		cout << "Bit of a rough night. Make sure you return and win it back." << endl;
	return 0;
}

int getRoll() {
	int roll = rand() % 6 + 1;
	return(roll);
}

void startGame() {
	cout << "*** Welcome to Craps ***" << endl << endl;
    cout << "Bet 0 to stop playing." << endl << endl;
}

void exitGame(int total) {
    cout << "Thanks for playing!" << endl;
    cout << "You leave the game with $" << total << endl;
	cout << "*** Game Over Man ***" << endl;
}

void getRolls(int &roll1, int &roll2) {
	roll1 = getRoll();
	roll2 = getRoll();
	cin.ignore();
    cout << "   Press enter to roll: " << endl;
	cin.ignore();
	cout << "   You rolled: " << roll1 + roll2 << "("
         << roll1 << " + " << roll2 << ")" << endl;
}

int getNumber(string prompt, int lowRange, int highRange) {
    int num = lowRange - 1;
    do {
        cout << prompt << highRange << ".\n";
		cout << "How much do you want to bet (0-" << highRange << "):";
        if (!(cin >> num)) {
            cin.clear();
            cin.ignore(255, '\n');
        }
        if ((num < lowRange) || (num > highRange))
            cout << "Bet must be between " << lowRange << 
                    " and " << highRange << "..." << endl;
    } while ((num < lowRange) || (num > highRange));
    return(num);
}

int getBet(int total) {
    string prompt = "You have $";
	int bet = getNumber(prompt,0,total);
	return (bet);
}

bool playGame(int total) {
    int bet, roll, roll1, roll2, target, outcome;
    bool isFirstRoll;
	startGame();
    do {
		outcome = 2;
		isFirstRoll = true;
        bet = getBet(total);
		if (bet == 0) {
			break;
		}
		while (outcome == 2) {
			getRolls(roll1, roll2);
			roll = roll1 + roll2;
			if (isFirstRoll == true) {
				target = roll;
			}
			outcome = getOutcome(isFirstRoll,target,roll);
			if (outcome == 0) {
				cout << "You lose $" << bet << endl << endl;
				total -= bet;
			}
			if (outcome == 1) {
				cout << "You win $" << bet << endl << endl;
				total += bet;
			}
			if (outcome == 2) {
				isFirstRoll = false;
			}
		}
    } while (total != 0);
	if (total > 500) 
		return(true);
	if (total < 500) 
		return(false);
}

int getOutcome(bool isFirstRoll, int target, int roll) {
    if (isFirstRoll == true) {
        if (roll == 2) {
            cout << "   Snake Eyes: ";
            return (0);
        }
        else if (roll == 12) {
            cout << "   Box Cars: ";
            return (0);
        }
        else if (roll == 7) {
            cout << "   Lucky 7: ";
            return (1);
        }
        else if (roll == 11) {
            cout << "   Lucky 11: ";
            return (1);
        }
		else {
			cout << "   Your target is: " << roll << endl;
			return (2);
		}
    }
    if (isFirstRoll == false) {
        if (roll == 7) {
        cout << "   Unlucky 7: ";
        return (0);
        }
        else if (roll == target) {
        cout << "   Target Hit: ";
        return (1);
        }
        else
            return (2);
    }
}
