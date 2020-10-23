#ifndef NODE_CLASS_HPP
#define NODE_CLASS_HPP

#include "../includes/Pos.class.hpp"
#include <math.h>

class Node
{
	public:
	Node(void);
	Node(short _y, short _x, short _value);
	~Node(void);

	Node const 	&operator=(Node const & ref);

	float 			pythagoras()	const;
	short 			manhattan() 	const;
	bool 			isMisplaced() const;

	Pos const		&getPos() const;
	Pos const		&getTruePos() const;
	short const		&getValue() const;

	void 			setValue(short const &v);
	void 			setPos(Pos const & p);
	void 			setTruePos(Pos const & p);


private:
	short			_value;
	Pos				_pos;
	Pos				_truePos;

};

std::ostream &operator<<(std::ostream &o, Node const &ref);

#endif
