#include "stdafx.h"
#include "Pizza_.h"


bool Pizza::CheckCoordinates(const Coord s, const Coord e)
{
	const int R = pizza_.size(), C = pizza_.at(0).size();

	//check whether s and e are within pizza rectangle
	if (s.x < 0 || s.y < 0 || e.x < 0 || e.y < 0 ||
		s.x >= C || s.y >= R )
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

unsigned int Pizza::CalculateComponent(const Coord & s, const Coord & e, Ingredient comp, bool &flag)
{
	unsigned int result = 0;
	pair<Ingredient, bool> *it;
	for (int i = s.y; i <= e.y; i++)
	{
		for (int j = s.x; j <= e.x; j++)
		{
			it = &pizza_.at(i).at(j);

			// if reached slice - set flag
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
#include <iostream>
using std::cout;
bool Pizza::CheckRectangle(const Coord &s, const Coord &e)
{
	bool flag = false, reached_cell = false;
	int qT = 0, qM = 0;
	int qCells;
	const int R = pizza_.size(), C = pizza_.at(0).size();

	if (!CheckCoordinates(s, e))
	{
		return flag;
	}

	qCells = (e.x + 1 - s.x) * (e.y + 1 - s.y);
	// check quantity of cells
	if (qCells < 2 * L_ || qCells > H_)
	{
		return flag;
	}

	qT = CalculateComponent(s, e, Ingredient::Tomato, reached_cell);
	qM = CalculateComponent(s, e, Ingredient::Mushroom, reached_cell);

	if (reached_cell)
	{
		return flag;
	}

	// if quantity of Mushrooms and Tomatoes is more than enough
	if (qT >= L_ && qM >= L_)
	{
		flag = true;
	}
	return flag;
}

// tries to cut rectangle(slice) with previous check
bool Pizza::TryCutSlice(Coord &s, Coord &e)
{
	// adjust end coordinates
	e.x = e.x < pizza_.at(0).size() ? e.x : (pizza_.at(0).size() - 1);
	e.y = e.y < pizza_.size() ? e.y : (pizza_.size() - 1);

	bool flag = CheckRectangle(s, e);
	if (flag)
	{
		for (int i = s.y; i <= e.y && i < pizza_.size(); i++)
		{
			for (int j = s.x; j != e.x && j < pizza_.at(0).size(); j++)
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
	int local_h = H_, k = 1;
	Coord s(0, 0), e(0, 0);
	queue<Coord> starts;
	vector<int> H_factoriz = MNumber(H_).GetDecomposition();

	starts.push(Coord(st.x, st.y));

	while (!starts.empty())
	{
		local_h = H_;
		s = starts.front();
		factoriz_index = 0;

		starts.pop();

		bool cut_flag = false;
		while (k <= local_h && !cut_flag)
		{
			k = H_factoriz.at(factoriz_index);

			local_h /= k;
			e.x = s.x + local_h - 1;
			e.y = s.y + k - 1;

			cut_flag = TryCutSlice(s, e);
			factoriz_index++;
		}
		if (k >= local_h && !cut_flag)
		{
			// ??
		}

		if (CheckCoordinates(Coord(s.x, e.y + 1), Coord(s.x + H_ - 1, e.y + 1)))
		{
			starts.push(Coord(s.x, e.y + 1));
		}
		if (CheckCoordinates(Coord(e.x + 1, s.y), Coord(e.x + H_, s.y)))
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
		out << slice.first.ToString() << "\t" << slice.second.ToString() << "\n";
	}
}
