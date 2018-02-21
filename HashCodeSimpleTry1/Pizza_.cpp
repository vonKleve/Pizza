#include "stdafx.h"
#include "Pizza_.h"


bool Pizza::CheckCoordinates(const Coord s, const Coord e)
{
	const int R = pizza_.size(), C = pizza_.at(0).size();

	//check whether s and e are within pizza rectangle
	if (s.x < 0 || s.y < 0 || e.x < 0 || e.y < 0 ||
		s.x >= C || s.y >= R || e.x >= C || e.y >= R)
	{
		return false;
	}

	//check whether s is really left-top point
	if (s.x > e.x || s.y > e.y)
	{
		return false;
	}

	return true;
}

// rectangle is defined with top-left coordinate (s) and bootom right coordinate (e)
// returns true if :
// rectangle contains 2 * L cells at min and H cells max,
// L cells with Mushrooms and L cells with Tomatoes
// and all cells must be "clear"(no slice contains any of the cells)
#include <iostream>
using std::cout;
bool Pizza::CheckRectangle(const Coord &s, const Coord &e)
{
	bool flag = false;
	int qT = 0, qM = 0;
	int qCells = (e.x + 1 - s.x) * (e.y + 1 - s.y);
	const pair<Ingredient, bool> *it;
	const int R = pizza_.size(), C = pizza_.at(0).size();

	if (!CheckCoordinates(s, e))
	{
		return flag;
	}

	// check quantity of cells
	if (qCells < 2 * L_ || qCells > H_)
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
bool Pizza::TryCutSlice(const Coord &s, const Coord &e)
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

// Simple try ^_^
// zero step is to cut H so it is an even number
// firstly try to cut horizontal rectangle k x H / k
// if attempt fails - increase k
// if k reaches value greater than H - ??(means that all previous attempts failed)
// if attempt succeeds - cut new slices below and on the right side
void Pizza::Cut(int factoriz_index, Coord st)
{
	int R = pizza_.size(), C = pizza_.at(0).size();
	int local_h = H_;
	Coord s(0, 0), e(0, 0);
	queue<Coord> starts;
	vector<int> H_factoriz = MNumber(H_).GetDecomposition();

	starts.push(Coord(st.x, st.y));

	if (H_ % 2 != 0)
	{
		local_h = H_ - 1;
	}

	while (!starts.empty())
	{
		local_h = H_;
		s = starts.front();
		factoriz_index = 0;

		starts.pop();

		bool cut_flag = false;
		while (factoriz_index <= local_h && !cut_flag)
		{
			int k = H_factoriz.at(factoriz_index);

			local_h /= k;
			e.x = s.x + local_h - 1;
			e.y = s.y + k - 1;

			cut_flag = TryCutSlice(s, e);
			factoriz_index++;
		}
		if (factoriz_index >= local_h && !cut_flag)
		{
			// ??
		}

		if (CheckCoordinates(Coord(s.x, e.y + 1), Coord(s.x + H_ - 1, e.y + 1)))
		{
			starts.push(Coord(s.x, e.y + 1));
		}
		if (CheckCoordinates(Coord(e.x + H_, s.y), Coord(e.x + H_, s.y)))
		{
			starts.push(Coord(e.x + 1, s.y));
		}
	}
}

void Pizza::ShowPizza(std::ostream & out)
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

void Pizza::ShowSlices(std::ostream & out)
{
	for (auto slice : slices_)
	{
		out << slice.first.x << " " << slice.second.y << "\t" << slice.second.x << " " << slice.second.y << "\n";
	}
}
