#ifndef ASTAR_CLASS_HPP
#define ASTAR_CLASS_HPP

#include "./Algorithm.class.hpp"
#include <list>
#include <stack>

using namespace std;

class Astar : public Algorithm
{
	public:
	Astar();
	~Astar();

	bool										isMovementOpposite(std::string const &currentMove, std::string const &lastMove);
	std::list<std::string>	findPath(nPuzzle &puzzle);
};


#endif
