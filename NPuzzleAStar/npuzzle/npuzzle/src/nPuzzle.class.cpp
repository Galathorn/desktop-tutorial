#include "../includes/nPuzzle.class.hpp"

using namespace std;

nPuzzle::nPuzzle(short size) : _size(size), _id(0), _gCost(0), _parent(nullptr), _lastMove(""), _empty(nullptr), _hCost(0.0), _heuristicMod(MANHATTAN_CONFLICT)
{
	this->setupGrid(size);
	this->fillSnailGrid(size);
//	this->fillClassicGrid(size);
}


nPuzzle::nPuzzle(short size, bool mode) : _size(size), _id(0), _gCost(0), _parent(nullptr), _lastMove(""), _empty(nullptr), _hCost(0.0), _heuristicMod(MANHATTAN_CONFLICT)
{
	this->setupGrid(size);
	mode == false ? this->fillSnailGrid(size) : this->fillClassicGrid(size);
}


nPuzzle::nPuzzle(void) : _size(0), _id(0), _gCost(0), _parent(nullptr), _lastMove(""), _empty(nullptr),  _hCost(0.0), _heuristicMod(MANHATTAN_CONFLICT)
{
	setupGrid(0);
}

nPuzzle::~nPuzzle(void) {}

void nPuzzle::setupGrid(short size)
{
		_grid = std::vector<std::vector<Node>>(size);
		for(short y = 0; y < size; ++y)
		{
			_grid[y] = std::vector<Node>(size);
				for(short x = 0; x < size; ++x)
					_grid[y][x] = Node(y, x, 0);
		}
}

// major fonction

void nPuzzle::fillClassicGrid(short mSize)
{
	short max = mSize * mSize;
	short current = 0;
	for(short y = 0; y < mSize; ++y)
		for(short x = 0; x < mSize; ++x)
			if (++current < max)
				_grid[y][x].setValue( current);
	this->fillEmpty(mSize);
}

void nPuzzle::fillSnailGrid(short mSize)
{
	short size = mSize;
	short goalValue = mSize * mSize;
	std::vector<std::string> directions = {"RIGHT","DOWN","LEFT","UP"};
	short directionSize = 4;
	short dir = 0;
	short countDir = mSize;
	short count = 0;
	short y = 0;
	short x = 0;
	short countDown = 1;
	while (++count <= goalValue)
	{
		_grid[y][x].setValue(count == goalValue ? 0 : count);
		countDir--;
		if (directions[dir] == "RIGHT")
			countDir == 0 ? y++ : x++;
		else if (directions[dir] == "DOWN")
			countDir == 0 ? x-- : y++;
		else if (directions[dir] == "LEFT")
			countDir == 0 ? y-- : x--;
		else if (directions[dir] == "UP")
			countDir == 0 ? x++ : y--;

			if (countDir == 0)
			{
				countDown++;
				if (countDown == 2)
				{
					countDown = 0;
					size--;
				}
				dir = (dir + 1) % directionSize;
				countDir = size;
			}
	}
	this->fillEmpty(mSize);
}


void nPuzzle::fillEmpty(short mSize)
{
	for (short y = 0; y < mSize; ++y)
		for (short x = 0; x < mSize; ++x)
		{
				if (_grid[y][x].getValue() == 0)
				{
						this->setEmpty( &(_grid[y][x]) );
						return ;
				}
		}
}

void nPuzzle::updateHcost()
{
	if (_heuristicMod == MANHATTAN_CONFLICT)
		this->setHcost(this->getManhattanAndLinearConflict()); // on recalcule tout l'heuristique a chaque deplacement.
	else if (_heuristicMod == MANHATTAN)
		this->setHcost(this->getManhattan()); // on recalcule tout l'heuristique a chaque deplacement.
	else if (_heuristicMod == LINEAR)
		this->setHcost(this->getPythagoras()); // on recalcule tout l'heuristique a chaque deplacement.
	else if (_heuristicMod == HAMMING)
		this->setHcost(this->getHamming());
	else if (_heuristicMod == UNIFORM)
		this->setHcost(0);
}

void nPuzzle::swapNode(short y, short x, short emptyY, short emptyX)
{
		Node tmpNode = _grid[y][x];
		_grid[y][x] = _grid[emptyY][emptyX];
		_grid[emptyY][emptyX] = tmpNode;
		Pos tmpPos = Pos(_grid[y][x].getPos().getY(), _grid[y][x].getPos().getX());
		_grid[y][x].setPos(_grid[emptyY][emptyX].getPos());
		_grid[emptyY][emptyX].setPos(tmpPos);

		_empty = &(_grid[y][x]); // on redéfinit l'adresse du pointeur sinon ça chie dans la colle.
		this->updateHcost();
}

