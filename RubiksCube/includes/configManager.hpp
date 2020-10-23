#ifndef CONFIG_MANAGER_HPP
#define CONFIG_MANAGER_HPP

#include	"./cube.hpp"
#include	"./cubeScrambler.hpp"
#include	"./nodeInfo.hpp"
#include	<vector>
#include	<iostream>
#include	<map>
#include	<list>
#include	<fstream>
#include	<unistd.h>
#include 	<cmath>
#include 	<stdio.h>


using namespace std;


class configManager
{
public:
	configManager();
	~configManager();

	string									cubeToConfiguration(Cube c, list<nodeInfo> l);
	int										getListMoveWeight(list<string> l);
	void									createConfig(string config, list<string> moves, string path);
	list<string>							getResolution(Cube c, string path, list<nodeInfo> interestPieces);
	bool									tryCreateNewConfiguration(Cube c, list<string> l, string s, list<nodeInfo> interestPieces);
	void									launchBruteForce(int depth, list<nodeInfo> interestPieces, vector<string> tabMoves, string path);
	vector<int>								getCounterBruteForce(int *depth);
	list<string>							getReverseSolution(vector<string> moves, vector<int> counters, int max);

	// function analysis
	bool									checkFirstPiece(Cube c);
	bool 									checkFirstPieceAndBackBlock(Cube c);
	bool 									checkFirstBlockRoux(Cube c);
	bool 									checkDoubleFirstPieceCross(Cube c);
	bool 									checkFrontPiece(Cube c);
	bool 									checkBackPiece(Cube c);

	list<nodeInfo>							stringToNodeInfoList(string b);
// setup Functions
	void									initialiseNodeTree();

	vector<string>							keys = {"R", "G", "O", "B", "Y", "W"};
	vector<string>							moves = {"R", "L", "U", "D", "F", "B", "M", "R2", "L2", "U2", "D2", "F2", "B2", "M2", "R'", "L'", "U'", "D'", "F'", "B'", "M'", "r", "r'", "r2", "l", "l'", "l2"};

	vector<string>							doublePieceCrossMoves = {"R", "L", "U", "D", "F", "B", "R2", "L2", "U2", "D2", "F2", "B2", "R'", "L'", "U'", "D'", "F'", "B'"};


	map<string, int>						weights;
	string									extension = ".txt";
	string									pathIndexes = "./files/initialisationFiles/indexBruteForce.txt";
	string									pathNodeTree = "./files/initialisationFiles/nodeTreeSetup.txt";
	cubeScrambler							scrambler;
	map<string, string>						reverseMovementHashTable;

	map<int, string>						valueToMatrix;
	map<string, int>						matrixToValue;
	map<int, map<int, list<nodeInfo>>>		nodeTree;

};


#endif
