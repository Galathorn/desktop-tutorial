#include "../includes/configManager.hpp"

configManager::configManager()
{
	vector<string> m = {"R","L","U","D","F","B","M", "R2","L2","U2","D2","F2","B2","M2","R'","L'","U'","D'","F'","B'","M'", "R'2","L'2","U'2","D'2","F'2","B'2","M'2"};
	vector<string> o = {"r","r2","r'","l","l2","l'","y", "y2", "y'"};
	for (int i = 0; i < m.size(); ++i)
		weights[m[i]] = 1;
	for (int i = 0; i < o.size(); ++i)
		weights[o[i]] = 2;
	
	m = {"R","L","U","D","F","B","M","y", "r", "l", "r2", "l2", "R2", "L2","U2","D2","F2","B2","M2","y2"};
	o = {"R'","L'","U'","D'","F'","B'","M'","y'", "r'","l'","r'2","l'2", "R'2","L'2","U'2","D'2","F'2","B'2","M'2","y'2"};
	for (int i = 0; i < m.size(); ++i)
	{
		reverseMovementHashTable[m[i]] = o[i];
		reverseMovementHashTable[o[i]] = m[i];
	}
	vector<string> s = {"FRONT","RIGHT","BACK","LEFT","TOP","DOWN"};
	for (int i = 0; i < 6; ++i)
	{
		valueToMatrix[i] = s[i];
		matrixToValue[s[i]] = i;
	}
	configManager::initialiseNodeTree();
}

configManager::~configManager() {}


list<nodeInfo> configManager::stringToNodeInfoList(string s)
{
	list<nodeInfo>	l;
	list<string>		res;

	size_t index = 0;
	size_t start = 0;
	while (start < std::string::npos)
	{
		index = s.find("-", !index ? index : index + 1);
		string tmp = s.substr(start, index - start);
		start = index == std::string::npos ? index : index + 1;
		res.push_back(tmp);
	}
	list<int> v;
	list<int> v2;
	int c = 0;
	for (list<string>::iterator it = res.begin(), end = res.end(); it != end; ++it)
	{
		if (c == 0)
			v2.push_back(matrixToValue[(*it)]);
		else if (c)
			v.push_back(stoi((*it)));
		c = (c + 1) % 2;
	}
	list<int>::iterator it1 = v.begin();
	list<int>::iterator it2 = v2.begin();
	list<int>::iterator vend = v.end();
	list<int>::iterator v2end = v2.end();

	for (; it1 != vend; ++it1, ++it2)
	{
		nodeInfo node;
		node.matrix = (*it2);
		node.index = (*it1);
		l.push_back(node);
	}
	return l;
}

void configManager::initialiseNodeTree()
{
	fstream		f;
	string		buff = "";
	vector<int> matrixes = vector<int>(6);

	f.open(pathNodeTree);
	getline(f, buff);
	for (int i = 0; i < 6; ++i)
	{
		getline(f, buff);
		matrixes[i] = matrixToValue[buff];
	}
	getline(f, buff);
	getline(f, buff);
	for (int i = 0; i < 6; ++i)
	{
		for (int j = 0; j < 9; ++j)
		{
			getline(f, buff);
			list<nodeInfo> l = stringToNodeInfoList(buff);
			if (l.size())
				nodeTree[i][j] = l;
		}
		getline(f, buff);
	}
}

string configManager::cubeToConfiguration(Cube c, list<nodeInfo> l)
{
	string 	conf = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
	Cube 	neutralCube;

	for (list<nodeInfo>::iterator it = l.begin(), end = l.end(); it != end; ++it)
	{	
		bool isPieceFound = false;
		for (int y = 0; y < 6; ++y)
		{
			for (int x = 0; x < 9; ++x)
			{
				if (c.matrix[y][x] == neutralCube.matrix[(*it).matrix][(*it).index] && nodeTree[(*it).matrix][(*it).index].size() == nodeTree[y][x].size())
				{
					list<nodeInfo>::iterator it2 = nodeTree[(*it).matrix][(*it).index].begin();
					list<nodeInfo>::iterator end2 = nodeTree[(*it).matrix][(*it).index].end();
					int counter = 0;
					for (; it2 != end2; ++it2)
					{
						list<nodeInfo>::iterator it3 = nodeTree[y][x].begin();
						list<nodeInfo>::iterator end3 = nodeTree[y][x].end();
						for (; it3 != end3; ++it3)
							if (c.matrix[(*it3).matrix][(*it3).index] == neutralCube.matrix[(*it2).matrix][(*it2).index])
							{
								counter++;
								break;
							}
					}
					if (counter == nodeTree[(*it).matrix][(*it).index].size())
					{
						isPieceFound = true;
						it2 = nodeTree[y][x].begin();
						end2 = nodeTree[y][x].end();
						for(; it2 != end2; ++it2)
							conf[(*it2).matrix * 9 + (*it2).index] = c.matrix[(*it2).matrix][(*it2).index] + 48;
						conf[y * 9 + x] = c.matrix[y][x] + 48;
						break;
					}
				}	
			}
			if (isPieceFound)
				break;
		}
	}
	return conf;
}

