#include "../includes/Scrambler.class.hpp"

Scrambler::Scrambler(void) : lastMove("")
{
  srand(time(nullptr));
}

Scrambler::~Scrambler(void) {}


bool Scrambler::applyMove(std::string move, nPuzzle &puzzle)
{
  if (move == lastMove)
    return false;
  if (move == "UP")
    return puzzle.Up();
  else if (move == "RIGHT")
    return puzzle.Right();
  else if (move == "DOWN")
    return puzzle.Down();
  else if (move == "LEFT")
    return puzzle.Left();
  return false;
}

void Scrambler::scramble(short n, nPuzzle &puzzle)
{
  std::string m = _moves[rand() % _moves.size()];
  short       v = 0;
  for (short i = 0; i < n; ++i)
  {
      while (true)
      {
        if (lastMove == "UP")
          m = _noUp[rand() % _noUp.size()];
        else if (lastMove == "RIGHT")
          m = _noRight[rand() % _noRight.size()];
        else if (lastMove == "DOWN")
          m = _noDown[rand() % _noDown.size()];
        else if (lastMove == "LEFT")
          m = _noLeft[rand() % _noLeft.size()];
          if (applyMove(m, puzzle) == true)
            break;
      }
      lastMove = m;
  }
}
