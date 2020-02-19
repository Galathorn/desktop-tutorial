#include "../includes/Pos.class.hpp"

Pos::Pos(void) : y(0), x(0) {} // constructor with nothing

Pos::Pos(short y, short x) : y(y), x(x) {} // constructor with position

Pos::~Pos() {} // destructor



// getter and setter

void Pos::setY(short y) {this->y = y;}
void Pos::setX(short x) {this->x = x;}
void Pos::setCoord(short y, short x)
{
	this->y = y;
	this->x = x;
}

short const &Pos::getY(void) const {return this->y;}
short const &Pos::getX(void) const {return this->x;}


// overload operator


std::ostream &operator<<(std::ostream &o, Pos const & ref)
{
	o << "[" << ref.getY() << ", " << ref.getX() << "]";
}

Pos & Pos::operator=(Pos const &ref)
{
	this->setY(ref.getY());
	this->setX(ref.getX());
	return *this;
}
