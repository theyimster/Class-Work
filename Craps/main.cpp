#include "craps.h"

int main()
{
    int total = 500;
    bool outcome;
    startGame();
    outcome = playGame(total);
    exitGame(total);
	return 0;
}

int getRoll() {
	srand(time(NULL));
	int roll = rand() % 6 + 1;
	return(roll);
}

void startGame() {
	cout << "*** Welcome to Craps ***" << endl;
    cout << "Bet 0 to stop playing." << endl;
}

void exitGame(int total) {
    cout << "Thanks for playing!" << endl;
    cout << "You leave the game with $" << total << endl;
	cout << "*** Game Over Man ***" << endl;
}

void getRolls(int& roll1, int& roll2) {
    cout << "   Press enter to roll: ";
    cin.get();
	cout << "   You rolled: " << roll1 + roll2 << "(roll1 + roll2)"
         << endl;
}

int getNumber(string prompt, int lowRange, int highRange) {
    int num = lowRange - 1;
    do {
        cout << prompt;
        if (!(cin >> num)) {
            cin.clear();
            cin.ignore(255, '\n');
        }
        if ((num < lowRange) || (num > highRange))
            cout << "Entry must be between " << lowRange << 
                    " and " << highRange << "..." << endl;
    } while ((num < lowRange) || (num > highRange));
    return(num);
}

int getBet(int total) {
    string prompt = "How much do you want to bet (0-"+total+"):";
	int bet = getNumber(prompt,0,total);
	return (bet);
}

bool playGame(int total) {
    int bet, roll, roll1, roll2, target, outcome;
    bool isFirstRoll = true;
    do {
        bet = getBet(total);
        roll1 = getRoll();
        roll2 = getRoll();
        getRolls(&roll1, &roll2);
        roll = roll1 + roll2;
        target = roll1 + roll2;
        outcome = getOutcome(isFirstRoll,target,roll)
        if (outcome == 0) {
            cout << "You lose $" << bet << endl;
            total -= bet;
        }
        if (outcome == 1) {
            cout << "You win $" << bet << endl;
            total += bet;
        }
        if (outcome == 2) {
            
        }
    while (bet != 0) }
}

int getOutcome(bool isFirstRoll, int target, int roll) {
    if (isFirstRoll == true) {
        if (roll == 2) {
            cout << "Snake Eyes: ";
            return (0);
        }
        if (roll == 12) {
            cout << "Box Cars: ";
            return (0);
        }
        if (roll == 7) {
            cout << "Lucky 7: ";
            return (1);
        }
        if (roll == 11) {
            cout << "Lucky 11: ";
            return (1);
        }
    }
    if (isFirstRoll == false) {
        cout << "Your target is: " << target << endl;
        if (roll == 7) {
        cout << "Unlucky 7: ";
        return (0);
        }
        else if (roll == target) {
        cout << "Target Hit: ";
        return (1);
        }
        else
            return (2);
    }
}