#ifndef CUBE_HPP
#define CUBE_HPP

#include "define.hpp"
#include <vector>


class Cube
{
public:
// constructor destructor
	Cube();
	~Cube();

	Cube &operator=(const Cube &c);

// methods
	void F();
	void F_prime();
	void F2();


	void R();
	void R_prime();
	void R2();

	void L();
	void L_prime();
	void L2();

	void B();
	void B_prime();
	void B2();

	void D();
	void D_prime();
	void D2();

	void U();
	void U_prime();
	void U2();

	void M();
	void M_prime();
	void M2();

	void r();
	void r_prime();
	void r2();

	void l();
	void l_prime();
	void l2();

	void y();
	void y_prime();
	void y2();

	void reinitialise();

	void rotateClockWise(int index);
	void rotateCounterClockWise(int index);

	void permuteLinesClockWise(int y);
	void permuteLinesCounterClockWise(int y);

	void permuteColumnClockWise(int x);
	void permuteColumnCounterClockWise(int x);

	void permuteAdjacentColumnClockWise(int x);
	void permuteAdjacentColumnCounterClockWise(int x);

// components
	std::vector<std::vector<int>> matrix;
};


#endif
