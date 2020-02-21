#include <iostream>

#include "../includes/nPuzzle.class.hpp"
#include "../includes/Scrambler.class.hpp"
#include "../includes/Environment.class.hpp"

using namespace std;

void printNpuzzle(nPuzzle &puzzle)
{
	cout << puzzle																						<< endl;
	cout << "id : "									<< puzzle.getId()					<< endl;
	cout << "size : "								<< puzzle.getSize()				<< endl;
	cout << "gCost : "							<< puzzle.getGcost()			<< endl;
	cout << "hCost : "							<< puzzle.getHcost()			<< endl;
	cout << "Entire Pythagoras : "	<< puzzle.getPythagoras()	<< endl;

	puzzle.getParent() == nullptr ? cout << "parent ID : NULL" << endl : cout << "parent ID : " << puzzle.getParent()->getId() << endl;
	cout << "defMove : " << (puzzle.getLastMove() == "" ? "NULL" : puzzle.getLastMove()) << endl;
	puzzle.getEmpty() == nullptr  ? cout << "empty : NULL" << endl : cout << *puzzle.getEmpty() << endl;
	cout << endl << endl;
}

int main()
{
	Environment env = Environment(3, 0);
	printNpuzzle(env.puzzle);
	env.scrambler.scramble(22, env.puzzle);
	printNpuzzle(env.puzzle);
	cout << "before findPath" << endl;
	env.astar.findPath(env.puzzle);

	return 0;
}
