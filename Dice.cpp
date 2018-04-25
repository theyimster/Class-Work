#include "Dice.h"

//
// Dice (constructor)
// Default to 6-sided dice.
//
Dice::Dice() {
    numSides = 6;
}   
//
// Dice (constructor - overloaded)
// Set number of sides to passed parameter.
//         
Dice::Dice(int n) {
    numSides = n;
}  
// 
// setRandom (static)
// Sets random number seed.
//   
void   Dice::setRandom() {
    srand(time(NULL));
}
//
// roll
// Returns a random roll of the dice.
// 
int    Dice::roll() {
    return(rand() % numSides + 1);
}  
//
// getSides
// Accessor method for numSides.
//    
int    Dice::getSides() {
    return(numSides);
}      
// 
// setSides
// Mutator method for numSides.
//
void   Dice::setSides(int n) {
    numSides = n;
}

DiceGroup::DiceGroup(int side, int dice) {
	numSides = side;
	numDice = dice;
	group = new Dice[numDice];
	group->setSides(numSides);
}

DiceRoll DiceGroup::roll() {
	DiceRoll d;
	d.numDice = numDice;
	d.numSides = numSides;
	d.diceInstances = new int[numDice];
	for (int i=0; i<numDice;i++) {
		d.diceInstances[i] = group->roll();
		d.total += d.diceInstances[i];
	}
	return(d);
}

int DiceGroup::getSides(int sides) {
	return(sides);
}

int DiceGroup::getNumDice(int dice) {
	return(dice);
}

DiceGroup::~DiceGroup() {
}