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
		p.setLastMove("");
		std::list<std::string> path;
		std::list<nPuzzle> openSet = std::list<nPuzzle>();
		std::list<nPuzzle> closedSet = std::list<nPuzzle>();

		cout << "ASTAR LAUNCH" << endl;
//		return path;
		openSet.push_back(p);
		int cycle = 0;
	/*	cout << p << endl;
		cout << "hcost :" << p.getHcost() << endl;
		cout << "gcost :" << p.getGcost() << endl;
		cout << "fcost :" << p.fCost() << endl;
 		*/while (openSet.size() > 0)
		{
				cycle++;
	//			cout << "cycle : " << cycle << endl;
				std::list<nPuzzle>::iterator current = openSet.begin();
				std::list<nPuzzle>::iterator it = openSet.begin();
				++it;
				std::list<nPuzzle>::iterator end = openSet.end();
				for (; it != end; ++it)
					if ((*it).fCost() < (*current).fCost() || ((*it).fCost() == (*current).fCost() && (*it).getHcost() < (*current).getHcost()))
							current = it;
/*
				cout << *current << endl;
				cout << "lastMove :" << (*current).getLastMove() << endl;
				cout << "empty value : " << *(*current).getEmpty() << endl;
				cout << "hcost    :" << (*current).getHcost() << endl;
				cout << "gcost    :" << (*current).getGcost() << endl;
				cout << "fcost    :" << (*current).fCost() << endl;
*/
				closedSet.splice(closedSet.end(), openSet, current);
				(*current).fillEmpty((*current).getSize());
				if ((*current).getHcost() <= 0)
				{
						cout << "path has been found after : [" << cycle << "] cycle" << endl;
						nPuzzle *c = (*current).getParent();
						if (c == nullptr)
							return path;
						path.push_back((*current).getLastMove());
						while (c->getId() > 0)
						{
								cout << "move : " << c->getLastMove() << endl;
								cout  << *c << endl;
								path.push_back(c->getLastMove());
								c = c->getParent();
						}
						path.reverse();
						return path;
				}
//				std::vector<nPuzzle> neighbours = getNeighbours(&current);

// ici on récupère les voisins manuellement.
				std::vector<nPuzzle > neighbours = std::vector<nPuzzle>();
//				cout << "neigbours size before search : " << neighbours.size() << endl;
				nPuzzle n;
/*
				if ((*current).getEmpty()->getPos().getY() + 1 < (*current).getSize())
					cout << "Up possible" << endl;
				if ((*current).getEmpty()->getPos().getY() - 1 >= 0)
					cout << "Down possible" << endl;
				if ((*current).getEmpty()->getPos().getX() - 1 >= 0)
					cout << "Right possible" << endl;
				if ((*current).getEmpty()->getPos().getX() + 1 < (*current).getSize())
					cout << "Left possible" << endl;
*/
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
	/*					cout << endl;
						cout << "neighbours[" << i << "].Hcost : " << neighbours[i].getHcost() << " move : " << neighbours[i].getLastMove() << endl;
						cout << "empty value : " << *(neighbours[i].getEmpty()) << endl;
						cout << neighbours[i] << endl;
*/
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
	/*			system ("/bin/stty raw");
				while(std::getchar() != 'e');
				system ("/bin/stty cooked");
*///				if (cycle == 2)
//					return path;
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

bool Astar::isMovementOpposite(std::string const &currentMove, std::string const &lastMove)
{
//		cout << "currentMove : " << currentMove << " lastMove : " << lastMove << endl;
		if ((lastMove == "UP" && currentMove == "DOWN") || (lastMove == "DOWN" && currentMove == "UP"))
		{
//			cout << "OPPOSITE with UP and DOWN are true" << endl;

			return true;
		}
		if ( (lastMove == "RIGHT" && currentMove == "LEFT") || (lastMove == "LEFT" && currentMove == "RIGHT"))
		{
	//			cout << "OPPOSITE with RIGHT and LEFT are true" << endl;
			return true;
		}
		return false;
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
