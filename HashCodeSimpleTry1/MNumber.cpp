#include "stdafx.h"
#include "MNumber.h"


void MNumber::SetDecomposition()
{
	int local_number = number_;

	decomposition_.push_back(1);
	while (local_number % 2 == 0)
	{
		local_number /= 2;
		decomposition_.push_back(2);
	}

	for (int i = 3; i <= sqrt(local_number); i = i + 2)
	{
		while (local_number % i == 0)
		{
			decomposition_.push_back(i);
			local_number = local_number / i;
		}
	}

	if (local_number > 2)
	{
		decomposition_.push_back(local_number);
	}
}

bool MNumber::CheckDecomposition()
{
	bool flag = false;
	int answer = 1;
	for (auto it : decomposition_)
	{
		answer *= it;
	}
	if (answer == number_)
	{
		flag = true;
	}
	return flag;
}

vector<int> MNumber::GetDecomposition()
{
	return decomposition_;
}
