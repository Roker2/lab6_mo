#include "StepFive.h"

void StepFive::buildNewX(double theta,
						 int j0,
						 int js,
						 const Matrix& z,
						 const std::set<int>& Jn,
						 std::vector<double>& x,
						 std::set<int>& Jb)
{
	for (const auto j : Jn)
		x[j] = 0.0;
	x[j0] = theta;
	int i = 0;
	for (const auto ji : Jb)
	{
		x[ji] -= theta * z[i][0];
		i++;
	}
	Jb.erase(js);
	Jb.emplace(j0);
}
