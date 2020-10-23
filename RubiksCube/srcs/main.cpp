#include <string.h>
#include <iostream>
#include "../includes/cube.hpp"
#include "../includes/cubePrinter.hpp"
#include "../includes/configManager.hpp"
#include <unistd.h>

using namespace std;

struct s_flag
{
	bool 			scramble = false;
	bool 			counterMovement = false;
	list<string>	movements;
};


int printTab [4] = {3, 0, 1, 2};

// fonction check des étapes de CFOP

bool isPairSolved(Cube c)
{
	if (c.matrix[FRONT][5] == c.matrix[FRONT][8] &&  c.matrix[FRONT][5] == c.matrix[FRONT][4] &&  c.matrix[RIGHT][3] == c.matrix[RIGHT][6] && c.matrix[RIGHT][3] == c.matrix[RIGHT][4]
		&& c.matrix[DOWN][2] == c.matrix[DOWN][4])
		return true;
	return false;
}

bool isOLLSolved(Cube c)
{
	for (int i = 0, size = c.matrix[TOP].size(); i < size; ++i)
		if (c.matrix[TOP][i] != YELLOW)
			return false;
	return true;
}

bool isPLLSolved(Cube c)
{
	for (int i = 0; i < 3; ++i)
	{
		if (c.matrix[FRONT][i] != c.matrix[FRONT][(i + 1) % 3])
			return false;
		if (c.matrix[RIGHT][i] != c.matrix[RIGHT][(i + 1) % 3])
			return false;
		if (c.matrix[BACK][i] != c.matrix[BACK][(i + 1) % 3])
			return false;
		if (c.matrix[LEFT][i] != c.matrix[LEFT][(i + 1) % 3])
			return false;
	}
	if (!isOLLSolved(c))
		return false;
	return true;
}

bool isCubeSolved(Cube c)
{
	for (int i = 0; i < 6; ++i)
		for (int j = 0; j < 9; ++j)
		{
			if (c.matrix[i][j] != c.matrix[i][4])
				return false;
		}
	return true;
}


list<list<string>> getAllAlgorithmFromFile(string path)
{
	list<list<string>>	l;
	fstream 			f;
	string 				buff;

	f.open(path);
	if (!f.is_open())
		cout << "ERROR file opening getAllAlgorithmFromFile" << endl;
	while (!f.eof())
	{
		getline(f, buff);
		list<string> 	algo;
		size_t 			start = buff.find("|");
		size_t 			index = start - 1;

		while (start < std::string::npos)
		{
			bool ok = true;
			index = buff.find("|", index + 1);
			string tmp = buff.substr(start, index - start);
			for (int i = 0; i < tmp.size(); ++i)
				if (tmp[i] == ',' || tmp[i] == ' ')
					ok = false;
			start = index == std::string::npos ? index : index + 1;
			if (ok)
				algo.push_back(tmp);
		}
		if (algo.size())
			l.push_back(algo);
	}
	return l;
}

void printListMove(list<string> solution)
{
	if (solution.size() == 0)
	{
		cout << "list empty" << endl;
		return ;
	}
	for (list<string>::iterator it = solution.begin(), end = solution.end(); it != end; ++it)
		cout << (*it) << " ";
	cout << endl;
}

void parseFileToAlgorithm(string path, string destPath)
{
	fstream f;
	f.open(path);
	if (!f.is_open())
	{
		cout << "error file opening" << endl;
		return;
	}
	string buff;
	list<list<string>> allF2L;
	while(!f.eof())
	{
		getline(f, buff);

		list<string>	l;
		size_t 			start = buff.find("\"");
		size_t 			index = start -1;

		while (start < std::string::npos)
		{
			bool ok = true;
			index = buff.find("\"", index + 1);
			string tmp = buff.substr(start, index - start);
			for (int i = 0; i < tmp.size(); ++i)
				if (tmp[i] == ',' || tmp[i] == ' ')
					ok = false;
			start = index == std::string::npos ? index : index + 1;
			if (ok)
				l.push_back(tmp);
		}
		if (l.size())
			allF2L.push_back(l);
	}
	ofstream f2;
	f2.open(destPath);
	if(f2.is_open())
	{
		cout << "is open correctly ! " << endl;
		for (list<list<string>>::iterator it = allF2L.begin(), end = allF2L.end(); it != end; ++it)
		{
			for (list<string>::iterator it2 = (*it).begin(), end2 = (*it).end(); it2 != end2; ++it2)
				f2 << (*it2) << "|";
			f2 << endl;
		}
		f2.close();
	}
	f.close();
}

