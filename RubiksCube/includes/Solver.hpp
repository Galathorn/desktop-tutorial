#ifndef SOLVER_HPP
#define SOLVER_HPP

#include <map>
#include <list>
#include <iostream>
using namespace std;

class Solver
{
public :
	Solver();
	~Solver();

	list<string>	optimiseSolution(list<string> solution);
	string			getStateRotation(string currentRotation, string move);


};

#endif
