#ifndef NPUZZLE_CLASS_HPP
#define NPUZZLE_CLASS_HPP

#include <iostream>

using namespace std;
#include "../includes/Node.class.hpp"
#include <vector>

class nPuzzle
{
	public :
	nPuzzle(void);
	nPuzzle(short size);
	~nPuzzle();

	nPuzzle 					&operator=(nPuzzle const & ref);
	// ensemble des methode du cube

	void 																	setSize(short s);
	short const 													&getSize(void) const;

	void 																	setId(short id);
	short const														&getId(void) const;

	void 																	setGcost(short gcost);
	short const														&getGcost(void) const;

	void 																	setParent(nPuzzle *parent);
	nPuzzle 															*getParent(void) const;

	void																	setDefMove(std::string defMove);
	std::string const											&getDefMove(void) const;

	void 																	setEmpty(Node *n);
	Node const 														*getEmpty(void) const;

	std::vector<std::vector<Node>> const 	&getGrid() const;

	void 																 	setupGrid(short size); // fonction qui va créer la grille de Node

	void 																	fillSnailGrid(); // cette fonction va remplir la grille du npuzzle en forme d'escargot
	void 																	fillClassicGrid(); // cette fonction va remplir la grille du npuzzle en forme d'escargot

	void 																	fillEmpty(); // cette fonction va chercher la case vide dans le puzzle et l'attribuer.
	void 																	swapNode(short y, short x, short emptyY, short emptyX); // fonction permettant de swapper deux node.
// movements functions
	bool 																	Up();
	bool 																	Right();
	bool 																	Down();
	bool 																	Left();

private:
	short				_size;
	short				_id;
	short 			_gCost;
	nPuzzle 		*_parent;
	std::string	_defMove;
	Node 				*_empty;
	std::vector<std::vector<Node>> _grid;

};

std::ostream &operator<<(std::ostream &o, nPuzzle const &src);

#endif