void printSpaces(int nb, cubePrinter printer)
{
	for (int i = 0; i < nb; ++i)
		cout << " ";
}

void printCube(Cube c, cubePrinter printer)
{
	static int counter = 0;
	if (counter > 0)
		cout << "\033[11A";
	int spaces = 3 * 2 + 1;
	for (int y = 0; y < 3; ++y)
	{
		printer.switchToNormal();
		printSpaces(spaces, printer);
		for (int x = 0; x < 3; ++x)
		{
			printer.switchColor(c.matrix[TOP][y * 3 + x]);
			cout << c.matrix[TOP][y * 3 + x];
			printer.switchToNormal();
			cout << " ";
		}
		cout << endl;
	}
	cout << endl;
	for (int i = 0; i < 3; ++i)
	{
		for (int x = 0; x < 4; ++x)
		{
			for (int j = 0; j < 3; ++j)
			{
				int v = c.matrix[printTab[x]][i * 3 + j];
				printer.switchColor(v);
				cout << v;
				printer.switchToNormal();
				cout << " ";
			}
			cout << " ";
		}
		cout << endl;
	}
	cout << endl;
	for (int y = 0; y < 3; ++y)
	{
		printer.switchToNormal();
		printSpaces(spaces, printer);
		for (int x = 0; x < 3; ++x)
		{
			int v = c.matrix[DOWN][y * 3 + x];
			printer.switchColor(v);
			cout << v;
			printer.switchToNormal();
			cout << " ";
		}
		cout << endl;
	}
	counter++;
}


void printConfig(Cube c, list<nodeInfo> interestPieces, configManager manager)
{
	string s = manager.cubeToConfiguration(c, interestPieces);
	for (int i = 0; i < s.size(); ++i)
	{
		if (i % 9 == 0)
			cout << " ";
		cout << s[i];
	}
	cout << endl;
}

list<string> solveF2L(Cube c, list<list<string>> f2l, configManager configManager)
{
	list<string>	l;
	Cube 			neutral = c;

	list<list<string>>::iterator it = f2l.begin();
	list<list<string>>::iterator end = f2l.end();
	while (it != end)
	{
		c = neutral;
		configManager.scrambler.applySpecificList(&c, (*it));
		if (isPairSolved(c))
			return (*it);
		it++;
	}
	return l;
}

list<string> solveOLL(Cube c, list<list<string>> moves, configManager configManager)
{
	list<string> 	l;
	Cube 			neutral = c;
	vector<string>	us = {"U", "U'","U2"};
	for (int i = -1, size = us.size(); i < size; ++i)
	{
		list<list<string>>::iterator it = moves.begin();
		list<list<string>>::iterator end = moves.end();
		while (it != end)
		{
			c = neutral;
			if (i >= 0)
				configManager.scrambler.applySpecificMove(&c, us[i]);
			configManager.scrambler.applySpecificList(&c, (*it));
			if (isOLLSolved(c))
			{
				if (i >= 0)
					l.push_back(us[i]);
				for (list<string>::iterator it2 = (*it).begin(), end2 = (*it).end(); it2 != end2; ++it2)
					l.push_back((*it2));
				return l;
			}
			it++;
		}
	}
	return l;	
}

list<string> solvePLL(Cube c, list<list<string>> moves, configManager configManager)
{
	list<string> 	l;
	Cube 			neutral = c;
	vector<string>	us = {"U", "U'","U2"};
	for (int i = -1, size = us.size(); i < size; ++i)
	{
		list<list<string>>::iterator it = moves.begin();
		list<list<string>>::iterator end = moves.end();
		while (it != end)
		{
			c = neutral;
			if (i >= 0)
				configManager.scrambler.applySpecificMove(&c, us[i]);
			configManager.scrambler.applySpecificList(&c, (*it));
			if (isPLLSolved(c))
			{
				if (i >= 0)
					l.push_back(us[i]);
				for (list<string>::iterator it2 = (*it).begin(), end2 = (*it).end(); it2 != end2; ++it2)
					l.push_back((*it2));
				return l;
			}
			it++;
		}
	}
	return l;	
}

