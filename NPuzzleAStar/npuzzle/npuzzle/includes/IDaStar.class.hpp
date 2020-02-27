#ifndef ID_ASTAR_CLASS_HPP
#define ID_ASTAR_CLASS_HPP

#include "./Algorithm.class.hpp"
#include <limits>

#define SHORT_MAX 32767
class IDaStar : public Algorithm
{
	public :
	IDaStar(void);
	~IDaStar(void);

	bool										isMovementOpposite(std::string const &currentMove, std::string const &lastMove);
	int 										search(list<nPuzzle> &path, short gCost, short bound, short cycle);
	std::list<std::string>	findPath(nPuzzle &puzzle);
};

#endif
