#include "../includes/IDaStar.class.hpp"

using namespace std;

IDaStar::IDaStar(void) : Algorithm() {}

IDaStar::~IDaStar(void) {}

bool IDaStar::isMovementOpposite(std::string const &currentMove, std::string const &lastMove)
{
		if ((lastMove == "UP" && currentMove == "DOWN") || (lastMove == "DOWN" && currentMove == "UP"))
			return true;
		if ( (lastMove == "RIGHT" && currentMove == "LEFT") || (lastMove == "LEFT" && currentMove == "RIGHT"))
			return true;
		return false;
}

int IDaStar::search(list<nPuzzle> &path, short g, short bound, short cycle)
{
	nPuzzle current = path.back();
	setTimeComplexity(getTimeComplexity() + 1);
	current.fillEmpty(current.getSize());
	short f = g + current.getHcost();
	if (f > bound)
		return f;
	if (current.getHcost() == 0 && current.isGoal())
		return 0;
	short min = SHORT_MAX;
	std::vector<nPuzzle > neighbours = std::vector<nPuzzle>();
	nPuzzle n;
	if (current.getEmpty()->getPos().getY() + 1 < current.getSize() && isMovementOpposite("UP", current.getLastMove()) == false)
	{
			n = nPuzzle(current.getSize());
			current.copyData(&n);
			n.Up();
			neighbours.push_back(n);
	}
	if (current.getEmpty()->getPos().getY() - 1 >= 0 && isMovementOpposite("DOWN", current.getLastMove()) == false)
	{
			n = nPuzzle(current.getSize());
			current.copyData(&n);
			n.Down();
			neighbours.push_back(n);
	}
	if (current.getEmpty()->getPos().getX() - 1 >= 0 && isMovementOpposite("RIGHT", current.getLastMove()) == false)
	{
			n = nPuzzle(current.getSize());
			current.copyData(&n);
			n.Right();
			neighbours.push_back(n);
	}
	if (current.getEmpty()->getPos().getX() + 1 < current.getSize() && isMovementOpposite("LEFT", current.getLastMove()) == false)
	{
			n = nPuzzle(current.getSize());
			current.copyData(&n);
			n.Left();
			neighbours.push_back(n);
	}
	for (short i = 0; i < neighbours.size(); ++i)
			if (std::find(path.begin(), path.end(), neighbours[i]) == path.end())
					{
						path.push_back(neighbours[i]);
						if (getSizeComplexity() < path.size())
							setSizeComplexity(path.size());
						short t = search(path, g + 1, bound, cycle + 1);
						if (t == 0)
							return 0;
						else if (t < min)
							min = t;
						if (path.size() > 0)
							path.pop_back();
					}
	return min;
}

list<string> IDaStar::findPath(nPuzzle &p)
{
	p.setLastMove("");
	list<nPuzzle>	l = list<nPuzzle>();
	list<string>	path = list<string>();
	l.push_back(p);
	short bound = p.getHcost();
	short cycle = 0;
	while (1)
	{
		short t = this->search(l, 0, bound, cycle);
		if (t == -1)
			return path;
		if (t == 0 || t == SHORT_MAX)
		{
			for (list<nPuzzle>::iterator it = l.begin(), end = l.end(); it != end; it++)
				if ((*it).getLastMove() != "")
					path.push_back((*it).getLastMove());
			return path;
		}
		bound = t;
	}

	return path;
}
