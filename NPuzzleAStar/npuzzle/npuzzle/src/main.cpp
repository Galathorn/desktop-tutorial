
#include "../includes/nPuzzle.class.hpp"
#include "../includes/Scrambler.class.hpp"
#include "../includes/Environment.class.hpp"
#include <unistd.h>
#include <stdio.h>
#include <iostream>

using namespace std;

bool analyseVector(vector<short> vec)
{
	short amountInversion = 0;
	for (short i = 0; i < vec.size(); ++i)
		for (short j = i + 1; j < vec.size(); ++j)
				if (vec[j] < vec[i])
					amountInversion++;
		if (amountInversion % 2 == 0 && vec.size() % 2 == 0)
		{
			cout << "Number of inversion is even and puzzle size too so the puzzle is NOT SOLVABLE." << endl;
			return false;
		}
		else if (amountInversion % 2 != 0 && vec.size() % 2 != 0)
		{
			cout << "Number of inversion is odd and puzzle size too, so the puzzle is NOT SOLVABLE." << endl;
			return false;
		}
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

void printDetailedSolution(list<string> path, nPuzzle &p, short speed)
{
	int modValue = 5;
	int amountJump = 0;
	list<string>::iterator it = path.begin();
	it++;
	list<string>::iterator end = path.end();
	bool once = false;
	cout << endl << endl;
	for(; it != end; ++it)
	{
		bool first = false;
		int count = 0;
		int jumpValue = p.getSize() + 4 + amountJump;
		amountJump = 0;
		if (once == true)
		 cout << "\033[" << jumpValue << "A";
		if (once == false)
			once = true;
		for (list<string>::iterator i = path.begin(), e = path.end(); i != e; ++i)
			{
				if (first == false)
					{
						first = true;
						continue;
					}
				if (i == it)
					cout << "\033[31m";
				else
					cout << "\033[0m";
				cout << *i << " ";
				if (++count % modValue == 0)
				{
					cout << endl;
					amountJump++;
				}
			}
		cout << "\033[0m";
		p.applyMove(*it);
		usleep((10 - speed) * 50000);
		cout << endl << p << endl;
	}
}

void setupHeuristic(nPuzzle & puzzle, unsigned long flags)
{
	if (flags & MANHATTAN_CONFLICT)
	{
		if (flags & VERBOSE)
			cout << "Heuristic is set to : MANHATTAN DISTANCE + LINEAR CONFLICT" << endl;
		puzzle.setHeuristicMod(MANHATTAN_CONFLICT);
	}
	else if (flags & MANHATTAN)
	{
		if (flags & VERBOSE)
			cout << "Heuristic is set to : MANHATTAN DISTANCE" << endl;
		puzzle.setHeuristicMod(MANHATTAN);
	}
	else if (flags & LINEAR)
	{
		if (flags & VERBOSE)
			cout << "Heuristic is set to : LINEAR DISTANCE" << endl;
		puzzle.setHeuristicMod(LINEAR);
	}
	else if (flags & HAMMING)
	{
		if (flags & VERBOSE)
			cout << "Heuristic is set to : HAMMING DISTANCE" << endl;
		puzzle.setHeuristicMod(HAMMING);
	}
}

void printSolution(list<string> path)
{
	list<string>::iterator it = path.begin();
	list<string>::iterator end = path.end();
	for (; it != end; ++it)
		cout << *it << " ";
	cout << endl;
}

int main(int argc, char**argv)
{
	Environment env = Environment();
	env.parseArgs(argc, argv);
	list<string> path;
	if (env.flags & VERBOSE)
		cout << "Basic puzzle state : " << endl << env.puzzle << endl;
	if (checkInversionCount(env.puzzle))
	{
		setupHeuristic(env.puzzle, env.flags);
		if (env.flags & ASTAR)
		{
				if (env.flags & VERBOSE)
					cout << "Path search with A* algorithm." << endl;
				path = env.astar.findPath(env.puzzle);
		}
		else
		{
			if (env.flags & VERBOSE)
					cout << "Path search with Iterative Deepening A* algorithm." << endl;
			path = env.idAstar.findPath(env.puzzle);
		}
		if (path.size() > 0 && env.flags & VISUAL)
			printDetailedSolution(path, env.puzzle, env.waitLevel);
		else if (path.size() > 0)
			printSolution(path);
	}
	return 0;
}