string solveLastOrientation(Cube c, configManager configManager)
{
	vector<string>	us = {"U", "U'","U2"};
	Cube 			neutral = c;

	for (int i = 0; i < 3; ++i)
	{
		c = neutral;
		configManager.scrambler.applySpecificMove(&c, us[i]);
		if (isCubeSolved(c))
			return us[i];
	}
	return string();
}


list<string> mergeTwoList(list<string> l, list<string> l2)
{
	for (list<string>::iterator it = l2.begin(), end = l2.end(); it != end; ++it)
		l.push_back((*it));
	return l;
}

list<string> solveCube(Cube c, configManager configManager)
{
	string 				frontPiecePath = "./files/42Configs/CROSS/frontPiece/";
	string 				backPiecePath = "./files/42Configs/CROSS/backPiece/";
	string 				twoPiecesPath = "./files/42Configs/CROSS/firstTwoPieces/";
	string 				pathF2LCleaned = "./files/brutFiles/F2L_brut.txt";
	string 				pathOLLCleaned = "./files/brutFiles/OLL_brut.txt";
	string				pathPLLCleaned = "./files/brutFiles/PLL_brut.txt";
	list<list<string>>	f2l = getAllAlgorithmFromFile(pathF2LCleaned);
	list<list<string>>	oll = getAllAlgorithmFromFile(pathOLLCleaned);
	list<list<string>>	pll = getAllAlgorithmFromFile(pathPLLCleaned);
	list<nodeInfo>		interestPieces;

	list<string> final;

	interestPieces.push_back(nodeInfo(LEFT, 7));
	interestPieces.push_back(nodeInfo(RIGHT, 7));

	list<string> solution = configManager.getResolution(c, twoPiecesPath, interestPieces);
	configManager.scrambler.applySpecificList(&c, solution);
	final = solution;

	interestPieces.push_back(nodeInfo(FRONT, 7));
	solution = configManager.getResolution(c, frontPiecePath, interestPieces);
	configManager.scrambler.applySpecificList(&c, solution);
	final = mergeTwoList(final, solution);

	// a ajouter après avoir trouvé les trois premières pièces
	interestPieces.push_back(nodeInfo(BACK, 7));
	solution = configManager.getResolution(c, backPiecePath, interestPieces);
	configManager.scrambler.applySpecificList(&c, solution);
	final = mergeTwoList(final, solution);

	for (int i = 0; i < 4; ++i)
	{
		list<string> nextF2L = solveF2L(c, f2l, configManager);
		configManager.scrambler.applySpecificList(&c, nextF2L);
		if (nextF2L.size())
			final = mergeTwoList(final, nextF2L);
		c.y();
		final.push_back("y");
	}

	list<string> OLL = solveOLL(c, oll, configManager);
	configManager.scrambler.applySpecificList(&c, OLL);
	if (OLL.size())
		final = mergeTwoList(final, OLL);

	list<string> PLL = solvePLL(c, pll, configManager);
	configManager.scrambler.applySpecificList(&c, PLL);
	if(PLL.size())
		final = mergeTwoList(final, PLL);

	string lastMovement = solveLastOrientation(c, configManager);
	configManager.scrambler.applySpecificMove(&c, lastMovement);
	if (lastMovement.size())
		final.push_back(lastMovement);
	return final;
}