// movements functions
bool nPuzzle::applyMove(string m)
{
	if (m == "UP")
		return Up();
	else if (m == "DOWN")
		return Down();
	else if (m == "LEFT")
		return Left();
	else if (m == "RIGHT")
		return Right();
	return false;
}


bool nPuzzle::Up()
{
	if (_empty->getPos().getY() + 1 >= _size)
		return false;
		Node n = _grid[_empty->getPos().getY() + 1][_empty->getPos().getX()];
		swapNode(n.getPos().getY(), n.getPos().getX(), _empty->getPos().getY(), _empty->getPos().getX());
		_lastMove = "UP";
		return true;
}

bool nPuzzle::Right()
{
	if (_empty->getPos().getX() - 1 < 0)
		return false;
		Node n = _grid[_empty->getPos().getY()][_empty->getPos().getX() - 1];
		swapNode(n.getPos().getY(), n.getPos().getX(), _empty->getPos().getY(), _empty->getPos().getX());
		_lastMove = "RIGHT";
		return true;
}

bool nPuzzle::Down()
{
	if (_empty->getPos().getY() - 1 < 0)
		return false;
		Node n = _grid[_empty->getPos().getY() - 1][_empty->getPos().getX()];
		swapNode(n.getPos().getY(), n.getPos().getX(), _empty->getPos().getY(), _empty->getPos().getX());
		_lastMove = "DOWN";
		return true;
}

bool nPuzzle::Left()
{
	if (_empty->getPos().getX() + 1 >= _size)
		return false;
		Node n = _grid[_empty->getPos().getY()][_empty->getPos().getX() + 1];
		swapNode(n.getPos().getY(), n.getPos().getX(), _empty->getPos().getY(), _empty->getPos().getX());
		_lastMove = "LEFT";
		return true;
}

// fonctions de copy de l'élément en cours

void nPuzzle::arrayToGrid(list<int> const &array)
{
	if (_size != sqrt(array.size()))
		{
			cout << "invalid size of array" << endl;
			return ;
		}
	nPuzzle tmp = nPuzzle(_size); // temporaire qui permettra de copier les truePos de chaque node de la nouvelle instance.
	std::list<int>::const_iterator it = array.begin();
	std::list<int>::const_iterator end = array.end();
	for (short y = 0; y < _size && it != end; ++y)
		for (short x = 0; x < _size && it != end; ++x)
			{
				_grid[y][x].setValue(*it);
				bool found = false;
				for (short _y = 0; _y <_size; ++_y)
				{
					if (found == true)
						break ;
					for (short _x = 0; _x < _size; ++_x)
						if (tmp.getGrid()[_y][_x].getValue() == *it)
							{
								_grid[y][x].setTruePos(tmp.getGrid()[_y][_x].getTruePos());
								found = true;
							}
				}
				it++;
			}
}

// cette fonction parcours la grille et vérifie que chaque node est bel est bien à sa place, si c'est le cas cela veut direque le puzzl en cours est bien la solution.
bool nPuzzle::isGoal(void) const
{
	for (short y = 0; y < _size; ++y)
		for (short x = 0; x < _size; ++x)
			if (_grid[y][x].getPos().getX() != _grid[y][x].getTruePos().getX() || _grid[y][x].getPos().getY() != _grid[y][x].getTruePos().getY())
				return false;
  return true;
}

// la fonction copyGrid va prendre en paramètre une grille pré éxistante et va copier chacun de ses éléments dans la grille de son instance.
// si jamais elle rencontre la grille empty, elle en profite pour attribuer le pointeur empty également afin de ne pas avoir à reparcourir
// l'ensemble de la grille plus tard juste pour cela.
void nPuzzle::copyGrid(std::vector<std::vector<Node>> const &grid, short gridSize)
{
	if (_grid.size() == 0)
		this->setupGrid(gridSize);
		for (short y = 0; y < gridSize; ++y)
			for (short x  = 0; x < gridSize; ++x)
			{
					_grid[y][x] = grid[y][x];
					if (_grid[y][x].getValue() == 0)
						_empty = &(_grid[y][x]);
			}
}

