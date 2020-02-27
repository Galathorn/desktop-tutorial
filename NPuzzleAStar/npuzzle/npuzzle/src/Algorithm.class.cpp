#include "../includes/Algorithm.class.hpp"

Algorithm::Algorithm() : _executionTime(0), _timeComplexity(0), _sizeComplexity(0) {}


Algorithm::~Algorithm() {}


void Algorithm::setExecutionTime(float nTime) {_executionTime = nTime;}
void Algorithm::setTimeComplexity(unsigned long long nTime) {_timeComplexity = nTime;}
void Algorithm::setSizeComplexity(unsigned long long nTime) {_sizeComplexity = nTime;}

float               Algorithm::getExecutionTime(void) const {return _executionTime;}
unsigned long long  Algorithm::getTimeComplexity(void) const {return _timeComplexity;}
unsigned long long  Algorithm::getSizeComplexity(void) const {return _sizeComplexity;}