// this function will return the cube's rotation's state depending on the current new Rotation movement (y, y2 or y')
int getCubeState(int state, string m)
{
	if (state == 0 && m == "y")
		return 1;
	if (state == 0 && (m == "y2" || m == "y'2"))
		return 2;
	if (state == 0 && m == "y'")
		return 3;

	if (state == 1 && m == "y")
		return 2;
	if (state == 1 && (m == "y2" || m == "y'2"))
		return 3;
	if (state == 1 && m == "y'")
		return 0;

	if (state == 2 && m == "y")
		return 3;
	if (state == 2 && (m == "y2" || m == "y'2"))
		return 0;
	if (state == 2 && m == "y'")
		return 1;

	if (state == 3 && m == "y")
		return 0;
	if (state == 3 && (m == "y2" || m == "y'2"))
		return 1;
	if (state == 3 && m == "y'")
		return 2;

	return 0;
}

map<string, map<string, string>> setupConvertor()
{
	map<string, map<string, string>>	c;
	vector<string> moves =			{"R", "L", "U", "D", "F", "B", "M", "R2", "L2", "U2", "D2", "F2", "B2", "M2", "R'", "L'", "U'", "D'", "F'", "B'", "M'", "r", "r'", "r2", "l", "l'", "l2", "R'2", "L'2", "U'2", "D'2", "F'2", "B'2"};
	vector<string> moves2 =			{"R", "L", "U", "D", "F", "B", "M", "R2", "L2", "U2", "D2", "F2", "B2", "M2", "R'", "L'", "U'", "D'", "F'", "B'", "M'", "r", "r'", "r2", "l", "l'", "l2", "R2", "L2", "U2", "D2", "F2", "B2"};
	vector<string> y_moves =		{"F", "B", "U", "D", "L", "R", "M", "F2", "B2", "U2", "D2", "L2", "R2", "M2", "F'", "B'", "U'", "D'", "L'", "R'", "M'", "r", "r'", "r2", "l", "l'", "l2", "F2", "B2", "U2", "D2", "L2", "R2"};
	vector<string> y2_moves =		{"L", "R", "U", "D", "B", "F", "M", "L2", "R2", "U2", "D2", "B2", "F2", "M2", "L'", "R'", "U'", "D'", "B'", "F'", "M'", "l", "l'", "l2", "r", "r'", "r2", "L2", "R2", "U2", "D2", "B2", "F2"};
	vector<string> y_prime_moves =	{"B", "F", "U", "D", "R", "L", "M", "B2", "F2", "U2", "D2", "R2", "L2", "M2", "B'", "F'", "U'", "D'", "R'", "L'", "M'", "r", "r'", "r2", "l", "l'", "l2", "B2", "F2", "U2", "D2", "R2", "L2"};

	for (int i = 0, size = moves.size(); i < size; ++i)
	{
		c["NULL"][moves[i]] = moves2[i]; 
		c["y"][moves[i]] = y_prime_moves[i]; 
		c["y2"][moves[i]] = y2_moves[i]; 
		c["y'2"][moves[i]] = y2_moves[i]; 
		c["y'"][moves[i]] = y_moves[i]; 
	}

	return c;
}

list<string> simplifySolution(list<string> s)
{
	map<string, map<string, string>>	convertor = setupConvertor();
	list<string>						finalList;
	int 								cubeState = 0;
	vector<string> 						rots = {"NULL", "y","y2","y'", "y'2"};

	for (list<string>::iterator it = s.begin(), end = s.end(); it != end; ++it)
	{
		if ( *it == rots[1] || *it == rots[2] || *it == rots[3] || *it == rots[4])
		{
			cubeState = getCubeState(cubeState, *it);
			continue;
		}
		if ((*it).size())
			finalList.push_back(convertor[rots[cubeState]][*it]);
	}
	return finalList;
}

void printUsage()
{
	cout << "USAGE : " << endl << "./RubiksCube \"*insert sequence movement*\"" << endl << "EXEMPLE : ./RubiksCube \"R2 U2 L D F U2 R2\"" << endl;
	cout << endl << "FLAGS : " << endl << "-s :  (for scramble) print a random scrambler for the cube, scramble a cube, solve it and print the solution." << endl;
	cout << "-l : (for line) print the amount of movement that the algorithm used to solve the cube." << endl;
	cout << endl << "Good to know : " << endl << "If -s is enabled but a scramble string is also specified, this scramble string will be ignored and a random scramble will be generated and used." << endl;
	cout << "If the parameters are neither -l or -s or a valid sequence of move, the program will be terminated." << endl;
	cout << "If multiple movements are send to the program as parameters but are not in one string, the program will only use the first movement and solve the cube." << endl;
	cout << "EXEMPLE : ./RubiksCube R2 F2 L2 --> In this exemple, the program will use R2 as only parameters and ignore F2 and L2. The correct input should be : ./RubiksCube \"R2 F2 L2\"." << endl;
	exit(0);
}

