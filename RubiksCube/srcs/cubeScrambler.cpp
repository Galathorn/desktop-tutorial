#include "../includes/cubeScrambler.hpp"

cubeScrambler::cubeScrambler()
{
	srand(time(nullptr));
}

cubeScrambler::~cubeScrambler() {}

void cubeScrambler::applySpecificMove(Cube *c, string move)
{
//	cout << "move : " << move << endl;
	if (move == "U")
		c->U();
	else if (move == "R")
		c->R();
	else if (move == "B")
		c->B();
	else if (move == "L")
		c->L();
	else if (move == "D")
		c->D();
	else if (move == "F")
		c->F();
	else if (move == "M")
		c->M();
	else if (move == "U2")
		c->U2();
	else if (move == "R2")
		c->R2();
	else if (move == "B2")
		c->B2();
	else if (move == "L2")
		c->L2();
	else if (move == "D2")
		c->D2();
	else if (move == "F2")
		c->F2();
	else if (move == "M2")
		c->M2();
	else if (move == "U'")
		c->U_prime();
	else if (move == "R'")
		c->R_prime();
	else if (move == "B'")
		c->B_prime();
	else if (move == "L'")
		c->L_prime();
	else if (move == "D'")
		c->D_prime();
	else if (move == "F'")
		c->F_prime();
	else if (move == "M'")
		c->M_prime();
	else if (move == "r")
		c->r();
	else if (move == "r'")
		c->r_prime();
	else if (move == "r2")
		c->r2();
	else if (move == "l")
		c->l();
	else if (move == "l'")
		c->l_prime();
	else if (move == "l2")
		c->l2();

	else if (move == "U'2")
		c->U2();
	else if (move == "R'2")
		c->R2();
	else if (move == "B'2")
		c->B2();
	else if (move == "L'2")
		c->L2();
	else if (move == "D'2")
		c->D2();
	else if (move == "F'2")
		c->F2();
	else if (move == "M'2")
		c->M2();
	else if (move == "r'2")
		c->r2();
	else if (move == "l'2")
		c->l2();

	else if (move == "y")
		c->y();
	else if (move == "y2")
		c->y2();
	else if (move == "y'")
		c->y_prime();
	else if( move.size() > 0)
	{
		cout << "ERROR CUBE SCRAMBLER CONVERTOR" << endl;
		cout << "|" << move << "|" << endl;
		exit(0);
	}

}

void cubeScrambler::applySpecificList(Cube *c, list<string> moves)
{
	list<string>::iterator it = moves.begin();
	list<string>::iterator end = moves.end();
	for (; it != end; ++it)
		applySpecificMove(c, (*it));
}

list<string> cubeScrambler::getRandomList(int amount, vector<string> tabMoves)
{
	list<string>	l;
	int 			size = tabMoves.size();

	for (int i = 0; i < amount; ++i)
		l.push_back(tabMoves[rand() % size]);
	return l;
}