int configManager::getListMoveWeight(list<string> l)
{
	int weight = 0;
	for (list<string>::iterator it = l.begin(), end = l.end(); it != end; ++it)
	{
		if ((*it).size())
		{
			weight += weights[(*it)];
//			cout << weights[(*it)] << " : " << (*it) << " ";
		}
	}
//	cout << endl;
	return weight;
}

void configManager::createConfig(string configName, list<string> moves, string path)
{
	int weight = configManager::getListMoveWeight(moves);
	ofstream f;

	f.open(path + configName + extension, std::fstream::trunc);
	f << weight << endl;
	for (list<string>::iterator it = moves.begin(), end = moves.end(); it != end; ++it)
		f << (*it) << endl;
	f.close();
}

list<string> configManager::getResolution(Cube c, string path, list<nodeInfo> interestPieces)
{
	list<string>	l;
	string			config = cubeToConfiguration(c, interestPieces);
	ifstream		file;

	file.open(path + config + extension);
	if (!file)
		return list<string>();
	string str;
	getline(file, str);
	while (!file.eof())
	{
		getline(file, str);
		if (str.size())
			l.push_back(str);
	}
	return l;
}

bool configManager::tryCreateNewConfiguration(Cube c, list<string> m, string path, list<nodeInfo> interestPieces)
{
	//	string conf = "XXXXXXX5XXXXXXXXXXXXXXXXXXXXXXXXXX3XXXXXXXXXXX1X5XXXXX";
/*
	vector<string> t = {"F'", "R'"};
	int i = 0;
	int counter = 0;
	if(m.size() == t.size())
	for (list<string>::iterator it = m.begin(), end = m.end(); it != end; ++it)
	{
		if (t[i] == (*it))
			counter++;
		i++;
	}
	if (counter == m.size())
	{
		string cfg = cubeToConfiguration(c, interestPieces);
		cout << "config : " << cfg << endl;
	}

*/
	list<string> l = configManager::getResolution(c, path, interestPieces);
	if (!l.size())
	{
		string cfg = cubeToConfiguration(c, interestPieces);
		/*
		if (cfg == conf)
		{
			cout << "creating file : " << endl;
			for (list<string>::iterator it = m.begin(), end = m.end(); it != end; ++it)
				cout << (*it) << " ";
			cout << endl;
		}
		*/
		configManager::createConfig(cfg, m, path);
	}
	else if (l.size() > m.size() ||  (l.size() == m.size() && getListMoveWeight(l) > getListMoveWeight(m)))
	{
	//	string cfg = cubeToConfiguration(c, interestPieces);
		/*
		if (cfg == conf)
		{
			cout << "replacing file : " << endl;
			cout << "l.size : " << l.size() << " m.size : " << m.size() << endl;
			for (list<string>::iterator it = m.begin(), end = m.end(); it != end; ++it)
				cout << (*it) << " ";
			for (list<string>::iterator it = l.begin(), end = l.end(); it != end; ++it)
				cout << (*it) << " ";
			cout << endl;
		}
		*/		
		createConfig(cubeToConfiguration(c, interestPieces), m, path);
	}
	else
		return false;
//	cout << endl << endl;
	return true;
}

vector<int> configManager::getCounterBruteForce(int *depth)
{
	vector<int>	v = vector<int>(9);
	ifstream	f;
	int			i = 0;
	
	f.open(pathIndexes);
	string str;
	getline(f, str); // we get the first usless line
	getline(f, str); // we get the currentDepth
	*depth = stoi(str); // we assign the correct depth
	getline(f,str); // we get the next usless line
	getline(f,str);
	while (!f.eof() && i < 9) // we get the 9 indexes
	{
		getline(f, str);
		v[i] = stoi(str);
		i++;
	}
	f.close();
	return v;
}

void printTab(vector<int> t)
{
	for(int i = 0; i < t.size(); ++i)
	{
		cout << "[" << t[i] << "]" << " ";
	}
	cout << endl;
}

bool configManager::checkFirstPiece(Cube c)
{
	if (c.matrix[LEFT][7] == BLUE && c.matrix[DOWN][3] == WHITE)
		return true;
	return false;
}

bool configManager::checkFirstPieceAndBackBlock(Cube c)
{
	bool a = checkFirstPiece(c);
	bool b = false;
	bool c2 = false;

	if (c.matrix[LEFT][6] == BLUE && c.matrix[DOWN][6] == WHITE && c.matrix[BACK][8] == ORANGE)
		b = true;
	if (c.matrix[LEFT][3] == BLUE && c.matrix[BACK][5] == ORANGE)
		c2 = true;
	if (a == true && b == true && c2 == true)
		return true;
	return false;
}