s_flag checkFlags(int ac, char** av)
{
	s_flag flags;

	for (int i = 1; i < ac; ++i)
	{
		if (!strcmp(av[i], "-l"))
			flags.counterMovement = true;
		if (!strcmp(av[i], "-s"))
			flags.scramble = true;
	}
	return flags;
}

list<string> strSplit(string s, string c)
{
	list<string>	l;
	size_t 			start = 0;
	size_t 			index = start - 1 < 0 ? 0 : start - 1;

	while (start < string::npos)
	{
		index = s.find(c, index + 1);
		string tmp = s.substr(start, index - start);
		start = index == string::npos ? index : index + 1;
		l.push_back(tmp);
	}
	return l;
}

bool isListValid(list<string> l)
{
	vector<string> moves = {"R", "L", "U", "D", "F", "B", "R2", "L2", "U2", "D2", "F2", "B2", "R'", "L'", "U'", "D'", "F'", "B'"};
	for (list<string>::iterator it = l.begin(), end = l.end(); it != end; ++it)
	{
		bool contains = false;
		for (int i = 0, size = moves.size(); i < size; ++i)
			if (moves[i] == (*it))
			{
				contains = true;
				break;
			}
		if (!contains)
			return false;
	}
	return true;
}

list<string> parseScrambler(int ac, char** av)
{
	for (int i = 1; i < ac; ++i)
	{
		string s = string(av[i]);
		list<string> tmpList = strSplit(s, " ");
		if (tmpList.size() && isListValid(tmpList))
			return tmpList;
	}
	cout << "Invalid arguments" << endl;
	exit(0);
	return list<string>();
}


int main(int ac, char **av)
{
	string pathF2LBrutFile = "../bruteFiles/f2l.txt";
	string pathF2LCleaned = "./files/brutFiles/F2L_brut.txt";

	string pathOLLBrut = "../bruteFiles/oll.txt";
	string pathOLLCleaned = "./files/brutFiles/OLL_brut.txt";

	string pathPLLBrut = "../bruteFiles/pll.txt";
	string pathPLLCleaned = "./files/brutFiles/PLL_brut.txt";

	string frontPiecePath = "./files/42Configs/CROSS/frontPiece/";
	string backPiecePath = "./files/42Configs/CROSS/backPiece/";
	string twoPiecesPath = "./files/42Configs/CROSS/firstTwoPieces/";

	Cube				c;
	cubePrinter			printer;
	configManager		configManager;
	s_flag 				flags;
	list<string> 		listMove;


	if (ac == 1)
		printUsage();
	else if (ac > 1)
		flags = checkFlags(ac, av);
	if (flags.scramble)
		listMove = configManager.scrambler.getRandomList(20, configManager.doublePieceCrossMoves);
	else
		listMove = parseScrambler(ac, av);
	if (listMove.size() == 0)
		return 0;
	cout << "Scrambler : " << endl;
	printListMove(listMove);
	configManager.scrambler.applySpecificList(&c, listMove);
	list<string> solution = simplifySolution(solveCube(c, configManager));
	cout << "Solution : " << endl;
	printListMove(solution);
	if (flags.counterMovement)
		cout << "Amount of move in solution : " << solution.size() << endl;
	return 0;
}



//	configManager.launchBruteForce(5, interestPieces, configManager.doublePieceCrossMoves, backPiecePath);

// first block interestPieces
/*
	interestPieces.push_back(nodeInfo(LEFT, 7));
	interestPieces.push_back(nodeInfo(LEFT, 6));
	interestPieces.push_back(nodeInfo(LEFT, 3));
	interestPieces.push_back(nodeInfo(LEFT, 5));
	interestPieces.push_back(nodeInfo(LEFT, 8));
*/
