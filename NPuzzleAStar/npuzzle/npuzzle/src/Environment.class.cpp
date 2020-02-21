#include "../includes/Environment.class.hpp"

using namespace std;

Environment::Environment(short sizePuzzle, int amountPuzzle) : pool(std::stack<nPuzzle>()), puzzle(nPuzzle(sizePuzzle)), scrambler(Scrambler()), astar(Astar())
{
  for (short x = 0; x < amountPuzzle; ++x)
    pool.push(nPuzzle(sizePuzzle));
}

Environment::~Environment() {}
