#ifndef ASTAR_CLASS_HPP
#define ASTAR_CLASS_HPP

#include "./Algorithm.class.hpp"
#include "./nPuzzle.class.hpp"
#include <list>

class Astar : public Algorithm
{
	public:
	Astar();
	~Astar();

	std::list<std::string> findPath(nPuzzle puzzle);
};


#endif
