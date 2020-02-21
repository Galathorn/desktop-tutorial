#include "../includes/Astar.class.hpp"

using namespace std;

Astar::Astar(void) : Algorithm()
{

}

Astar::~Astar(void)
{

}


// function without pool

std::vector<nPuzzle *> Astar::getNeighbours(nPuzzle * current)
{
		std::vector<nPuzzle *> neighbours = std::vector<nPuzzle *>();
		nPuzzle *n;
		if (current->getEmpty()->getPos().getY() + 1 < current->getSize())
		{
				n = current->copy();
				n->Up();
				neighbours.push_back(n);
		}
		if (current->getEmpty()->getPos().getY() - 1 >= 0)
		{
				n = current->copy();
				n->Down();
				neighbours.push_back(n);
		}
		if (current->getEmpty()->getPos().getX() - 1 >= 0)
		{
				n = current->copy();
				n->Right();
				neighbours.push_back(n);
		}
		if (current->getEmpty()->getPos().getX() + 1 < current->getSize())
		{
				n = current->copy();
				n->Left();
				neighbours.push_back(n);
		}
		return neighbours;
}

std::list<std::string> Astar::findPath(nPuzzle &p)
{
		std::list<std::string> path;
		std::list<nPuzzle *> openSet = std::list<nPuzzle *>();
		std::list<nPuzzle *> closedSet = std::list<nPuzzle *>();

		cout << "ASTAR LAUNCH" << endl;
		openSet.push_back(&p);
		int cycle = 0;
		while (openSet.size() > 0)
		{
				cycle++;
	//			cout << "cycle : " << cycle << endl;
				nPuzzle *current = *openSet.begin();
				std::list<nPuzzle *>::iterator it = openSet.begin();
				++it;
				std::list<nPuzzle *>::iterator end = openSet.end();
				for (; it != end; ++it)
					if ((*it)->fCost() < current->fCost() || (*it)->fCost() == current->fCost() && (*it)->getHcost() < current->getHcost())
							current = (*it);
				openSet.remove(current);
				closedSet.push_back(current);
				if (current->getHcost() <= 0)
				{

						cout << "path has been found after : [" << cycle << "] cycle" << endl;
						while (current->getId() > 0)
						{
								cout << current->getLastMove() << endl;
								current = current->getParent();
						}
						return path;
				}
				std::vector<nPuzzle *> neighbours = getNeighbours(current);
				for (short i = 0; i < neighbours.size(); ++i)
				{
						if (std::find(closedSet.begin(), closedSet.end(), neighbours[i]) != closedSet.end())
								continue;
						bool contains = std::find(openSet.begin(), openSet.end(), neighbours[i]) == openSet.end() ? false : true;
						short newMovementCostToNeighbour = current->getGcost() + 1;
						if (newMovementCostToNeighbour < neighbours[i]->getGcost() || contains == false)
						{
									neighbours[i]->setGcost(newMovementCostToNeighbour);
									neighbours[i]->setParent(current);
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
