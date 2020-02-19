#include "../includes/Node.class.hpp"

Node::Node(void) : _value(0)
{
  _pos = Pos(0, 0);
  _truePos = Pos(0, 0);
}

Node::Node(short y, short x, short value) : _value(value)
{
  _pos = Pos(y, x);
  _truePos = Pos(y, x);
}

Node::~Node() {}


float Node::getDistance() const
{
  float x = _truePos.getX() - _pos.getX();
  float y = _truePos.getY() - _pos.getY();
  x *= x;
  y *= y;
  return static_cast<float>(sqrt(x + y));
}

//getter and setter

void Node::setValue(short const &v) {_value = v;}
void Node::setPos(Pos const &p)
{
  _pos.setY(p.getY());
  _pos.setX(p.getX());
}
void Node::setTruePos(Pos const &p)
{
  _truePos.setY(p.getY());
  _truePos.setX(p.getX());
}

Pos const   &Node::getPos()     const {return _pos;}
Pos const   &Node::getTruePos() const {return _truePos;}
short const &Node::getValue()   const {return _value;}

// overload
std::ostream &operator<<(std::ostream &o, Node const &ref)
{
    o << "value : " << ref.getValue() << " pos : " << ref.getPos() << " truePos : " << ref.getTruePos();
    return o;
}

Node const &Node::operator=(Node const & ref)
{
  _pos.setCoord( ref.getPos().getY(), ref.getPos().getX() );
  _truePos.setCoord( ref.getTruePos().getY(), ref.getTruePos().getX() );

  _value = ref.getValue();
  return *this;
}
