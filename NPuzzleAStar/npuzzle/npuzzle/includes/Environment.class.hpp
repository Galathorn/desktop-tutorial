#ifndef ENVIRONMENT_CLASS_HPP
#define ENVIRONMENT_CLASS_HPP

#include "./nPuzzle.class.hpp"
#include "./Scrambler.class.hpp"
#include "./Astar.class.hpp"
#include "./IDaStar.class.hpp"
#include <stack>
#include <string.h>

class Environment
{
	public:
	Environment(short puzzleSize);
	~Environment(void);

	void 								parseArgs(int ac, char**av);


	nPuzzle							puzzle;
	Scrambler						scrambler;
	Astar 							astar;
	IDaStar 						idAstar;

	int 								flags;

};

#endif
