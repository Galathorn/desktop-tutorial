#include "../includes/cube.hpp"
#include "../includes/define.hpp"

// constructor and destructor

Cube::Cube() : matrix(std::vector<std::vector<int>>(6)) 
{
	reinitialise();
}

Cube::~Cube() {}


void Cube::reinitialise()
{
	for (int i = 0, v = 0; i < 6; ++i, ++v)
	{
		matrix[i] = std::vector<int>(9);
		for (int j = 0; j < 9; ++j)
			matrix[i][j] = v;
	}
}


// movement function

void Cube::F()
{
	rotateClockWise(FRONT);
	permuteAdjacentColumnClockWise(0);
}

void Cube::F_prime()
{
	rotateCounterClockWise(FRONT);
	permuteAdjacentColumnCounterClockWise(0);
}

void Cube::F2()
{
	F();
	F();
}

void Cube::R()
{
	rotateClockWise(RIGHT);
	permuteColumnClockWise(2);
}

void Cube::R_prime()
{
	rotateCounterClockWise(RIGHT);
	permuteColumnCounterClockWise(2);
}

void Cube::R2()
{
	R();
	R();
}

void Cube::L()
{
	rotateClockWise(LEFT);
	permuteColumnCounterClockWise(0);
}

void Cube::L_prime()
{
	rotateCounterClockWise(LEFT);
	permuteColumnClockWise(0);
}

void Cube::L2()
{
	L();
	L();
}

void Cube::U()
{
	rotateClockWise(TOP);
	permuteLinesClockWise(0);
}

void Cube::U_prime()
{
	rotateCounterClockWise(TOP);
	permuteLinesCounterClockWise(0);
}

void Cube::U2()
{
	U();
	U();
}

void Cube::D()
{
	rotateClockWise(DOWN);
	permuteLinesCounterClockWise(2);
}

void Cube::D_prime()
{
	rotateCounterClockWise(DOWN);
	permuteLinesClockWise(2);
}

void Cube::D2()
{
	D();
	D();
}

void Cube::B()
{
	rotateClockWise(BACK);
	permuteAdjacentColumnCounterClockWise(2);
}

void Cube::B_prime()
{
	rotateCounterClockWise(BACK);
	permuteAdjacentColumnClockWise(2);
}

void Cube::B2()
{
	B();
	B();
}

void Cube::M()
{
	permuteColumnCounterClockWise(1);
}

void Cube::M_prime()
{
	permuteColumnClockWise(1);
}

void Cube::M2()
{
	M();
	M();
}

void Cube::r()
{
	R();
	M_prime();
}

void Cube::r_prime()
{
	R_prime();
	M();
}

void Cube::r2()
{
	r();
	r();
}

void Cube::l()
{
	M();
	L();
}

void Cube::l_prime()
{
	L_prime();
	M_prime();
}

void Cube::l2()
{
	l();
	l();
}


void Cube::y()
{
	U();
	permuteLinesClockWise(1);
	D_prime();
}

void Cube::y_prime()
{
	U_prime();
	permuteLinesCounterClockWise(1);
	D();
}

void Cube::y2()
{
	y();
	y();
}

// tools function

void Cube::rotateClockWise(int index)
{
	std::vector<int> tmpFace = matrix[index];
	for (int y = 0; y < 3; ++y)
		for (int x = 0; x < 3; ++x)
			matrix[index][2 - y + (x * 3)] = tmpFace[y * 3 + x];

}

void Cube::rotateCounterClockWise(int index)
{

	std::vector<int> tmpFace = matrix[index];
	for (int y = 0; y < 3; ++y)
		for (int x = 0; x < 3; ++x)
			matrix[index][6 + y - (x * 3)] = tmpFace[y * 3 + x];
}

void Cube::permuteLinesClockWise(int y)
{
	y *= 3;
	for (int i = 0; i < 3; ++i)
	{
		int tmp = matrix[FRONT][y + i];
		matrix[FRONT][y + i] = matrix[RIGHT][y + i];
		matrix[RIGHT][y + i] = matrix[BACK][y + i];
		matrix[BACK][y + i] = matrix[LEFT][y + i];
		matrix[LEFT][y + i] = tmp;
	}
}

void Cube::permuteLinesCounterClockWise(int y)
{
	y *= 3;
	for (int i = 0; i < 3; ++i)
	{
		int tmp = matrix[FRONT][y + i];
		matrix[FRONT][y + i] = matrix[LEFT][y + i];
		matrix[LEFT][y + i] = matrix[BACK][y + i];
		matrix[BACK][y + i] = matrix[RIGHT][y + i];
		matrix[RIGHT][ y + i] = tmp;
	}
}

void Cube::permuteColumnClockWise(int x)
{
	for (int i = 0; i < 3; ++i)
	{
		int tmp = matrix[FRONT][i * 3 + x];
		matrix[FRONT][i * 3 + x] = matrix[DOWN][i * 3 + x];
		matrix[DOWN][i * 3 + x] = matrix[BACK][8 - i * 3 - x];
		matrix[BACK][8 - i * 3 - x] = matrix[TOP][i * 3 + x];
		matrix[TOP][i * 3 + x] = tmp;
	}
}

void Cube::permuteColumnCounterClockWise(int x)
{
	for (int i = 0; i < 3; ++i)
	{
		int tmp = matrix[FRONT][i * 3 + x];
		matrix[FRONT][i * 3 + x] = matrix[TOP][i * 3 + x];
		matrix[TOP][i * 3 + x] = matrix[BACK][8 - i * 3 - x];
		matrix[BACK][8 - i * 3 - x] = matrix[DOWN][i * 3 + x];
		matrix[DOWN][i * 3 + x] = tmp;
	}
}

void Cube::permuteAdjacentColumnClockWise(int x)
{
	for (int i = 0; i < 3; ++i)
	{
		int tmp = matrix[RIGHT][i * 3 + x];
		matrix[RIGHT][i * 3 + x] = matrix[TOP][6 - x * 3 + i];
		matrix[TOP][6 - x * 3 + i] = matrix[LEFT][8 - i * 3 - x];
		matrix[LEFT][8 - i * 3 - x] = matrix[DOWN][2 + x * 3 - i];
		matrix[DOWN][2 + x * 3 - i] = tmp;
	}

}

void Cube::permuteAdjacentColumnCounterClockWise(int x)
{
	for (int i = 0; i < 3; ++i)
	{
		int tmp = matrix[RIGHT][i * 3 + x];
		matrix[RIGHT][i * 3 + x] = matrix[DOWN][2 + x * 3 - i];
		matrix[DOWN][2 + x * 3 - i] = matrix[LEFT][8 - i * 3 - x];
		matrix[LEFT][8 - i * 3 - x] = matrix[TOP][6 - x * 3 + i];
		matrix[TOP][6 - x * 3 + i] = tmp;
	}
}

Cube &Cube::operator=(const Cube &c)
{
	for (int i = 0; i < matrix.size(); ++i)
		for (int j = 0; j < matrix[i].size(); ++j)
			this->matrix[i][j] = c.matrix[i][j];
	return *this;
}


/*
 * [0 1 2]
 * [3 4 5]
 * [6 7 8]
 *
 *
 *
 */
