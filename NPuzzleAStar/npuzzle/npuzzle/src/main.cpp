#include <iostream>

#include "../includes/nPuzzle.class.hpp"
#include "../includes/Scrambler.class.hpp"

using namespace std;

void printNpuzzle(nPuzzle &puzzle)
{
	cout << puzzle << endl;
	cout << "id : " << puzzle.getId() << endl;
	cout << "size : " << puzzle.getSize() << endl;
	
}

int main()
{
	nPuzzle		puzzle = nPuzzle(3);
	Scrambler scramble = Scrambler();


	cout << puzzle << endl;
	cout << "empty coord : " << puzzle.getEmpty()->getPos() << endl;


	scramble.scramble(50, puzzle);


		cout << puzzle << endl;
		cout << "empty coord : " << puzzle.getEmpty()->getPos() << endl;

		cout << endl << endl << "a partir de maintenant je vais instantier un nouveau nPuzzle, l'afficher, copier le premier npuzzle dans le second et ré afficher l'instance :" << endl;

		nPuzzle p2 = nPuzzle(3);

		cout << p2 << endl;
		cout << "empty coord : " << puzzle.getEmpty()->getPos() << endl << endl;

		puzzle.copyData(p2); // copy de l'ensemble de puzzle vers p2

		cout << p2 << endl;
		cout << "empty coord : " << puzzle.getEmpty()->getPos() << endl << endl;

	return 0;
}