// cette fonction prend en paramètre une référence vers un puzzle pré éxistant et va copier l'intégralité des valeurs de l'instance en cours
// vers cette référence. Cette fonction sera l'équivalente de la fonction qui renverra une copie égal à l'instance en cours sauf qu'elle ne prend
// pas de mémoire supplémentaire. Elle permet l'utilisation d'un pooling system de nPuzzle non assigné.
// Cette fonction ne copie pas tout à fait les bonnes valeurs. Elle modifie tout de même l'ID de l'instance généré pour montrer qu'elle ne sont pas les mêmes.
bool nPuzzle::copyData(nPuzzle *newPuzzle) const
{
		if (newPuzzle->getSize() > 0 && newPuzzle->getSize() != this->getSize())
			return false;
		newPuzzle->setId(_id + 1);
		newPuzzle->setSize(_size);
		newPuzzle->setGcost(_gCost);
		newPuzzle->copyGrid(_grid, _size);
		newPuzzle->setHcost(_hCost);
		newPuzzle->setHeuristicMod(_heuristicMod);
		return true;
}

nPuzzle *nPuzzle::copy() const
{
	nPuzzle *copy = new nPuzzle(_size);
	this->copyData(copy);
	copy->fillEmpty(copy->getSize());
	return copy;
}

// toutes les fonctions heuristiques.

// cette fonction va parcourir l'ensemble des éléments de la grille et récupérer la valeur de retour de la fonction pythagore
// la somme de toute ces valeurs va donner une heuristiques qu'utilisera l'algorithme afin de déterminer ses futurs choix.
float nPuzzle::getPythagoras() const
{
	float hCost = 0.0;
	for(short y = 0; y < _size; ++y)
		for(short x = 0; x < _size; ++x)
				if (_grid[y][x].getValue() != 0)
					hCost += _grid[y][x].pythagoras();
		return hCost;
}

short nPuzzle::getManhattan() const
{
	short hCost = 0;
	for(short y = 0; y < _size; ++y)
		for(short x = 0; x < _size; ++x)
			if (_grid[y][x].getValue() != 0)
				hCost += _grid[y][x].manhattan();
		return hCost;
}

short nPuzzle::getHamming() const
{
	short hCost = 0;
	for(short y = 0; y < _size; ++y)
		for(short x = 0; x < _size; ++x)
			if (_grid[y][x].getValue() != 0 && _grid[y][x].isMisplaced())
					hCost++;
		return hCost;
}

bool nPuzzle::isLinearConflicted(Node const &node) const
{
	Node dest = _grid[node.getTruePos().getY()][node.getTruePos().getX()];
	short destY = dest.getPos().getY();
	short destX = dest.getPos().getX();
	for (short x = 0; x < _size; ++x)
	{
		Node current = _grid[node.getPos().getY()][x];
				if (current.getValue() != 0 && x != node.getPos().getX())
					{
							if (current.getTruePos().getY() == node.getTruePos().getY())
									if (current.getPos().getX() <= node.getPos().getX() && current.getPos().getX() >= destX || current.getPos().getX() >= node.getPos().getX() && current.getPos().getX() <= destX)
												if (current.getPos().getY() == current.getTruePos().getY() && node.getPos().getY() == node.getTruePos().getY())
													if (node.getPos().getX() >= node.getTruePos().getX() && current.getPos().getX() <= current.getTruePos().getX() || node.getPos().getX() <= node.getTruePos().getX() && current.getPos().getX() >= current.getTruePos().getX())
															return true;
							else if (current.getTruePos().getX() == node.getTruePos().getX())
									if (current.getPos().getY() <= node.getPos().getY() && current.getPos().getY() >= destY || current.getPos().getY() >= node.getPos().getY() && current.getPos().getY() <= destY)
												if (current.getPos().getX() == current.getTruePos().getX() && node.getPos().getX() == node.getTruePos().getX())
													if (node.getPos().getY() >= node.getTruePos().getY() && current.getPos().getY() <= current.getTruePos().getY() || node.getPos().getY() <= node.getTruePos().getY() && current.getPos().getY() >= current.getTruePos().getY())
														return true;
					}
	}

	for (short y = 0; y < _size; ++y)
	{
			Node current = _grid[y][node.getPos().getX()];
			if (current.getValue() != 0 && y != node.getPos().getY())
				{
					if (current.getTruePos().getY() == node.getTruePos().getY())
							if (current.getPos().getX() <= node.getPos().getX() && current.getPos().getX() >= destX || current.getPos().getX() >= node.getPos().getX() && current.getPos().getX() <= destX)
										if (current.getPos().getY() == current.getTruePos().getY() && node.getPos().getY() == node.getTruePos().getY())
											if (node.getPos().getX() >= node.getTruePos().getX() && current.getPos().getX() <= current.getTruePos().getX() || node.getPos().getX() <= node.getTruePos().getX() && current.getPos().getX() >= current.getTruePos().getX())
													return true;
					else if (current.getTruePos().getX() == node.getTruePos().getX())
							if (current.getPos().getY() <= node.getPos().getY() && current.getPos().getY() >= destY || current.getPos().getY() >= node.getPos().getY() && current.getPos().getY() <= destY)
										if (current.getPos().getX() == current.getTruePos().getX() && node.getPos().getX() == node.getTruePos().getX())
											if (node.getPos().getY() >= node.getTruePos().getY() && current.getPos().getY() <= current.getTruePos().getY() || node.getPos().getY() <= node.getTruePos().getY() && current.getPos().getY() >= current.getTruePos().getY())
												return true;
				}
	}
	return false;
}

