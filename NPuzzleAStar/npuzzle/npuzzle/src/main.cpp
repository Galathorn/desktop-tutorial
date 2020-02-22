#include <iostream>

#include "../includes/nPuzzle.class.hpp"
#include "../includes/Scrambler.class.hpp"
#include "../includes/Environment.class.hpp"
#include <unistd.h>

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
	int amount = 0;
	while(c = std::getchar())
	{
			if (c == 'e')
				break;
			else if (c == 'z' && ++amount)
				env.puzzle.Up();
			else if (c == 's' && ++amount)
				env.puzzle.Down();
			else if (c == 'd' && ++amount)
				env.puzzle.Right();
			else if (c == 'q' && ++amount)
				env.puzzle.Left();
			else if (c == 'r' && ++amount)
				env.scrambler.scramble(1, env.puzzle);

			system ("/bin/stty cooked");
			cout << endl << "\033[" << env.puzzle.getSize() + 6 << "A";
			cout << "puzzle state modified by [" << amount << "] moves" << endl;
			cout << "hCost : " << env.puzzle.getHcost() << endl;
			cout << env.puzzle << endl;
			system ("/bin/stty raw");
	}
	system ("/bin/stty cooked");

}


int main()
{
	int maxScramble = 1000;
	std::list<std::string> path;
	Environment env = Environment(3, 0);
	printNpuzzle(env.puzzle);
	cout << endl << endl;
	cout << "puzzle state modified by [0] moves" << endl;
	cout << "hCost : " << env.puzzle.getHcost() << endl;
	cout << env.puzzle << endl;
	bool once = false;
	while (once == false || env.puzzle.getHcost() != 0)
	{
			once = true;
			dealInput(env);
			path = env.astar.findPath(env.puzzle);
			std::list<std::string>::iterator it = path.begin();
			std::list<std::string>::iterator end = path.end();
			cout << endl;
			while (it != end )
			{
				cout << *it << endl;
				it++;
			}
			cout << endl;
			cout << env.puzzle << endl;
			if (path.size() != 0)
				break;
	}
	for(int i = 0; i < env.puzzle.getSize() + 3; ++i)
		cout << endl;
	std::list<string>::iterator it = path.begin();
	std::list<string>::iterator end = path.end();
	for(;it != end; ++it)
	{
		if (*it == "UP")
			env.puzzle.Up();
		if (*it == "DOWN")
			env.puzzle.Down();
		if (*it == "RIGHT")
			env.puzzle.Right();
		if (*it == "LEFT")
			env.puzzle.Left();
		cout << "\033[" << env.puzzle.getSize() + 4 << "A";
		for(int i = 0; i < env.puzzle.getSize() + 4; ++i)
			cout << "                                       " << endl;

		cout << "\033[" << env.puzzle.getSize() + 4 << "A";
		cout << "last move : " << *it << endl;
		cout << env.puzzle << endl;
		system ("/bin/stty raw");

		while(std::getchar() != 'e');
		system ("/bin/stty cooked");
		//usleep(1000000);


	}
	cout << "\033[" << (env.puzzle.getSize()) + 3  << "A";
	cout << env.puzzle << endl;
	return 0;
}
