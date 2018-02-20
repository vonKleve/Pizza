#include "stdafx.h"
#include "Pizza_.h"

// rectangle is defined with top-left coordinate (s) and bootom right coordinate (e)
// returns true if :
// rectangle contains 2 * L cells at min and H cells max,
// L cells with Mushrooms and L cells with Tomatoes
// and all cells must be "clear"(no slice contains any of the cells)
bool Pizza::CheckRectangle(const Coord &s, const Coord &e)
{
	bool flag = false;
	int qT = 0, qM = 0;
	int qCells = (e.x - s.x) * (e.y - s.y);
	const pair<Ingredient, bool> *it;

	// check quantity of cells
	if (qCells <= 2 * L_ || qCells >= H_)
	{
		return flag;
	}
	// check every cell and calc qT and qM
	for (int i = s.y; i <= e.y && i <= pizza_.size(); i++)
	{
		for (int j = s.x; j != e.x && j <= pizza_.at(0).size(); j++)
		{
			it = &pizza_.at(i).at(j);
			// if reached slice then return false
			if ((*it).second)
			{
				return flag;
			}
			// depending on the Ingredient increase qT or qM
			switch ((*it).first)
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

	// if quantity of Mushrooms and Tomatoes is more than enough
	if (qT >= L_ && qM >= L_)
	{
		flag = true;
	}
	return flag;
}

// tries to cut rectangle(slice) with previous check
bool Pizza::CutSlice(const Coord &s, const Coord &e)
{
	bool flag = CheckRectangle(s, e);
	if (flag)
	{
		for (int i = s.y; i <= e.y && i <= pizza_.size(); i++)
		{
			for (int j = s.x; j != e.x && j <= pizza_.at(0).size(); j++)
			{
				// mark every cell in rectangle
				pizza_.at(i).at(j).second = true;
			}
		}
		slices_.push_back(pair<Coord, Coord>(s, e));
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

void Pizza::show(std::ostream & out)
{
	for (auto line : pizza_)
	{
		for (auto cell : line)
		{
			switch (cell.first)
			{
			case(Ingredient::Mushroom):
				out << "M" << " ";
				break;
			case(Ingredient::Tomato):
				out << "T" << " ";
				break;
			}
		}
		out << "\n";
	}
}
