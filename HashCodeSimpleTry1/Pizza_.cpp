#include "stdafx.h"
#include "Pizza_.h"

bool Pizza::check(Coord s, Coord e)
{
	bool flag = false;
	int qT = 0, qM = 0;
	for (int i = s.y; i <= e.y && i <= pizza_.size(); i++)
	{
		for (int j = s.x; j != e.x && j <= pizza_.at(0).size(); j++)
		{
			pair<Ingredient, bool> it = pizza_.at(i).at(j);
			// if reached slice then return false
			if (it.second)
			{
				return false;
			}
			// depending on the INgredient increase qT or qM
			switch (it.first)
			{
			case(Ingredient::Mushroom):
				qM++;
				break;
			case(Ingredient::Tomato):
				qT++;
				break;
			}
		}
	}

	if (qT < L_ && qM < L_)
	{
		flag = true;
	}
	return flag;
}

void Pizza::cut(int k)
{
	int R = pizza_.size(), C = pizza_.at(0).size();
	if (R < H_ || C < H_)
	{
		// k++ ?
	}
	int sY = 0, sX = 0;
	// try to cut slice as k x H/k
	
}
