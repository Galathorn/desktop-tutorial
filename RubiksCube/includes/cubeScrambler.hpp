#ifndef CUBE_SCRAMBLER_HPP
#define CUBE_SCRAMBLER_HPP

#include "./cube.hpp"
#include <list>
#include <iostream>

using namespace std;

class cubeScrambler
{
public:

	cubeScrambler();
	~cubeScrambler();

	void			applySpecificMove(Cube *c, string move);
	void			applySpecificList(Cube *c, list<string> moves);
	list<string>	getRandomList(int amount, vector<string> tabMoves);

	vector<string>			moves = {"R", "L", "U", "D", "F", "B", "M", "R2", "L2", "U2", "D2", "F2", "B2", "M2", "R'", "L'", "U'", "D'", "F'", "B'", "M'", "r", "r'", "r2", "l", "l'", "l2"};
};


#endif
