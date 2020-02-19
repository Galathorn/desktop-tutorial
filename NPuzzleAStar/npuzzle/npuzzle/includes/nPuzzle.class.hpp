#ifndef NPUZZLE_CLASS_HPP
#define NPUZZLE_CLASS_HPP

#include <iostream>

#include "../includes/Node.class.hpp"

class nPuzzle
{
	public :
	nPuzzle(void);
	nPuzzle(short size);
	~nPuzzle();

	nPuzzle 			&operator=(nPuzzle const & ref);
	// ensemble des methode du cube

	void 				setSize(short &s);
	short const 		&getSize(void) const;

	void 				setId(short id);
	short const			&getId(void) const;

	void 				setGcost(short gcost);
	short const			&getGcost(void) const;

	void 				setParent(nPuzzle *parent);
	nPuzzle 			*getParent(void) const;

	void				setDefMove(std::string defMove);
	std::string const	&getDefMove(void) const;

	void 				setEmpty(Node *n);
	Node const 			*getEmpty(void) const;

private:
	short		_size;
	short		_id;
	short 		_gCost;
	nPuzzle 	*_parent;
	std::string	_defMove;
	Node 		*_empty;

};

std::ostream &operator<<(std::ostream &o, nPuzzle const &src);

#endif
