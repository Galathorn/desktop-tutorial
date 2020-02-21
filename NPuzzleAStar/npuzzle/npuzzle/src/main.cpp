#include <iostream>

#include "../includes/nPuzzle.class.hpp"
#include "../includes/Scrambler.class.hpp"
#include "../includes/Environment.class.hpp"

using namespace std;
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77


#include <stdio.h>

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

void dealInput(Environment &env)
{
	char c;
	system ("/bin/stty raw");

	while(c = std::getchar())
	{
			if (c == 'e')
				break;
			else if (c == 'z')
				env.puzzle.Up();
			else if (c == 's')
				env.puzzle.Down();
			else if (c == 'd')
				env.puzzle.Right();
			else if (c == 'q')
				env.puzzle.Left();

			system ("/bin/stty cooked");

			cout << "\033[" << env.puzzle.getSize() + 3 << "A";
			cout << env.puzzle << endl;
			system ("/bin/stty raw");
	}
	system ("/bin/stty cooked");

}


int main()
{
	Environment env = Environment(3, 0);
	printNpuzzle(env.puzzle);
	env.scrambler.scramble(0, env.puzzle);
	cout << env.puzzle << endl;
	dealInput(env);

	std::list<std::string> path = env.astar.findPath(env.puzzle);
	std::list<std::string>::iterator it = path.begin();
	std::list<std::string>::iterator end = path.end();
	while (it != end )
	{
		cout << *it << endl;
		it++;
	}

		cout << env.puzzle << endl;

	dealInput(env);


	return 0;
}
