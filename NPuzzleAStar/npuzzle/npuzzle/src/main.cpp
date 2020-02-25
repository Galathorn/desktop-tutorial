#include <iostream>

#include "../includes/nPuzzle.class.hpp"
#include "../includes/Scrambler.class.hpp"
#include "../includes/Environment.class.hpp"
#include <unistd.h>
#include <stdio.h>
using namespace std;

bool analyseVector(vector<short> vec)
{
	short amountInversion = 0;
	for (short i = 0; i < vec.size(); ++i)
		for (short j = i + 1; j < vec.size(); ++j)
				if (vec[j] < vec[i])
					amountInversion++;
		cout << "Nombre d'inversion : " << amountInversion << endl;
		if (amountInversion % 2 == 0 && vec.size() % 2 == 0)
		{
			cout << "nombre inversion est pair et le puzzle aussi donc ce dernier n'est PAS SOLVABLE" << endl;
			return false;
		}
		else if (amountInversion % 2 != 0 && vec.size() % 2 != 0)
		{
			cout << "nombre inversion est impair et le puzzle aussi donc ce dernier n'est PAS SOLVABLE" << endl;
			return false;
		}
		cout << "Puzzle est SOLVABLE !" << endl;
		return true;
}

// dans un premier temps, nous allons remplir un tableau vector de short. Pour chaque élément dans la grille, nous allons le mettre dans le vector
// puis nous appellerons une fonction qui analysera ce vector.
bool checkInversionCount(nPuzzle &p)
{
	short size = p.getSize();
	short goalValue = size * size;
	std::vector<std::string> directions = {"RIGHT","DOWN","LEFT","UP"};
	short directionSize = 4;
	short dir = 0;
	short countDir = size;
	short count = 0;
	short y = 0;
	short x = 0;
	short countDown = 1;

	vector<short> vec = vector<short>(goalValue);
	while (++count <= goalValue)
	{
		vec[count - 1] = p.getGrid()[y][x].getValue();
		countDir--;
		if (directions[dir] == "RIGHT")
			countDir == 0 ? y++ : x++;
		else if (directions[dir] == "DOWN")
			countDir == 0 ? x-- : y++;
		else if (directions[dir] == "LEFT")
			countDir == 0 ? y-- : x--;
		else if (directions[dir] == "UP")
			countDir == 0 ? x++ : y--;

			if (countDir == 0)
			{
				countDown++;
				if (countDown == 2)
				{
					countDown = 0;
					size--;
				}
				dir = (dir + 1) % directionSize;
				countDir = size;
			}
	}
	return analyseVector(vec);
}

int main(int argc, char**argv)
{
	int maxScramble = 1000;
	list<string> path;
	Environment env = Environment(4);
	env.parseArgs(argc, argv);
	cout << env.puzzle << endl << endl << endl;
	env.scrambler.scramble(maxScramble, env.puzzle);
	cout << "puzzle state modified by ["<< maxScramble << "] moves" << endl;
	cout << "hCost : " << env.puzzle.getHcost() << endl;
	cout << env.puzzle << endl;
	cout << "Check inversion cout : " << endl;
	checkInversionCount(env.puzzle);
	return 0;
}
