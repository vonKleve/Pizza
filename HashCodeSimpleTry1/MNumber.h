#pragma once

#include <vector>
#include <bitset>
#include <exception>

using std::vector;
using std::bitset;

class MNumber
{
	void SetDecomposition();
	bool CheckDecomposition();
public:
	MNumber(int inum) : number_(inum) { SetDecomposition(); };
	MNumber(int inum, vector<int> idecomp) : number_(inum), decomposition_(idecomp) { if (!CheckDecomposition()) { throw std::logic_error("Invalid decomposition or number!"); } };
	MNumber(vector<int> idecomp) : decomposition_(idecomp), number_(1) { for (auto it : decomposition_) { number_ *= it; }};
	~MNumber() {};

	vector<int> GetDecomposition();
private:
	vector<int> decomposition_;
	int number_;
};

