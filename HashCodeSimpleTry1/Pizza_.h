#pragma once

#include <vector>
#include <utility>
#include <ostream>
#include <queue>
#include <string>
#include "MNumber.h"

using std::vector;
using std::pair;
using std::queue;

enum Ingredient { Tomato, Mushroom };

struct Coord 
{
	int x, y;
	Coord(int ix, int iy) : x(ix), y(iy) {};
	std::string ToString()
	{
		return std::to_string(x) + " " + std::to_string(y);
	}
};

class Pizza
{
	bool CheckCoordinates(const Coord & s, const Coord & e);
	bool CheckRectangle(const Coord &s, const Coord &e);
	bool TryCutSlice(Coord &s, Coord &e);
	unsigned int CalculateComponent(const Coord &s, const Coord &e, Ingredient comp, bool &flag);

public:
	Pizza(vector<vector<pair<Ingredient, bool>>> ipizza, int iL, int iH) : pizza_(ipizza), L_(iL), H_(iH) {};
	Pizza(vector<std::string> ipizza, int iL, int iH) : L_(iL), H_(iH) 
	{
		int i = 0;
		pizza_.resize(ipizza.size());
		for (auto line : ipizza)
		{
			for (auto cell : line)
			{
				Ingredient ingr;
				switch (cell)
				{
				case 'T':
					ingr = Ingredient::Tomato;
					break;
				case 't':
					ingr = Ingredient::Tomato;
					break;
				case 'M':
					ingr = Ingredient::Mushroom;
					break;
				case 'm':
					ingr = Ingredient::Mushroom;
					break;
				default:
					break;
				}
				pizza_.at(i).push_back(pair<Ingredient, bool>(ingr, false));
			}
			i++;
		}
	};
	~Pizza() {};

	void Cut(int k, Coord st);
	void ShowPizza(std::ostream &out);
	void ShowSlices(std::ostream &out);
private:

	vector<vector<pair<Ingredient, bool>>>pizza_;
	vector<pair<Coord, Coord>> slices_;
	int L_, H_;
};

