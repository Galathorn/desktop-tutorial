#ifndef CUBE_PRINTER_HPP
#define CUBE_PRINTER_HPP

#include <map>
#include <iostream>

using namespace std;

class cubePrinter
{
public:
	cubePrinter();
	~cubePrinter();


	void switchTextColor(int v);
	void switchColor(int v);
	void switchBackGroundColor(int v);
	void switchToNormal();


	map<string, int> fgColorCode;
	map<string, int> bgColorCode;
	map<int, string> valueToKey;

	string keyString;


};


#endif
