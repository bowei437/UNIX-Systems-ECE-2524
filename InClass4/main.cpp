#include "Game.h"
#include <iostream>
#include <fstream>

using std::ifstream;
using std::cin;
using std::cout;
using std::string;

int main(int argc, char *argv[])
{
	string p1, p2;
	p1 = argv[1];
	p2 = argv[2];
	Game g;
	ifstream in1( p1.c_str() );
	ifstream in2( p2.c_str() );
	g.playGame( in1, in2, cout );
	in1.close();
	in2.close();
	return 0;
}
