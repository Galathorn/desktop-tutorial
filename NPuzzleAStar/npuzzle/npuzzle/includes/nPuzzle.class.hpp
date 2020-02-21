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
	bool 							operator==(nPuzzle const &ref);
	// ensemble des methode du cube

	void 																	setSize(short s);
	short const 													&getSize(void) const;

	void 																	setId(short id);
	short const														&getId(void) const;

	void 																	setGcost(short gcost);
	short const														&getGcost(void) const;

	void 																	setHcost(float h);
	float const 													&getHcost(void) const;

	void 																	setParent(nPuzzle *parent);
	nPuzzle 															*getParent(void) const;

	void																	setLastMove(std::string defMove);
	std::string const											&getLastMove(void) const;

	void 																	setEmpty(Node *n);
	Node			 														*getEmpty(void) const;

	std::vector<std::vector<Node>> const 	&getGrid() const;

	void 																 	setupGrid(short size); // fonction qui va créer la grille de Node

	void 																	fillSnailGrid(short mSize); // cette fonction va remplir la grille du npuzzle en forme d'escargot
	void 																	fillClassicGrid(short mSize); // cette fonction va remplir la grille du npuzzle en forme d'escargot

	void 																	fillEmpty(short mSize); // cette fonction va chercher la case vide dans le puzzle et l'attribuer.
	void 																	swapNode(short y, short x, short emptyY, short emptyX); // fonction permettant de swapper deux node.

// cette fonction prend en paramètre une référence vers une grille préexistante et copie chaque élément vers la grille de l'instance en cours.
	void 																	copyGrid(std::vector<std::vector<Node>> const &grid, short gridSize);
	bool 																	copyData(nPuzzle *n);
	nPuzzle																*copy();


// heuristics functions
// cette fonctions va faire calculer pythagore à chaque élément de la grille et renvoie la somme de toute ces valeurs là.
	float 																getPythagoras() const;
	short																	getManhattan() const;
	float 																fCost();

	float 																increaseHcost(Node const &n);
	float 																reduceHcost(Node const &n);


// movements functions
	bool 																	Up();
	bool 																	Right();
	bool 																	Down();
	bool 																	Left();

private:
	short																	_size;
	short																	_id;
	short 																_gCost;
	nPuzzle 															*_parent;
	std::string														_lastMove;
	Node 																	*_empty;
	std::vector<std::vector<Node>>				_grid;
	float 																_hCost;

};

std::ostream &operator<<(std::ostream &o, nPuzzle const &src);

#endif
