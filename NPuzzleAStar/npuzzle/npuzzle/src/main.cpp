
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
			exit(0);
		}
		else if (amountInversion % 2 != 0 && vec.size() % 2 != 0)
		{
			cout << "Number of inversion is odd and puzzle size too, so the puzzle is NOT SOLVABLE." << endl;
			exit(0);
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

void printExecutionDetails(Environment const &env, int size)
{
	if (env.flags & ASTAR)
		{
				cout << endl << "Amount of movement : [" << size << "]" << endl;
				cout << "Complexity in time : [" << env.astar.getTimeComplexity() << "]" << endl;
				cout << "Complexity in size : [" << env.astar.getSizeComplexity() << "]" << endl << endl;
		}
	else
	{
		cout << endl << "Amount of movement : [" << size << "]" << endl;
		cout << "Complexity in time : [" << env.idAstar.getTimeComplexity() << "]" << endl;
		cout << "Complexity in size : [" << env.idAstar.getSizeComplexity() << "]" << endl << endl;
	}
}

void printDetailedSolution(list<string> path, nPuzzle &p, short speed)
{
	int modValue = 5;
	int amountJump = 0;
	list<string>::iterator it = path.begin();
	if (*it == "")
		it++;
	list<string>::iterator end = path.end();
	bool once = false;
	cout << endl << endl;

	for(; it != end; ++it)
	{
		int count = 0;
		int jumpValue = p.getSize() + 4 + amountJump;
		amountJump = 0;
		if (once == true)
		 cout << "\033[" << jumpValue << "A";
		if (once == false)
			once = true;
		for (list<string>::iterator i = path.begin(), e = path.end(); i != e; ++i)
			{
				if (*i == "")
						continue;
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
	else if (flags & UNIFORM)
	{
		if (flags & VERBOSE)
			cout << "Heuristic is set to : UNIFORM SEARCH -> BRUTE FORCE" << endl;
			puzzle.setHeuristicMod(UNIFORM);
	}
}

void printSolution(list<string> path)
{
	list<string>::iterator it = path.begin();
	if (*it == "")
		it++;
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

	if (env.flags & FILE)
		checkInversionCount(env.puzzle);
	else if (env.flags & SIZE)
	{
		if (env.flags & CLASSIC && env.flags && VERBOSE)
			cout << "Classic position is enabled" << endl << endl;
		env.puzzle = nPuzzle(env.sizePuzzle, env.flags & CLASSIC ? true : false);
	}
	else
	{
		env.puzzle = nPuzzle(3, env.flags & CLASSIC ? true : false);
		env.flags |= SCRAMBLER;
		env.scramblerAmountMove = 100;
		if (env.flags & VERBOSE)
			cout << "No file or size provided. Auto-generated random 3*3 puzzle." << endl << endl;
		if (env.flags & VERBOSE && env.flags & CLASSIC)
			cout << "Classic position is enabled" << endl << endl;
	}
	setupHeuristic(env.puzzle, env.flags);
	if (!(env.flags & FILE))
		cout << "Basic puzzle state : " << endl << env.puzzle << endl;
	if ((env.flags & SCRAMBLER) && env.scramblerAmountMove > 0)
	{
			env.scrambler.scramble(static_cast<int>(env.scramblerAmountMove), env.puzzle);
			if (env.flags & VERBOSE)
			{
				cout << "Puzzle is scramble with : " << env.scramblerAmountMove << endl;
				cout << "New puzzle state :" << endl << env.puzzle << endl;
			}
	}
	if (env.flags & ASTAR)
		{
				if (env.flags & VERBOSE)
					cout << "Path search with A* algorithm." << endl << endl;
				path = env.astar.findPath(env.puzzle);
		}
	else
		{
			if (env.flags & VERBOSE)
					cout << "Path search with Iterative Deepening A* algorithm." << endl << endl;
			path = env.idAstar.findPath(env.puzzle);
		}
	if (path.size() > 0)
		printExecutionDetails(env, path.size());
	if (path.size() > 0 && env.flags & VISUAL)
			printDetailedSolution(path, env.puzzle, env.waitLevel);
	else if (path.size() > 0)
			printSolution(path);
	return 0;
}
