#include "../includes/nPuzzle.class.hpp"

using namespace std;

nPuzzle::nPuzzle(short size) : _size(size), _id(0), _gCost(0), _parent(nullptr), _defMove(""), _empty(nullptr)
{
	setupGrid(_size);
	fillSnailGrid();
}

nPuzzle::nPuzzle(void) : _size(0), _id(0), _gCost(0), _parent(nullptr), _defMove(""), _empty(nullptr)
{
	setupGrid(0);
}

nPuzzle::~nPuzzle(void) {}


void nPuzzle::setupGrid(short size)
{
	_grid = std::vector<std::vector<Node>>(_size);
		for(short y = 0; y < _size; ++y)
		{
			_grid[y] = std::vector<Node>(_size);
				for(short x = 0; x < _size; ++x)
					_grid[y][x] = Node(y, x, 0);
		}
}

// major fonction

void nPuzzle::fillClassicGrid()
{
	short max = _size * _size;
	short current = 0;
	for(short y = 0; y < _size; ++y)
		for(short x = 0; x < _size; ++x)
			if (++current < max)
				_grid[y][x].setValue( current);
	fillEmpty();
}

void nPuzzle::fillSnailGrid()
{
	short size = _size;
	short goalValue = _size * _size;
	std::vector<std::string> directions = {"RIGHT","DOWN","LEFT","UP"};
	short directionSize = 4;
	short dir = 0;
	short countDir = _size;
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
	fillEmpty();
}


void nPuzzle::fillEmpty()
{
	for(short y = 0; y < _size; ++y)
		for(short x = 0; x < _size; ++x)
			if (_grid[y][x].getValue() == 0)
				_empty = &(_grid[y][x]);
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
}

// movements functions

bool nPuzzle::Up()
{
	if (_empty->getPos().getY() + 1 >= _size)
		return false;
		cout << "UP" << std::endl;
		Node n = _grid[_empty->getPos().getY() + 1][_empty->getPos().getX()];
		swapNode(n.getPos().getY(), n.getPos().getX(), _empty->getPos().getY(), _empty->getPos().getX());
		return true;
}

bool nPuzzle::Right()
{
	if (_empty->getPos().getX() - 1 < 0)
		return false;
		cout << "RIGHT" << std::endl;

		Node n = _grid[_empty->getPos().getY()][_empty->getPos().getX() - 1];
		swapNode(n.getPos().getY(), n.getPos().getX(), _empty->getPos().getY(), _empty->getPos().getX());
		return true;
}

bool nPuzzle::Down()
{
	if (_empty->getPos().getY() - 1 < 0)
		return false;
		cout << "DOWN" << std::endl;

		Node n = _grid[_empty->getPos().getY() - 1][_empty->getPos().getX()];
		swapNode(n.getPos().getY(), n.getPos().getX(), _empty->getPos().getY(), _empty->getPos().getX());
		return true;
}

bool nPuzzle::Left()
{
	if (_empty->getPos().getX() + 1 >= _size)
		return false;
		cout << "LEFT" << std::endl;

		Node n = _grid[_empty->getPos().getY()][_empty->getPos().getX() + 1];
		swapNode(n.getPos().getY(), n.getPos().getX(), _empty->getPos().getY(), _empty->getPos().getX());
		return true;
}

// setters and getters
void nPuzzle::setSize(short size)				{_size = size;}
void nPuzzle::setId(short id)						{_id = id;}
void nPuzzle::setGcost(short g)					{_gCost = g;}
void nPuzzle::setParent(nPuzzle *p)			{_parent = p;}
void nPuzzle::setDefMove(std::string s)	{_defMove = s;}
void nPuzzle::setEmpty(Node *n) 				{_empty = n;}

short const 													&nPuzzle::getSize(void)			const		{return _size;}
short const														&nPuzzle::getId(void)				const		{return _id;}
short const														&nPuzzle::getGcost(void)		const		{return _gCost;}
nPuzzle 															*nPuzzle::getParent(void)		const		{return _parent;}
std::string const											&nPuzzle::getDefMove(void)	const		{return _defMove;}
Node const 														*nPuzzle::getEmpty(void)		const		{return _empty;}
std::vector<std::vector<Node>> const	&nPuzzle::getGrid()					const		{return _grid;}


// overload operator
std::ostream &operator<<(std::ostream &o, nPuzzle const & ref)
{
		for(short y = 0; y < ref.getSize(); ++y)
		{
				for(short x = 0; x < ref.getSize(); ++x)
				{
					std::string s = "   ";
					s += std::to_string(ref.getGrid()[y][x].getValue());
					s.resize(5, ' ');
					o << s;
				}
				o << endl;
		}
	return o;
}

nPuzzle & nPuzzle::operator=(nPuzzle const & src)
{
	(void)src;
	// copy everything
	return *this;
}
