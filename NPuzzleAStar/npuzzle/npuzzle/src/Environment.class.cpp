#include "../includes/Environment.class.hpp"

using namespace std;

Environment::Environment(short sizePuzzle) : puzzle(nPuzzle(sizePuzzle)), scrambler(Scrambler()), astar(Astar()) {}

Environment::~Environment() {}

void Environment::parseArgs(int argc, char**argv)
{
	if (argc == 1)
	{
		cout << "USAGE :" << endl;
		cout << "-Astar  			: Activate the A* resolution algorithm." << endl;
		cout << "-greedy   		: Activate the greedy search mod" << endl;
		cout << "-uniform   		: all heuristic will return 0. Brute Force will be enabled" << endl;
		cout << "-manhattan 		: set heuristic to Manhattan distance." << endl;
		cout << "-linear 		: set heuristic to Linear distance (pythagoras)" << endl;
		cout << "-hamming 		: set heuristic to Hamming distance (amount of disabled tile)" << endl;
		cout << "-size:NUMBER 		: The programm will setup a random grid by itself, scramble it and solve it. If a file is found, this option is disabled." << endl;
		cout << "-scrambler:NUMBER	: The programm wil randomly apply NUMBER moves on the current puzzle (file or auto-generate nPuzzle)" << endl << endl;
		cout << "info : if multiple heuristic are enabled, the programm will shut down." << endl;
		exit(0);
	}
	else
	{
		for (int i = 1; i < argc; ++i)
		{
      string s = string(argv[i]);
				if (!strcmp("-Astar", argv[i]))
					flags |= 0x01;
				else if (!strcmp("-greedy", argv[i]))
					flags |= 0x02;
				else if (!strcmp("-uniform", argv[i]))
					flags |= 0x04;
				else if (!strcmp("-manhattan", argv[i]))
					flags |= 0x08;
				else if (!strcmp("-linear", argv[i]))
					flags |= 0x10;
				else if (!strcmp("-hamming", argv[i]))
					flags |= 0x20;
				else if (s.find("-size:"))
				{
          flags |= 0x40;
					cout << "size is specified and found !" << endl;
				}
				else if (s.find("-scrambler:"))
				{
          flags |= 0x80;
					cout << "scrambler has been called" << endl;
				}
	   }
   }

   if (flags &= 0x01 != 0)
      cout << "a star has been activated" << endl;
   if (flags &= 0x02 != 0)
      cout << "greedy has been activated" << endl;
   if (flags &= 0x04 != 0)
      cout << "uniform has been activated" << endl;
   if (flags &= 0x08 != 0)
      cout << "manhattan has been activated" << endl;
   if (flags &= 0x10 != 0)
      cout << "linear has been activated" << endl;
   if (flags &= 0x20 != 0)
      cout << "hamming has been activated" << endl;
   if (flags &= 0x40 != 0)
      cout << "size  has been specified" << endl;
   if (flags &= 0x80 != 0)
      cout << "scrambler has been specified" << endl;

}
