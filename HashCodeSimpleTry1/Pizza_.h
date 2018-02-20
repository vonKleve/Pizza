#pragma once

#include <vector>
#include <utility>
#include <ostream>

using std::vector;
using std::pair;

enum Ingredient { Tomato, Mushroom };

struct Coord 
{
	int x, y;
	Coord(int ix, int iy) : x(ix), y(iy) {};
};

class Pizza
{
	bool CheckRectangle(const Coord &s, const Coord &e);
	bool CutSlice(const Coord &s, const Coord &e);
public:
	Pizza(vector<vector<pair<Ingredient, bool>>> ipizza, int iL, int iH) : pizza_(ipizza), L_(iL), H_(iH) {};
	~Pizza() {};

	void cut(int k);
	void show(std::ostream &out);
private:

	vector<vector<pair<Ingredient, bool>>>pizza_;
	vector<pair<Coord, Coord>> slices_;
	int L_, H_;
};

