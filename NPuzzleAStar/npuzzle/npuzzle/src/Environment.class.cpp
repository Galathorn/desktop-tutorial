#include "../includes/Environment.class.hpp"

using namespace std;

Environment::Environment(short sizePuzzle) : puzzle(nPuzzle(sizePuzzle)), scrambler(Scrambler()), astar(Astar()), flags(0), waitLevel(0) {}

Environment::Environment(void) : scrambler(Scrambler()), astar(Astar()), flags(0), waitLevel(0) {}


Environment::~Environment() {}

void Environment::checkForFile(char*argv)
{
	ifstream ifs;
	ifs.open(argv);
	if (ifs.good() && flags & SIZE)
			cout << "ERROR : SIZE IS ALREADY ENABLED" << endl;
	else if (!ifs.good())
	{
		cout << "ERROR : INVALID ARGUMENT OR CANT OPEN THE FILE"<< endl;
		exit(0);
	}
	flags |= FILE; // on active le flag FILE sur la variable file
	list<int> l; // liste contenant l'ensemble des nombres
	string		line;
	bool			first = true;
	while (!ifs.eof())
	{
		getline(ifs, line);
		for (short i = 0 ; i < line.size(); ++i)
		{
				if (line[i] == '#')
					break;
				if (isdigit(line[i]))
				{
					string number = string("");
					for (short x = i; x <= line.size(); x++)
					{
								if (!isdigit(line[x]))
								{
									i = x;
									break;
								}
								number += line[x];
					}
					if (first == true)
					{
						first = false;
						this->puzzle = nPuzzle(stoi(number));
					}
					else
						l.push_back(stoi(number));
				}
		}
		cout << line << endl;
	}
	ifs.close();
	puzzle.arrayToGrid(l);
	puzzle.updateHcost();
	puzzle.fillEmpty(puzzle.getSize());
}


void Environment::parseArgs(int argc, char**argv)
{
	if (argc == 1)
	{
		cout << "USAGE :" << endl;
		cout << "-Astar  		: Activate the A* resolution algorithm." << endl;
		cout << "-greedy   		: Activate the greedy search mod" << endl;
		cout << "-uniform   		: all heuristic will return 0. Brute Force will be enabled" << endl;
		cout << "-classic   		: set solve mode to classic mode (the opposite is : 'The snail solution')." << endl;
		cout << "-manhattan 		: set heuristic to Manhattan distance." << endl;
		cout << "-linear 		: set heuristic to Linear distance (pythagoras)" << endl;
		cout << "-hamming 		: set heuristic to Hamming distance (amount of misplaced tile)" << endl;
		cout << "-visual:NUMBER		: Activate the visual mode when solving the puzzle. Enter the number between 0 and 9 to define speed solving" << endl;
		cout << "-size:NUMBER 		: The programm will setup a random grid by itself, scramble it and solve it. If a file is found, this option is disabled." << endl;
		cout << "-scrambler:NUMBER	: The programm wil randomly apply NUMBER moves on the current puzzle (file or auto-generate nPuzzle)" << endl << endl;
		cout << "info : read README.txt to see more info about nPuzzle parser behavior" << endl;
		exit(0);
	}
	else
	{
		for (int i = 1; i < argc; ++i)
		{
      string s = string(argv[i]);
				if (!strcmp("-Astar", argv[i]))
					flags |= ASTAR;
				else if (!strcmp("-greedy", argv[i]))
					flags |= GREEDY;
				else if (!strcmp("-uniform", argv[i]))
					flags |= UNIFORM;
				else if (!strcmp("-manhattan", argv[i]))
					flags |= MANHATTAN;
				else if (!strcmp("-linear", argv[i]))
					flags |= LINEAR;
				else if (!strcmp("-hamming", argv[i]))
					flags |= HAMMING;
				else if (!strcmp("-classic", argv[i]))
					flags |= CLASSIC;
				else if (s.find("-visual:", 0) != string::npos)
				{
					flags |= VISUAL;
					waitLevel = s[s.find(":") + 1] - 48;
					if (waitLevel < 0 || waitLevel > 9)
						{
								cout << "ERROR : invalid number after -visual: " << endl;
								exit(0);
						}
				}
				else if (s.find("-size:", 0) != string::npos)
				{
					int i = s.find(":") + 1;
					cout << "index : "<< i << endl;
					string str = "";
					for(;s[i] != '\0'; ++i)
					{
						if (!isdigit(s[i]))
						{
							cout << "ERROR : invalid number after -size:" << endl;
							exit(0);
						}
						str += s[i];
					}
					if (str.size() > 0)
						sizePuzzle = stoi(str);
					cout << "sizePuzzle : " << sizePuzzle << endl;
          flags |= SIZE;
				}
				else if (s.find("-scrambler:", 0) != string::npos)
				{
          flags |= SCRAMBLER;


				}
				else
					checkForFile(argv[i]);
	   }
   }
	 short heuristicCounter = 0;
   if ((flags & MANHATTAN))
	 		heuristicCounter++;
   if ((flags & LINEAR))
	 		heuristicCounter++;
   if ((flags & HAMMING))
	 		heuristicCounter++;
	 if (heuristicCounter > 1)
	 	{
				cout << "ERROR : MULTIPLE HEURISTIC FOUND" << endl;
				exit(0);
		}
	 if (flags & GREEDY && flags & UNIFORM)
		{
				cout << "ERROR : OPPOSITE BEHAVIOR DETECTED: GREEDY AND UNIFORM MOD BOTH ENABLED" << endl;
				exit(0);
		}
		if (flags & FILE && flags & SIZE)
		{
			cout << "ERROR : OPPOSITE BEHAVIOR DETECTED : FILE AND SIZE CAN'T BE BOTH ENABLED" << endl;
			exit(0);
		}
		if (flags & CLASSIC && flags & FILE )
		{
			cout << "ERROR : CANT ACTIVATE CLASSIC MODE ON EXTERIOR PUZZLE" << endl;
			exit(0);
		}
}
