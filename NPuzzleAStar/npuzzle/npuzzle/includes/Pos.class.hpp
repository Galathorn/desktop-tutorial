#ifndef POS_CLASS_HPP
#define POS_CLASS_HPP

#include <iostream>

class Pos
{
	public:
	Pos();
	Pos(short y, short x);
	~Pos();

	Pos &operator=(Pos const & ref);
	bool operator==(Pos const & ref);

	void setX(short x);
	short const &getX(void) const;

	void setY(short y);
	short const &getY(void) const;

	void setCoord(short y, short x);

private:
	short y;
	short x;
};

std::ostream &operator<<(std::ostream &o, Pos const & ref);

#endif
