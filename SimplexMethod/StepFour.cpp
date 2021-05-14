#include "StepFour.h"

double StepFour::getTheta(const std::vector<double>& x,
						  const Matrix& z,
						  const std::set<int>& Jb,
						  int& s,
						  int& js)
{
	std::vector<double> thetaVec;
	std::vector<int> jsVec;
	std::vector<int> sVec;
	int i = 0;
    int additional = 0; // if z[i][0] <= 0
	for (int j : Jb)
	{
        if (z[i][0] > 0) {
            thetaVec.push_back(x[j] / z[i][0]);
            jsVec.push_back(j);
            sVec.push_back(i + additional);
        } else {
            additional++;
        }
		i++;
	}
	std::vector<double>::iterator result = std::min_element(thetaVec.begin(), thetaVec.end());
	int sIndex = std::distance(thetaVec.begin(), result); // it is index of minimum teta
    s = sVec[sIndex];
	js = jsVec[sIndex];
    /*std::cout << thetaVec << std::endl;
    std::cout << s << std::endl;
    std::cout << js << std::endl;*/
	return thetaVec[sIndex]; // minimum teta
}
