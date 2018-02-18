#pragma once

#include <vector>
#include <utility>

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
	bool check(Coord s, Coord e);
public:
	Pizza(vector<vector<pair<Ingredient, bool>>> ipizza) : pizza_(ipizza) {};
	~Pizza() {};

	void cut(int k);
private:

	vector<vector<pair<Ingredient, bool>>>pizza_;
	vector<pair<int, int>> slices_;
	int L_, H_;
};

