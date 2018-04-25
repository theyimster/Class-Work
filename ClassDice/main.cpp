#include "Dice.h"

int main(int argc, char **argv)
{
	cout << "How many people are in your Dice Group: ";
	int dicers;
	cin >> dicers;
	cout << "How many sides should their dice have: ";
	int sides;
	cin >> sides;
	DiceGroup people(sides,dicers);
	DiceRoll group = people.roll();
	cout << "Rolling " << group.numDice << "x" << group.numSides
		 << "-sided:" << endl;
	for (int i=0;i<group.numDice;i++) 
		cout << "    " << i+1 << ":" << group.diceInstances[i] << endl;
	cout << "Total: " << group.total << endl;
	return 0;
}
