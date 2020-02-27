#include "../includes/Environment.class.hpp"

using namespace std;

Environment::Environment(short sizePuzzle) : puzzle(nPuzzle(sizePuzzle)), scrambler(Scrambler()), astar(Astar()), flags(0), waitLevel(0), scramblerAmountMove(0) {}

Environment::Environment(void) : scrambler(Scrambler()), astar(Astar()), flags(0), waitLevel(0), scramblerAmountMove(0) {}

Environment::~Environment() {}

void Environment::checkFile(char*av) const
{
	ifstream file;
	file.open(av);
	string line;
	int size = 0;
	bool first = true;
	bool sizeFound = false;
	while (!file.eof())
	{
		int amountNumber = 0;
		bool isFirstTrigger = false;
		getline(file, line);
		if (line.size() == 0)
			continue;
		for (short i = 0; i < line.size(); ++i)
			{
				if (line[i] == '#')
					break;
				if (line[i] != ' ' && !isdigit(line[i]))
					error("ERROR : invalid file format.");
				if (first == true && isdigit(line[i])) // on essai de récupérer la taille du puzzle.
				{
					first = false;
					sizeFound = true;
					int x = i;
					while (x < line.size() && line[x] != ' ')
						x++;
					 size = stoi(line.substr(i, i - x));
					 if (size > 30)
					 	error("ERROR : Puzzle size is to large... My program can't solve 5*5 puzzle efficiently so no use to deal with such big puzzles.");
					 else if (x < line.size())
					 	error("ERROR : invalid format for getting true size of puzzle");
					 else if (size == 0)
						error("ERROR : A puzzle can't have a size of zero.");
					isFirstTrigger = true;
					 break;
				}
				if (first == false && isdigit(line[i]))
				{
					if (amountNumber == 0)
						amountNumber++;
					else if (i - 1 > 0 && !isdigit(line[i - 1]))
						amountNumber++;
				}
			}
			if (first == false && amountNumber != size && isFirstTrigger == false)
				error("ERROR : bad amount of number in file on each line...");
	}
}

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
	this->checkFile(argv);
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
	// dernier check pour verifier que les nombres sont bien contiguës
	l.sort();
	list<int>::iterator it = l.begin();
	list<int>::iterator tmp = it;
	it++;
	list<int>::iterator end = l.end();
	for (int i = 2; it != end; ++it, ++i)
	{
		if ( (*tmp) != (*it) - 1 && (*it) != i)
			error("ERROR: Number does not a series of n + 1 or/and does not start with 1.");
		tmp++;
	}
}


void Environment::checkForFlagsError() const
{
	short heuristicCounter = 0;
	if ((flags & MANHATTAN))
		 heuristicCounter++;
	if ((flags & LINEAR))
		 heuristicCounter++;
	if ((flags & HAMMING))
		 heuristicCounter++;
	if ((flags & UNIFORM))
			heuristicCounter++;
	if (heuristicCounter > 1)
		error("ERROR : MULTIPLE HEURISTIC FOUND");
	if (flags & GREEDY && flags & UNIFORM)
		error("ERROR : OPPOSITE BEHAVIOR DETECTED: GREEDY AND UNIFORM MOD BOTH ENABLED");
	if (flags & FILE && flags & SIZE)
	 	error("ERROR : OPPOSITE BEHAVIOR DETECTED : FILE AND SIZE CAN'T BE BOTH ENABLED");
	if (flags & CLASSIC && flags & FILE )
	 	error("ERROR : CANT ACTIVATE CLASSIC MODE ON EXTERIOR PUZZLE");
}

void Environment::error(string s) const
{
	cout << s << endl;
	exit(0);
}

void Environment::parseArgs(int argc, char**argv)
{
	if (argc == 1)
	{
		cout << "USAGE :" << endl;
		cout << "-verbose		: allow program to print more information than asks in the 42 subject" << endl;
		cout << "-Astar  		: Activate the A* resolution algorithm." << endl;
		cout << "-greedy   		: Activate the greedy search mod" << endl;
		cout << "-uniform   		: all heuristic will return 0. Brute Force will be enabled" << endl;
		cout << "-classic   		: set solve mode to classic mode (the opposite is : 'The snail solution')." << endl;
		cout << "-manhattan 		: set heuristic to Manhattan distance." << endl;
		cout << "-linear 		: set heuristic to Linear distance (pythagoras)" << endl;
		cout << "-hamming 		: set heuristic to Hamming distance (amount of misplaced tile)" << endl;
		cout << "-visual:NUMBER		: Activate the visual mode when solving the puzzle. Enter the number between 0 and 9 to define speed solving" << endl;
		cout << "-size:NUMBER 		: The programm will setup a random grid by itself, scramble it and solve it." << endl;
		cout << "-scrambler:NUMBER	: The programm wil randomly apply NUMBER moves on the current puzzle (file or auto-generate nPuzzle)" << endl << endl;
		cout << "info : read README.txt to see more info about nPuzzle parser behavior, and possible errors." << endl;
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
				else if (!strcmp("-verbose", argv[i]))
					flags |= VERBOSE;
				else if (s.find("-visual:", 0) != string::npos)
				{
					flags |= VISUAL;
					if (s[s.find(":") + 2] != '\0')
						error("ERROR : invalid number after -visual:");
					waitLevel = s[s.find(":") + 1] - 48;
					if (waitLevel < 0 || waitLevel > 9)
						error("ERROR : invalid number after -visual: ");
				}
				else if (s.find("-size:", 0) != string::npos)
				{
					int i = s.find(":") + 1;
					string str = "";
					for(;s[i] != '\0'; ++i)
					{
						if (!isdigit(s[i]))
							error("ERROR : invalid number after -size:");
						str += s[i];
					}
					if (str.size() > 2)
						error("ERROR : invalid number after -size, number too big. (My program can't solve a 5*5 anyway so it's usless to create a grid that big.)");
					if (str.size() > 0)
						sizePuzzle = stoi(str);
					if (sizePuzzle < 2)
						error("ERROR : Can't create a puzzle of sizes less than 2.");
          flags |= SIZE;
				}
				else if (s.find("-scrambler:", 0) != string::npos)
				{
					int i = s.find(":") + 1;
					string str = "";
					for(;s[i] != '\0'; ++i)
					{
						if (!isdigit(s[i]))
							error("ERROR : invalid number after -scrambler:");
						str += s[i];
					}
					if (str.size() > 5)
						error("ERROR : PARSING SCRAMBLER : too much amount of move.");
					if (str.size() > 0)
						scramblerAmountMove = stoi(str);
					if (scramblerAmountMove < 0)
						error("ERROR : PARSING SCRAMBLER : invalid amount of move.");
          flags |= SCRAMBLER;
				}
				else
					checkForFile(argv[i]);
	   }
   }
	 if (!(flags & LINEAR) && !(flags & HAMMING) && !(flags & MANHATTAN) && !(flags & UNIFORM))
	 	flags |= MANHATTAN_CONFLICT;
	 checkForFlagsError();
}
