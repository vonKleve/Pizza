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
	cin >> R >> C >> L >> H;
	vector<string> piz = { "TMTMTM", "TMTMTM", "TMTMTM" };
	Pizza yam(piz, L, H);
	yam.ShowPizza(cout);
//	yam.Cut(1, Coord(0, 0));  // under improving
	yam.ShowPizza(cout);
	yam.ShowSlices(cout);
	system("pause");
	return 0;
}

