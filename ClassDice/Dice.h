#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

class Dice {
    private:
        int numSides;
        
    public:
        Dice();                  // default is 6-sided
        Dice(int n);             // number of sides
        static void setRandom(); //sets random number seed
        int    roll();           // returns random roll
        int    getSides();       // accessor method for numSides
        void   setSides(int n);  // mutator method for numSides
};

struct DiceRoll {
	int numDice;
	int numSides;
	int * diceInstances;
	int total;
};

class DiceGroup {
	public:
		DiceGroup(int side, int dice);
		DiceRoll roll();
		int getNumDice(int dice);
		int getSides(int sides);
		~DiceGroup();
		
	private:
		int numSides;
		int numDice;
		Dice * group;
};
