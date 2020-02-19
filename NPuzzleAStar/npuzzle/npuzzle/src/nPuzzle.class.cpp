#include "../includes/nPuzzle.class.hpp"

nPuzzle::nPuzzle(short size) : _size(size), _id(0), _gCost(0), _parent(nullptr), _defMove(nullptr), _empty(nullptr) {}

nPuzzle::nPuzzle(void) : _size(0), _id(0), _gCost(0), _parent(nullptr), _defMove(nullptr), _empty(nullptr) {}

nPuzzle::~nPuzzle(void)
{
	// destroy everything
}

std::ostream &operator<<(std::ostream &o, nPuzzle const & ref)
{
	o << "printing content of nPuzzle" << std::endl;
	return o;
}

nPuzzle & nPuzzle::operator=(nPuzzle const & src)
{
	(void)src;
	// copy everything
	return *this;
}
