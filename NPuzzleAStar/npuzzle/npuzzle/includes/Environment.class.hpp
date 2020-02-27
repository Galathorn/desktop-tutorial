#ifndef ENVIRONMENT_CLASS_HPP
#define ENVIRONMENT_CLASS_HPP

using namespace std;

#include "./nPuzzle.class.hpp"
#include "./Scrambler.class.hpp"
#include "./Astar.class.hpp"
#include "./IDaStar.class.hpp"
#include <stack>
#include <string.h>
#include <iostream>
#include <fstream>
#include <bitset>

#define ASTAR 0x01
#define GREEDY 0x02
#define UNIFORM 0X04
#define MANHATTAN 0x08
#define LINEAR 0x10
#define HAMMING 0x20
#define SIZE 0x40
#define SCRAMBLER 0x80
#define VISUAL (1 << 8)
#define FILE (1 << 9)
#define CLASSIC (1 << 10)
#define MANHATTAN_CONFLICT (1 << 11)
#define VERBOSE (1 << 12)

class Environment
{
	public:
		Environment(short puzzleSize);
		Environment(void);
		~Environment(void);

		void 									error(string s) const;
		void 									checkForFlagsError() const;
		void 									checkForFile(char * argv);
		void 									parseArgs(int ac, char**av);


	nPuzzle									puzzle;
	Scrambler								scrambler;
	Astar 									astar;
	IDaStar 								idAstar;

	unsigned long						flags;

	short 									sizePuzzle; // taille du puzzle qui devra etre construit
	short 									waitLevel; // niveau d'attente
	short 									scramblerAmountMove;

};

#endif
