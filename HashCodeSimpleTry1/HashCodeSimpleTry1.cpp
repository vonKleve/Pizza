// HashCodeSimpleTry1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>

#include "Pizza_.h"

using namespace std;


int main()
{
	vector<vector<pair<Ingredient, bool>>> piz(3);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			char c;
			cin >> c;
			pair<Ingredient, bool> pr;
			switch (c)
			{
			case 'T':
				pr = pair<Ingredient, bool>(Ingredient::Tomato, false);
				break;
			case 'M':
				pr = pair<Ingredient, bool>(Ingredient::Mushroom, false);
				break;
			}
			piz[i].push_back(pr);
		}
	}
	Pizza yam(piz, 1, 3);
	yam.show(cout);
	system("pause");
	return 0;
}