bool configManager::checkFirstBlockRoux(Cube c)
{
	bool b = checkFirstPieceAndBackBlock(c);
	bool a = false;
	bool c2 = false;
	if (c.matrix[LEFT][5] == BLUE && c.matrix[FRONT][3] == RED)
		a = true;
	if (c.matrix[LEFT][8] == BLUE && c.matrix[FRONT][6] == RED && c.matrix[DOWN][0] == WHITE)
		c2 = true;
	if (a == true && b == true && c2 == true)
		return true;
	return false;
}

bool configManager::checkFrontPiece(Cube c)
{
	if (c.matrix[FRONT][7] == RED && c.matrix[DOWN][1] == WHITE)
		return true;
	return false;
}

bool configManager::checkBackPiece(Cube c)
{
	if (c.matrix[BACK][7] == ORANGE && c.matrix[DOWN][7] == WHITE)
		return true;
	return false;
}

bool configManager::checkDoubleFirstPieceCross(Cube c)
{
	if (c.matrix[RIGHT][7] == GREEN && c.matrix[DOWN][5] == WHITE && checkFirstPiece(c))
		return true;
	return false;
}

list<string> configManager::getReverseSolution(vector<string> array, vector<int> counters, int max)
{
	list<string>	t;
	for (int i = 0; i < max; ++i)
		t.push_back(reverseMovementHashTable[array[counters[i]]]);
	return t;
}

bool increaseCounter(int startIndex, vector<int>*counters, int depthMax, int limit, int *currentDepth)
{
	if (startIndex == *currentDepth && *currentDepth <= depthMax)
	{
		*currentDepth += 1;
		return true;
	}
	//if (startIndex >= depthMax)
	//	return false;
	(*counters)[startIndex] = ((*counters)[startIndex] + 1) % limit;
	if (!(*counters)[startIndex])
		return increaseCounter(startIndex + 1, counters, depthMax, limit, currentDepth);

	return true;
}

bool isLoopPaused = false;
bool loopStopped = false;

void waitForUserInput()
{
	system ("/bin/stty raw");

	cout << "begin user input" << endl;
	int input = getchar();
	if (input == 'p')
	{
		isLoopPaused = isLoopPaused ? false : true;
		cout << "ROGRAM " << (isLoopPaused ? " PAUSED ..." : " IS UNPAUSED...") << endl;
	}
	if (input == 'x')
	{
		loopStopped = true;
		cout << "PROGRAM EXIT" << endl;
	}
	system ("/bin/stty cooked");

	cout << "end user input" << endl;
}

#define PRINT_RATIO 30000.f
void configManager::launchBruteForce(int maxDepth, list<nodeInfo> interestPieces, vector<string> tabMoves, string path)
{
	Cube 						c;
	int							movesSize = tabMoves.size();
	int							currentDepth = 0;
	int							c_depth = 0;
	vector<int>					counters = configManager::getCounterBruteForce(&currentDepth);
	int 						nbConfig = 0;

	unsigned long long 			counter = 0;
	bool 						run = true;
	unsigned long long  		totalIteration = pow(movesSize, maxDepth);

	while (run)
	{
		int counterMaxValue = 0;
		for (int i = 0; i < maxDepth; ++i)
		{
			if (counters[i] < movesSize - 1)
				break;
			else if (counters[i] == movesSize - 1)
				counterMaxValue++;
		}
		if (counterMaxValue == maxDepth)
			run = false;
	
		if (fmod(counter, PRINT_RATIO) == 0)
		{
			double tmp = (double)counter / (double)totalIteration * 100;
			cout << "[" << tmp << "] %    |     "; printTab(counters); cout << endl;
		}

		c.reinitialise();
		for (int j = currentDepth - 1; j >= 0; --j)
		{
			scrambler.applySpecificMove(&c, tabMoves[counters[j]]);
//			cout << tabMoves[counters[j]] << " "; cout << "    |    "; printTab(counters);
		}
		
		if (checkDoubleFirstPieceCross(c) && checkFrontPiece(c) && !checkBackPiece(c))
		{
	//		cout << "NEW CONFIG" << endl;
			list<string> algorithm = getReverseSolution(tabMoves, counters, currentDepth);
			tryCreateNewConfiguration(c, algorithm, path, interestPieces);
		}
		
		increaseCounter(0, &counters, maxDepth, movesSize, &currentDepth);
		counter += 1;	
	}
//	system ("/bin/stty cooked");

	cout << "[100] %" << endl;
	for (int i = 0; i < maxDepth; i++)
		cout << tabMoves[counters[i]] << " ";
	printTab(counters);
	cout << endl;
}
