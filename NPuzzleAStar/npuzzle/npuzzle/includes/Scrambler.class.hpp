#ifndef SCRAMBLER_CLASS_HPP
#define SCRAMBLER_CLASS_HPP

#include <vector>
#include <iostream>
#include "../includes/nPuzzle.class.hpp"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;

class Scrambler
{
	public:
	Scrambler();
	~Scrambler();

	void scramble(short nMoves, nPuzzle &puzzle);
	bool applyMove(std::string move, nPuzzle &puzzle);

	private:
	std::vector<std::string> _moves =	{"UP", "RIGHT","DOWN","LEFT"};
	std::vector<std::string> _noUp =		{"RIGHT", "LEFT"};
	std::vector<std::string> _noDown =	{"RIGHT", "LEFT"};
	std::vector<std::string> _noRight =	{"UP", "DOWN"};
	std::vector<std::string> _noLeft =	{"UP", "DOWN"};
	std::string lastMove;
};

#endif
