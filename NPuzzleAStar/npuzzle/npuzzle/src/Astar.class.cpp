#include "../includes/Astar.class.hpp"

using namespace std;

Astar::Astar(void) : Algorithm()
{

}

Astar::~Astar(void)
{

}


// function without pool

std::vector<nPuzzle > Astar::getNeighbours(nPuzzle * current)
{
		std::vector<nPuzzle > neighbours = std::vector<nPuzzle>();
		nPuzzle n;
		if (current->getEmpty()->getPos().getY() + 1 < current->getSize())
		{
				n = nPuzzle(current->getSize());
				n = current->copyData(&n);
				n.Up();
				neighbours.push_back(n);
		}
		if (current->getEmpty()->getPos().getY() - 1 >= 0)
		{
				n = nPuzzle(current->getSize());
				n = current->copyData(&n);
				n.Down();
				neighbours.push_back(n);
		}
		if (current->getEmpty()->getPos().getX() - 1 >= 0)
		{
				n = nPuzzle(current->getSize());
				n = current->copyData(&n);
				n.Right();
				neighbours.push_back(n);
		}
		if (current->getEmpty()->getPos().getX() + 1 < current->getSize())
		{
				n = nPuzzle(current->getSize());
				n = current->copyData(&n);
				n.Left();
				neighbours.push_back(n);
		}
		return neighbours;
}

std::list<std::string> Astar::findPath(nPuzzle &p)
{
		std::list<std::string> path;
		std::list<nPuzzle> openSet = std::list<nPuzzle>();
		std::list<nPuzzle> closedSet = std::list<nPuzzle>();

		cout << "ASTAR LAUNCH" << endl;
		openSet.push_back(p);
		int cycle = 0;
		while (openSet.size() > 0)
		{
				cycle++;
	//			cout << "cycle : " << cycle << endl;
				std::list<nPuzzle>::iterator current = openSet.begin();
				std::list<nPuzzle>::iterator it = openSet.begin();
				++it;
				std::list<nPuzzle>::iterator end = openSet.end();
				for (; it != end; ++it)
					if ((*it).fCost() < (*current).fCost() || (*it).fCost() == (*current).fCost() && (*it).getHcost() < (*current).getHcost())
							current = it;
				closedSet.splice(closedSet.end(), openSet, current);
				if ((*current).getHcost() <= 0)
				{
						cout << "path has been found after : [" << cycle << "] cycle" << endl;
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
//				std::vector<nPuzzle> neighbours = getNeighbours(&current);

// ici on récupère les voisins manuellement.
				std::vector<nPuzzle > neighbours = std::vector<nPuzzle>();
				nPuzzle n;
				if ((*current).getEmpty()->getPos().getY() + 1 < (*current).getSize())
				{
						n = nPuzzle((*current).getSize());
						(*current).copyData(&n);
						n.Up();
						neighbours.push_back(n);
				}
				if ((*current).getEmpty()->getPos().getY() - 1 >= 0)
				{
						n = nPuzzle((*current).getSize());
						(*current).copyData(&n);
						n.Down();
						neighbours.push_back(n);
				}
				if ((*current).getEmpty()->getPos().getX() - 1 >= 0)
				{
						n = nPuzzle((*current).getSize());
						(*current).copyData(&n);
						n.Right();
						neighbours.push_back(n);
				}
				if ((*current).getEmpty()->getPos().getX() + 1 < (*current).getSize())
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
/*
				if (current->getHcost() <= 2)
				{
						cout << cycle << endl;
				cout << *current << endl;
				cout << "gcost : " << current->getGcost() << endl;
				cout << "Hcost : " << current->getHcost() << endl;
				cout << "fcost : " << current->fCost() << endl;
				while(cin.get() != '\n');
			}
*/
		}




		return path;
}

// functions using pool
std::vector<nPuzzle> Astar::getNeighboursUsingPool(nPuzzle &current, std::stack<nPuzzle> &pool)
{

}

std::list<std::string> Astar::findPathUsingPool(nPuzzle &p, std::stack<nPuzzle> &pool)
{
	std::list<std::string> path;
	path.push_back("swag");
	return path;
}
