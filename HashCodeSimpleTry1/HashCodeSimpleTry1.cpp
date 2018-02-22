// HashCodeSimpleTry1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>

#include "Pizza_.h"

using namespace std;


int main()
{
	int R, C, L, H;
	cin >> L >> H;
	vector<string> piz = { "TTTTT", "TMMMT", "TMMMT" ,"TMMMT", "TTTTT" };
	//vector<string> piz = { "TMTMTM", "TMTMTM" , "TMTMTM"};
	R = piz.size(), C = piz.at(0).size();
	Pizza yam(piz, L, H);
	yam.ShowPizza(cout);
	yam.Cut(Coord(0, 0));  // under improving
	yam.ShowSlices(cout);
	system("pause");
	return 0;
}

