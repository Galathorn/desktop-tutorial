#ifndef ASTAR_CLASS_HPP
#define ASTAR_CLASS_HPP

#include "./Algorithm.class.hpp"
#include "./nPuzzle.class.hpp"
#include <list>
#include <stack>

class Astar : public Algorithm
{
	public:
	Astar();
	~Astar();

	std::vector<nPuzzle> getNeighboursUsingPool(nPuzzle &current, std::stack<nPuzzle> &pool);
	std::vector<nPuzzle> getNeighbours(nPuzzle *current);

	std::list<std::string> findPath(nPuzzle &puzzle);
	std::list<std::string> findPathUsingPool(nPuzzle &puzzle, std::stack<nPuzzle> &pool);
};


#endif
