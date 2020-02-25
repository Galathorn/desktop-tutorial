#include "../includes/Astar.class.hpp"

using namespace std;

Astar::Astar(void) : Algorithm() {}

Astar::~Astar(void) {}

std::list<std::string> Astar::findPath(nPuzzle &p)
{
		p.setLastMove("");
		std::list<std::string> path;
		std::list<nPuzzle> openSet = std::list<nPuzzle>();
		std::list<nPuzzle> closedSet = std::list<nPuzzle>();

		openSet.push_back(p);
		int cycle = 0;
 		while (openSet.size() > 0)
		{
				cycle++;
				std::list<nPuzzle>::iterator current = openSet.begin();
				std::list<nPuzzle>::iterator it = openSet.begin();
				++it;
				std::list<nPuzzle>::iterator end = openSet.end();
				for (; it != end; ++it)
					if ((*it).fCost() < (*current).fCost() || ((*it).fCost() == (*current).fCost() && (*it).getHcost() < (*current).getHcost()))
							current = it;
				closedSet.splice(closedSet.end(), openSet, current);
				(*current).fillEmpty((*current).getSize());
				if ((*current).getHcost() <= 0)
				{
						nPuzzle *c = (*current).getParent();
						if (c == nullptr)
							return path;
						path.push_back((*current).getLastMove());
						while (c->getId() > 0)
						{
								path.push_back(c->getLastMove());
								c = c->getParent();
						}
						path.reverse();
						return path;
				}
				std::vector<nPuzzle > neighbours = std::vector<nPuzzle>();
				nPuzzle n;
				if ((*current).getEmpty()->getPos().getY() + 1 < (*current).getSize() && isMovementOpposite("UP", (*current).getLastMove()) == false)
				{
						n = nPuzzle((*current).getSize());
						(*current).copyData(&n);
						n.Up();
						neighbours.push_back(n);
				}
				if ((*current).getEmpty()->getPos().getY() - 1 >= 0 && isMovementOpposite("DOWN", (*current).getLastMove()) == false)
				{
						n = nPuzzle((*current).getSize());
						(*current).copyData(&n);
						n.Down();
						neighbours.push_back(n);
				}
				if ((*current).getEmpty()->getPos().getX() - 1 >= 0 && isMovementOpposite("RIGHT", (*current).getLastMove()) == false)
				{
						n = nPuzzle((*current).getSize());
						(*current).copyData(&n);
						n.Right();
						neighbours.push_back(n);
				}
				if ((*current).getEmpty()->getPos().getX() + 1 < (*current).getSize() && isMovementOpposite("LEFT", (*current).getLastMove()) == false)
				{
						n = nPuzzle((*current).getSize());
						(*current).copyData(&n);
						n.Left();
						neighbours.push_back(n);
				}
				for (short i = 0; i < neighbours.size(); ++i)
				{
						if (std::find(closedSet.begin(), closedSet.end(), neighbours[i]) != closedSet.end())
								continue;
						neighbours[i].fillEmpty(neighbours[i].getSize());
						bool contains = std::find(openSet.begin(), openSet.end(), neighbours[i]) == openSet.end() ? false : true;
						short newMovementCostToNeighbour = (*current).getGcost() + 1;
						if (newMovementCostToNeighbour < neighbours[i].getGcost() || contains == false)
						{
									neighbours[i].setGcost(newMovementCostToNeighbour);
									neighbours[i].setParent(&(*current));
									if (contains == false)
										openSet.push_back(neighbours[i]);
						}
				}
		}
		return path;
}

bool Astar::isMovementOpposite(std::string const &currentMove, std::string const &lastMove)
{
		if ((lastMove == "UP" && currentMove == "DOWN") || (lastMove == "DOWN" && currentMove == "UP"))
			return true;
		if ( (lastMove == "RIGHT" && currentMove == "LEFT") || (lastMove == "LEFT" && currentMove == "RIGHT"))
			return true;
		return false;
}
