#include "../includes/cubePrinter.hpp"
#include "../includes/define.hpp"

cubePrinter::cubePrinter() : keyString("\033[")
{

	fgColorCode["BLACK"] = 30;
	fgColorCode["RED"] = 31;
	fgColorCode["GREEN"] = 32;
	fgColorCode["YELLOW"] = 33;
	fgColorCode["BLUE"] = 34;
	fgColorCode["MAGENTA"] = 35;
	fgColorCode["CYAN"] = 36;
	fgColorCode["WHITE"] = 37;


	bgColorCode["BLACK"] = 40;
	bgColorCode["RED"] = 41;
	bgColorCode["GREEN"] = 42;
	bgColorCode["YELLOW"] = 43;
	bgColorCode["BLUE"] = 44;
	bgColorCode["MAGENTA"] = 45;
	bgColorCode["CYAN"] = 46;
	bgColorCode["WHITE"] = 47;


	valueToKey[RED] = "RED";
	valueToKey[GREEN] = "GREEN";
	valueToKey[MAGENTA] = "MAGENTA";
	valueToKey[BLUE] = "BLUE";
	valueToKey[YELLOW] = "YELLOW";
	valueToKey[WHITE] = "WHITE";
	valueToKey[BLACK] = "BLACK";
}

cubePrinter::~cubePrinter() {}

void cubePrinter::switchTextColor(int c)
{
	cout << keyString << fgColorCode[valueToKey[c]] << "m";
}

void cubePrinter::switchBackGroundColor(int v)
{
	cout << keyString << bgColorCode[valueToKey[v]] << "m";

}

void cubePrinter::switchColor(int v)
{
	cubePrinter::switchTextColor(v);
	cubePrinter::switchBackGroundColor(v);
}

void cubePrinter::switchToNormal()
{
	cubePrinter::switchTextColor(WHITE);
	cout << keyString << "0m";
//	cubePrinter::switchBackGroundColor(DEFAUT);
}




