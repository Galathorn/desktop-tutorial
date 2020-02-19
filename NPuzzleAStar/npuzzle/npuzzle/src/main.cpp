#include <iostream>

#include "../includes/nPuzzle.class.hpp"
#include "../includes/Scrambler.class.hpp"

using namespace std;

int main()
{
	nPuzzle		puzzle = nPuzzle(3);
	Scrambler scramble = Scrambler();


	cout << puzzle << endl;
	cout << "empty coord : " << puzzle.getEmpty()->getPos() << endl;


	scramble.scramble(500, puzzle);


		cout << puzzle << endl;
		cout << "empty coord : " << puzzle.getEmpty()->getPos() << endl;




	return 0;
}
