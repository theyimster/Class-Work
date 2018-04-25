#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <limits>
using namespace std;
bool playGame(int total); // passed player total amount - plays a complete game, returns true for win and false for loss
int getBet(int total); // passed player total amount and returns a valid bet (0 - total)
int getNumber(string prompt, int lowRange, int highRange); // returns a number in the given range
int getRoll(); // return 1 6-sided dice roll
void getRolls(int &roll1, int &roll2); // uses reference parameters - discussed in Week 7
int getOutcome(bool isFirstRoll, int target, int roll); // prints appropriate game end messages and returns 0=loss, 1=win, 2=ongoing
void startGame(); // print appropriate messages when the game begins
void exitGame(int total); // print appropriate messages when user exits the game