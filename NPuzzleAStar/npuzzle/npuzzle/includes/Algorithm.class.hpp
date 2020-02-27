#ifndef ALGORITHM_CLASS_HPP
#define ALGORITHM_CLASS_HPP

#include "nPuzzle.class.hpp"
#include <list>
#include <algorithm>

class Algorithm
{
	public :
	Algorithm(void);
	~Algorithm(void);

	float 				getExecutionTime(void)	const;
	unsigned long long getTimeComplexity(void) const;
	unsigned long long getSizeComplexity(void) const;

	void setExecutionTime(float nTime);
	void setTimeComplexity(unsigned long long nTime);
	void setSizeComplexity(unsigned long long nTime);

private:
	float 				_executionTime;	// le temps qu'a mis le programme pour résoudre le puzzle.
	unsigned long long _timeComplexity; // nombre de fois que current est séléctionné (cycle correspond à timeComplexity)
	unsigned long long _sizeComplexity; // nombre d'instance de puzzle stocké en mémoire donc la taille de path.


};
#endif
