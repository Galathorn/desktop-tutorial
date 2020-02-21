#ifndef ENVIRONMENT_CLASS_HPP
#define ENVIRONMENT_CLASS_HPP

#include "./nPuzzle.class.hpp"
#include "./Scrambler.class.hpp"
#include "./Astar.class.hpp"
#include <stack>

class Environment
{
	public:
	Environment(short puzzleSize, int amountStack);
	~Environment(void);

	std::stack<nPuzzle>	pool; // container stockant l'ensemble des node sur lesquel va travailler les algorithmes.
	nPuzzle							puzzle;
	Scrambler						scrambler;
	Astar 							astar;

};

#endif