short nPuzzle::getManhattanAndLinearConflict() const
{
	short hCost = 0;
	short nLinearConflict = 0;
	for(short y = 0; y < _size; ++y)
		for(short x = 0; x < _size; ++x)
			if (_grid[y][x].getValue() != 0)
			{
				hCost += _grid[y][x].manhattan();
				if (isLinearConflicted(_grid[y][x]) == true)
					nLinearConflict++;
			}
		return ( hCost + (nLinearConflict * 2) );
}

float nPuzzle::fCost() const
{
	return _gCost + _hCost;
}

// setters and getters
void nPuzzle::setSize(short size)								{_size = size;}
void nPuzzle::setId(short id)										{_id = id;}
void nPuzzle::setGcost(short g)									{_gCost = g;}
void nPuzzle::setHcost(float h)									{_hCost = h;}
void nPuzzle::setParent(nPuzzle *p)							{_parent = p;}
void nPuzzle::setLastMove(std::string s)				{_lastMove = s;}
void nPuzzle::setEmpty(Node *n) 								{_empty = n;}
void nPuzzle::setHeuristicMod(unsigned long h)	{_heuristicMod = h;}

short const 													&nPuzzle::getSize(void)			const		{return _size;}
short const														&nPuzzle::getId(void)				const		{return _id;}
short const														&nPuzzle::getGcost(void)		const		{return _gCost;}
float const														&nPuzzle::getHcost(void)		const		{return _hCost;}
nPuzzle 															*nPuzzle::getParent(void)		const		{return _parent;}
std::string const											&nPuzzle::getLastMove(void)	const		{return _lastMove;}
Node			 														*nPuzzle::getEmpty(void)		const		{return _empty;}
std::vector<std::vector<Node>> const	&nPuzzle::getGrid()					const		{return _grid;}
unsigned long const 									&nPuzzle::getHeuristicMod() const 	{return _heuristicMod;}

// overload operator
std::ostream &operator<<(std::ostream &o, nPuzzle const & ref)
{
	o << endl;
		for(short y = 0; y < ref.getSize(); ++y)
		{
				for(short x = 0; x < ref.getSize(); ++x)
				{
					std::string s = "   ";
					if (ref.getGrid()[y][x].getValue() == 0)
						s += " ";
					else
						s += std::to_string( ref.getGrid()[y][x].getValue() );
					s.resize(5, ' ');
					o << s;
				}
				o << endl;
		}
		o << endl;
	return o;
}

nPuzzle & nPuzzle::operator=(nPuzzle const & src)
{
	this->setId(src.getId());
	this->setSize(src.getSize());
	this->setGcost(src.getGcost());
	this->copyGrid(src.getGrid(), src.getSize());
	this->setHcost(src.getHcost());
	this->setParent(nullptr);
	this->fillEmpty(_size);
	this->setHeuristicMod(src.getHeuristicMod());
	return *this;
}

bool nPuzzle::operator==(nPuzzle const &ref)
{
		if (ref.getId() != _id)
			return false;
		if (ref.getSize() != _size)
			return false;
		if (ref.getGcost() != _gCost)
			return false;
		if (ref.getLastMove() != _lastMove)
			return false;
		if (ref.getHcost() != _hCost)
			return false;
		if (ref.getHeuristicMod() != _heuristicMod)
			return false;
		for (short y = 0; y < _size; ++y)
			for (short x = 0; x < _size; ++x)
				{
						Node _n = _grid[y][x];
						Node n = ref.getGrid()[y][x];
						if (n.getPos().getY() != _n.getPos().getY())
							return false;
						if (n.getPos().getX() != _n.getPos().getX())
							return false;
						if (n.getTruePos().getY() != _n.getTruePos().getY())
							return false;
						if (n.getTruePos().getX() != _n.getTruePos().getX())
							return false;
						if (n.getValue() != _n.getValue())
							return false;
				}

	return true;
}
