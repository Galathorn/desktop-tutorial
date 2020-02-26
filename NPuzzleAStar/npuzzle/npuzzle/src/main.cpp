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

void printSolution(list<string> path, nPuzzle &p, short speed)
{
	list<string>::iterator it = path.begin();
	list<string>::iterator end = path.end();
	bool once = false;
	cout << endl << endl;
	for(; it != end; ++it)
	{
		if (once == true)
		 cout << "\033[" << p.getSize() + 4 << "A";
		if (once == false)
			once = true;
		for (list<string>::iterator i = path.begin(), e = path.end(); i != e; ++i)
			{
		//		if (it == end)
		//			break;
				if (i == it)
					cout << "\033[31m";
				else
					cout << "\033[0m";
				cout << *i << " ";
			}
		cout << "\033[0m";
		p.applyMove(*it);
		usleep((10 - speed) * 50000);
		cout << endl << p << endl;
	}
}

int main(int argc, char**argv)
{
	int maxScramble = 1000;
	list<string> path;
	Environment env = Environment();
	env.parseArgs(argc, argv);
	cout << env.puzzle << endl << endl << endl;
//	env.scrambler.scramble(maxScramble, env.puzzle);
//	cout << "puzzle state modified by ["<< maxScramble << "] moves" << endl;
	cout << "hCost : " << env.puzzle.getHcost() << endl;
	cout << env.puzzle << endl;
	cout << "Check inversion cout : " << endl;
	bool solvable = checkInversionCount(env.puzzle);
	if (solvable == true)
	{
		path = env.idAstar.findPath(env.puzzle);
		if (path.size() > 0 && env.flags & VISUAL)
			printSolution(path, env.puzzle, env.waitLevel);
	}
	return 0;
}
