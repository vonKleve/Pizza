#include "stdafx.h"
#include "Pizza_.h"

// checks coordinates :
//  1) whether they are in pizza rectangle
//  2) whether s - top-left and e - bottom-right vertices
bool Pizza::CheckCoordinates(const Coord & s, const Coord & e)
{
	const int R = pizza_.size(), C = pizza_.at(0).size();

	if (s.x < 0 || s.y < 0 || e.x < 0 || e.y < 0 ||
		s.x >= C || s.y >= R || e.x >= C || e.y >= R ||
		s.x > e.x || s.y > e.y)
	{
		return false;
	}

	return true;
}

// returns quantity of component and sets flag as true if contains at least 1 cell from any slice
unsigned int Pizza::CalculateComponent(const Coord & s, const Coord & e, Ingredient comp, bool &flag)
{
	unsigned int result = 0;
	pair<Ingredient, bool> *it;
	for (int i = s.y; i <= e.y; i++)
	{
		for (int j = s.x; j <= e.x; j++)
		{
			it = &pizza_.at(i).at(j);

			if ((*it).second)
			{
				flag = true;
			}

			if (comp == (*it).first)
			{
				result++;
			}
		}
	}
	return result;
}

// rectangle is defined with top-left coordinate (s) and bootom right coordinate (e)
// returns true if :
// rectangle contains 2 * L cells at min and H cells max,
// L cells with Mushrooms and L cells with Tomatoes
// and all cells must be "clear"(no slice contains any of the cells)
bool Pizza::CheckSlice(const Coord &s, const Coord &e)
{
	bool reached_cell = false;
	const int qT = CalculateComponent(s, e, Ingredient::Tomato, reached_cell),
		qM = CalculateComponent(s, e, Ingredient::Mushroom, reached_cell),
		qCells = (e.x + 1 - s.x) * (e.y + 1 - s.y);

	if (qCells < 2 * L_ || qCells > H_ || reached_cell || qT < L_ || qM < L_)
	{
		return false;
	}
	return true;
}

#include <iostream>
using std::cout;
// tries to cut rectangle(slice) with previous check
// 1 - adjust coords
// 2 - check location of the coords and whether they form a rectangle
// 3 - check slice
// 4 - if passed 3 - mark every cell
// 5 - return true if succeeded
bool Pizza::TryCutSlice(const Coord & as, const Coord & ae)
{
	Coord s = as, e = ae;

	e.x = e.x < pizza_.at(0).size() ? e.x : (pizza_.at(0).size() - 1);
	e.y = e.y < pizza_.size() ? e.y : (pizza_.size() - 1);

	if (!CheckCoordinates(s, e))
	{
		return false;
	}

	bool flag = CheckSlice(s, e);
	if (flag)
	{
		for (int i = s.y; i <= e.y; i++)
		{
			for (int j = s.x; j <= e.x; j++)
			{
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
void Pizza::Cut(Coord st)
{
	int R = pizza_.size(), C = pizza_.at(0).size();
	int local_h = H_, k = 1, factoriz_index = 0;
	Coord s(0, 0), e(0, 0);
	queue<Coord> starts;
	vector<int> H_factoriz = MNumber(H_).GetDecomposition();

	starts.push(Coord(st.x, st.y));

	int count1 = 0, count2 = 0;
	while (!starts.empty())
	{
		local_h = H_;
		s = starts.front();
		factoriz_index = 0;
		
		starts.pop();

		bool cut_flag = false;
		while (local_h != 1 && !cut_flag)
		{
			k = H_factoriz.at(factoriz_index);

			local_h /= k;
			e.x = s.x + local_h - 1;
			e.y = s.y + k - 1;

			cut_flag = TryCutSlice(s, e);
			if (!cut_flag)
			{
				std::swap(e.x, e.y);
				cut_flag = TryCutSlice(s, e);
				std::swap(e.x, e.y);
			}
			factoriz_index++;
		}

		if (local_h == 1 && !cut_flag)
		{
			if(s.x + 1 < C && !pizza_.at(s.y).at(s.x + 1).second)
				starts.push(Coord(s.x + 1, s.y));
			if (s.y + 1 < R && !pizza_.at(s.y  + 1).at(s.x).second)
				starts.push(Coord(s.x, s.y + 1));
		}
		else
		{
			if (e.y + 1 < R && !pizza_.at(s.x).at(e.y + 1).second)
			{
				starts.push(Coord(s.x, e.y + 1));
			}
			if (e.x + 1 < C && !pizza_.at(e.x + 1).at(s.y).second)
			{
				starts.push(Coord(e.x + 1, s.y));
			}
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
		out << slice.first.ToString() << "\t" << slice.second.ToString() << "\n";
	}
}
